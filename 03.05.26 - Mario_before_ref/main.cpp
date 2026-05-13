// Нужен для расширенных возможностей ncurses, включая wide-char ввод через get_wch().
#define _XOPEN_SOURCE_EXTENDED 1

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>   // Нужен для setlocale(), чтобы корректно работала кириллица в терминале.
#include <wchar.h>    // Нужен для wide-символов и wint_t, которые использует get_wch().
#include <unistd.h>   // usleep() используется для небольшой задержки между кадрами.
#include <ncurses.h>  

typedef struct SOblect {
    float x, y;
    float width, height;
    float vertSpeed;
    bool IsFly;
    char cType;
} TObject;

#define mapWidth 80
#define mapHeight 25

char map[mapHeight][mapWidth + 1];
TObject mario;
TObject *brick = NULL;
int brickLength;
int level = 1;

void ClearMap()
{
    for (int i = 0; i < mapWidth; i ++)
        map[0][i] = ' ';
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
    obj->x = xPos;
    obj->y = yPos;
}

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType){
    SetObjectPos(obj, xPos, yPos);
    obj->width = oWidth;
    obj->height = oHeight;
    obj->vertSpeed = 0;
    obj->IsFly = false;  
    obj->cType = inType;
}

bool IsCollision(TObject o1, TObject o2);

void CreateLevel(int lvl);

void VertMoveObject(TObject *obj)
{
    obj->IsFly = true;
    obj->vertSpeed +=0.06; // немного сильнее гравитация — чуть быстрее вертикальное движение
    SetObjectPos(obj, obj->x, obj->y + obj->vertSpeed);

    for (int i = 0; i < brickLength; i++)

        if ( IsCollision ( *obj, brick[i]))
        {
            obj->y -= obj->vertSpeed;
            obj->vertSpeed = 0;
            obj->IsFly = false;

            if (brick[i].cType == '+'){
                level++;
                if (level > 2) level = 1;

                CreateLevel(level);
                usleep(10000);
            }
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
                map[j][i] = obj.cType;
}

void HorizonMoveMap( float dx)
{
    // Проверяем столкновение, не меняя положение mario на самом деле.
    TObject test = mario;
    test.x -= dx;
    for (int i = 0; i < brickLength; i++)
        if ( IsCollision(test, brick[i]) ){
            return;
        }

    // Если столкновений нет — сдвигаем мир (кирпичи).
    for (int i = 0; i < brickLength; i++)
        brick[i].x += dx;
          
}

bool IsCollision(TObject o1, TObject o2){
    return (o1.x + o1.width > o2.x) && (o1.x < ( o2.x + o2.width)) &&
           ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height)); 
}

void CreateLevel(int lvl){
    InitObject(&mario, 39, 10, 3 ,3, '@');

    if (lvl == 1){
        brickLength = 6;
        delete[] brick; 
        brick = new TObject[brickLength];
        // el, xpos, ypos, oWidth, oHeight, type
        InitObject(brick + 0, 20, 20, 40, 5, '#');
        InitObject(brick + 1, 60, 15, 10, 10, '#');
        InitObject(brick + 2, 80, 20, 20, 5, '#');
        InitObject(brick + 3, 105, 15, 10, 10, '#');
        InitObject(brick + 4, 120, 20, 40, 5, '#');
        InitObject(brick + 5, 165, 15, 10, 10, '+' );
    }

    if (lvl == 2){
        brickLength = 6;
        delete[] brick; 
        brick = new TObject[brickLength];
        //(0, 0) - левый верхний угол 
        // el, xpos, ypos, oWidth, oHeight, type
        InitObject(brick + 0, 10, 20, 60, 5, '#');
        InitObject(brick + 1, 75, 16, 12, 2, '#');
        InitObject(brick + 2, 95, 13, 12, 2, '#');
        InitObject(brick + 3, 115, 10, 12, 2, '#');
        InitObject(brick + 4, 135, 15, 14, 2, '#');
        InitObject(brick + 5, 152, 12, 10, 2, '+' );
    }

}

int main()
{   
    setlocale(LC_ALL, "");

    initscr();  // Инициализирует ncurses библиотеку
    cbreak();  // Включает посимвольный ввод без ожидания Enter
    noecho();  // Отключает отображение введённых символов на экран

    nodelay(stdscr, TRUE);  // Делает getch() неблокирующим (не ждёт ввода)
    keypad(stdscr, TRUE);  // Включает обработку специальных клавиш (стрелки, функции)
    
    CreateLevel(level);
    
    // Направление движения по горизонтали: 1 - влево, -1 - вправо, 0 - стоим.
    // Горизонтальная скорость (используется и для скроллинга карты)
    const float H_SPEED = 0.3f; // чуть быстрее
    int moveDirection = 0;
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

            // Прыжок
            if (ch == L' ')
                jumpRequested = true;

            // A / стрелка влево / русская 'ф'  влево.
            if (ch == L'a' || ch == L'A' || ch == L'ф' || ch == L'Ф' || ch == KEY_LEFT)
            {
                if (moveDirection == -1)
                    moveDirection = 0;
                else if (moveDirection == 0)
                    moveDirection = 1;
            }

            // D / стрелка вправо / русская 'в' вправо.
            if (ch == L'd' || ch == L'D' || ch == L'в' || ch == L'В' || ch == KEY_RIGHT)
            {
                if (moveDirection == 1)
                    moveDirection = 0;
                else if (moveDirection == 0)
                    moveDirection = -1;
            }
        }

        // Если Mario упал ниже карты, пересоздаём уровень 
        if (mario.y > mapHeight) CreateLevel(level);

        if (shouldExit)
            break;

        if (jumpRequested && mario.IsFly == false )
            mario.vertSpeed = -1.1f; // чуть более энергичный старт прыжка

        jumpRequested = false;

        if (moveDirection != 0)
        {

            HorizonMoveMap((float)moveDirection * H_SPEED);
        }

        clear(); 
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
