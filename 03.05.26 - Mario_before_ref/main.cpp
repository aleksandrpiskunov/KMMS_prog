// Нужен для расширенных возможностей ncurses, включая wide-char ввод через get_wch().
#define _XOPEN_SOURCE_EXTENDED 1

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>   // Нужен для setlocale()
#include <wchar.h>    // Нужен для wide-символов и wint_t
#include <unistd.h>   // usleep() 
#include <ncurses.h>  
#include <string.h>

typedef struct SOblect {
    float x, y;
    float width, height;
    float vertSpeed;
    bool IsFly;
    char cType;
    float horizSpeed;
} TObject;

#define mapWidth 80
#define mapHeight 25

char map[mapHeight][mapWidth + 1];
TObject mario;

TObject *brick = NULL;
int brickLength;

TObject *moving = NULL;
int movingLength;

int level = 1;
int score;
int maxLvl; 

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
    obj->horizSpeed = 0.2;
}

bool IsCollision(TObject o1, TObject o2);

void CreateLevel(int lvl);

void PlayerDead();

TObject *GetNewMoving();

void VertMoveObject(TObject *obj)
{
    obj->IsFly = true;
    obj->vertSpeed +=0.06; 
    SetObjectPos(obj, obj->x, obj->y + obj->vertSpeed);

    for (int i = 0; i < brickLength; i++)

        if ( IsCollision ( *obj, brick[i]))
        {
            if ( ( brick[i].cType == '?') && (obj[0].vertSpeed < 0) && (obj == &mario) ){
                brick[i].cType = '-';
                InitObject(GetNewMoving(), brick[i].x, brick[i].y - 3, 3, 2, '$');
                moving[movingLength - 1].vertSpeed= -0.7;
            }

            obj->y -= obj->vertSpeed;
            obj->vertSpeed = 0;
            obj->IsFly = false;

            if ((brick[i].cType == '+') && (obj-> cType == '@')){
                level++;
                if (level > maxLvl) level = 1;
                if (has_colors()){
                    wbkgd(stdscr, COLOR_PAIR(3));
                    clear();
                    ShowMap();
                    refresh();
                }
                usleep(500000);
                CreateLevel(level);
                if (has_colors()){
                    wbkgd(stdscr, COLOR_PAIR(1));
                    clear();
                }
            }
            break;
        }
}

void DeleteMoving(int i){

    movingLength--;
    TObject *newMoving = new TObject[movingLength];

    for (int j = 0, k = 0; j < movingLength + 1; j++){
        if (j == i)
            continue;

        newMoving[k] = moving[j];
        k++;
    }

    delete[] moving;
    moving = newMoving;
}

void MarioCollision(){
    for (int i = 0; i < movingLength; i++){
        if (IsCollision( mario, moving[i]))
        {
            if (moving[i].cType == 'o'){
                if ( (mario.IsFly == true)   
                    && (mario.vertSpeed > 0)
                    && (mario.y + mario.height < moving[i].y + moving[i].height * 0.5)
                    )
                {
                    score +=50;
                    DeleteMoving(i);
                    i--;
                    continue;
                }
                else {
                    PlayerDead();
                }
            }

            if (moving[i].cType == '$')
            {
                DeleteMoving(i);
                score += 100;
                i--;
                continue;
            }
        }
    }
}

void HorizonMoveObject ( TObject *obj){
    obj[0].x += obj[0].horizSpeed;

    for (int i = 0; i < brickLength; i++)
        if (IsCollision(obj[0], brick[i]))
        {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = - obj[0].horizSpeed;
            return;
        }
    

    if (obj[0].cType == 'o'){    
        TObject tmp = * obj;
        VertMoveObject(&tmp);
        if (tmp.IsFly == true){
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
        }
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

void PutScoreOnMap()
{
    char c[30];
    snprintf(c, sizeof(c), "Score: %d", score);
    int len = strlen(c);
    for (int i = 0; i < len && (i+5) < mapWidth; i++)
        map[1][i+5] = c[i];
}

void HorizonMoveMap( float dx)
{
    TObject test = mario;
    test.x -= dx;
    for (int i = 0; i < brickLength; i++)
        if ( IsCollision(test, brick[i]) ){
            return;
        }

    for (int i = 0; i < brickLength; i++)
        brick[i].x += dx;

    for (int i = 0; i < movingLength; i++)
        moving[i].x += dx;
          
}

bool IsCollision(TObject o1, TObject o2){
    return (o1.x + o1.width > o2.x) && (o1.x < ( o2.x + o2.width)) &&
           ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height)); 
}

TObject *GetNewBrick(){
    brickLength++;
    TObject *newBrick = new TObject[brickLength];
    for (int i = 0; i < brickLength - 1; i++)
        newBrick[i] = brick[i];

    delete[] brick;
    brick = newBrick;
    return brick + brickLength - 1;
}

TObject *GetNewMoving(){
    movingLength++;
    TObject *newMoving = new TObject[movingLength];
    for (int i = 0; i < movingLength - 1; i++)
        newMoving[i] = moving[i];

    delete[] moving;
    moving = newMoving;
    return moving + movingLength - 1;
}

