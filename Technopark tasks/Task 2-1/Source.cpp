#include <iostream>
#include <vector>
using namespace std;

bool compare(pair <int,int> fPoint, pair <int,int> sPoint)
{
	if (fPoint.first > sPoint.first)
		return true;
	else
		if (fPoint.first < sPoint.first)
			return false;
		
	if (fPoint.second > sPoint.second)
		return true;
	else
		return false;
			
}

void ins_sort(vector <pair<int,int>> &arr)
{
	pair <int,int> temp;
	int j;
	for (int i = 1; i < arr.size(); i++)			
	{
		temp = arr[i];
		for (j = i - 1; j >= 0 && compare(arr[j], temp); --j)		//���� ����� �������� � ������������������
			arr[j + 1] = arr[j];									//�������� ������� ������� ���� �� �� ������� �� ���� �����
		arr[j + 1] = temp;											//��������� �������
	}
}

int main()
{
	int n;
	cin >> n;
	vector <pair<int, int>> array;
	pair <int,int> temp;
	for (int i = 0; i < n; i++)
	{
		cin >> temp.first >> temp.second;
		array.push_back(temp);
	}

	ins_sort(array);

	for (int i = 0; i < array.size(); i++)
		cout << array[i].first<<' '<<array[i].second << endl;
}