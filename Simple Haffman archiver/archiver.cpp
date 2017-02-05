#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <ctime>
using namespace std;


//���������� ������
//error = 1 - error in open file
// = 2 - Error in creating output file
// = 3 - Incorrect input file's format
void StopProgram(int error, bool program_mode)
{
	if (program_mode)
	{
		switch (error)
		{
		case 0:
			cout << endl << "Done!" << endl;
			break;
		case 1:
			cout << "Error in open file" << endl;
			break;
		case 2:
			cout << "Error creating output file" << endl;
			break;
		case 3:
			cout << endl << "Incorrect format!" << endl;
			break;
		}
		
		char st;
		cout << endl << "Exit y/n ?" << endl;
		cin >> st;
		if (st == 'y')
			exit(0);
		cout << endl << "---------------------------------------------------------------------" << endl << endl;
	}
	else
		exit(error);
}

//������� ��������� ��� ���������� ������� �������� pair
bool pairCompare(const pair<unsigned char, long> firstElem, const pair<unsigned char, long> secondElem)
{
	return firstElem.second < secondElem.second;
}

//��������� ��������� ������
struct tree
{
	unsigned char inf;			//��� �����
	unsigned long quan;			//����������� ���������� �����
	tree *left, *right;

	//���������� ������ �������� ������
	tree add(tree* l, tree* r)	
	{
		this->quan = (*l).quan + (*r).quan;		
		this->left = l;
		this->right = r;		
		return *this;
	}

	tree() :	inf(0), quan(0), left(NULL), right(NULL)
	{}

	tree(pair <unsigned char,long> inf) :	quan(inf.second), inf(inf.first), left(NULL), right(NULL)
	{}
};

//������� ������� ��������� ������
void Free(tree *&root)
{
	if (root->left)
		Free(root->left);

	if (root->right)
		Free(root->right);

	delete root;
}

//��� ������ ������������ �������
class tree_ptr_compare
{
	public:
		bool operator() (const tree* const  &a, const tree* const  &b) {
			return a->quan > b->quan;
	}
};

//����� ������ ��� ���������� ������� �������
void generate_code_table(tree *tree, string code[], string s)
{
	if (tree->left == NULL && tree->right == NULL)
		code[tree->inf] = s;
	else
	{
		generate_code_table(tree->left, code, s.append("0"));	//���������� �� ������ �������, �������� � ������ "0"
		s.erase(s.end() - 1);
		generate_code_table(tree->right, code, s.append("1"));	//���������� �� �������, �������� "1"
		s.erase(s.end() - 1);
	}
}

//��������� ������ �������� � �������� ������� �������
tree* create_Haffman_tree(vector<pair<unsigned char, long>> fr_count)
{
	//�������� ������� � ������������ ��� �������� ������ ��������
	priority_queue<tree*, vector<tree*>, tree_ptr_compare> mass;

	//�������� ������� ������
	for (int i = 255; i >=0; i--)
		if (fr_count[i].second != 0)
			mass.push(new tree(fr_count[i]));

	//�������� ����� ������ 
	while (mass.size() > 1)
	{
		tree* right = mass.top();
		mass.pop();

		tree* left = mass.top();
		mass.pop();
		
		tree* parent = new tree();
		parent->add(right, left);
		mass.push(parent);
	}	
	return mass.top();
}


//������� ������������
void Haffman_decode(bool program_mode, string name)
{
	ifstream fin;
	ofstream fout;
	char in_file[248], out_file[256];						//����� ������
	unsigned char byte;										//������ ��� ���������� �� �����

	if (program_mode)
	{
		cout << endl << "Chose input file" << endl << "-->	";
		cin >> in_file;
	}
	else
		strcpy_s(in_file, name.c_str());

	strcpy_s(out_file, in_file);
	char a[] = ".haf\0";
	char* pos = strstr(out_file, a);
	if (!pos)
	{
		StopProgram(3, program_mode);
		return;
	}
	out_file[pos - out_file] = 0;

	//�������� �������� �����
	fin.open(in_file, ios::in | ios::binary);
	if (fin.is_open() == NULL)
	{
		StopProgram(1, program_mode);
		return;
	}

	vector <pair <unsigned char, long>>  fr_count;		//������ ��� �������� ����� ���������� ����
	for (int i = 0; i < 256; i++)
	{
		long buffer;
		fin.read((char *)&buffer, sizeof(long));
		fr_count.push_back(make_pair(i, buffer));
	}
	cout << "Start decoding..." << endl;
		
	unsigned int start_time = clock();
	
	//���������� ������� ����� ���������� ����
	sort(fr_count.begin(), fr_count.end(), pairCompare);

	//�������� ������ �������� ��� ������			
	tree* top = create_Haffman_tree(fr_count);

	//c������� ��������� �����
	fout.open(out_file, ios::out | ios::binary);
	if (!fout)
	{
		StopProgram(1, program_mode);
		return;
	}

	//������������ �����
	tree* child = top;
	unsigned long input_bytes = 0, output_bytes = 0;

	while (fin.read((char *)&byte, sizeof(char)))
	{		
		input_bytes++;
		for (int i = 0; i < 8; i++)
		{
			child = (byte >= 128 ? child->right : child->left);
			byte <<= 1;
			if (child->left == NULL && child->right == NULL)
			{
				fout.write((char *) &child->inf, sizeof(char));
				child = top;
				output_bytes++;
			}
		}
	}

	//����� ����������
	unsigned int end_time = clock();
	cout << endl << "Bytes read:	" << input_bytes << endl << "Bytes written:	" << output_bytes-1 << endl << "Runtime:	" << end_time - start_time << "ms" << endl;

	Free(top);
	fin.close();
	fout.close();
	StopProgram(0, program_mode);
}

