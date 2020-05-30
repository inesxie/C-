#ifndef _BODY
#define _BODY

#include "BodyManager.h"  // car utilisation de Box
#include <string>
#include<conio.h>
#include"Console.h"
using namespace std;

//class BodyManager;
struct Box;
struct Position;

class Body {
	friend class BodyManager;
public:
	Body(const string &name, const Box &box, const Position &position, const string &pix) :
		name(name), box(box), prevPosition(position), position(position),
		pix(pix), disabled(false), requestDraw(false), bodyManager(nullptr) {
		//if (pix.size() != box.height*box.width) throw runtime_error("pix string size must fit box size");
	}
	virtual void update() {};
	void draw();
	bool disabled; //disabled bodies are not checked for collisions
	bool requestDraw; //force drawing at next tick
	inline const string &getName() const { return name; };
	inline const Position &getPosition() const { return position; };
	const Box &getBox() const { return box; };
	int bcount = 0;
protected:
	const string name;
	Box box;
	Position prevPosition;
	Position position;
	string pix;
	BodyManager *bodyManager; //set when the body is added by a bodyManager
};

class Balle :public Body {
public:
	friend class Barre;
	Barre* barre;
	unsigned short speed_x = 1;
	unsigned short speed_y = 1;
	Balle(const string &name, const Box &box, const Position &position, const string &des, Barre &br) :
		Body(name, box, position, des), barre(&br) {}
	void update();
};

class Barre :public Body {
public:
	Barre(const string &name, const Box &box, const Position &position, const string &des) :
		Body(name, box, position, des) {}
	void update();
};

class Brique :public Body {
public:
	friend class Balle;
	Balle *balle;
	Brique(const string &name, const Box &box, const Position &position, const string &des, Balle ba) :
		Body(name, box, position, des), balle(&ba) {}
};

class Bound :public Body {
public:
	bool disabled = 1;
	Bound(const string &name, const Box &box, const Position &position, const string &des) :
		Body(name, box, position, des) {}
};
#endif //_BODY
