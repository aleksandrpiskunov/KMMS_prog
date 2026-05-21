#pragma once

namespace pav{
        class Game;
        class Mario {
        protected:
                float x;
                float y;
                float width;
                float height;
                float vertSpeed;
                bool IsFly;
                char cType;
                float horizSpeed;

        public:
                Mario(const float xPos, const float yPos,
                          const float oWidth, const float oHeight,
                          const char inType)
                        : x(xPos), y(yPos), width(oWidth), height(oHeight), vertSpeed(0.0f), IsFly(false), cType(inType), horizSpeed(0.0f) {}

                ~Mario() = default;

                void mario_collision(Game &game);
                void player_dead(Game &game);

                void update(Game &game);

                void set_pos(const float xPos, const float yPos) { x = xPos; y = yPos; }

                float get_x() const { return x; }
                float get_y() const { return y; }
                float get_width() const { return width; }
                float get_height() const { return height; }
                char get_type() const { return cType; }
        };

}