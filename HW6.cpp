#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

void ReadFile(string fileName, vector<int> &getSSN)	//reads from the file and put integers into a vector
{
	ifstream in;
	in.open(fileName);
	if (!in.is_open())	//if could not find the file will let the user know
	{
		cout << "I could not find " << fileName << endl;
		return;
	}
	int ssn;
	while (in.peek() != EOF)	//reads one integer at the time and put it into a vector
	{
		in >> ssn;
		in.ignore();
		getSSN.push_back(ssn);	
	}
	in.clear();
	in.close();
}

int extraction_method(int ssn)	//this function returns the key consisting of 3rd, 5th, 7th and 8th number of the integer ssn
{
	int key3 = ssn / 1000000 % 10;	//takes third number from integer ssn and assigns it to key3
	int key5 = ssn / 10000 % 10;	//takes fifth number from integer ssn and assigns it to key5
	int key7 = ssn / 100 % 10;	//takes seventh number from integer ssn and asigns it to key7
	int key8 = ssn / 10 % 10;	//takes eight number from integer ssn and assigns it to key8
	int key = (key3 * 1000) + (key5 * 100) + (key7 * 10) + key8;	//creates key from key3, key5, key7 and key8
	return key;
}

int hashing(int key, int number)	//hashes key
{
	return key % number;
}

int quadratic_probing(int *hash_table, int key, int number, int ssn) //looks for the place where to put ssn
{
	int index;
	for (int i = 0; i < number; i++)
	{
		index = (hashing(key, number) +  i * i) % number;
		if (hash_table[index] == 0)	//empty slot
		{
			hash_table[index] = ssn;
			return index;
		}
	}	//table overflow
	return -1;
}

void WriteOutFile(string fileName, int *hash_table, int number)	//writes hash_table to the file
{
	ofstream out;
	out.open(fileName);
	for (int i = 0; i < number; i++)
	{
		if (i != number - 1)
		{
			out << hash_table[i] << ",";
		}
		else
		{
			out << hash_table[i];
		}
	}
	out.clear();
	out.close();
}

int main()
{
	vector<int> getSSN;
	string fileName = "everybodys_socials.txt";
	ReadFile(fileName, getSSN);
	cout << "Pick a number from 1 to 450 million" << endl;	
	int number;
	cin >> number;	//takes input from the user 
	int *hash_table = new int[number];	//creates hash_table and sets its maximum to number provided by the user
	for (int k = 0; k < number; k++)  //initializes the hash table to contain 0s
	{
		hash_table[k]=0;
	} 
	for (int i = 0; i < getSSN.size(); i++)	//assigns ssn to the hash_table using quadratic probing
	{
		int key = extraction_method(getSSN[i]);
		quadratic_probing(hash_table, key, number, getSSN[i]);	//collision occurs
	}
	WriteOutFile("hashed_socials.txt", hash_table, number);	//writes hash_table to the file 
	return 0;
}
