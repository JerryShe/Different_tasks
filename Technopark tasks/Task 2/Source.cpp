#include <cmath> // для gcc
#include <iostream>
using namespace std;

int main()
{
	int quan;
	cin >> quan;

	int zero_point_X, zero_point_Y;
	int point_X, point_Y;
	int prev_point_X, prev_point_Y;

	cin >> zero_point_X >> zero_point_Y;

	prev_point_X = zero_point_X;
	prev_point_Y = zero_point_Y;

	double area = 0;
	for (int i = 1; i < quan; i++)
	{
		cin >> point_X >> point_Y;
		area += (point_X + prev_point_X) * (point_Y - prev_point_Y);
		prev_point_X = point_X;
		prev_point_Y = point_Y;
	}

	area += (zero_point_X + prev_point_X) * (zero_point_Y - prev_point_Y);
	area = abs(area) / 2;
	cout << area;

	return 0;
}