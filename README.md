# Implementaton-of-Hill-Cipher-in-c-
Hill cipher is a technique that is used to encrypt and decrypt messages in such a way that only the person who has the key can know what the actual message is. This can be used to transmit the messages in such a way that no can can understand what the message is except the person having the key. So this can be used for transmitting the messages secretly.
The implementation for the hill cipher in c++ is given below:


#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
using namespace std;

//This loop is converting the letters of the input text to capital letters. 
void to_UPPER_CASES(char key[], int length)
{
    for (int i = 0; i < length; i++)
        if (key[i] >= 97 && key[i] <= 122)
            key[i] -= 32;
}

//This loop is removing the spaces from the input text.
int remove_spaces(char key[])
{
    int i, count = 0;
    for (i = 0; i < strlen(key); i++)
    {
        if (key[i] != ' ')
        {
            key[count] = key[i];
            count++;
        }
    }
    key[count] = '\0';
    return count;
}

//This loop is for mutiplying the two 3x3 matrices.
void matrix_multiply_3(int key[][3], int sub[][1], int result[][1])
{
    int i, j, k;

    for (i = 0; i < 3; i++)
    {
        result[i][j] = 0;
        for (j = 0; j < 1; j++)
        {
            for (k = 0; k < 3; k++)
                result[i][j] += key[i][k] * sub[k][j];
        }
    }
}

//This loop is for multiplying the two 2x2 matrices.
void matrix_multiply_2(int key[][2], int sub[][1], int result[][1])
{
    int i, j, k;

    for (i = 0; i < 2; i++)
    {
        result[i][j] = 0;
        for (j = 0; j < 1; j++)
        {
            for (k = 0; k < 2; k++)
                result[i][j] += key[i][k] * sub[k][j];
        }
    }
}

//In this subroutine the plaintext is converted into encrypted text or the encrypted text is decyphered back into plain text. 
void cipher_text_3(char message[], int length, int dimension, int key[][3], int num)
{
    int i, result[3][1];
    int temp = 0;
    char c_t[length];

    for (i = 0; i < strlen(message); i += dimension)
    {
        for (int h = 0; h < 3; h++)
            for (int k = 0; k < 1; k++)
                result[h][k] = 0;

        int sub[dimension][1];
        sub[0][0] = (message[i]) % 65;
        if ((i + 1) >= strlen(message))
            sub[1][0] = 'X';
        else
            sub[1][0] = (message[i + 1]) % 65;

        if (dimension == 3)
        {
            if ((i + 2) >= strlen(message))
                sub[2][0] = 'X';
            else
                sub[2][0] = (message[i + 2]) % 65;
        }

        //Here first the input text is converted into corresponding nx1 matrix where n is the size of the input text and each element of the matrix
        // corresponds to the alphabet number of the input text starting from 0. i.e. 'A' corresponds to 0,'B' corresponds to 1 and so on.And then 
        // this matrix is multiplied with the key matrix to obtain the corresponding encrypted or decrypted text.
        matrix_multiply_3(key, sub, result);

        //This loop is performing the modulo 26 operatio on the elements of the result matrix.
        for (int p = 0; p < 3; p++)
        {
            for (int j = 0; j < 1; j++)
            {
                if (result[p][j] < 0)
                {
                    result[p][j] = (26 * (((result[p][j] * (-1)) / 26) + 1)) + result[p][j];
                }
                else
                {
                    result[p][j] = (result[p][j]) % 26;
                }
            }
        }

        //This loop is converting the elements of the result matrix into the corresponding alphabets as per the rules stated above.
        for (int j = 0; j < dimension; j++)
        {
            c_t[temp] = (char)(result[j][0] + 65);
            temp++;
        }
    }

    c_t[temp] = '\0';
    // Printing the corresponding encrypted text or the decrypted text as per the input given.
    if (num == 1)
        cout << "The cipher text for corresponding message is :" << endl;
    else if (num == 0)
        cout << endl << "The decrypted text for entered cipher text is :" << endl;
    cout << c_t;
}