//������� ���������
void Haffman_encode(bool program_mode, string name)
{
	ifstream fin;
	ofstream fout;

	char input_file[256], output_file[256];						//����� ������
	unsigned char byte;												//������ ��� ���������� �� �����

	vector <pair <unsigned char, long>>  fr_count;			//������ ��� �������� ����� ���������� ����  <��� �����, ����� ��������� ����� �����>
	for (int i = 0; i < 256; i++)
		fr_count.push_back(make_pair(i, 0));

	//�������� �������� �����
	if (program_mode == true)
	{
		cout << endl << "Chose input file" << endl << "-->	";
		cin >> input_file;
	}
	else
		strcpy_s(input_file, name.c_str());

	fin.open(input_file, ios::in | ios::binary);
	if (!fin)
	{
		StopProgram(1, program_mode);
		return;
	}
	cout << "Start encoding..." << endl;

	unsigned int start_time = clock();

	//������� ����� ���������� ���� �� ������� �����
	while (fin)
	{
		fin.read((char *)&byte, sizeof(char));
		fr_count[byte].second++;
	}
	fin.close();

	//�������� ��������� �����
	strcpy_s(output_file, input_file);
	strcat_s(output_file, ".haf");
	fout.open(output_file, ios::out | ios::binary);

	if (!fout)
	{
		StopProgram(2, program_mode);
		return;
	}

	//������ ������� ������������� ����	
	for (int i = 0; i < 256; i++)
		fout.write((char *)&fr_count[i].second, sizeof(long));

	//���������� ������� ����� ���������� ����
	sort(fr_count.begin(), fr_count.end(), pairCompare);

	//�������� ������ �������� � ������� �������
	tree* top = create_Haffman_tree(fr_count);

	string code_table[256];
	generate_code_table(top, code_table, "");

	//����������� ��������� ������
	fin.open(input_file, ios::in | ios::binary);
	if (!fin)
	{
		StopProgram(1, program_mode);
		return;
	}

	int counter = 0;
	char output = 0;
	double input_bytes = 0, output_bytes = 0;	

	while (fin.read((char *)&byte, sizeof(char)))
	{
		input_bytes++;
		int length = code_table[byte].length();
		for (int i = 0; i < length; i++)
		{
			counter++;
			output <<= 1;
			if (code_table[byte][i] == '1')
				output += 1;
			if (counter == 8)
			{
				output_bytes++;
				fout.write((char *)&output, sizeof(char));
				counter = output = 0;
			}
		}
	}

	if (counter)
	{
		for (counter; counter < 8; counter++)
			output <<= 1;
		fout.write((char *)&output, sizeof(char));
		output_bytes++;
	}

	//����� ����������
	unsigned int end_time = clock();
	cout << endl << "Bytes read:		" << (long)input_bytes-1 << endl << "Bytes written:		" << (long)output_bytes << endl;
	cout << "Compression ratio:	" << input_bytes / output_bytes << endl << "Runtime:		" << end_time - start_time << "ms" << endl;
	
	Free(top);
	fin.close();
	fout.close();
	StopProgram(0, program_mode);
}


int main(int argc, char* argv[])
{	
	if (argc > 1)		//������ � ����������� ��������� ������
	{
		if (argv[1] == (string)"0")
			Haffman_encode(false, argv[2]);
		else
			if (argv[1] == (string)"1")
				Haffman_decode(false, argv[2]);
			else 
				cout << "Wrong mode";
	}
	else
		while (1)		// ������ � �������������
		{	
			string mode;
			cout << "Encode '0' or decode '1' ?" << endl << "-->	";
			cin >> mode;
			if (mode[0] == '1')
				Haffman_decode(true,"");
			if (mode[0] == '0')
				Haffman_encode(true,"");
		}
	return 0;
}