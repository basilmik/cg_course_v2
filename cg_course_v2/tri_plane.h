#pragma once
#include "point.h"
#include "stdio.h"
#include "math.h"
#include "../libwinbgi/src/graphics.h"

class tri_plane
{
	point* A, * B, * C;

	int fill_color;

	void color(float _xs, float _ys, float _x2, float _y2, float _x3, float _y3, int color, int _i)
	{
		setcolor(color);
		float xs = 0, ys = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;
		if (_x2 <= _x3)
		{
			if (_xs <= _x2) // xs x2 x3
			{
				xs = _xs; ys = _ys; x2 = _x2;  y2 = _y2; x3 = _x3;  y3 = _y3;
			}
			else
				if (_xs <= _x3) // x2 xs x3
				{
					xs = _x2; ys = _y2; x2 = _xs;  y2 = _ys; x3 = _x3;  y3 = _y3;
				}
				else // x2 x3 xs
				{
					xs = _x2; ys = _y2; x2 = _x3;  y2 = _y3; x3 = _xs;  y3 = _ys;
				}
		}
		else // x3 x2
		{
			if (_xs <= _x3) // xs x3 x2
			{
				xs = _xs; ys = _ys; x2 = _x3;  y2 = _y3; x3 = _x2;  y3 = _y2;
			}
			else
				if (_xs <= _x2) // x3 xs x2
				{
					xs = _x3; ys = _y3; x2 = _xs;  y2 = _ys; x3 = _x2;  y3 = _y2;
				}
				else  // x3 x2 xs
				{
					xs = _x3; ys = _y3; x2 = _x2;  y2 = _y2; x3 = _xs;  y3 = _ys;
				}
		}


		float y1d, y2d;
		float point = xs--;
		point = ceil(point);
		float k1 = ((x2 <= x3 ? y2 : y3) - ys) / ((x2 <= x3 ? x2 : x3) - xs),
			k2 = ((x2 > x3 ? y2 : y3) - ys) / ((x2 > x3 ? x2 : x3) - xs);
		float b1 = (ys - k1 * xs),
			b2 = (ys - k2 * xs);

		while (point <= (x2 < x3 ? x2 : x3))
		{
			y1d = k1 * point + b1;
			if (point == round(xs))
				y1d = ys;

			y2d = k2 * point + b2;

			line(point, ceil(y1d), point, ceil(y2d));
			point++;
		}

		if (x2 != x3)
		{
			k1 = ((x2 >= x3 ? y2 : y3) - (x2 <= x3 ? y2 : y3)) / ((x2 >= x3 ? x2 : x3) - (x2 <= x3 ? x2 : x3));
			b1 = ((x2 < x3 ? y2 : y3) - k1 * (x2 < x3 ? x2 : x3));

			while (point <= (x2 > x3 ? x2 : x3))
			{
				y1d = k1 * (point)+b1;
				if (point == round(xs)) y1d = ys;

				y2d = k2 * point + b2;

				line((point), ceil(y1d), (point), ceil(y2d));
				point++;
			}
		}
	}


public:

	void print()
	{
		printf("A->x(), A->y(), B->x(), B->y(), C->x(), C->y()\n%f %f %f %f %f %f\n", A->x(), A->y(), B->x(), B->y(), C->x(), C->y());
	}

	point* get(int i)
	{
		switch (i)
		{
		case 0:
			return A;
		case 1:
			return B;
		case 2:
			return C;
		}
	}

	tri_plane(int fc) {
		A = new point;
		B = new point;
		C = new point;

		fill_color = fc;
	}

	void set(point* p1, point* p2, point* p3) {
		A = p1;
		B = p2;
		C = p3;
	}


	int midX() {
		int sum = 0;
		for (int i = 0; i < 3; i++)
			sum += get(i)->x();

		return (sum / 3);
	}

	int midY() {
		int sum = 0;
		for (int i = 0; i < 3; i++)
			sum += get(i)->y();

		return (sum / 3);
	}

	point* operator[](int i)
	{
		switch (i)
		{
		case 0:
			return A;
		case 1:
			return B;
		case 2:
			return C;

		}
	}

	void lineDraw()
	{
		int x1, x2, y1, y2;
		int next_i = 1;
		for (int i = 0; i < 3; i++)
		{
			if (next_i == 3)
				next_i = 0;

			x1 = (*this)[i]->x();
			y1 = (*this)[i]->y();
			x2 = (*this)[next_i]->x();
			y2 = (*this)[next_i]->y();

			line(x1, y1, x2, y2);

			next_i++;
		}
	}

	void draw(int _i)
	{
		color(A->x(), A->y(), B->x(), B->y(), C->x(), C->y(), fill_color, _i);
	}

};
