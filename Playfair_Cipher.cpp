
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <string>
using namespace std;

//Converting the alphabets to capital letters.
void to_UPPER_CASE(char* message, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (message[i] >= 97 && message[i] <= 122)
			message[i] -= 32;
	}
}

//Remving spaces from the input string.
int remove_spaces(char* message, int len)
{
	int count = 0;
	for (int i = 0; i < len; i++)
	{
		if (message[i] != ' ')
		{
			message[count] = message[i];

			count++;
		}
	}
	message[count] = '\0';
	return count;
}

//Generating the 5x5 table to generate the encrypted text or the decrypted text by the helpof this table.In this table the alphabets are first placed and then 
// the remaining alphabets are placed and alphabets 'I' and 'J' are placed in the same box.Then by the help of rules of encryption and decryption the plaintext is 
// is converted to encrypted text or the encrypted text is decyphered into plain text.
void generate_table(char table[5][5], char key[], int length)
{
	int a, b, c, * ptr;
	ptr = (int*)calloc(26, sizeof(int));
	for (a = 0; a < length; a++)
	{
		if (key[a] != 'J')
			ptr[key[a] - 65] = 2;
		else if (key[a] == 'J')
		{
			ptr['I' - 65] = 2;
			key[a] = 'I';
		}

	}
	ptr['J' - 65] = 1;
	a = 0;
	b = 0;

	for (c = 0; c < length; c++)
	{
		if (ptr[key[c] - 65] == 2)
		{
			ptr[key[c] - 65] -= 1;
			table[a][b] = key[c];
			b++;
			if (b == 5)
			{
				a++;
				b = 0;
			}
		}
	}

	for (c = 0; c < 26; c++)
	{
		if (ptr[c] == 0)
		{
			table[a][b] = (char)(c + 65);
			b++;
			if (b == 5)
			{
				a++;
				b = 0;

			}
		}
	}
}

// Searching the alphabet of the input text in the table generated and then replacing the corresponding alphabet of the encrypted text or decyphered text.
void search(char table[5][5], char a, char b, int arr[])
{
	int h, k;
	if (b == 'J')
		b = 'I';
	else if (a == 'J')
		a = 'I';

	for (h = 0; h < 5; h++)
		for (k = 0; k < 5; k++)
		{
			if (table[h][k] == a)
			{
				arr[0] = h;
				arr[1] = k;
			}
			if (table[h][k] == b)
			{
				arr[2] = h;
				arr[3] = k;
			}
		}
}

//This subroutine is used for encryption of the plain text.Encryption takes place with the help of some rules and similarly decryption takes place 
//by the help of some rules.
void encr(char table[5][5], char message[], int length)
{
	char cipher_text[20000];
	int i, a[4], j = 0;
	for (i = 0; i < length; i += 2)
	{
		if ((i + 1) >= length)
		{
			search(table, message[i], 'Z' , a);
		}

		else if (message[i] == message[i + 1] && ((i + 1) < length))
		{
			search(table, message[i], 'X' , a);
			i = i - 1;
		}

		else
		{
			search(table, message[i], message[i + 1], a);

		}
		if (a[0] == a[2])
		{
			cipher_text[j] = table[a[0]][(a[1] + 1) % 5];
			cipher_text[j + 1] = table[a[0]][(a[3] + 1) % 5];
		}
		else if (a[1] == a[3])
		{
			cipher_text[j] = table[(a[0] + 1) % 5][a[1]];
			cipher_text[j + 1] = table[(a[2] + 1) % 5][a[1]];
		}
		else
		{
			cipher_text[j] = table[a[0]][a[3]];
			cipher_text[j + 1] = table[a[2]][a[1]];
		}
		j = j + 2;
	}
	cout << "According to the key entered the cipher text for corresponding message is :" << endl << cipher_text;
}

