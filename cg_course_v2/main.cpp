#include "../libwinbgi/src/graphics.h"
#include "stdio.h"
#include "piramida.h"
#include "table.h"



int main()
{
	initwindow(1300, 700);
	piramida p1(2, 3, 4, 5, (char*)"A",(char*)"B", (char*)"C", (char*)"D");
	piramida p2(9, 10, 11, 12, (char*)"E", (char*)"F", (char*)"G", (char*)"H");
	table t;
	t.paint();

	p1.scale(0.2, 0.2, 0.2);
	p1.rotate(10, 0);
	p2.scale(0.2, 0.2, 0.2);
	p2.move(400, 100, 0);
	p1.paint();
	p2.paint();

	char sym;
	while (true)
	{
		sym = getch();
		switch (sym)
		{
		case '1':
			p1.moveS(10, 0, 0);
			p2.moveS(10, 0, 0);
			break;
		case '2':
			p1.moveS(-10, 0, 0);
			p2.moveS(-10, 0, 0);
			break;
		case '3':
			p1.moveS(0, 10, 0);
			p2.moveS(0, 10, 0);
			break;
		case '4':
			p1.moveS(0, -10, 0);
			p2.moveS(0, -10, 0);
			break;
		case '5':
			p1.moveS(0, 0, 10);
			p2.moveS(0, 0, 10);
			break;
		case '6':
			p1.moveS(0, 0, -10);
			p2.moveS(0, 0, -10);
			break;

		case 'r':
			p1.rotate(10, 0);
			break;
		case 'f':
			p1.rotate(-10, 0);
			break;
		
		case 't':
			p1.rotate(10, 1);
			break;
		case 'g':
			p1.rotate(-10, 1);
			break;

		case 'c':
			p1.rotate(10, 2);
			break;
		case 'v':
			p1.rotate(-10, 2);
			break;

		case 'z':
			p1.scale(2, 2, 2);
			break;
		case 'x':
			p1.scale(0.5, 0.5, 0.5);
			break;

		case 'w':
			p1.move(0, -10, 0);
			break;
		case 's':
			p1.move(0, 10,0);
			break;
		case 'a':
			p1.move(-10, 0, 0);
			break;
		case 'd':
			p1.move(10, 0, 0);
			break;
		case 'q':
			p1.move(0, 0, 10);
			break;
		case 'e':
			p1.move(0, 0, -10);
			break;
		


		case 'o':
			p2.rotate(10, 0);
			break;
		case 'l':
			p2.rotate(-10, 0);
			break;

		case 'p':
			p2.rotate(10, 1);
			break;
		case ';':
			p2.rotate(-10, 1);
			break;

		case 'm':
			p2.rotate(10, 2);
			break;
		case ',':
			p2.rotate(-10, 2);
			break;

		case 'b':
			p2.scale(2, 2, 2);
			break;
		case 'n':
			p2.scale(0.5, 0.5, 0.5);
			break;

		case 'u':
			p2.move(0, -10, 0);
			break;
		case 'j':
			p2.move(0, 10, 0);
			break;
		case 'h':
			p2.move(-10, 0, 0);
			break;
		case 'k':
			p2.move(10, 0, 0);
			break;
		case 'y':
			p2.move(0, 0, 10);
			break;
		case 'i':
			p2.move(0, 0, -10);
			break;


		case '0':
			closegraph();
			return 0;

		}
		clearviewport();
		t.paint();
		p1.paint();
		p2.paint();

	}
	getch();
	closegraph();
	return 0;
}