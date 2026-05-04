#define _XOPEN_SOURCE_EXTENDED 1

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <unistd.h> 
#include <ncurses.h>  

typedef struct SOblect {
    float x, y;
    float width, height;
    float vertSpeed;
    bool IsFly;
} TObject;

#define mapWidth 80
#define mapHeight 25

char map[mapHeight][mapWidth + 1];
TObject mario;
TObject *brick = NULL;
int brickLength;

void ClearMap()
{
    for (int i = 0; i < mapWidth; i ++)
        map[0][i] = '.';
    map[0][mapWidth] = '\0';
    for ( int j = 1; j < mapHeight; j++)
        snprintf(map[j], mapWidth + 1, "%s", map[0]);
}

void ShowMap()
{
    for (int j = 0; j < mapHeight; j++)
        mvprintw(j, 0, "%s", map[j]);  
    refresh();  // Обновляет экран ncurses для отображения изменений
}

void SetObjectPos( TObject *obj, float xPos, float yPos){
    (*obj).x = xPos;
    (*obj).y = yPos;
}

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight){
    SetObjectPos(obj, xPos, yPos);
    (*obj).width = oWidth;
    (*obj).height = oHeight;
    (*obj).vertSpeed = 0;
    (*obj).IsFly = false;  
}

bool IsCollision(TObject o1, TObject o2);

void VertMoveObject(TObject *obj)
{
    (*obj).IsFly = true;
    (*obj).vertSpeed +=0.05;
    SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);

    for (int i = 0; i < brickLength; i++)

        if ( IsCollision ( *obj, brick[i]))
        {
            (*obj).y -= (*obj).vertSpeed;
            (*obj).vertSpeed = 0;
            (*obj).IsFly = false;
            break;
        }
}


bool IsPosInMap(int x, int y){
    return ( ( x >= 0) && ( x < mapWidth) && ( y>= 0) && ( y < mapHeight));
}

void PutObjectOmMap(TObject obj)
{
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < ix + iWidth; i++)
        for (int j = iy; j < iy + iHeight; j++)
            if (IsPosInMap( i, j))
                map[j][i] = '@';
}

void HorizonMoveMap( float dx)
{
    for (int i = 0; i < brickLength; i++)
        brick[i].x +=dx;
}

bool IsCollision(TObject o1, TObject o2){
    return (o1.x + o1.width > o2.x) && (o1.x < ( o2.x + o2.width)) &&
           ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height)); 
}

void CreateLevel(){
    InitObject(&mario, 39, 10, 3 ,3);

    brickLength = 5;
    brick = new TObject[brickLength];
    InitObject(brick + 0, 20, 20, 40, 5);
    InitObject(brick + 1, 60, 15, 10, 10);
    InitObject(brick + 2, 80, 20, 20, 5);
    InitObject(brick + 3, 120, 15, 10, 10);
    InitObject(brick + 4, 150, 20, 40, 5);


}

int main()
{   
    setlocale(LC_ALL, "");
    initscr();  // Инициализирует ncurses библиотеку
    cbreak();  // Включает посимвольный ввод без ожидания Enter
    noecho();  // Отключает отображение введённых символов на экран
    nodelay(stdscr, TRUE);  // Делает getch() неблокирующим (не ждёт ввода)
    keypad(stdscr, TRUE);  // Включает обработку специальных клавиш (стрелки, функции)
    
    CreateLevel();
    
    int moveDirection = 0;
    int moveFrames = 0;
    bool jumpRequested = false;

    do
    {
        wint_t ch = 0;
        bool shouldExit = false;

        while (get_wch(&ch) != ERR)
        {
            if (ch == 27)  // 27 = ESC для выхода
            {
                shouldExit = true;
                break;
            }

            if (ch == L' ')
                jumpRequested = true;
            if (ch == L'a' || ch == L'A' || ch == L'ф' || ch == L'Ф' || ch == KEY_LEFT)
            {
                moveDirection = 1;
                moveFrames = 24;
            }
            if (ch == L'd' || ch == L'D' || ch == L'в' || ch == L'В' || ch == KEY_RIGHT)
            {
                moveDirection = -1;
                moveFrames = 24;
            }
        }

        if (shouldExit)
            break;

        if (jumpRequested && mario.IsFly == false)
            mario.vertSpeed = -1;
        jumpRequested = false;

        if (moveFrames > 0)
        {
            HorizonMoveMap((float)moveDirection * 0.7f);
            moveFrames--;
        }

        clear();  // Очищает экран
        ClearMap();
        
        VertMoveObject(&mario);  // Обновление физики
        for (int i = 0; i < brickLength; i++)
            PutObjectOmMap(brick[i]);
        PutObjectOmMap(mario);
        ShowMap();
        usleep(10000);  // Задержка 10 мс
        
    } while (true);
    
    delete[] brick;
    endwin();  // Завершает работу ncurses, восстанавливает исходное состояние консоли
    return 0;
}
