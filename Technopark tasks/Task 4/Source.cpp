#include <iostream>
using namespace std;

// шаблонный класс динамического массива
template  <typename ValueType>  class ExpandingArray
{
private:

	// массив необходимого типа
	ValueType *Array = NULL;	
	// длинна массива
	int Length = 0;			
	// коэффициент расширения массива Len += Len/ExpandRate;
	int ExpandRate = 2;								

public:

	ExpandingArray(const int _size = 2)				
	{
		Array = new ValueType[_size];
		Length = _size;
	}

	~ExpandingArray()
	{
		delete[] Array;
	}

	int size() const
	{
		return Length;
	}

	// функция добавления необходимого числа элементов в правую часть массива
	int expand_left(int _expand_len = -1)					
	{
		if (_expand_len == -1)
			_expand_len = Length / ExpandRate;
		ValueType *new_array = new ValueType[Length + _expand_len];

		for (int i = 0; i < _expand_len; i++)
			new_array[i] = 0;
		for (int i = _expand_len; i < Length + _expand_len; i++)
			new_array[i] = Array[i-_expand_len];
		
		Length += _expand_len;

		delete[] Array;
		Array = new_array;

		return _expand_len;
	}

	// функция добавления необходимого числа элементов в левую часть массива
	int expand_right(int _expand_len = -1)				
	{
		if (_expand_len == -1)
			_expand_len = Length / ExpandRate;
		ValueType *new_array = new ValueType[Length + _expand_len];

		for (int i = 0; i < Length; i++)
			new_array[i] = Array[i];
		for (int i = Length; i < Length + _expand_len; i++)
			new_array[i] = 0;
		
		Length += _expand_len;

		delete [] Array;
		Array = new_array;		
		return _expand_len;
	}

	// функция добавления необходимого числа элементов начиная с указанного индекса массива
	int expand_mid(const int _pos, int _expand_len = -1)							
	{
		if (_expand_len == -1)
			_expand_len = Length / ExpandRate;

		ValueType *new_array = new ValueType[Length + _expand_len];

		for (int i = 0; i < _pos; i++)
			new_array[i] = Array[i];
		for (int i = _pos; i < _pos + _expand_len; i++)
			new_array[i] = 0;
		for (int i = _pos + _expand_len; i < Length + _expand_len; i++)
			new_array[i] = Array[i - _expand_len];

		Length += _expand_len;

		delete[] Array;
		Array = new_array;

		return _expand_len;
	}

	ValueType &operator[] (const int _index) 
	{
		return Array[_index];
	}

	friend ostream& operator << (std::ostream &_s, ExpandingArray _massive)
	{
		for (int i = 0; i < _massive.Length; i++)
			_s << _massive[i] << ' ';
		_s << endl;
		return _s;
	}
};


// класс дека, фронт пишется влево, бэк вправо
class cycle_deq
{
	ExpandingArray <int> queue;
	// индекс элемента массива, куда мы запишем следующий элемент, пришедший в конец очереди
	int Back;			
	// индекс элемента массива, куда мы запишем следующий элемент, пришедший в начало очереди
	int Front;					
	// Переменная, показывающая текущий принцип записи в очередь, 0 - если прямой порядок, 1, если обратный порядок записи, т.е. фронт начал писаться в свободное место в начале массива, или бэк - в конец массива
	bool Points_placement = false;				

public:
	
	cycle_deq()
	{
		Front = 1;
		Back = 0;
	};

	~cycle_deq()
	{
		//для удаления динамического массива в классе ExpandingArray
		//queue.ExpandingArray_destr();			
	}

	void push_front(const int i);
	int pop_front();
	void push_back(const int i);
	int pop_back();

	//функция вывода дека в консоль для ручной отладки
	void print()								
	{
		cout << endl << Front << ' ' << Back << ' ' << queue.size() << endl;
		cout << queue;
	}
};


void cycle_deq::push_front(const int _elem)
{
	if (!Points_placement)
		// порядок записи стандартный, место в массиве еще есть, просто добавляем элемент
		if (Front < queue.size())			
			queue[Front++] = _elem;
		else
			// порядок записи стандартный, места в левой части массива нет, а в правой есть, начинаеем записывать начало очереди в левую часть массива
			if (Back != -1)					
			{
				Points_placement = true;
				Front = 1;				
				queue[0] = _elem;
			}
			// порядок записи стандартный, а места ни слева, ни справа не осталось, расширяем массив справа
			else								
			{
				queue.expand_right();
				queue[Front++] = _elem;
			}

	else				
		// порядок записи обратный, место между началом и концом очереди еще есть, просто записываем элемент
		if (Front <= Back)
			queue[Front++] = _elem;
		// порядок записи обратный, а места не осталось, расширяем массив между началом и концом очереди
		else									
		{
			Back += queue.expand_mid(Front);
			queue[Front++] = _elem;
		}
}


