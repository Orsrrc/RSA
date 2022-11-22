#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <math.h>

int N = 0;
int E = 0;
int D = 0;
int L = 0;

int init_value()
{
	int temp = 0;
	scanf_s("%d", &temp);
	return temp;
}

int init_value(int L, int E, int D)
{
	bool flag = true;
	while (flag)
	{
		if ((E * D) % L != 1 || D < 1)
		{
			D++;
		}
		else {
			break;
		}
		if (D > L)
		{
			printf("error!\n");
			printf("No such number!\n");
			return 0;
		}
	}
	return D;
}


int init_value(int p, int q) //get Euler function
{
	int temp = 0;
	temp = (p > q ? p : q); //L is the biggest number in q, p
	bool flag = true;
	while (flag == true)
	{
		if (temp % p == 0 && temp %q == 0)
		{
			flag = false;
		}
		else {
			temp++;
		}
	}
	return temp;
}

int add_RSA(int Plain_text, int E, int N) {
	//c ≡ m^e mod n
	double sum = pow(Plain_text, E);
	double result = fmod(sum, N);
	return result;
}

int remove_RSA(int Cipher_text, int D, int N)
{
	//m ≡ c^d mod n
	long double sum = pow(Cipher_text, D);
	double result = fmodl(sum, N);
	return result;
}

int Generate_secret_key() {
	int q = 0, p = 0;
	//Generate secret key
	printf("Please input two positive numbers: (p,q)\n");
	printf("Enter q's value：");
	q = init_value(); //init q's value

	printf("Enter p's value：");
	p = init_value();//init p's value

	if (p < q) //default p > q
	{
		int temp = 0;
		temp = p;
		p = q;
		q = temp;
	}

	if (p%q == 0) //if p and q is not coprime number return error
	{
		printf("error!\n");
		printf("These numbers is not positive numbers\n");
		printf("Try again!\n");
		Generate_secret_key();
		return 0;
	}

	//get N's value
	N = q * p;
	printf("Generating Number's value...\n");
	Sleep(1000);
	printf("N's value is：%d\n", N);

	//Generate L's value
	printf("Generating L's value....\n");
	Sleep(1000);
	L = init_value(p - 1, q - 1);
	printf("L's value is :%d\n", L);

	//Init E's value
	printf("Please enter the value of E:\n ");
	printf("(The value of e is an integer between 1 and L and the maximum common divisor with L is 1)\n");
	E = init_value();
	while (1)
	{
		if (E > L || L % E == 0)
		{
			printf("error! please try again\n");
			E = init_value();
		}
		else {
			break;
		}
	}
	//init D's value
	D = init_value(L, E, D);
	printf("D's value is %d\n", D);
	return 0;
}
int Encryption() {
	//Encryption
	//if N = 0 means failed to generate secret key
	if (N == 0)
	{
		printf("Error!Failed to generate secret key!\n");
		printf("Please!Try again!\n");
		return 0;
	}
	int Plain_text = 0;
	int Cipher_text = 0;
	printf("Enter the Plaintext, if the value type is not 'int', please replace with ASCII\n");
	Plain_text = init_value();
	//Plaintext number must be less than Euler's value
	if (Plain_text > L)
	{
		printf("Error!the Plaintext is bigger than Euler's value\n");
		printf("Please Try again!\n");
		system("pause");
		system("cls");
		Encryption();
		return 0;
	}
	Cipher_text = add_RSA(Plain_text, E, N);
	printf("Cipher_text number is %d\n", Cipher_text);
	return 0;
}

int Decrypt() {
	//Decrypt
	//if N = 0 means failed to generate secret key
	if (N == 0)
	{
		printf("Error!Failed to generate secret key!\n");
		printf("Please!Try again!\n");
		return 0;
	}
	int Plain_text = 0;
	int Cipher_text = 0;
	printf("Enter the Ciphertext, if the value type is not 'int', please replace with ASCII\n");
	Cipher_text = init_value();
	//Cipher number must be less than Euler's value
	if (Cipher_text > L)
	{
		printf("Error!the Ciphertext is bigger than Euler's value\n");
		printf("Please Try again!\n");
		system("pause");
		system("cls");
		Decrypt();
		return 0;
	}
	Plain_text = remove_RSA(Cipher_text, D, N);
	printf("Plain_text number is %d\n", Plain_text);
	return 0;
}

//Select
void Function_Select(int Choose)
{
	switch (Choose)
	{
	case 1:
		//Generate_secret_key
		system("cls");
		Generate_secret_key();
		system("pause");
		system("cls");
		break;
	case 2:
		//Encryption
		system("cls");
		Encryption();
		system("pause");
		system("cls");
		break;
	case 3:
		//Decrypt
		system("cls");
		Decrypt();
		system("pause");
		system("cls");
		break;
	}
}

//Menu function
int Menu() {
	int Choose;
	bool flag = true;
	while (flag == true)
	{
		printf("---------RSA----------\n");
		printf("Function:\n");
		printf("1、Generate secret key\n");
		printf("2、Encryption\n");
		printf("3、Decrypt\n");
		printf("4、Exit\n");
		printf("----------------------\n");
		printf("Select:");
		scanf_s("%d", &Choose);
		if (Choose == 4)
		{
			flag = false;
			printf("System Exit!\n");
			return 0;
		}
		//out of choose
		if (Choose != 1 && Choose != 2 && Choose != 3)
		{
			printf("error!\n");
			printf("Wrong input!\n");
			printf("Please try again!");
			Menu();
		}
		else
		{
			Function_Select(Choose);
		}
	}
	return 0;
}

//main function
int main() {
	printf("网安201 宋刚旭 2020240313\n");
	Menu();
	system("pause");
	return 0;
}