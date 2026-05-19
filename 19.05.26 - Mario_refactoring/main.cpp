// Нужен для расширенных возможностей ncurses, включая wide-char ввод через get_wch().
#define _XOPEN_SOURCE_EXTENDED 1
#define mapWidth 80
#define mapHeight 25

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>   // Нужен для setlocale()
#include <wchar.h>    // Нужен для wide-символов и wint_t
#include <unistd.h>   // usleep() 
#include <ncurses.h>
#include <string.h>

typedef struct TObject {
    float x, y;
    float width, height;
    float vertSpeed;
    bool IsFly;
    char cType;
    float horizSpeed;
} TObject;

typedef struct GameState {
    char map[mapHeight][mapWidth + 1];
    TObject mario;

    TObject *brick;
    int brickLength;

    TObject *moving;
    int movingLength;

    int level;
    int score;
    int maxLvl; 
} GameState;

bool IsPosInMap(const int x, const int y);
bool IsCollision(const TObject &o1, const TObject &o2);

void ClearMap(GameState &state);
void ShowMap(const GameState &state);
void PutObjectOmMap(const TObject &obj, GameState &state);
void PutScoreOnMap(GameState &state);

void SetObjectPos(TObject *obj, const float xPos, const float yPos);
void InitObject(TObject *obj, const float xPos, const float yPos, const float oWidth, const float oHeight, const char inType);
TObject *GetNewBrick(GameState &state);
TObject *GetNewMoving(GameState &state);
void DeleteMoving(const int i, GameState &state);

void CreateLevel(GameState &state, const int lvl);
void PlayerDead(GameState &state);

void VertMoveObject(TObject *obj, GameState &state);
void HorizonMoveObject(TObject *obj, GameState &state);
void HorizonMoveMap(const float dx, GameState &state);
void MarioCollision(GameState &state);

void keyboard_detect(int &moveDirection, bool &jumpRequested, bool &shouldExit);

bool IsPosInMap(const int x, const int y){
    return ( ( x >= 0) && ( x < mapWidth) && ( y>= 0) && ( y < mapHeight));
}

bool IsCollision(const TObject &o1, const TObject &o2){
    return (o1.x + o1.width > o2.x) && (o1.x < ( o2.x + o2.width)) &&
           ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height)); 
}

void ClearMap(GameState &state)
{
    for (int j = 0; j < mapHeight; j++) {
        memset(state.map[j], ' ', mapWidth);
        state.map[j][mapWidth] = '\0';
    }
}

void ShowMap(const GameState &state)
{
    for (int j = 0; j < mapHeight; j++)
        mvprintw(j, 0, "%s", state.map[j]);  
    refresh();
}

void PutObjectOmMap(const TObject &obj, GameState &state)
{
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < ix + iWidth; i++)
        for (int j = iy; j < iy + iHeight; j++)
            if (IsPosInMap(i, j))
                state.map[j][i] = obj.cType;
}

