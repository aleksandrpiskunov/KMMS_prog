// Нужен для расширенных возможностей ncurses, включая wide-char ввод через get_wch().
#define _XOPEN_SOURCE_EXTENDED 1
#define mapWidth 80
#define mapHeight 25

#include <locale.h>   // Нужен для setlocale()
#include <math.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   // usleep()
#include <wchar.h>    // Нужен для wide-символов и wint_t

typedef struct TObject {
    float x, y;
    float width, height;
    float vertSpeed;
    bool IsFly;
    char cType;
    float horizSpeed;
} TObject;

void ClearMap(char map[mapHeight][mapWidth+1]);
void CreateLevel(TObject &mario, TObject *&brick, TObject *&moving, int &movingLength, int &brickLength, const int &lvl, int &score, int &maxLvl);
void DeleteMoving(const int i, TObject *&moving, int &movingLength);
TObject *GetNewBrick(int &brickLength, TObject *&brick);
TObject *GetNewMoving(int &movingLength, TObject *&moving);
void HorizonMoveMap(const float dx, TObject &mario, int &brickLength, TObject *&brick, int &movingLength, TObject *&moving);
void HorizonMoveObject(TObject *obj, TObject &mario, int &brickLength, TObject *&moving, TObject *&brick, int &movingLength, int &level, int &maxLvl, int &score, char map[mapHeight][mapWidth+1]);
void InitObject(TObject *obj, const float xPos, const float yPos, const float oWidth, const float oHeight, const char inType);
bool IsCollision(const TObject &o1, const TObject &o2);
bool IsPosInMap(const int x, const int y);
void keyboard_detect(int &moveDirection, bool &jumpRequested, bool &shouldExit);
void MarioCollision(char map[mapHeight][mapWidth+1], TObject &mario, TObject *&moving, int &movingLength, TObject *&brick, int &brickLength, int &score, int &level, int &maxLvl);
void PlayerDead(char map[mapHeight][mapWidth+1], TObject &mario, TObject *&brick, TObject *&moving, int &movingLength, int &brickLength, int &level, int &score, int &maxLvl);
void PutObjectOmMap(const TObject &obj, char map[mapHeight][mapWidth+1]);
void PutScoreOnMap(char map[mapHeight][mapWidth+1], int &score);
void SetObjectPos(TObject *obj, const float xPos, const float yPos);
void ShowMap(char map[mapHeight][mapWidth+1]);
void VertMoveObject(TObject *obj, TObject &mario, TObject *&moving, TObject *&brick, int &brickLength, int &movingLength, int &level, int &maxLvl, int &score, char map[mapHeight][mapWidth+1]);

bool IsPosInMap(const int x, const int y){
    return ( ( x >= 0) && ( x < mapWidth) && ( y>= 0) && ( y < mapHeight));
}

bool IsCollision(const TObject &o1, const TObject &o2){
    return (o1.x + o1.width > o2.x) && (o1.x < ( o2.x + o2.width)) &&
           ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height)); 
}

void ClearMap(char map[mapHeight][mapWidth+1])
{
    for (int j = 0; j < mapHeight; j++) {
        memset(map[j], ' ', mapWidth);
        map[j][mapWidth] = '\0';
    }
}

void ShowMap(char map[mapHeight][mapWidth+1])
{
    for (int j = 0; j < mapHeight; j++)
        mvprintw(j, 0, "%s", map[j]);  
    refresh();
}

void PutObjectOmMap(const TObject &obj, char map[mapHeight][mapWidth+1])
{
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < ix + iWidth; i++)
        for (int j = iy; j < iy + iHeight; j++)
            if (IsPosInMap(i, j))
                map[j][i] = obj.cType;
}

void PutScoreOnMap(char map[mapHeight][mapWidth+1], int &score)
{
    char c[30];
    snprintf(c, sizeof(c), "Score: %d", score);
    int len = strlen(c);
    for (int i = 0; i < len && (i+5) < mapWidth; i++)
        map[1][i+5] = c[i];
}


void SetObjectPos(TObject *obj, const float xPos, const float yPos){
    obj->x = xPos;
    obj->y = yPos;
}

void InitObject(TObject *obj, const float xPos, const float yPos, const float oWidth, const float oHeight, const char inType){
    SetObjectPos(obj, xPos, yPos);
    obj->width = oWidth;
    obj->height = oHeight;
    obj->vertSpeed = 0;
    obj->IsFly = false;  
    obj->cType = inType;
    obj->horizSpeed = 0.2;
}

TObject *GetNewBrick(int &brickLength, TObject *&brick){
    brickLength++;
    TObject *newBrick = new TObject[brickLength];
    if (brick != NULL){
        for (int i = 0; i < brickLength - 1; i++)
            newBrick[i] = brick[i];
        delete[] brick;
    }
    brick = newBrick;
    return brick + brickLength - 1;
}

