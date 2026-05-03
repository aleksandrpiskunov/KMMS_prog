#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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
TObject brick[1];

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
    (*obj).IsFly = false;  // Инициализация флага полёта
}

bool IsCollision(TObject o1, TObject o2);

void VertMoveObject(TObject *obj)
{
    (*obj).IsFly = true;
    (*obj).vertSpeed +=0.05;
    SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);
    if ( IsCollision ( *obj, brick[0]))
    {
        (*obj).y -= (*obj).vertSpeed;
        (*obj).vertSpeed = 0;
        (*obj).IsFly = false;
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
    brick[0].x += dx;
}

bool IsCollision(TObject o1, TObject o2){
    return (o1.x + o1.width > o2.x) && (o1.x < ( o2.x + o2.width)) &&
           ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height)); 
}

int main()
{   
    initscr();  // Инициализирует ncurses библиотеку
    noecho();  // Отключает отображение введённых символов на экран
    nodelay(stdscr, TRUE);  // Делает getch() неблокирующим (не ждёт ввода)
    keypad(stdscr, TRUE);  // Включает обработку специальных клавиш (стрелки, функции)
    
    InitObject(&mario, 39, 10, 3, 3);
    InitObject(brick, 20, 20, 40, 5);
    
    int ch = 0;  // Получение кода нажатой клавиши
    do
    {
        clear();  // Очищает экран
        ClearMap();

        if (ch == ' ' && mario.IsFly == false) mario.vertSpeed = -1;  // Пробел для прыжка
        if (ch == 'a' || ch == 'A') HorizonMoveMap(1);  // A - движение влево (на macOS)
        if (ch == 'd' || ch == 'D') HorizonMoveMap(-1);  // D - движение вправо (на macOS)
        
        VertMoveObject(&mario);  // Обновление физики
        PutObjectOmMap(brick[0]);
        PutObjectOmMap(mario);
        ShowMap();
        usleep(10000);  // Задержка 10 мс
        
        int newCh = getch();  // Получает код нажатой клавиши
        if (newCh != ERR) ch = newCh;  // Обновляем ch только если получен валидный ввод
    } while (ch != 27);  // 27 = ESC для выхода
    
    endwin();  // Завершает работу ncurses, восстанавливает исходное состояние консоли
    return 0;
}