// This subroutine is similar to the subroutine cipher_text_3 bt this is for 3x3 matrices. 
void cipher_text_2(char message[], int length, int dimension, int key[][2], int num)
{
    int i, result[2][1];
    char c_t[length];
    int temp = 0;
    for (i = 0; i < strlen(message); i += dimension)
    {
        for (int h = 0; h < 2; h++)
            for (int k = 0; k < 1; k++)
                result[h][k] = 0;

        int sub[dimension][1];
        sub[0][0] = (message[i]) % 65;
        if ((i + 1) >= length)
            sub[1][0] = 'X';
        else
            sub[1][0] = (message[i + 1]) % 65;

        matrix_multiply_2(key, sub, result);

        for (int p = 0; p < 2; p++)
        {
            for (int j = 0; j < 1; j++)
            {
                if (result[p][j] < 0)
                {
                    result[p][j] = (26 * (((result[p][j] * (-1)) / 26) + 1)) + result[p][j];
                }
                else
                {
                    result[p][j] = (result[p][j]) % 26;
                }
            }
        }
        for (int j = 0; j < dimension; j++)
        {
            c_t[temp] = (char)(result[j][0] + 65);
            temp++;
        }
    }
    c_t[temp] = '\0';

    if (num == 1)

        cout << endl << "The cipher text for corresponding message is :" << endl;
    else if (num == 0)
        cout << endl << "The decrypted text for entered cipher text is :" << endl;
    cout << c_t;
}


void check(int* a)
{
    if (*a < 0)
        *a = (26 * (((*a * (-1)) / 26) + 1)) + *a;
    else
        *a = (*a) % 26;
}

//This subroutine is calculating the inverse of the input 3x3 matrix.
void inverse(int key[][3])
{
    int temp[3][3];

    int det = (key[0][0] * (key[1][1] * key[2][2] - key[2][1] * key[1][2])) - (key[0][1] * (key[1][0] * key[2][2] -
        key[2][0] * key[1][2])) + (key[0][2] * (key[1][0] * key[2][1] - key[2][0] * key[1][1]));
    int i = 1;
    while (i)
    {
        if (((det * i) % 26) == 1)
            break;
        else
            i++;

    }

    temp[0][0] = ((key[1][1] * key[2][2] - key[2][1] * key[1][2]) * i);
    check(&temp[0][0]);
    temp[0][1] = -((key[0][1] * key[2][2] - key[2][1] * key[0][2]) * i);
    check(&temp[0][1]);

    temp[0][2] = ((key[0][1] * key[1][2] - key[1][1] * key[0][2]) * i);
    check(&temp[0][2]);
    temp[1][0] = -((key[1][0] * key[2][2] - key[2][0] * key[1][2]) * i);
    check(&temp[1][0]);
    temp[1][1] = ((key[0][0] * key[2][2] - key[2][0] * key[0][2]) * i);
    check(&temp[1][1]);
    temp[1][2] = -((key[0][0] * key[1][2] - key[1][0] * key[0][2]) * i);
    check(&temp[1][2]);
    temp[2][0] = ((key[1][0] * key[2][1] - key[2][0] * key[1][1]) * i);
    check(&temp[2][0]);
    temp[2][1] = -((key[0][0] * key[2][1] - key[2][0] * key[0][1]) * i);
    check(&temp[2][1]);
    temp[2][2] = ((key[0][0] * key[1][1] - key[0][1] * key[1][0]) * i);
    check(&temp[2][2]);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            key[i][j] = temp[i][j];

}

//This subroutine is calculating the inverse of the input 2x2 matrix.
void inverse_1(int key[][2], int det)
{
    int temp[2][2];

    cout << det << endl;
    int i = 1;
    while (i)
    {
        if (((det * i) % 26) == 1)
            break;
        else
            i++;
    }
    cout << i << endl;
    int t;
    t = key[1][1];
    temp[1][1] = key[0][0] * i;
    check(&temp[1][1]);
    temp[0][0] = t * i;
    check(&temp[0][0]);
    temp[0][1] = -(key[0][1] * i);
    check(&temp[0][1]);
    temp[1][0] = -(key[1][0] * i);
    check(&temp[1][0]);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            key[i][j] = temp[i][j];
}

