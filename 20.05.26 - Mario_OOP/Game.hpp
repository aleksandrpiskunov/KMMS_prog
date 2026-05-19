#pragma once
#include <vector>
#include <memory>
#include "BaseClass.hpp"

namespace pav{
    class Mario;
    class Game {
    private:
        std::vector<std::vector<char>> map;
        int mapWidth, mapHeight;
        int level;
        int score;
        int maxLvl; 

        std::unique_ptr<TObject> mario;
        std::vector<std::unique_ptr<TObject>> bricks;
        std::vector<std::unique_ptr<TObject>> moving;
    
    public:
        Game(int width, int height);
        ~Game();

        Game() = delete;                   
        Game(const Game&) = delete;         
        Game& operator=(const Game&) = delete;  
        Game(Game&&) = delete;              
        Game& operator=(Game&&) = delete;  
        
        bool is_pos_in_map(const int x, const int y) const;
        void clear_map();
        void show_map() const;
        void put_score_on_map();
        void create_level(int lvl);
        void horizon_move_map(const float dx);

        // object management
        TObject* create_brick(const float x, const float y, const float w, const float h, const char type);
        TObject* create_moving(const float x, const float y, const float w, const float h, const char type);
        void delete_moving(std::size_t index);

        void put_object_on_map(const TObject &obj);

        void keyboard_detect(int &moveDirection, bool &jumpRequested, bool &shouldExit);
    };
}