TObject *GetNewMoving(int &movingLength, TObject *&moving){
    movingLength++;
    TObject *newMoving = new TObject[movingLength];
    if (moving != NULL){
        for (int i = 0; i < movingLength - 1; i++)
            newMoving[i] = moving[i];
        delete[] moving;
    }
    moving = newMoving;
    return moving + movingLength - 1;
}

void DeleteMoving(const int i,TObject *&moving, int &movingLength){
    if (moving == NULL || i < 0 || i >= movingLength) return;

    int oldLen = movingLength;
    movingLength--;

    if (movingLength == 0){
        delete[] moving;
        moving = NULL;
        return;
    }

    TObject *newMoving = new TObject[movingLength];
    for (int j = 0, k = 0; j < oldLen; j++){
        if (j == i) continue;
        newMoving[k++] = moving[j];
    }
    delete[] moving;
    moving = newMoving;
}

void CreateLevel(TObject &mario, TObject *&brick, TObject *&moving, int &movingLength, int &brickLength, const int &lvl, int &score, int &maxLvl){
    if (brick != NULL){ delete[] brick; brick = NULL; }
    brickLength = 0;
    if (moving != NULL){ delete[] moving; moving = NULL; }
    movingLength = 0;

    InitObject(&mario, 39, 10, 3 ,3, '@');
    score = 0;

    switch (lvl) {
    case 1:
        // el, xpos, ypos, oWidth, oHeight, type
        InitObject(GetNewBrick(brickLength, brick), 15, 20, 3, 5, '+');
        InitObject(GetNewBrick(brickLength, brick), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(brickLength, brick), 30, 12, 5, 3, '?');
        InitObject(GetNewBrick(brickLength, brick), 50, 12, 5, 3, '?');
        InitObject(GetNewBrick(brickLength, brick), 60, 15, 40, 10, '#');
        InitObject(GetNewBrick(brickLength, brick), 60, 5, 10, 3, '-');
        InitObject(GetNewBrick(brickLength, brick), 70, 5, 5, 3, '?');
        InitObject(GetNewBrick(brickLength, brick), 75, 5, 5, 3, '-');
        InitObject(GetNewBrick(brickLength, brick), 80, 5, 5, 3, '?');
        InitObject(GetNewBrick(brickLength, brick), 85, 10, 10, 3, '-');
        InitObject(GetNewBrick(brickLength, brick), 100, 20, 20, 5, '#');
        InitObject(GetNewBrick(brickLength, brick), 120, 15, 20, 10, '#');
        InitObject(GetNewBrick(brickLength, brick), 150, 20, 40, 5, '#');
        InitObject(GetNewBrick(brickLength, brick), 200, 15, 10, 10, '+' );

        InitObject(GetNewMoving(movingLength, moving), 25 ,10 ,3 ,2, 'o' );
        InitObject(GetNewMoving(movingLength, moving), 80 ,10 ,3 ,2, 'o' );
        break;
    case 2:
        InitObject(GetNewBrick(brickLength, brick), 15, 20, 3, 5, '+');
        InitObject(GetNewBrick(brickLength, brick), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(brickLength, brick), 60, 15, 10, 10, '#');
        InitObject(GetNewBrick(brickLength, brick), 80, 20, 20, 5, '#');
        InitObject(GetNewBrick(brickLength, brick), 105, 15, 10, 10, '#');
        InitObject(GetNewBrick(brickLength, brick), 120, 20, 40, 5, '#');
        InitObject(GetNewBrick(brickLength, brick), 165, 15, 10, 10, '+' );
        InitObject(GetNewMoving(movingLength, moving), 25 ,10 ,3 ,2, 'o' );
        InitObject(GetNewMoving(movingLength, moving), 80 ,10 ,3 ,2, 'o' );
        InitObject(GetNewMoving(movingLength, moving), 65,10 ,3 ,2, 'o' );
        InitObject(GetNewMoving(movingLength, moving), 120 ,10 ,3 ,2, 'o' );
        InitObject(GetNewMoving(movingLength, moving), 175,10 ,3 ,2, 'o' );
        break;
    case 3:
        InitObject(GetNewBrick(brickLength, brick), 5, 20, 3, 5, '+');
        InitObject(GetNewBrick(brickLength, brick), 10, 20, 60, 5, '#');
        InitObject(GetNewBrick(brickLength, brick), 75, 16, 12, 2, '#');
        InitObject(GetNewBrick(brickLength, brick), 95, 13, 12, 2, '#');
        InitObject(GetNewBrick(brickLength, brick), 115, 10, 12, 2, '#');
        InitObject(GetNewBrick(brickLength, brick), 135, 15, 14, 2, '#');
        InitObject(GetNewBrick(brickLength, brick), 152, 12, 10, 2, '+' );

        InitObject(GetNewMoving(movingLength, moving), 18, 10, 3, 2, 'o');
        InitObject(GetNewMoving(movingLength, moving), 72, 10, 3, 2, 'o');
        InitObject(GetNewMoving(movingLength, moving), 98, 7, 3, 2, 'o');
        InitObject(GetNewMoving(movingLength, moving), 128, 8, 3, 2, 'o');
        InitObject(GetNewMoving(movingLength, moving), 156, 10, 3, 2, 'o');
        break;
    default:
        break;
    }
    maxLvl = 3;
}