void PutScoreOnMap(GameState &state)
{
    char c[30];
    snprintf(c, sizeof(c), "Score: %d", state.score);
    int len = strlen(c);
    for (int i = 0; i < len && (i+5) < mapWidth; i++)
        state.map[1][i+5] = c[i];
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

TObject *GetNewBrick(GameState &state){
    state.brickLength++;
    TObject *newBrick = new TObject[state.brickLength];
    if (state.brick != NULL){
        for (int i = 0; i < state.brickLength - 1; i++)
            newBrick[i] = state.brick[i];
        delete[] state.brick;
    }
    state.brick = newBrick;
    return state.brick + state.brickLength - 1;
}

TObject *GetNewMoving(GameState &state){
    state.movingLength++;
    TObject *newMoving = new TObject[state.movingLength];
    if (state.moving != NULL){
        for (int i = 0; i < state.movingLength - 1; i++)
            newMoving[i] = state.moving[i];
        delete[] state.moving;
    }
    state.moving = newMoving;
    return state.moving + state.movingLength - 1;
}

void DeleteMoving(const int i, GameState &state){
    if (state.moving == NULL || i < 0 || i >= state.movingLength) return;

    int oldLen = state.movingLength;
    state.movingLength--;

    if (state.movingLength == 0){
        delete[] state.moving;
        state.moving = NULL;
        return;
    }

    TObject *newMoving = new TObject[state.movingLength];
    for (int j = 0, k = 0; j < oldLen; j++){
        if (j == i) continue;
        newMoving[k++] = state.moving[j];
    }
    delete[] state.moving;
    state.moving = newMoving;
}

void CreateLevel(GameState &state, const int lvl){
    if (state.brick != NULL){ delete[] state.brick; state.brick = NULL; }
    state.brickLength = 0;
    if (state.moving != NULL){ delete[] state.moving; state.moving = NULL; }
    state.movingLength = 0;

    InitObject(&state.mario, 39, 10, 3 ,3, '@');
    state.score = 0;

    switch (lvl) {
    case 1:
        // el, xpos, ypos, oWidth, oHeight, type
        InitObject(GetNewBrick(state), 15, 20, 3, 5, '+');
        InitObject(GetNewBrick(state), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(state), 30, 12, 5, 3, '?');
        InitObject(GetNewBrick(state), 50, 12, 5, 3, '?');
        InitObject(GetNewBrick(state), 60, 15, 40, 10, '#');
        InitObject(GetNewBrick(state), 60, 5, 10, 3, '-');
        InitObject(GetNewBrick(state), 70, 5, 5, 3, '?');
        InitObject(GetNewBrick(state), 75, 5, 5, 3, '-');
        InitObject(GetNewBrick(state), 80, 5, 5, 3, '?');
        InitObject(GetNewBrick(state), 85, 10, 10, 3, '-');
        InitObject(GetNewBrick(state), 100, 20, 20, 5, '#');
        InitObject(GetNewBrick(state), 120, 15, 20, 10, '#');
        InitObject(GetNewBrick(state), 150, 20, 40, 5, '#');
        InitObject(GetNewBrick(state), 200, 15, 10, 10, '+' );

        InitObject(GetNewMoving(state), 25 ,10 ,3 ,2, 'o' );
        InitObject(GetNewMoving(state), 80 ,10 ,3 ,2, 'o' );
        break;
    case 2:
        InitObject(GetNewBrick(state), 15, 20, 3, 5, '+');
        InitObject(GetNewBrick(state), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(state), 60, 15, 10, 10, '#');
        InitObject(GetNewBrick(state), 80, 20, 20, 5, '#');
        InitObject(GetNewBrick(state), 105, 15, 10, 10, '#');
        InitObject(GetNewBrick(state), 120, 20, 40, 5, '#');
        InitObject(GetNewBrick(state), 165, 15, 10, 10, '+' );
        InitObject(GetNewMoving(state), 25 ,10 ,3 ,2, 'o' );
        InitObject(GetNewMoving(state), 80 ,10 ,3 ,2, 'o' );
        InitObject(GetNewMoving(state), 65,10 ,3 ,2, 'o' );
        InitObject(GetNewMoving(state), 120 ,10 ,3 ,2, 'o' );
        InitObject(GetNewMoving(state), 175,10 ,3 ,2, 'o' );
        break;
    case 3:
        InitObject(GetNewBrick(state), 5, 20, 3, 5, '+');
        InitObject(GetNewBrick(state), 10, 20, 60, 5, '#');
        InitObject(GetNewBrick(state), 75, 16, 12, 2, '#');
        InitObject(GetNewBrick(state), 95, 13, 12, 2, '#');
        InitObject(GetNewBrick(state), 115, 10, 12, 2, '#');
        InitObject(GetNewBrick(state), 135, 15, 14, 2, '#');
        InitObject(GetNewBrick(state), 152, 12, 10, 2, '+' );

        InitObject(GetNewMoving(state), 18, 10, 3, 2, 'o');
        InitObject(GetNewMoving(state), 72, 10, 3, 2, 'o');
        InitObject(GetNewMoving(state), 98, 7, 3, 2, 'o');
        InitObject(GetNewMoving(state), 128, 8, 3, 2, 'o');
        InitObject(GetNewMoving(state), 156, 10, 3, 2, 'o');
        break;
    default:
        break;
    }
    state.maxLvl = 3;
}

void PlayerDead(GameState &state){
    const int DEATH_DELAY_US = 500000;
    const int COLOR_DEAD = 2;
    const int COLOR_NORMAL = 1;
    
    if (has_colors()){
        wbkgd(stdscr, COLOR_PAIR(COLOR_DEAD));
        clear();
        ShowMap(state);
        refresh();
    }
    usleep(DEATH_DELAY_US);
    CreateLevel(state, state.level);
    if (has_colors()){
        wbkgd(stdscr, COLOR_PAIR(COLOR_NORMAL));
        clear();
    }
}

void VertMoveObject(TObject *obj, GameState &state)
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
    const char ITEM_Y_OFFSET = 3;
    const char ITEM_WIDTH = 3;
    const char ITEM_HEIGHT = 2;

    obj->IsFly = true;
    obj->vertSpeed += GRAVITY;
    SetObjectPos(obj, obj->x, obj->y + obj->vertSpeed);

    if (state.brick == NULL || state.brickLength == 0) return;

    for (int i = 0; i < state.brickLength; i++)
        if (IsCollision(*obj, state.brick[i]))
        {
            if ((state.brick[i].cType == MYSTERY_BLOCK) && (obj->vertSpeed < 0) && (obj == &state.mario)){
                state.brick[i].cType = EMPTY_BLOCK;
                InitObject(GetNewMoving(state), state.brick[i].x, state.brick[i].y - ITEM_Y_OFFSET, ITEM_WIDTH, ITEM_HEIGHT, COLLECTIBLE);
                state.moving[state.movingLength - 1].vertSpeed = ITEM_BOUNCE_SPEED;
            }

            obj->y -= obj->vertSpeed;
            obj->vertSpeed = 0;
            obj->IsFly = false;

            if ((state.brick[i].cType == EXIT_BLOCK) && (obj->cType == PLAYER)){
                state.level++;
                if (state.level > state.maxLvl) state.level = 1;
                if (has_colors()){
                    wbkgd(stdscr, COLOR_PAIR(COLOR_COMPLETE));
                    clear();
                    ShowMap(state);
                    refresh();
                }
                usleep(LEVEL_COMPLETE_DELAY_US);
                CreateLevel(state, state.level);
                if (has_colors()){
                    wbkgd(stdscr, COLOR_PAIR(COLOR_NORMAL));
                    clear();
                }
                return;
            }
            break;
        }
}

