#include <iostream>
#include <vector>
using namespace std;




struct Node {
	long long value;
	long long index;
	Node() : value(0), index(0) {}
	Node(int val, int indx) : value(val), index(indx) {}

	bool operator<(const Node& node) 
	{
		return value < node.value;
	}
};


class Heap
{
public:
	Heap(int heapSize);
	~Heap() {}

	Node getMax() const;				//просмотр макс значения
	Node extractMax();					//извлечение максимума
	void add(Node value);				//добавление элемента в кучу
	bool isEmpty() const;						//проверка кучи на пустоту
	void blockStep(int indx);			//проверка кучи на элементы с устаревшими индексами

private:
	vector<Node> heap;					//куча
	int heapSize;						//размер кучи
	int blockSize;							//размер буффера

	int parent(int i);				//получения индекса родителя в массиве
	int	left(int i);				//получения индекса левого ребенка в массиве
	int	right(int i);				//получения индекса правого ребенка в массиве
	void heapify(int num = 1);		//функция для восстановления основного свойства кучи


};


Heap::Heap(int heapSize)
{
	if (heapSize <= 8)
		heapSize = 8;
	heap.resize(heapSize + 1);
	blockSize = heapSize + 1;
	this->heapSize = 0;
}

Node Heap::getMax() const
{
	return heap[1];
}

Node Heap::extractMax()
{
	if (isEmpty())
		return Node();
	Node temp = heap[1];
	heap[1] = heap[heapSize];
	heap[heapSize] = Node();
	heapify();
	return temp;
}

void Heap::add(Node value)
{
	if ((heapSize + 1) == blockSize)
	{
		heap.resize(blockSize * 2);
		blockSize *= 2;
	}
	heapSize++;
	int index = heapSize;
	while (index > 1 && heap[parent(index)] < value)
	{
		heap[index] = heap[parent(index)];
		index = parent(index);
	}
	heap[index] = value;
}

void Heap::heapify(int num)
{
	int l = left(num);
	int r = right(num), largest = 0;
	if (l <= heapSize && heap[num].value < heap[l].value)
		largest = l;
	else
		largest = num;

	if (r <= heapSize && heap[largest] < heap[r])
		largest = r;
	if (largest != num)
	{
		swap(heap[num], heap[largest]);
		heapify(largest);
	}
}

bool Heap::isEmpty() const
{
	return heapSize == 0;
}


void Heap::blockStep(int indx)
{
	while (getMax().index < indx)
		extractMax();
}


int Heap::parent(int i)
{
	if (heapSize <= 0)
		return 0;
	else
		return i / 2;
}


int Heap::left(int i)
{
	if (i == 0)
		return 2;
	return 2 * i;
}


int Heap::right(int i)
{
	if (i == 0)
		return 3;

	return 2 * i + 1;
}


int main(void) {
	int size = 0, block = 0, value = 0;
	vector<int> vector;
	Node maxValue;

	cin >> size;									//считываем длину массива
	if (size <= 0)
		return 0;

	for (size_t i = 0; i < size; ++i)
	{
		cin >> value;								//считываем массив
		vector.push_back(value);
	}

	cin >> block;									//считываем размер "окна"
	if (block <= 0)
		return 0;

	Heap heap = Heap(block);


	for (size_t i = 0; i < block; ++i)
		heap.add(Node(vector[i], i));				//добавляем первые k элементов в кучу

	maxValue = heap.getMax();
	cout << maxValue.value << ' ';
	for (size_t i = block; i < size; ++i)
	{

		heap.add(Node(vector[i], i));				//добавляем новый элемент в кучу
		heap.blockStep(i - block + 1);				//проверка и удаление элементов с неактуальным индексом(за пределами "окна") 
		maxValue = heap.getMax();

		cout << maxValue.value << ' ';
	}


	return 0;

}
