#include "MovingItems.hpp"

namespace pav{

void MovingItem::update(Game &game) {
	vert_move(game);
	horiz_move(game);
}

}