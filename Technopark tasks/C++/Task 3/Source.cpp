#include <iostream>
using namespace std;

int bin_search(const int *array, const int num, int mass_size)
{
	int mid_pointer, left_pointer = 0;
	int right_pointer = mass_size - 1;
	while (right_pointer > left_pointer)
	{
		if (right_pointer - left_pointer == 1)
		{
			if (array[left_pointer] >= num)
				return left_pointer;
			else
				if (array[right_pointer] >= num)
					return right_pointer;
				else return mass_size;
		}
		mid_pointer = int(float(right_pointer + left_pointer) / 2 + 0.5);
		if (array[mid_pointer] < num)
			left_pointer = mid_pointer;
		else
			right_pointer = mid_pointer;
	}
	return mid_pointer;
}

int main()
{
	int n, m, B;
	cin >> n >> m;
	int *A = new int[n];

	for (int i = 0; i < n; i++)
		cin >> A[i];
	for (int i = 0; i < m; i++)
	{
		cin >> B;
		cout << bin_search(A, B, n) << ' ';
	}

	delete[] A;
	return 0;
}
