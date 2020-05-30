#include "BodyManager.h"
#include "Body.h"
#include <algorithm>
#include<string>
#include<iostream>
#include "console.h"
using namespace std;

bool BodyManager::addBody(Body &body) {
	if (fitBody(body, body.position)) {
		bodies.push_back(&body);
		body.bodyManager = this;
		return true;
	}
	else return false;
}

bool BodyManager::moveBody(Body &body, const Position &position, Body **collidingBody) {
	if (find(bodies.begin(), bodies.end(), &body) == bodies.end())
		return false; //body not found
	if (fitBody(body, position, collidingBody)) {
		body.position = position;
		return true;
	}
	else return false;
}

bool BodyManager::fitBody(const Body &body, const Position &position, Body **collidingBody) {
	if ((position.x + body.box.width > worldBox.width) || (position.y + body.box.height > worldBox.height))
		return false; //doesn't fit in the world

	//for (auto it = bodies.begin(); it != bodies.end(); ++it) {
		//if ((*it) == &body) continue; //do not check with itself
		//if (collide(**it, body.box, position)) {
			//cerr << "collision between body " << (*it)->name << " and body " << body.name;
			//if (collidingBody) *collidingBody = *it;
	for (auto it : bodies) {
		if ((it) == &body) continue; //do not check with itself
		if (collide(*it, body.box, position)) {
			string b = "brique";
			string c = (it->name);
			if (c.compare(b) == 0) {
				it->requestDraw = 1;
				it->disabled = 1;
				count++;
			}
			if (it->getName() == "brique1") {
				it->requestDraw = 1; it->bcount++;
				if (it->bcount == 2) { it->disabled = 1; count++; }
			}
			if (collidingBody) *collidingBody = it;
			return false;
		}

	}
	if (collidingBody) *collidingBody = nullptr;
	return true;
}

bool BodyManager::collide(const Body & body, const Box &box, const Position &position) { //collision
	if (body.disabled) return false;
	if (body.getName() == "brique" || body.getName() == "brique1") {
		if ((position.x + box.width * 2 <= body.position.x) || (body.position.x + body.box.width * 2 <= position.x))
			return false;
		else {
			if ((position.y + box.height <= body.position.y) || (body.position.y + body.box.height <= position.y))
				return false;
			else return true;
		}
	}
	if ((position.x + box.width <= body.position.x) || (body.position.x + body.box.width <= position.x))
		return false;
	else {
		if ((position.y + box.height <= body.position.y) || (body.position.y + body.box.height <= position.y))
			return false;
		else return true;
	}
}

void BodyManager::run() {
	for (auto it = bodies.begin(); it != bodies.end(); ++it) {
		(*it)->draw();
	}
	//getConsole().set_pen_color(black);
	int i = 0;
	getConsole().set_hide_cursor();
	while (!exit) {
		for (auto it = bodies.begin(); it != bodies.end(); ++it) {
			getConsole().set_pen_color(yellow);
			if ((*it)->getName() == "balle") { i++; if (i == 5) { i = 0; } else continue; }
			(*it)->update();
			if ((*it)->requestDraw || ((*it)->prevPosition != (*it)->position)) {
				if ((*it)->bcount >= 1 && it == bodies.begin() + 2) getConsole().set_pen_color(green);
				else if ((*it)->bcount >= 1 && (it == bodies.begin() + 8 || it == bodies.begin() + 9)) getConsole().set_pen_color(green);
				else getConsole().set_pen_color(red);
				if ((*it)->disabled == 1)
					getConsole().set_pen_color(black);
				(*it)->draw();
				if ((*it)->getPosition().y > 34) exit = 1;
			}
		}

		getConsole().set_hide_cursor();
		Sleep(10); //relax cpu (should use a periodic timer set with CreateTimerQueueTimer instead, but too complex for this project)
		if (count == 14) exit = 1;

	}
}

