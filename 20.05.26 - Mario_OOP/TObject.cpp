#include "TObject.hpp"
#include "Constants.hpp"
#include "Game.hpp"

using pav::TObject;

TObject::TObject(const float xPos, const float yPos, const float oWidth, const float oHeight, const char inType)
	: x(xPos), y(yPos), width(oWidth), height(oHeight), vertSpeed(0.0f), IsFly(false), cType(inType), horizSpeed(0.0f){};

void TObject::vert_move(Game &game){
    IsFly = true;
    vertSpeed += GRAVITY;
    set_pos(x, y + vertSpeed);

    if (game.brick == NULL || game.brickLength == 0) return;

    for (int i = 0; i < game.brickLength; i++)
        if (IsCollision(*obj, brick[i]))
        {
            if ((brick[i].cType == MYSTERY_BLOCK) && (obj->vertSpeed < 0) && (obj == &mario)){
                brick[i].cType = EMPTY_BLOCK;
                InitObject(GetNewMoving(movingLength, moving), brick[i].x, brick[i].y - ITEM_Y_OFFSET, ITEM_WIDTH, ITEM_HEIGHT, COLLECTIBLE);
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

void TObject::horiz_move(Game &game){}