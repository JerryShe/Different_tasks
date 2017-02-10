#include <iostream>
#include <vector>
using namespace std;

bool compare(pair <int, int> fPair, pair <int, int> sPair)
{
	if (fPair.second > sPair.second)
		return true;
	if (fPair.second < sPair.second)
		return false;

	if (fPair.first > sPair.first)
		return false;
		
	return true;
}


void swap(pair <int,int> &n1, pair <int,int> &n2)
{
	pair <int,int> temp = n1;
	n1 = n2;
	n2 = temp;
}

void siftDown(vector <pair<int,int>> &numbers, int root, int bottom) 
{
	int done, maxChild;
	done = 0;
	while ((root * 2 <= bottom) && (!done)) 
	{
		if (root * 2 == bottom)
			maxChild = root * 2;
		else 
			if (compare (numbers[root * 2], numbers[root * 2 + 1]))
				maxChild = root * 2;
			else
				maxChild = root * 2 + 1;
		if (!compare (numbers[root], numbers[maxChild])) 
		{
			swap (numbers[root], numbers[maxChild]);
			root = maxChild;
		}
		else
			done = 1;
	}
}

void heapSort(vector <pair<int,int>> &numbers) 
{
	for (int i = (numbers.size() / 2 + 1) - 1; i >= 0; i--)
		siftDown(numbers, i, numbers.size() - 1);
	for (int i = numbers.size() - 1; i >= 1; i--) 
	{
		swap (numbers[0], numbers[i]);
		siftDown(numbers, 0, i - 1);
	}
}


int main()
{
	int n;
	cin >> n;

	pair <int, int> temp;
	vector <pair<int, int>> array;

	for (int i = 0; i < n; ++i)
	{
		cin>>temp.first>>temp.second;
		array.push_back(temp);
	}

	if (n == 1)
	{
		cout << 2;
		return 0;
	}
	
	heapSort(array);

	int curr = array[0].second;
	int last = array[0].second - 1;
	int count = 2;

	for (int i = 1; i < n; i++)
	{
		if (array[i].first > curr)
		{
			count += 2;
			last = array[i].second - 1;
			curr = array[i].second;
			
		}
		else if (array[i].first > last)
		{
			count++;
			last = curr;
			curr = array[i].second;
		}		
	}

	cout << count;


	return 0;
}