void PlayerDead(char map[mapHeight][mapWidth+1], TObject &mario, TObject *&brick, TObject *&moving, int &movingLength, int &brickLength, int &level, int &score, int &maxLvl){
    const int DEATH_DELAY_US = 500000;
    const int COLOR_DEAD = 2;
    const int COLOR_NORMAL = 1;

    if (has_colors()){
        wbkgd(stdscr, COLOR_PAIR(COLOR_DEAD));
        clear();
        ShowMap(map);
        refresh();
    }
    usleep(DEATH_DELAY_US);
    CreateLevel(mario, brick, moving, movingLength, brickLength, level, score, maxLvl);
    if (has_colors()){
        wbkgd(stdscr, COLOR_PAIR(COLOR_NORMAL));
        clear();
    }
}

void VertMoveObject(TObject *obj, TObject &mario, TObject *&moving, TObject *&brick, int &brickLength, int &movingLength, int &level, int &maxLvl, int &score, char map[mapHeight][mapWidth+1])
{
    const float GRAVITY = 0.06f;
    const float ITEM_BOUNCE_SPEED = -0.7f;
    const int LEVEL_COMPLETE_DELAY_US = 500000;
    const int COLOR_COMPLETE = 3;
    const int COLOR_NORMAL = 1;
    const char MYSTERY_BLOCK = '?';
    const char EMPTY_BLOCK = '-';
    const char EXIT_BLOCK = '+';
    const char PLAYER = '@';
    const char COLLECTIBLE = '$';

    obj->IsFly = true;
    obj->vertSpeed += GRAVITY;
    SetObjectPos(obj, obj->x, obj->y + obj->vertSpeed);

    if (brick == NULL || brickLength == 0) return;

    for (int i = 0; i < brickLength; i++)
        if (IsCollision(*obj, brick[i]))
        {
            if ((brick[i].cType == MYSTERY_BLOCK) && (obj->vertSpeed < 0) && (obj == &mario)){
                brick[i].cType = EMPTY_BLOCK;
                InitObject(GetNewMoving(movingLength, moving), brick[i].x, brick[i].y - 3, 3, 2, COLLECTIBLE);
                moving[movingLength - 1].vertSpeed = ITEM_BOUNCE_SPEED;
            }

            obj->y -= obj->vertSpeed;
            obj->vertSpeed = 0;
            obj->IsFly = false;

            if ((brick[i].cType == EXIT_BLOCK) && (obj->cType == PLAYER)){
                level++;
                if (level > maxLvl) level = 1;
                if (has_colors()){
                    wbkgd(stdscr, COLOR_PAIR(COLOR_COMPLETE));
                    clear();
                    ShowMap(map);
                    refresh();
                }
                usleep(LEVEL_COMPLETE_DELAY_US);
                CreateLevel(mario, brick, moving, movingLength, brickLength, level, score, maxLvl);
                if (has_colors()){
                    wbkgd(stdscr, COLOR_PAIR(COLOR_NORMAL));
                    clear();
                }
                return;
            }
            break;
        }
}

void HorizonMoveObject(TObject *obj, TObject &mario, int &brickLength, TObject *&moving, TObject *&brick, int &movingLength, int &level, int &maxLvl, int &score, char map[mapHeight][mapWidth+1]){
    const char ENEMY = 'o';

    obj[0].x += obj[0].horizSpeed;

    for (int i = 0; i < brickLength; i++)
        if (IsCollision(obj[0], brick[i]))
        {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
            return;
        }

    if (obj[0].cType == ENEMY){
        TObject tmp = obj[0];
        VertMoveObject(&tmp, mario, moving, brick, brickLength, movingLength, level, maxLvl, score, map );
        if (tmp.IsFly == true){
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
        }
    }
}
void HorizonMoveMap(const float dx, TObject &mario, int &brickLength, TObject *&brick, int &movingLength, TObject *&moving)
{
    TObject test = mario;
    test.x -= dx;
    for (int i = 0; i < brickLength; i++)
        if (IsCollision(test, brick[i]))
            return;

    for (int i = 0; i < brickLength; i++)
        brick[i].x += dx;

    for (int i = 0; i < movingLength; i++)
        moving[i].x += dx;
}

