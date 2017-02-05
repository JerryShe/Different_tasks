#include <iostream>
#include <stdio.h>
using namespace std;


// функция сравнения для qsort
int comparator(const void *p, const void *q)
{
	pair <long,long> l = *(const pair<long,long> *)p;
	pair <long, long> r = *(const pair<long, long> *)q;
	return (l.first + l.second) - (r.first + r.second);
} 


// класс динамического массива
template  <typename ValueType>  class ExpandingArray
{
private:
	ValueType *Array = NULL;						// массив необходимого типа
	int Len = 0;									// его длинна
	const int ExpandRate = 2;						// коэффициент расширения
	int ElemIndex = 0;								// индекс для вставки в конец массива

public:

	ExpandingArray(const int _size = 2)
	{
		Array = new ValueType[_size];
		Len = _size;
	}

	~ExpandingArray()
	{
		delete[] Array;
	}

	int size()
	{
		return ElemIndex;
	}

	// функция добавления необходимого числа элементов в правую часть массива
	int expand_right(int _expand_len = -1)					
	{
		if (_expand_len == -1)
			_expand_len = Len / ExpandRate;
		ValueType *new_array = new ValueType[Len + _expand_len];

		for (int i = 0; i < Len; i++)
			new_array[i] = Array[i];
		//for (int i = Len; i < Len + _expand_len; i++)
			//new_array[i] = 0;

		Len += _expand_len;

		delete[] Array;
		Array = new_array;
		return _expand_len;
	}

	// функция вставки элемента в конец массива
	void push_back(const ValueType _elem)
	{
		if (ElemIndex == Len)
			this->expand_right();
		Array[ElemIndex++] = _elem;
	}

	// функция сортировки элементов в массиве
	void sort()
	{
		qsort(Array, ElemIndex, sizeof(ValueType), comparator);
	}

	ValueType &operator[] (const int _index)
	{
		return Array[_index];
	}
};


int main() 
{
	ExpandingArray <pair <long, long>> ArrayOfMassAndPowers;
	long m = 0, p = 0;
	while (scanf("%ld %ld", &m, &p) == 2)
		ArrayOfMassAndPowers.push_back(pair<long, long> (m, p));

	ArrayOfMassAndPowers.sort();

	int CurrentMass = ArrayOfMassAndPowers[0].first, MaxHeight = 1;

	for (int i = 1; i < ArrayOfMassAndPowers.size(); i++) {
		if (ArrayOfMassAndPowers[i].second >= CurrentMass) {
			CurrentMass += ArrayOfMassAndPowers[i].first;
			MaxHeight++;
		}
	}
	cout << MaxHeight;
	
	return 0;
}