void HorizonMoveObject(TObject *obj, GameState &state){
    const char ENEMY = 'o';

    obj[0].x += obj[0].horizSpeed;

    for (int i = 0; i < state.brickLength; i++)
        if (IsCollision(obj[0], state.brick[i]))
        {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
            return;
        }

    if (obj[0].cType == ENEMY){
        TObject tmp = obj[0];
        VertMoveObject(&tmp, state);
        if (tmp.IsFly == true){
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
        }
    }
}

void HorizonMoveMap(const float dx, GameState &state)
{
    TObject test = state.mario;
    test.x -= dx;
    for (int i = 0; i < state.brickLength; i++)
        if (IsCollision(test, state.brick[i]))
            return;

    for (int i = 0; i < state.brickLength; i++)
        state.brick[i].x += dx;

    for (int i = 0; i < state.movingLength; i++)
        state.moving[i].x += dx;
}

void MarioCollision(GameState &state){
    const char ENEMY = 'o';
    const char COLLECTIBLE = '$';
    const int ENEMY_KILL_POINTS = 50;
    const int COLLECTIBLE_POINTS = 100;
    const float TOP_COLLISION_THRESHOLD = 0.5f;

    if (state.moving == NULL || state.movingLength == 0) return;
    for (int i = 0; i < state.movingLength; i++){
        if (IsCollision(state.mario, state.moving[i]))
        {
            switch (state.moving[i].cType) {
            case ENEMY:
                if ((state.mario.IsFly == true)
                    && (state.mario.vertSpeed > 0)
                    && (state.mario.y + state.mario.height < state.moving[i].y + state.moving[i].height * TOP_COLLISION_THRESHOLD))
                {
                    state.score += ENEMY_KILL_POINTS;
                    DeleteMoving(i, state);
                    i--;
                } else {
                    PlayerDead(state);
                }
                break;
            case COLLECTIBLE:
                DeleteMoving(i, state);
                state.score += COLLECTIBLE_POINTS;
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

    GameState state{};
    state.brick = NULL;
    state.brickLength = 0;
    state.moving = NULL;
    state.movingLength = 0;
    state.level = 1;
    state.score = 0;
    state.maxLvl = 0;

    CreateLevel(state, state.level);
    
    int moveDirection = MOVE_STOP;
    bool jumpRequested = false;

    do
    {
        bool shouldExit = false;
        keyboard_detect(moveDirection, jumpRequested, shouldExit);

        if (state.mario.y > mapHeight) 
            PlayerDead(state);

        if (shouldExit)
            break;

        if (jumpRequested && state.mario.IsFly == false)
            state.mario.vertSpeed = JUMP_SPEED;

        jumpRequested = false;

        if (moveDirection != MOVE_STOP)
            HorizonMoveMap(static_cast<float>(moveDirection) * HORIZONTAL_SPEED, state);

        clear(); 
        ClearMap(state);
        
        VertMoveObject(&state.mario, state);
        MarioCollision(state);

        for (int i = 0; i < state.brickLength; i++)
            PutObjectOmMap(state.brick[i], state);

        for (int i = 0; i < state.movingLength; i++){
            VertMoveObject(state.moving + i, state);
            HorizonMoveObject(state.moving + i, state);
            if (state.moving[i].y > mapHeight){
                DeleteMoving(i, state);
                i--;
                continue;
            }
            PutObjectOmMap(state.moving[i], state);
        }

        PutObjectOmMap(state.mario, state);
        PutScoreOnMap(state);
        ShowMap(state);

        usleep(FRAME_DELAY_US);
        
    } while (true);
    
    if (state.brick != NULL) delete[] state.brick;
    if (state.moving != NULL) delete[] state.moving;
    endwin();
    return 0;
}