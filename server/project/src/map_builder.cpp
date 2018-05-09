#include "map_builder.hpp"

void MapBuilder::build(GameField& gf) {
	for (int i = 0; i< 10; ++i) {
		StaticObject* s = new StaticObject(200 + i, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(100, 100+i*20));
		gf.add_object(s);
	}
	AidKit* s = new AidKit(300, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(100, 50));
	gf.add_object(s);

	AidKit* s1 = new AidKit(300, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(-310, 121));
	gf.add_object(s1);

	LandingMine* l = new LandingMine(301, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(204, -100));
	gf.add_object(l);

	BulletContainer* b = new BulletContainer(302, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(-100, 30));
	gf.add_object(b);

	Weapon* w = new Weapon(302, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(-300, 30), 102);
	gf.add_object(w);

	Weapon* w1 = new Weapon(302, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(-350, 30), 101);
	gf.add_object(w1);

	Weapon* w2 = new Weapon(302, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(-400, 30), 103);
	gf.add_object(w2);
}