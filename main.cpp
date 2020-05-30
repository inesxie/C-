#include<iostream>
#include<string.h>
#include <algorithm>
#include"Body.h"
#include"Console.h"
#include"BodyManager.h"

int main() {

	Console c;
	void SetConsole(Console&);
	SetConsole(c);

	//welcomepage
	bool bienvenu(Console& c);
	if (bienvenu(c) == 0) return 0;
	c.clear();

loop:
	BodyManager BM(Box(100, 100), c);
	char str2[] = { 0xFEu ,0xFEu ,0xFEu,0xFEu,0xFEu,0xFEu, 0xFEu ,0xFEu ,'\0' };
	string dessinbr = str2;
	Barre br("barre", Box(8, 1), Position(23, 34), dessinbr);
	char bal[] = { 0xDBu,'\0' };
	string ball = bal;
	Balle ba("balle", Box(1, 1), Position(30, 33), ball, br);

	char des1[] = { 0xB1u ,0xB1u ,0xB1u,0xB1u,'\0' };
	string dessin1 = des1;

	char des2[] = { 0xDDu,0xDDu, 0xDDu, 0xDDu, '\0' };
	string dessin2 = des2;

	char des3[] = { 0xB2u,0xB2u, 0xB2u, 0xB2u, '\0' };
	string dessin3 = des3;

	Brique b1("brique1", Box(2, 2), Position(28, 1), dessin1, ba);
	Brique b2("brique", Box(2, 2), Position(24, 4), dessin1, ba);
	Brique b3("brique", Box(2, 2), Position(32, 4), dessin1, ba);
	Brique b4("brique", Box(2, 2), Position(22, 7), dessin1, ba);
	Brique b5("brique", Box(2, 2), Position(28, 7), dessin1, ba);
	Brique b6("brique", Box(2, 2), Position(34, 7), dessin1, ba);
	Brique b7("brique1", Box(1, 4), Position(4, 10), dessin2, ba);
	Brique b8("brique1", Box(1, 4), Position(53, 10), dessin2, ba);
	Brique b9("brique", Box(2, 2), Position(20, 10), dessin1, ba);
	Brique b10("brique", Box(2, 2), Position(26, 10), dessin1, ba);
	Brique b11("brique", Box(2, 2), Position(32, 10), dessin1, ba);
	Brique b12("brique", Box(2, 2), Position(38, 10), dessin1, ba);
	Brique b13("brique", Box(4, 1), Position(18, 15), dessin3, ba);
	Brique b14("brique", Box(4, 1), Position(36, 15), dessin3, ba);

	char bound1[31];
	for (int i = 0; i < 31; i++) {
		if (i == 30) bound1[i] = '\0';
		else bound1[i] = 0xDCu;
	}
	char bound2[35];
	for (int i = 0; i < 35; i++) {
		if (i == 34) bound2[i] = '\0';
		else bound2[i] = 0xDEu;
	}
	char bound3[35];
	for (int i = 0; i < 35; i++) {
		if (i == 34) bound2[i] = '\0';
		else bound2[i] = 0xDDu;
	}
	string d1 = bound1;
	string d2 = bound2;
	string d3 = bound3;

	Bound bb1("bound", Box(30, 1), Position(0, 0), d1);
	Bound bb2("bound", Box(1, 34), Position(57, 1), d2);
	Bound bb3("bound", Box(1, 34), Position(0, 1), d2);

	BM.addBody(ba);
	BM.addBody(br);
	BM.addBody(b1); BM.addBody(b2); BM.addBody(b3); BM.addBody(b4); BM.addBody(b5); BM.addBody(b6); BM.addBody(b7); BM.addBody(b8); BM.addBody(b9);
	BM.addBody(b10); BM.addBody(b11); BM.addBody(b12); BM.addBody(b13); BM.addBody(b14);
	BM.addBody(bb1); BM.addBody(bb2); BM.addBody(bb3);
	Body** colliding = nullptr;

	BM.run();


	if (BM.count == 14) c.put_string("GAGNER", 24, 18);
	else c.put_string("PERDRE", 24, 18);

	bool isterminer(Console& c);
	if (isterminer(c))
	{
		c.clear(); c.set_cursor_position(20, 10); cout << "GAME OVER! ";
	}
	else goto loop;
	return 0;
}