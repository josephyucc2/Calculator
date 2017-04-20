// Name: 林弘翔
// Date: April 13,2017
// Statement: 1114
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigInt
{
public:
	void ADD(string number1, string number2);
	void SUB(string number1, string number2);
private:
	int sign = 0;
};

void BigInt::ADD(string number1, string number2)
{
	vector<int> temp;
	string sum;
	//Processing
#pragma region negative + negative -A + -B = -(A+B)
	if (number1[0] == '-' && number2[0] == '-')
	{
		number1.erase(number1.begin());
		number2.erase(number2.begin());
		sign = -1;
		ADD(number1, number2);
		return;
	}
#pragma endregion
#pragma region negative + positive -A + B = -(A-B)
	else if (number1[0] == '-' && number2[0] != '-')
	{
		number1.erase(number1.begin());
		sign = -1;
		SUB(number1, number2);
		return;
	}
#pragma endregion
#pragma region positive + negative  A + -B = A-B
	else if (number1[0] != '-' && number2[0] == '-')
	{
		number2.erase(number2.begin());
		SUB(number1, number2);
		return;
	}
#pragma endregion
#pragma region positive + positive A + B = A+B
	else if (number1[0] != '-' && number2[0] != '-')
	{
		//make number1 as long as number2 , insert 0
		if (number1.size() > number2.size()) //number1 is longer than number2
		{
			int quantity = number1.size() - number2.size();
			for (int i = 0; i < quantity; i++)
			{
				number2.insert(0, "0");
			}
		}
		else if (number1.size() < number2.size()) //number1 is shorter than number2
		{
			int quantity = number2.size() - number1.size();
			for (int i = 0; i < quantity; i++)
			{
				number1.insert(0, "0");
			}
		}

		for (int i = number1.size() - 1; i >= 0; i--) //addition
		{
			temp.push_back(number1[i] - '0' + number2[i] - '0');
		}
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp[i] > 9) //carry
			{
				if (i == temp.size() - 1) //only one digit
				{
					temp.push_back(1);
				}
				else
				{
					temp[i + 1]++;
				}
				temp[i] %= 10;
			}
		}
	}
#pragma endregion
	//Output
	if (sign == -1)
	{
		sum.push_back('-');
	}
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		sum.push_back(temp[i] + '0');
	}
	if (sum == "-0")
	{
		sum = "0";
	}
	cout << sum << endl;
	sign = 0;
}

void BigInt::SUB(string number1, string number2)
{
	vector<int> temp;
	string difference;
	//Processing
#pragma region negative - negative -A - -B = -A+B = -(A-B)
	if (number1[0] == '-' && number2[0] == '-')
	{
		number1.erase(number1.begin());
		number2.erase(number2.begin());
		sign = -1;
		SUB(number1, number2);
		return;
	}
#pragma endregion
#pragma region negative - positive -A - B = -(A+B)
	else if (number1[0] == '-' && number2[0] != '-')
	{
		number1.erase(number1.begin());
		sign = -1;
		ADD(number1, number2);
		return;
	}
#pragma endregion
#pragma region positive - negative A - -B = A+B
	else if (number1[0] != '-' && number2[0] == '-')
	{
		number2.erase(number2.begin());
		ADD(number1, number2);
		return;
	}
#pragma endregion
#pragma region positive - positive A - B = A-B
	else if (number1[0] != '-' && number2[0] != '-')
	{
		//make number1 as long as number2 , insert 0
		if (number1.size() > number2.size()) //number1 is longer than number2
		{
			int quantity = number1.size() - number2.size();
			for (int i = 0; i < quantity; i++)
			{
				number2.insert(0, "0");
			}
		}
		else if (number1.size() < number2.size()) //number1 is shorter than number2
		{
			int quantity = number2.size() - number1.size();
			for (int i = 0; i < quantity; i++)
			{
				number1.insert(0, "0");
			}
		}
		//keep larger number substract smaller number
		//substraction
		if (number1.compare(number2) > 0) //number1 is larger than number2
		{
			for (int i = number1.size() - 1; i >= 0; i--)
			{
				temp.push_back(number1[i] - number2[i]);
			}
		}
		else if (number1.compare(number2) < 0)// number1 is smaller than number2
		{
			if (sign == -1) //double minus get positive
			{
				sign = 0;
			}
			else
			{
				sign = -1;
			}
			for (int i = number1.size() - 1; i >= 0; i--)
			{
				temp.push_back(number2[i] - number1[i]);
			}
		}
		else if (number1.compare(number2) == 0)
		{
			for (int i = number1.size() - 1; i >= 0; i--)
			{
				temp.push_back(number2[i] - number1[i]);
			}
		}
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp[i] < 0) //borrow
			{
				temp[i + 1]--;
				temp[i] += 10;
			}
		}
	}
#pragma endregion
	//Output
	if (sign == -1)
	{
		difference.push_back('-');
	}
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		difference.push_back(temp[i] + '0');
	}
	int currentsize = difference.size();
	for (int i = 0; i < currentsize; i++)
	{
		if (difference.size() != 1 && difference[0] == '0') //delete the front zero
		{
			difference.erase(difference.begin());
		}
		else if (difference.size() != 2 && difference[0] == '-' && difference[1] == '0')
		{
			difference.erase(difference.begin() + 1);
		}
	}
	if (difference == "-0")
	{
		difference = "0";
	}
	cout << difference << endl;
	sign = 0;
}


int main()
{
	BigInt input;
	string instruction, number1, number2;
	while (cin >> instruction)
	{
		if (!(instruction.compare("ADD")))
		{
			cin >> number1 >> number2;
			input.ADD(number1, number2);
		}
		else if (!(instruction.compare("SUB")))
		{
			cin >> number1 >> number2;
			input.SUB(number1, number2);
		}
		else if (!(instruction.compare("Exit")))
		{
			break;
		}
	}
	return 0;
}