void CreateLevel(int lvl){
    brickLength = 0;
    delete[] brick;
    brick = new TObject[brickLength];
    movingLength = 0;
    delete[] moving;
    moving = new TObject[movingLength];   

    InitObject(&mario, 39, 10, 3 ,3, '@');
    score = 0;

    if (lvl == 1){
                // el, xpos, ypos, oWidth, oHeight, type
        InitObject(GetNewBrick(), 20, 20, 40, 5, '#');
            InitObject(GetNewBrick(), 30, 12, 5, 3, '?');
            InitObject(GetNewBrick(), 50, 12, 5, 3, '?');
        InitObject(GetNewBrick(), 60, 15, 40, 10, '#');
            InitObject(GetNewBrick(), 60, 5, 10, 3, '-');
            InitObject(GetNewBrick(), 70, 5, 5, 3, '?');
            InitObject(GetNewBrick(), 75, 5, 5, 3, '-');
            InitObject(GetNewBrick(), 80, 5, 5, 3, '?');
            InitObject(GetNewBrick(), 85, 10, 10, 3, '-');
        InitObject(GetNewBrick(), 100, 20, 20, 5, '#');
        InitObject(GetNewBrick(), 120, 15, 20, 10, '#');
        InitObject(GetNewBrick(), 150, 20, 40, 5, '#');
        InitObject(GetNewBrick(), 200, 15, 10, 10, '+' );

        InitObject( GetNewMoving(), 25 ,10 ,3 ,2, 'o' );
        InitObject( GetNewMoving(), 80 ,10 ,3 ,2, 'o' );
    }

    if (lvl == 2){
        // el, xpos, ypos, oWidth, oHeight, type
        InitObject(GetNewBrick(), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(), 60, 15, 10, 10, '#');
        InitObject(GetNewBrick(), 80, 20, 20, 5, '#');
        InitObject(GetNewBrick(), 105, 15, 10, 10, '#');
        InitObject(GetNewBrick(), 120, 20, 40, 5, '#');
        InitObject(GetNewBrick(), 165, 15, 10, 10, '+' );
        
        InitObject( GetNewMoving(), 25 ,10 ,3 ,2, 'o' );
        InitObject( GetNewMoving(), 80 ,10 ,3 ,2, 'o' );
        InitObject( GetNewMoving(), 65,10 ,3 ,2, 'o' );
        InitObject( GetNewMoving(), 120 ,10 ,3 ,2, 'o' );
        InitObject( GetNewMoving(), 175,10 ,3 ,2, 'o' );
    }

    if (lvl == 3){
        //(0, 0) - левый верхний угол 
        // el, xpos, ypos, oWidth, oHeight, type
        InitObject(GetNewBrick(), 10, 20, 60, 5, '#');
        InitObject(GetNewBrick(), 75, 16, 12, 2, '#');
        InitObject(GetNewBrick(), 95, 13, 12, 2, '#');
        InitObject(GetNewBrick(), 115, 10, 12, 2, '#');
        InitObject(GetNewBrick(), 135, 15, 14, 2, '#');
        InitObject(GetNewBrick(), 152, 12, 10, 2, '+' );

        InitObject(GetNewMoving(), 18, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 72, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 98, 7, 3, 2, 'o');
        InitObject(GetNewMoving(), 128, 8, 3, 2, 'o');
        InitObject(GetNewMoving(), 156, 10, 3, 2, 'o');
    }
    maxLvl = 3;

}

void PlayerDead(){
    if (has_colors()){
        wbkgd(stdscr, COLOR_PAIR(2));
        clear();
        ShowMap();
        refresh();
    }
    usleep(500000); // 0.5s
    CreateLevel(level);
    if (has_colors()){
        wbkgd(stdscr, COLOR_PAIR(1));
        clear();
    }
}

int main()
{   
    setlocale(LC_ALL, "");

    initscr();  // Инициализирует ncurses 
    cbreak();  // Включает посимвольный ввод без ожидания Enter
    noecho();  // Отключает отображение введённых символов на экран

    // Инициализация цветов: фон по умолчанию — синий
    if (has_colors()){
        start_color();
        use_default_colors();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);   // обычный фон — синий
        init_pair(2, COLOR_WHITE, COLOR_RED);    // фон при смерти — красный
        init_pair(3, COLOR_WHITE, COLOR_GREEN);  // фон при успешном завершении — зелёный
        wbkgd(stdscr, COLOR_PAIR(1));
        clear();
    }

    nodelay(stdscr, TRUE);  // Делает getch() неблокирующим 
    keypad(stdscr, TRUE);  // Включает обработку специальных клавиш (стрелки, функции)
    
    CreateLevel(level);
    
    // Направление движения по горизонтали: 1 - влево, -1 - вправо, 0 - стоим.
    // Горизонтальная скорость (используется и для скроллинга карты)
    const float H_SPEED = 0.3f; 
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

        if (mario.y > mapHeight) PlayerDead();

        if (shouldExit)
            break;

        if (jumpRequested && mario.IsFly == false )
            mario.vertSpeed = -1.1f; 

        jumpRequested = false;

        if (moveDirection != 0)
        {

            HorizonMoveMap((float)moveDirection * H_SPEED);
        }

        clear(); 
        ClearMap();
        
        VertMoveObject(&mario);  // Обновление физики
        MarioCollision();

        for (int i = 0; i < brickLength; i++)
            PutObjectOmMap(brick[i]);

        for (int i = 0; i < movingLength; i++){
            VertMoveObject(moving + i);
            HorizonMoveObject(moving + i);
            if (moving[i].y > mapHeight){
                DeleteMoving(i);
                i--;
                continue;
            }
            PutObjectOmMap(moving[i]);
        }
        
        PutObjectOmMap(mario);

        PutScoreOnMap();
        ShowMap();

        usleep(10000);  
        
    } while (true);
    
    delete[] brick;
    endwin();  // Завершает работу ncurses
    return 0;
}
