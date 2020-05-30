//#include "pch.h"
#include "Body.h"
#include<conio.h>

void Body::draw() {
	if (requestDraw) requestDraw = false;
	else {
		if (prevPosition != position) {
			for (unsigned short line = 0; line < box.height; line++) {
				bodyManager->getConsole().put_string(string(box.width, ' '), prevPosition.x, prevPosition.y + line);
			}
			prevPosition = position;
		}
	}
	for (unsigned short line = 0; line < box.height; line++) {
		bodyManager->getConsole().put_string(pix.substr(line*box.width, box.width), position.x, position.y + line);
	}

}

void Barre::update() {
	int c;
	if (_kbhit()) {
		c = _getch();
		switch (c)
		{
		case(75): {if (position.x > 1)position.x--; break; }
		case(77): {if (position.x + 15 < 56) position.x++; break; }
		default:
			break;
		}
	}
}

void Balle::update() {
	if (position.y == barre->getPosition().y - 1 && (position.x >= barre->getPosition().x && position.x <= barre->getPosition().x + 16))
	{
		speed_y = -speed_y;
		if (position.x >= barre->getPosition().x && position.x < barre->getPosition().x + 7) speed_x = -1;
		else if (position.x <= (barre->getPosition().x + 16) && position.x > barre->getPosition().x + 7) speed_x = 1;
		else speed_x = 0;
	}
	if (position.y == 1) speed_y = -speed_y;
	if (position.x == 1 || position.x == 55) {
		speed_x = -speed_x;
	}
	Position pos(position.x + speed_x, position.y + speed_y);
	if (bodyManager->moveBody(*this, pos, bodyManager->colliding));
	else {
		speed_y = -speed_y;
		position.y += speed_y;
		position.x += speed_x;
	}
}