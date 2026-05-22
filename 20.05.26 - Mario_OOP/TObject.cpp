#include "Constants.hpp"
#include "Game.hpp"
#include "TObject.hpp"

#include <locale.h>   // Нужен для setlocale()
#include <math.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   // usleep()
#include <wchar.h>    // Нужен для wide-символов и wint_t

namespace pav{

TObject::TObject(const float xPos, const float yPos, const float oWidth, const float oHeight, const char inType)
	: x(xPos), y(yPos), width(oWidth), height(oHeight), vertSpeed(0.0f), IsFly(false), cType(inType), horizSpeed(0.0f){};

void TObject::vert_move(Game &game){
    IsFly = true;
    vertSpeed += GRAVITY;
    set_pos(x, y + vertSpeed);

    if (game.get_brick_length() == 0) return;

    for (int i = 0; i < game.get_brick_length(); i++){
        if (TObject::is_collision(*this, *game.get_bricks()[i]))
        {
            if ( ((*game.get_bricks()[i]).get_cType() == MYSTERY_BLOCK) && (vertSpeed < 0)){
                (*game.get_bricks()[i]).set_cType(EMPTY_BLOCK);
                TObject* new_moving = game.create_moving(game.get_bricks()[i]->get_x(), game.get_bricks()[i]->get_y() - 3, 3, 2, COLLECTIBLE);
                (*game.get_moving()[game.get_moving_length() - 1]).vertSpeed = ITEM_BOUNCE_SPEED;
            } 

            y -= vertSpeed;
            vertSpeed = 0;
            IsFly = false;

            if ( ((*game.get_bricks()[i]).get_cType() == EXIT_BLOCK) && (cType == PLAYER)){
                game.rise_level();
                if (game.get_level() > game.get_maxLvl()) game.reset_level();
                if (has_colors()){
                    wbkgd(stdscr, COLOR_PAIR(COLOR_COMPLETE));
                    clear();
                    game.show_map();
                    refresh();
                }
                usleep(50000);
                game.create_level(game.get_level());
                if (has_colors()){
                    wbkgd(stdscr, COLOR_PAIR(COLOR_NORMAL));
                    clear();
                }
                return;
            }
            break;
        }
    }
}

void TObject::horiz_move(Game &game){
    x += horizSpeed;

    for (int i = 0; i < game.get_brick_length(); i++){
        if (TObject::is_collision(*this, *game.get_bricks()[i])){
            x -= horizSpeed;
            horizSpeed = -horizSpeed;
            return;
        }

        if (cType == ENEMY) {
            bool wasFlying = IsFly;
            float prevX = x;
            float prevY = y;
            float prevVertSpeed = vertSpeed;
            vert_move(game);
            if (IsFly == true ){
                x = prevX;
                y = prevY;
                vertSpeed = prevVertSpeed;
                IsFly = wasFlying;
                x -= horizSpeed;
                horizSpeed = -horizSpeed;
            }
        }
    }
}
} //namespace pav