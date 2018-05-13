#include "map_builder.hpp"
#include <fstream>

void build_wall(GameField& gf, int x, int y, std::ifstream& fstream) {
	int sx = 0;
	int sy = 0;
	int dir = 0;
	int cnt = 0;
	int txt = 0;

	fstream >> sx >> sy >> dir >> cnt >> txt;

	switch(dir) {
		//По x
		case 1: 
		for (int i = 0; i < cnt; ++i) {
			StaticObject* s = new StaticObject(200 + i, gf.get_physics_world(), b2Vec2(sx, sy), b2Vec2(x + i * sx, y), txt);
			gf.add_object(s);
		}
		break;
		//По y
		case 2: 
		for (int i = 0; i < cnt; ++i) {
			StaticObject* s = new StaticObject(200 + i, gf.get_physics_world(), b2Vec2(sx, sy), b2Vec2(x, y + i * sy), txt);
			gf.add_object(s);
		}
		break;
	}
}
void MapBuilder::build(GameField& gf) {
	std::ifstream f_stream("map.txt");
    std::string type;
    int x = 0;
    int y = 0;

    while(f_stream >> type >> x >> y) {
        PhysicsObject* obj  = nullptr;
        if (type == "wall") {
        	build_wall(gf, x, y, f_stream);
        }
        if (type == "med") {
        	obj = new AidKit(300, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(x, y));
        }
        if (type == "mine") {
        	obj = new LandingMine(301, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(x, y));
        }
        if (type == "bullet") {
			obj = new BulletContainer(302, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(-100, 30));
        }
        if (type == "weapon") {
        	int id = 0;
        	f_stream >> id;
        	obj = new Weapon(302, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(x, y), id);
        }
        if (obj != nullptr) {
        	gf.add_object(obj);
        }
    }

    f_stream.close();
}