#include <iostream>
using namespace std;

// функция, вычисляющая максимальную высоту пирамиду из N кубиков
int max_h(int N)
{
	if (N == 1)
		return 1;

	for (int i = 1; i <= N; i++)
		if (N < i*(i + 1) / 2)
			return --i;
}


int main()
{
	int N;
	cin >> N;

	// проверка для введенного нуля
	if (!N)
	{
		cout << 0;
		return 0;
	}

	// узнаем максимальную высоту пирамиды из N кубиков
	int MaxHeight = max_h(N);

	// создаем мастрицу, в которой будем считать варианты создания пирамиды
	long long ** ArrayOfVariants = new long long *[N];

	int CurIndex = 0;
	for (int j = 2; j <= MaxHeight + 1; j++)
	{
		for (int i = 0; i < j && CurIndex < N; i++, CurIndex++)
		{
			ArrayOfVariants[CurIndex] = new long long[j - 1];
			ArrayOfVariants[CurIndex][0] = 1;
		}
	}

	// заполняем таблицу, учитывая, что Array[i][j] = Array[i - j - 1][j] + Array[i - j-1][j - 1];
	int CurHeight = 0;
	for (int j = 1; j < MaxHeight; j++)
	{
		CurHeight += j + 1;
		for (int i = j + 1; i < N; i++)
		{
			if (CurHeight - (i - j) >= 0)
				ArrayOfVariants[i][j] = ArrayOfVariants[i - j - 1][j - 1];
			else
				ArrayOfVariants[i][j] = ArrayOfVariants[i - j - 1][j] + ArrayOfVariants[i - j - 1][j - 1];
		}
	}
	// таким образом количество вариантов построить пирамидку из N кубиков - это сумма ячеек матрицы N-го столбца

	long long LevelsSum = 0;
	for (int i = 0; i < MaxHeight; i++)
		LevelsSum += ArrayOfVariants[N - 1][i];

	cout << LevelsSum;
	
	for (int i = 0; i < N; i++)
		delete [] ArrayOfVariants[i];
	delete [] ArrayOfVariants;

	return 0;
}