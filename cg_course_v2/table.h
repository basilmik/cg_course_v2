#pragma once
#include "point.h"
#include "stdio.h"
#include "math.h"
#include "../libwinbgi/src/graphics.h"

class table
{
	point* A, *B, *C, *D;


	void color_quad()
	{
		
		float k1 = (D->y() - A->y()) / (D->x() - A->x());
		float b1 = k1 * A->x() - A->y();

		float z1 = k1 * D->x() - b1;
		float z2 = k1 * A->x() - b1;
		int xd = D->x() - A->x();

		for (int x = D->x(); x < C->x(); x++)
		{
			if ((int)x % 1 == 0 && (int)x % 3 == 0 && (int)x % 5 == 0)
			{
				if ((int)x % 2 == 0 && (int)x % 4 == 0)
					setcolor(6);
				else
					setcolor(8);
				line(x, z1, x - xd, z2);
			}
		}
	}

	
public:
	
	table()
	{
		A = new point; 
		A->set(-100, 400, -400, 1);
		A->rotate(35, X);
		A->rotate(-35, Y);

		B = new point; 
		B->set(1200, 400, -400, 1);
		B->rotate(35, X);
		B->rotate(-35, Y);

		C = new point; 
		C->set(1200, 400, 500, 1);		
		C->rotate(35, X);
		C->rotate(-35, Y);

		D = new point;
		D->set(-100, 400, 500, 1);		
		D->rotate(35, X);
		D->rotate(-35, Y);

	}


	void paint()
	{
		color_quad();
		
	}

};