void MarioCollision(char map[mapHeight][mapWidth+1], TObject &mario, TObject *&moving, int &movingLength, TObject *&brick, int &brickLength, int &score, int &level, int &maxLvl){
    const char ENEMY = 'o';
    const char COLLECTIBLE = '$';
    const int ENEMY_KILL_POINTS = 50;
    const int COLLECTIBLE_POINTS = 100;
    const float TOP_COLLISION_THRESHOLD = 0.5f;

    if (moving == NULL || movingLength == 0) return;
    for (int i = 0; i < movingLength; i++){
        if (IsCollision(mario, moving[i]))
        {
            switch (moving[i].cType) {
            case ENEMY:
                if ((mario.IsFly == true)
                    && (mario.vertSpeed > 0)
                    && (mario.y + mario.height < moving[i].y + moving[i].height * TOP_COLLISION_THRESHOLD))
                {
                    score += ENEMY_KILL_POINTS;
                    DeleteMoving(i, moving, movingLength);
                    i--;
                } else {
                    PlayerDead(map, mario, brick, moving, movingLength, brickLength, level, score, maxLvl);
                }
                break;
            case COLLECTIBLE:
                DeleteMoving(i, moving, movingLength);
                score += COLLECTIBLE_POINTS;
                i--;
                break;
            }
        }
    }
}

void keyboard_detect(int &moveDirection, bool &jumpRequested, bool &shouldExit){
    wint_t ch = 0;
    shouldExit = false;

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
}

int main()
{   
    const int COLOR_NORMAL = 1;
    const int COLOR_DEAD = 2;
    const int COLOR_COMPLETE = 3;
    const float HORIZONTAL_SPEED = 0.3f; 
    const float JUMP_SPEED = -1.1f;
    const int FRAME_DELAY_US = 10000;
    const int MOVE_STOP = 0;
    
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    if (has_colors()){
        start_color();
        use_default_colors();
        init_pair(COLOR_NORMAL, COLOR_WHITE, COLOR_BLUE);
        init_pair(COLOR_DEAD, COLOR_WHITE, COLOR_RED);
        init_pair(COLOR_COMPLETE, COLOR_WHITE, COLOR_GREEN);
        wbkgd(stdscr, COLOR_PAIR(COLOR_NORMAL));
        clear();
    }

    TObject *brick = NULL;
    int brickLength = 0;
    TObject *moving = NULL;
    int movingLength = 0;
    int level = 1;
    int score = 0;
    int maxLvl = 0;

    char map[mapHeight][mapWidth+1];
    TObject mario;

    CreateLevel(mario, brick, moving, movingLength, brickLength, level, score, maxLvl);
    
    int moveDirection = MOVE_STOP;
    bool jumpRequested = false;

    do
    {
        bool shouldExit = false;
        keyboard_detect(moveDirection, jumpRequested, shouldExit);

        if (mario.y > mapHeight) 
            PlayerDead(map, mario, brick, moving, movingLength, brickLength, level, score, maxLvl);

        if (shouldExit)
            break;

        if (jumpRequested && mario.IsFly == false)
            mario.vertSpeed = JUMP_SPEED;

        jumpRequested = false;

        if (moveDirection != MOVE_STOP)
            HorizonMoveMap(static_cast<float>(moveDirection) * HORIZONTAL_SPEED, mario, brickLength, brick, movingLength, moving);

        clear(); 
        ClearMap(map);

        VertMoveObject(&mario, mario, moving, brick, brickLength, movingLength, level, maxLvl, score, map);
        MarioCollision(map, mario, moving, movingLength, brick, brickLength, score, level, maxLvl);

        for (int i = 0; i < brickLength; i++)
            PutObjectOmMap(brick[i], map);

        for (int i = 0; i < movingLength; i++){
            VertMoveObject(moving + i, mario, moving, brick, brickLength, movingLength, level, maxLvl, score, map);
            HorizonMoveObject(moving + i, mario, brickLength, moving, brick, movingLength, level, maxLvl, score, map);
            if (moving[i].y > mapHeight){
                DeleteMoving(i, moving, movingLength);
                i--;
                continue;
            }
            PutObjectOmMap(moving[i], map);
        }

        PutObjectOmMap(mario, map);
        PutScoreOnMap(map, score);
        ShowMap(map);

        usleep(FRAME_DELAY_US);
        
    } while (true);
    
    if (brick != NULL) delete[] brick;
    if (moving != NULL) delete[] moving;
    endwin();
    return 0;
}