#include <iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;
	int *mass = new int[N];

	for (int i = 0; i < N; i++)
		cin >> mass[i];


	//будем считать, что наш массив это направленный граф
	int f_pos = mass[N - 1];					//указатель на текущее положение в графе
	for (int i = 0; i < N; i++)
		f_pos = mass[f_pos];					//таким образом заходим в цикл в графе

	//находим длинну этого цикла
	int s_pos = f_pos,
		cycle_len = 0;
	do
	{
		cycle_len++;
		f_pos = mass[f_pos];
	} while (f_pos != s_pos);

	//делаем cycle_len шагов первым указателем
	s_pos = f_pos = mass[N - 1];
	for (int i = 0; i < cycle_len; i++)
		f_pos = mass[f_pos];

	//теперь шагаем двумя одновременно пока они не совпадут
	while (f_pos != s_pos)
	{
		f_pos = mass[f_pos];
		s_pos = mass[s_pos];
	}

	//точка, в которую мы пришли и есть один из повторяющихся элементов
	cout << f_pos;

	delete[] mass;
}