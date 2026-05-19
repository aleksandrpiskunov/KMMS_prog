#pragma once

namespace pav{
    class Game;
    class TObject{
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
            TObject() = delete;
            TObject(const float xPos, const float yPos, const float oWidth, const float oHeight, const char inType);
            TObject(const TObject&) = delete;         
            TObject& operator=(const TObject&) = delete;  
            TObject(TObject&&) = delete;              
            TObject& operator=(TObject&&) = delete;  
            virtual ~TObject() = default;

            static bool is_collision(const TObject &a, const TObject &b) {
                return (a.x + a.width > b.x) && (a.x < (b.x + b.width)) && ((a.y + a.height) > b.y) && (a.y < (b.y + b.height));
            }

            void set_pos(const float xPos, const float yPos) { x = xPos; y = yPos; }

            void vert_move(Game &game);
            void horiz_move(Game &game);

            virtual void update(Game &game) = 0;
    };

}