#pragma once

namespace pav{
	class Game;
	class BaseObject{
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
		BaseObject() = delete;
		BaseObject(const float xPos, const float yPos, const float oWidth, const float oHeight, const char inType)
			: x(xPos), y(yPos), width(oWidth), height(oHeight), vertSpeed(0.0f), IsFly(false), cType(inType), horizSpeed(0.0f){};
		BaseObject(const BaseObject&) = delete;         
		BaseObject& operator=(const BaseObject&) = delete;  
		BaseObject(BaseObject&&) = delete;              
		BaseObject& operator=(BaseObject&&) = delete;  
		virtual ~BaseObject() = default;

		bool is_collision(const BaseObject &a, const BaseObject &b) {
			return (a.x + a.width > b.x) && (a.x < (b.x + b.width)) && ((a.y + a.height) > b.y) && (a.y < (b.y + b.height));
		}

		void set_pos(const float xPos, const float yPos) { x = xPos; y = yPos; }
		void set_vert_speed(const float speed) { vertSpeed = speed; }
		void set_horiz_speed(const float speed) { horizSpeed = speed; }

		float get_x() const { return x; }
		float get_y() const { return y; }
		float get_width() const { return width; }
		float get_height() const { return height; }
		char get_type() const { return cType; }

		char get_cType() const{
			return cType;
		}

		void set_cType(char type){
			cType = type;
		}

		void vert_move(Game &game);
		void horiz_move(Game &game);

		virtual void update(Game &game) = 0;


	};

}