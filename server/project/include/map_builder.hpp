#ifndef SCAV_SERVER_MAP_BUILDER_HPP_
#define SCAV_SERVER_MAP_BUILDER_HPP_

#include "Box2D/Box2D.h"
#include <SFML/System.hpp>
#include "game_object.hpp"
#include "game_field.hpp"

class MapBuilder {
public:
	static void build(GameField& gf);
};


#endif