void cycle_deq::push_back(const int _elem)
{
	if (!Points_placement)
		if (Back != -1)		
			// порядок записи стандартный, место в массиве еще есть, просто добавляем элемент
			queue[Back--] = _elem;
		else
			// порядок записи стандартный, места в правой части массива нет, а в левой есть, начинаеем записывать конец очереди в правую часть массива
			if (Front != queue.size())		
			{
				Points_placement = true;
				Back = queue.size() - 1;
				queue[Back--] = _elem;
			}
			// порядок записи стандартный, а места ни слева, ни справа массива не осталось, расширяем массив слева
			else								
			{
				int l = queue.expand_left();
				queue[l - 1] = _elem;
				Front += l;
				Back += l - 1;
			}
	else		
		// порядок записи обратный, место между началом и концом очереди еще есть, просто записываем элемент
		if (Back >= Front)
			queue[Back--] = _elem;
		// порядок записи обратный, а места не осталось, расширяем массив между началом и концом очереди
		else									
		{
			Back += queue.expand_mid(Back + 1);
			queue[Back--] = _elem;
		}
}


int cycle_deq::pop_front()
{
	if (!Points_placement)
		// если выполняется это условие, значит очередь пуста
		if (Front == Back + 1)				
			return -1;
		else
			// порядок записи стандартный, достаем элемент из начала очереди
			return queue[--Front];				
	else
	{
		// если начало очереди слева, а конец - справа, то очередь пуста
		if (Front == 0 && Back == queue.size() - 1)		
			return -1;
		// порядок записи обратный, и все элементы начала очереди из левой части массива уже вынуты, переходим к правой части массива
		if (!Front)							
		{
			Points_placement = false;
			Front = queue.size() - 1;
			return queue[Front];
		}
		// порядок записи обратный, в левой части массива еще есть элементы из начала очереди, выводим их
		else									
			return queue[--Front];
	}
}


int cycle_deq::pop_back()
{
	if (!Points_placement)
		// если выполняется это условие, значит очередь пуста
		if (Front == Back + 1)				
			return -1;
		else
			// порядок записи стандартный, достаем элемент из конца очереди
			return queue[++Back];				
	else
	{
		// если начало очереди слева, а конец - справа, то очередь пуста
		if (Front == 0 && Back == queue.size() - 1)		
			return -1;
		// порядок записи обратный, и все элементы конца очереди из правой части массива уже вынуты, переходим к левой части массива
		if (Back == queue.size() - 1)		
		{
			Points_placement = false;
			Back = 0;
			return queue[Back];
		}
		// порядок записи обратный, в правой части массива еще есть элементы из конца очереди, выводим их
		else									
			return queue[++Back];
	}
}



int main()
{
	int Size;
	cin >> Size;

	int commands;
	int numbers;

	//для ручной отладки, 0 - без вывода дека в консоль после операций, 1 - с выводом
	const bool mode = false;						
	bool answer = true;

	cycle_deq deq;
	
	// 1 - push front
	// 2 - pop front
	// 3 - push back
	// 4 - pop back	

	for (int i = 0; i < Size; i++)
	{
		cin >> commands >> numbers;
		switch (commands)
		{
		case 1:
		{
			deq.push_front(numbers);

			if (mode)
				deq.print();

			break;
		}


		case 2:
		{
			if (deq.pop_front() != numbers)
				answer = false;

			if (mode)
			{
				deq.print();
				if (!answer)
				{
					cout << "NO";
					return 0;
				}
			}
			break;
		}


		case 3:
		{
			deq.push_back(numbers);

			if (mode)
				deq.print();

			break;
		}


		case 4:
		{
			if (deq.pop_back() != numbers)
				answer = false;

			if (mode)
			{
				deq.print();
				if (!answer)
				{
					cout << "NO";
					return 0;
				}
			}

			break;
		}
		default:
			break;
		}
	}

	if (answer)
		cout << "YES";
	else
		cout << "NO";
	
	return 0;
}

