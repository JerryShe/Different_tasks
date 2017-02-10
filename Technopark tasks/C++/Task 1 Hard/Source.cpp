#include <iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;
	int * Array_Of_Numbers = new int[N];

	// из теоремы о распределении простых чисел 
	int size = (N / (log(N) - 1.2));								
	int * Array_Of_Prime_Numbers = new int[size];	
	// текущий индекс массива простых
	int index = 0;													

	for (int k = 0; k < N; k++)
		Array_Of_Numbers[k] = 0;
	for (int k = 0; k < size; k++)
		Array_Of_Prime_Numbers[k] = 0;
	

	// здесь элемент массива A[i] - это минимальный простой делитель числа i
	for (int i = 2; i < N; i++)
	{
		// если A[i] == 0, то у него не было найдено делителей, а так как мы шли начиная с 2 до i, то у него нет нетривиальных делителей
		if (Array_Of_Numbers[i] == 0)								
		{
			Array_Of_Numbers[i] = i;
			// заносим найденое число в массив простых чисел 
			Array_Of_Prime_Numbers[index++] = i;					
			if (index > size)
				return 1;											
		}
		// любое не простое число можно представить ввиде d = a * p, где p - минимальный простой делитель b и любой делитель a >= p
		// т.е. мы берем и каждое из чисел массива простых B[j] и умножаем на i пока B[j] <= минимального простого делителя i
		for (int j = 0; (j < index) && (i*Array_Of_Prime_Numbers[j]) < N; j++)							
		{													
			// здесь A[i] - это p, а a - это B[]*(i/A[i])
			// тогда число d = B[]*i/A[i]*A[i] = B[]*i
			if (Array_Of_Prime_Numbers[j] > Array_Of_Numbers[i])										
				break;									
			// получается, проходя массивы таким образом, мы ровно по одному разу записываем значения ячеек 0 или их минимальным простым делителем
			// а так же одновременно запоминаем все простые числа меньше заданного N
			Array_Of_Numbers[i * Array_Of_Prime_Numbers[j]] = Array_Of_Prime_Numbers[j];				
		}																								

	}
	for (int i = 0; i < index && index < size; i++)														
		cout << Array_Of_Prime_Numbers[i] << ' ';														
																										
	delete [] Array_Of_Numbers;
	delete [] Array_Of_Prime_Numbers;

	return 0;
}