#pragma once
#include <vector>
#include <memory>
#include "Constants.hpp"
#include "BaseObject.hpp"
#include "Mario.hpp"

namespace pav{
	class Game {
	private:
		std::vector<std::vector<char>> map;
		int mapWidth, mapHeight;
		int level = 1;
		int score;
		int maxLvl; 
		int brickLength;
		int movingLength;

		std::unique_ptr<Mario> mario;
		std::vector<std::unique_ptr<BaseObject>> brick;
		std::vector<std::unique_ptr<BaseObject>> moving;
    
	public:
		Game(int width = MAP_WIDTH, int height = MAP_HEIGHT);
		~Game();

		Game() = delete;                   
		Game(const Game&) = delete;         
		Game& operator=(const Game&) = delete;  
		Game(Game&&) = delete;              
		Game& operator=(Game&&) = delete;  
		
		bool is_pos_in_map(const int x, const int y) const {
			return ( ( x >= 0) && ( x < mapWidth) && ( y>= 0) && ( y < mapHeight));
		}

		void clear_map();

		void show_map() const;
		void put_score_on_map();
		void create_level(int lvl);
		void horizon_move_map(const float dx);
		void run();

		BaseObject* create_brick(const float x, const float y, const float w, const float h, const char type);
		BaseObject* create_moving(const float x, const float y, const float w, const float h, const char type);
		void delete_moving(std::size_t index);

		void put_object_on_map(const BaseObject &obj);
		void put_object_on_map(const Mario &player);

		void keyboard_detect(int &moveDirection, bool &jumpRequested, bool &shouldExit);

		const std::vector<std::unique_ptr<BaseObject>>& get_bricks() const {
			return brick;
		}

		int get_brick_length() const {
			return brickLength;
		}

		const std::vector<std::unique_ptr<BaseObject>>& get_moving() const {
			return moving;
		}

		int get_moving_length() const {
			return movingLength;
		}

		int get_level() const {
			return level;
		}

		void rise_level() {
			level++;
		}

		void reset_level(){
			level = 1;
		}

		int get_score() const {
			return score;
		}

		void set_score(const int newScore) {
			score = newScore;
		}

		int get_maxLvl() const {
			return maxLvl;
		}

		void set_maxLvl(const int newMaxLvl) {
			maxLvl = newMaxLvl;
		}
	};
}

