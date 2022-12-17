//#include "figure.h"
//#include "polygon.h"
#include "../libwinbgi/src/graphics.h"
#include "stdio.h"
#include "point.h"
#include "tri_plane.h"

#define SHADOW 8
#define V_NUM 4

class piramida
{
	int side_color[4];
	tri_plane* sides[4];
	tri_plane* shadow[4];
	point* A;
	point* B;
	point* C;
	point* D;
	point* S;

	double midX, midY, midZ;

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
		case 3:
			return D;
		}
	}

	void upd_mids()
	{
		midX = 0;
		for (int i = 0; i < V_NUM; i++)
			midX += (*this)[i]->x();
		midX /= 4.0;

		midY = 0;
		for (int i = 0; i < V_NUM; i++)
			midY += (*this)[i]->y();
		midY /= 4.0;

		midZ = 0;
		for (int i = 0; i < V_NUM; i++)
			midZ += (*this)[i]->z();
		midZ /= 4.0;
	}

	void scale_each(double _x, double _y, double _z)
	{
		for (int i = 0; i < V_NUM; i++)
			(*this)[i]->scale(_x, _y, _z);
	}

	void rotate_each(double _phi, int axis)
	{
		for (int i = 0; i < V_NUM; i++)
			(*this)[i]->rotate(_phi, axis);
	}

	void colour(int fill_c, int x_isx, int y_isx)
	{
		if (x_isx == 0 || y_isx == 0)
			return;

		if (getpixel(x_isx, y_isx) != fill_c)
		{
			putpixel(x_isx, y_isx, fill_c);
			colour(fill_c, x_isx + 1, y_isx);
			colour(fill_c, x_isx, y_isx + 1);
			colour(fill_c, x_isx - 1, y_isx);
			colour(fill_c, x_isx, y_isx - 1);
		}
	}

	void project()
	{
		rotate_each(30, X);
	}

	void unproject()
	{
		rotate_each(-30, X);
	}

	void painters_alg()
	{
		upd_sides();

		double midZ[4] = {
			(A->z() + B->z() + C->z()) / 3,
			(A->z() + B->z() + D->z()) / 3,
			(D->z() + B->z() + C->z()) / 3,
			(A->z() + D->z() + C->z()) / 3
		};

		int sorted_idx[4] = { 0, 1, 2, 3 };
		double tmp;
		for (int idx = 0; idx < 4; )
		{
			if ((idx + 1) != 4 && midZ[sorted_idx[idx]] > midZ[sorted_idx[idx + 1]])
			{
				// swap
				tmp = sorted_idx[idx];
				sorted_idx[idx] = sorted_idx[idx + 1];
				sorted_idx[idx + 1] = tmp;
				idx = 0;
			}
			else idx++;
		}


		for (int i = 0; i < 4; i++)
		{
			sides[sorted_idx[i]]->draw(i);
			switch (sorted_idx[i])
			{
			case 0:
				A->printName((A->x() > midX), (A->y() > midY));
				B->printName((B->x() > midX), (B->y() > midY));
				C->printName((C->x() > midX), (C->y() > midY));
				break;
			case 1:
				A->printName((A->x() > midX), (A->y() > midY));
				B->printName((B->x() > midX), (B->y() > midY));
				D->printName((D->x() > midX), (D->y() > midY));
				break;
			case 2:
				C->printName((C->x() > midX), (C->y() > midY));
				B->printName((B->x() > midX), (B->y() > midY));
				D->printName((D->x() > midX), (D->y() > midY));
				break;
			case 3:
				A->printName((A->x() > midX), (A->y() > midY));
				C->printName((C->x() > midX), (C->y() > midY));
				D->printName((D->x() > midX), (D->y() > midY));
				break;
			}
		}

	}

	void upd_sides()
	{
		sides[0]->set(A, B, C);
		sides[1]->set(A, B, D);
		sides[2]->set(D, B, C);
		sides[3]->set(A, D, C);
	}

	void upd_shadow()
	{
		double y = 400;

		double t = (y - A->y()) / (S->y() - A->y());
		double x = (S->x() - A->x()) * t + A->x();
		double z = (S->z() - A->z()) * t + A->z();

		point* A_ = new point; A_->set(x, y, z, 1);

		t = (y - B->y()) / (S->y() - B->y());
		x = (S->x() - B->x()) * t + B->x();
		z = (S->z() - B->z()) * t + B->z();
		point* B_ = new point; B_->set(x, y, z, 1);

		t = (y - C->y()) / (S->y() - C->y());
		x = (S->x() - C->x()) * t + C->x();
		z = (S->z() - C->z()) * t + C->z();
		point* C_ = new point; C_->set(x, y, z, 1);

		t = (y - D->y()) / (S->y() - D->y());
		x = (S->x() - D->x()) * t + D->x();
		z = (S->z() - D->z()) * t + D->z();
		point* D_ = new point; D_->set(x, y, z, 1);

		A_->rotate(30, X);
		B_->rotate(30, X);
		C_->rotate(30, X);
		D_->rotate(30, X);

		shadow[0]->set(A_, B_, C_);
		shadow[1]->set(A_, B_, D_);
		shadow[2]->set(D_, B_, C_);
		shadow[3]->set(A_, D_, C_);

	}


	void draw_shadow()
	{
		upd_shadow();
		for (int i = 0; i < 4; i++)
			shadow[i]->draw(i);
	}

public:

	piramida(int _c0, int _c1, int _c2, int _c3, char* n1, char* n2, char* n3, char* n4)
	{
		midX = midY = midZ = 0;

		side_color[0] = _c0;
		side_color[1] = _c1;
		side_color[2] = _c2;
		side_color[3] = _c3;

		A = new point(n1, _c0);  A->set(0, 300, 0, 1);
		B = new point(n2, _c0);  B->set(300, 10, 200, 1);
		C = new point(n3, _c0);  C->set(500, 350, 400, 1);
		D = new point(n4, _c0);  D->set(300, 150, 0, 1);
		S = new point; S->set(0, 0, 0, 1);

		for (int i = 0; i < 4; i++)
		{
			sides[i] = new tri_plane(side_color[i]);
			shadow[i] = new tri_plane(SHADOW);
		}
	}


	void paint()
	{
		draw_shadow();
		project();
		painters_alg();
		unproject();
	}


	void move(double _x, double _y, double _z)
	{
		for (int i = 0; i < V_NUM; i++)
			(*this)[i]->move_point(_x, _y, _z);
	}

	void scale(double _x, double _y, double _z)
	{
		upd_mids();
		move(-midX, -midY, -midZ);
		scale_each(_x, _y, _z);
		move(midX, midY, midZ);
	}

	void rotate(double _phi, int axis)
	{
		upd_mids();
		move(-midX, -midY, -midZ);
		rotate_each(_phi, axis);
		move(midX, midY, midZ);
	}

	void moveS(double _x, double _y, double _z)
	{
		S->move_point(_x, _y, _z);
	}


};

