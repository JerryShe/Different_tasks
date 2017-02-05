#include <iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;
	int * Array_Of_Numbers = new int[N];

	// �� ������� � ������������� ������� ����� 
	int size = (N / (log(N) - 1.2));								
	int * Array_Of_Prime_Numbers = new int[size];	
	// ������� ������ ������� �������
	int index = 0;													

	for (int k = 0; k < N; k++)
		Array_Of_Numbers[k] = 0;
	for (int k = 0; k < size; k++)
		Array_Of_Prime_Numbers[k] = 0;
	

	// ����� ������� ������� A[i] - ��� ����������� ������� �������� ����� i
	for (int i = 2; i < N; i++)
	{
		// ���� A[i] == 0, �� � ���� �� ���� ������� ���������, � ��� ��� �� ��� ������� � 2 �� i, �� � ���� ��� ������������� ���������
		if (Array_Of_Numbers[i] == 0)								
		{
			Array_Of_Numbers[i] = i;
			// ������� �������� ����� � ������ ������� ����� 
			Array_Of_Prime_Numbers[index++] = i;					
			if (index > size)
				return 1;											
		}
		// ����� �� ������� ����� ����� ����������� ����� d = a * p, ��� p - ����������� ������� �������� b � ����� �������� a >= p
		// �.�. �� ����� � ������ �� ����� ������� ������� B[j] � �������� �� i ���� B[j] <= ������������ �������� �������� i
		for (int j = 0; (j < index) && (i*Array_Of_Prime_Numbers[j]) < N; j++)							
		{													
			// ����� A[i] - ��� p, � a - ��� B[]*(i/A[i])
			// ����� ����� d = B[]*i/A[i]*A[i] = B[]*i
			if (Array_Of_Prime_Numbers[j] > Array_Of_Numbers[i])										
				break;									
			// ����������, ������� ������� ����� �������, �� ����� �� ������ ���� ���������� �������� ����� 0 ��� �� ����������� ������� ���������
			// � ��� �� ������������ ���������� ��� ������� ����� ������ ��������� N
			Array_Of_Numbers[i * Array_Of_Prime_Numbers[j]] = Array_Of_Prime_Numbers[j];				
		}																								

	}
	for (int i = 0; i < index && index < size; i++)														
		cout << Array_Of_Prime_Numbers[i] << ' ';														
																										
	delete [] Array_Of_Numbers;
	delete [] Array_Of_Prime_Numbers;

	return 0;
}