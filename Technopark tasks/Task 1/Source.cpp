#include <iostream>
#include <math.h>
using namespace std;


int main()
{
	int input;
	cin>>input;

	int num = 2;
	while (num <= sqrt(input))
	{
		
		if (input%num == 0)
		{
			input /= num;
			cout << num << ' ';
		}
		else 
			num++;
	}

	if (input != 1)
		cout << input << ' ';

	return 0;
}