int main()
{
    int num;
    cout << "Enter 1 for encryption and 0 for decryption." << endl;
    cin >> num;
    int dimension;
    cout << "Enter the dimension of the key matrix which is either 2 or 3." << endl;
    cin >> dimension;
    int flag = 1;

    while (flag)
    {
        
        if (dimension > 3 || dimension < 2) 
        {
            cout << "Invalid dimension." << endl << endl;
            continue;
        }
        cout << endl << "Enter the key matrix of order" << dimension << "x" << dimension << "beginning from top and inserting from left to right such that it has non - zero determinant and the determinant value should not be divisible by 2 and 13." << endl;
        int det;

        if (dimension == 3) // This if condition is for the key matrices of the order 3x3.
        {
            int key[3][3];
            for (int i = 0; i < dimension; i++)
                for (int j = 0; j < dimension; j++)
                    cin >> key[i][j];
            cout << "Input key is :" << endl;
            for (int i = 0; i < dimension; i++)
            {
                for (int j = 0; j < dimension; j++)
                    cout << key[i][j] << " ";
                cout << endl;
            }
            det = (key[0][0] * (key[1][1] * key[2][2] - key[2][1] * key[1][2])) - (key[0][1] * (key[1][0] * key[2][2] -
                key[2][0] * key[1][2])) + (key[0][2] * (key[1][0] * key[2][1] - key[2][0] * key[1][1])); // Calculating the determinant value of the matrix. 
            if (det == 0 || ((det % 2) == 0) || (det % 13) == 0)
            {
                cout << "Here determinant is :" << det << ".So key matrix is not valid.Re - enter valid key matrix and please read the instructions to input key matrix." << endl << endl;
                continue;
            }
            if (num == 1)
            {
                char message[20000];
                cout << endl << "Enter the message to be transmitted consisting of only alphabetsand having length less than 20000:" << endl;

                cin.getline(message, 20000);
                cin.getline(message, 20000); // Taking input the text that is to be encrypted or decrypted. 
                int length = remove_spaces(message); // Removing the spaces from the input text. 
                to_UPPER_CASES(message, length); // Converting all the alphabets of the input text to the capital alphabets.
                cipher_text_3(message, length, dimension, key, num);
            }
            else if (num == 0)
            {
                char message[20000];
                cout << endl << "Enter the message to be transmitted consisting of only alphabetsand having length less than 20000" << endl;
                cin.getline(message, 20000);
                cin.getline(message, 20000); // Taking input the text that is to be encrypted or decrypted. 
                int length = remove_spaces(message); // Removing the spaces from the input text. 
                to_UPPER_CASES(message, length); // Converting all the alphabets of the input text to the capital alphabets.
                inverse(key); // Calculating the inverese of the key matrix.

                cipher_text_3(message, length, dimension, key, num);
            }
        }
        else if (dimension == 2) // This condition is for the key matrices of the order 2x2.
        {
            int key[2][2];
            for (int i = 0; i < dimension; i++)
                for (int j = 0; j < dimension; j++)
                    cin >> key[i][j];
            cout << "Input key is :" << endl;

            for (int i = 0; i < dimension; i++)
            {
                for (int j = 0; j < dimension; j++)
                    cout << key[i][j] << " ";
                cout << endl;
            }
            det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
            if (det == 0 || ((det % 2) == 0) || (det % 13) == 0)
            {
                cout << "Here determinant is :" << det << ".So key matrix is not valid.Re - enter valid key matrix and please read the instructions to input key matrix." << endl << endl;
                continue;
            }
            if (num == 1)
            {
                char message[20000];
                cout << endl << "Enter the message to be transmitted consisting of only alphabetsand having length less than 20000:" << endl;
                cin.getline(message, 20000);
                cin.getline(message, 20000); // Taking input the text that is to be encrypted or decrypted. 
                int length = remove_spaces(message); //Removing the spaces from the input text. 
                to_UPPER_CASES(message, length); //Removing the spaces from the input text. 

                cipher_text_2(message, length, dimension, key, num);
            }
            else if (num == 0)
            {

                char message[20000];
                cout << endl << "Enter the message to be transmitted consisting of only alphabetsand having length less than 20000:" << endl;
                cin.getline(message, 20000);
                cin.getline(message, 20000); // Taking input the text that is to be encrypted or decrypted. 
                int length = remove_spaces(message); //Removing the spaces from the input text. 
                to_UPPER_CASES(message, length); //Removing the spaces from the input text. 
                inverse_1(key, det); // Calculating the inverese of the key matrix. 
                cipher_text_2(message, length, dimension, key, num);
            }
        }
        flag = 0;
    }
    return 0;
}
