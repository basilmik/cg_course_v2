#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "stdio.h"
#include "math.h"
#include "../libwinbgi/src/graphics.h"

#define X 0
#define Y 1
#define Z 2
#define W 3

class point
{
	double cor[4];
	char* name;
	int c;

	double* multiply(double _m[4][4])
	{
		double x = cor[X];
		double y = cor[Y];
		double z = cor[Z];
		double w = cor[W];
		double cpy[4] = { x, y, z, w };
		double res[4] = { 0,0,0,0 };

		res[X] = cpy[0] * _m[0][0] + cpy[1] * _m[1][0] + cpy[2] * _m[2][0] + cpy[3] * _m[3][0];
		res[Y] = cpy[0] * _m[0][1] + cpy[1] * _m[1][1] + cpy[2] * _m[2][1] + cpy[3] * _m[3][1];
		res[Z] = cpy[0] * _m[0][2] + cpy[1] * _m[1][2] + cpy[2] * _m[2][2] + cpy[3] * _m[3][2];
		res[W] = cpy[0] * _m[0][3] + cpy[1] * _m[1][3] + cpy[2] * _m[2][3] + cpy[3] * _m[3][3];

		cor[X] = res[X];
		cor[Y] = res[Y];
		cor[Z] = res[Z];
		cor[W] = res[W];
		return res;
	}

	void rotateX(double _phi) {
		_phi = _phi * 3.1415 / 180;

		double matrix[4][4] = {
			1, 0, 0, 0,
			0, cos(_phi), -sin(_phi), 0,
			0, sin(_phi), cos(_phi),
			0, 0, 0, 0, 1 };
		multiply(matrix);
	}

	void rotateY(double _phi) {
		_phi = _phi * 3.1415 / 180;

		double matrix[4][4] = {
			cos(_phi), 0, -sin(_phi), 0,
			0, 1, 0, 0,
			sin(_phi), 0, cos(_phi), 0,
			0, 0, 0, 1 };
		multiply(matrix);
	}

	void rotateZ(double _phi) {
		_phi = _phi * 3.1415 / 180;

		double matrix[4][4] = {
			cos(_phi), -sin(_phi), 0, 0,
			sin(_phi), cos(_phi), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };
		multiply(matrix);
	}

public:
	point()
	{
	}

	point(char* _name, int _c)
	{
		name = _name;
		c = _c;
	}

	void print()
	{
		printf("%f %f %f\n", cor[0], cor[1], cor[2]);
	}

	void set(double x, double y, double z, double w)
	{
		cor[X] = x;
		cor[Y] = y;
		cor[Z] = z;
		cor[W] = w;
	}

	void move_point(double _x, double _y, double _z)
	{
		double matrix[4][4] = {
			1,  0,  0,  0,
			0,  1,  0,  0,
			0,  0,  1,  0,
			_x, _y, _z, 1 };

		multiply(matrix);
	}

	void scale(double _x, double _y, double _z) {
		double matrix[4][4] = {
			_x, 0, 0, 0,
			0, _y, 0, 0,
			0, 0, _z, 0,
			0, 0, 0, 1 };

		multiply(matrix);
	}

	void rotate(double _phi, int _axis) {
		if (_axis == X)
			rotateX(_phi);
		if (_axis == Y)
			rotateY(_phi);
		if (_axis == Z)
			rotateZ(_phi);
	}

	void printName(bool plusX, bool plusY) {
		char message[128];
		setcolor(c);

		sprintf_s(message, "%c", *name);
		int dx = 0;
		if (plusX)
			dx = 25;
		else
			dx = -25;
		int dy = 0;
		if (plusY)
			dy = 25;
		else
			dy = -25;

		outtextxy(x() + dx, y() + dy, message);
	}

	double x() {
		return cor[X];
	}
	void x(double _x) {
		cor[X] = _x;
	}
	double y() {
		return cor[Y];
	}
	void y(double _y) {
		cor[Y] = _y;
	}
	double z() {
		return cor[Z];
	}
	void z(double _z) {
		cor[Z] = _z;
	}
};