//This subroutine is used for the decryption of the encrypted text.
void decr(char table[5][5], char message[], int length)
{
	char cipher_text[20000];
	int i, a[4], j = 0;

	for (i = 0; i < length; i += 2)
	{
		search(table, message[i], message[i + 1], a);

		if (a[0] == a[2])
		{
			if (a[1] == 0)
				a[1] = 10;
			if (a[3] == 0)
				a[3] = 10;
			cipher_text[j] = table[a[0]][(a[1] - 1) % 5];
			cipher_text[j + 1] = table[a[0]][(a[3] - 1) % 5];
		}
		else if (a[1] == a[3])
		{
			if (a[0] == 0)
				a[0] = 10;
			if (a[2] == 0)
				a[2] = 10;
			cipher_text[j] = table[(a[0] - 1) % 5][a[1]];
			cipher_text[j + 1] = table[(a[2] - 1) % 5][a[1]];
		}
		else
		{
			cipher_text[j] = table[a[0]][a[3]];

			cipher_text[j + 1] = table[a[2]][a[1]];
		}
		j = j + 2;
	}
	if (cipher_text[strlen(cipher_text) - 1] == 'Z')
		cipher_text[strlen(cipher_text) - 1] = '\0';
	for (int i = 0; i < strlen(cipher_text); i++)
	{
		if (cipher_text[i] == 'X')
		{
			if ((i - 1) >= 0 && (i + 1) < strlen(cipher_text))
			{
				if (cipher_text[i - 1] == cipher_text[i + 1])
				{
					for (int j = i; j < strlen(cipher_text); j++)
					{
						if (j == strlen(cipher_text) - 1)
							cipher_text[j] = '\0';
						else
							cipher_text[j] = cipher_text[j + 1];

					}
				}
			}
		}
	}
	// Printing the corresponding encrypted or decrypted text as output.
	cout << "According to the key entered the decrypted text is :" << endl << cipher_text;
}

//Subroutine to encrypt the input text.
void Encrypt(char key[], char message[])
{
	int len1 = remove_spaces(key, strlen(key)); // Removing spaces from the key.
	int len2 = remove_spaces(message, strlen(message)); // Removing spaces from the input message.
	to_UPPER_CASE(key, len1); // Converting the alphabets of the key to Upper Case.
	to_UPPER_CASE(message, len2); // Converting the alphabets of the key to Upper Case.
	char table[5][5];
	generate_table(table, key, len1); // Generating the table from the key.
	encr(table, message, len2); // Decrypting the input message.
}

//Subroutine to decrypt the output text.
void Decrypt(char key[], char message[])
{
	int len1 = remove_spaces(key, strlen(key)); // Removing spaces from the key.
	int len2 = remove_spaces(message, strlen(message)); // Removing spaces from the input message.
	to_UPPER_CASE(key, len1); // Converting the alphabets of the key to Upper Case.
	to_UPPER_CASE(message, len2); // Converting the alphabets of the key to Upper Case.
	char table[5][5];
	generate_table(table, key, len1); // Generating the table from the key.
	decr(table, message, len2); // Decrypting the input message.

}

int main()
{
	int num;
	cout << "Enter 1 for encryption and 0 for decryption." << endl;
	cin >> num;
	cout << endl;
	cout << "Enter the key which consists of only alphabets :" << endl;
	char key[20000];
	cin >> key;
	cout << endl;

	if (num == 1)
	{
		cout << "Enter the message to be transmitted consisting of only alphabets and having less than 20000 alphabets:" << endl;
		char message[20000];
		cin.getline(message, 20000); // Taking the plain text as input.
		cin.getline(message, 20000);
		cout << endl;

		Encrypt(key, message);
	}
	else if (num == 0)
	{

		cout << "Enter the cipher text to be to be decrypted :" << endl;
		char message[20000];
		cin.getline(message, 20000); //Taking the encrypted text as input.
		cin.getline(message, 20000);
		cout << endl;
		Decrypt(key, message);
	}
	else
		cout << "Entered invalid number.Please enter either 0 or 1." << endl;

	return 0;
}
