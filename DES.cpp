#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
#include<vector>
#include <random>
#include <sstream>
#include <bitset>
#define block_size 8

using namespace std;
//GLOBAL
string input_key;
string plain_text;
char chunk_of_64[100][64];
int num_row;
string K_I[16]; ///stores key generated in each roung


void add_padding_at_end()
{
    string output_str;
    int len = strlen(plain_text.c_str());

    output_str = plain_text;
    while(output_str.length() % block_size != 0)
    {
        output_str+= "~";
    }

    printf("data string after padding : %s\n\n",output_str.c_str());
    plain_text = output_str;
}

string convertToBinary(unsigned int n)
{
    string r;
    while(n!=0)
    {
        r=(n%2==0 ?"0":"1")+r;
        n/=2;
    }
    reverse(r.begin(),r.end());
    while(r.length() % 8 != 0)
        r.push_back('0');
    reverse(r.begin(),r.end());

    return r;
}

string strToBinary(string s)
{
    int len = s.length();
    string returned_binary_str;

    for (int i = 0; i <= len; i++)
    {
        // convert each char to
        // ASCII value
        int val = int(s[i]);

        // Convert ASCII value to binary
        returned_binary_str += convertToBinary(val);

    }
    //cout << returned_binary_str;
    return returned_binary_str;
}

void binary_str_to_64_bit_block(string str)
{

    int j=-1;
    for(int i =0; i < str.length(); i++)
    {

        if(i%64 == 0)
        {
            j++;
            cout<<endl;
        }
        chunk_of_64[j][i%64] = str[i];
        //cout << j << "-" << i%64 << " " << str[i] <<endl;

    }

}

void printMatrix()
{
    cout << "Printing 64bit block " << endl;
    for(int i =0; i < plain_text.length()/8; i++)
    {
        for(int j =0; j < 64; j++)
        {
            cout << chunk_of_64[i][j];
        }
        cout<<endl;
    }
}

string leftrotate(string s, int d)
{
    reverse(s.begin(), s.begin()+d);
    reverse(s.begin()+d, s.end());
    reverse(s.begin(), s.end());
    return s;
}

void printString(string str)
{
    //cout<< "\n~~~~~~~ printing string ~~~~~~~~~~" <<endl;
    for(int i =0; i< str.length(); i++)
    {
        cout<< str[i];
    }
    cout<<endl;
}
void generate_key(string key)
{

    int CP_1[56] = {57, 49, 41, 33, 25, 17, 9,
                    1, 58, 50, 42, 34, 26, 18,
                    10, 2, 59, 51, 43, 35, 27,
                    19, 11, 3, 60, 52, 44, 36,
                    63, 55, 47, 39, 31, 23, 15,
                    7, 62, 54, 46, 38, 30, 22,
                    14, 6, 61, 53, 45, 37, 29,
                    21, 13, 5, 28, 20, 12, 4
                   };

    int SHIFT[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

    int CP_2[48] = {14, 17, 11, 24, 1, 5, 3, 28,
                    15, 6, 21, 10, 23, 19, 12, 4,
                    26, 8, 16, 7, 27, 20, 13, 2,
                    41, 52, 31, 37, 47, 55, 30, 40,
                    51, 45, 33, 48, 44, 49, 39, 56,
                    34, 53, 46, 42, 50, 36, 29, 32
                   };

    string modified_key;
    string modified_key_2;


    for(int i=0; i< 56; i++)
    {
        modified_key[i] = key[CP_1[i]-1];
    }

    //printing modified key
    cout<<"\n\nmodified key after using CP_1 i.e key in round 0 \n";
    for(int j=0; j< 56; j++)
    {
        cout << modified_key[j];
    }
    cout<<endl;


    string key_in_round[16] ="";
    string first_28_bits="";
    string last_28_bits="";
    string left_rotated_first_28_bits="";
    string left_rotated_last_28_bits="";


    for(int j=0; j< 56; j++)
    {
        key_in_round[0] += modified_key[j];
    }


    ///16 iterations should start from here
    for(int itr=0; itr < 2; itr++)
    {
        first_28_bits = "";
        last_28_bits = "";
        left_rotated_first_28_bits = "";
        left_rotated_last_28_bits = "";

        if(itr != 0)
        {

            for(int i=0; i<56; i++)
            {
                key_in_round[itr] += key_in_round[itr-1][i];
            }
            cout<<"\n\n..............Input key for round "<<itr << "..............\n";
            printString(key_in_round[itr]);
        }


        cout<<"\nRound - " << itr << " : First 28 bits of key : \n";
        for(int i = 0; i<28; i++)
        {
            first_28_bits += key_in_round[itr][i];
        }

        printString(first_28_bits);

        cout<<"\nRound - " << itr << " : Last 28 bits of key : \n";
        for(int j = 0; j<28; j++)
        {
            last_28_bits += key_in_round[itr][28+j];
        }
        printString(last_28_bits);

        left_rotated_first_28_bits = leftrotate(first_28_bits, SHIFT[itr]);
        left_rotated_last_28_bits = leftrotate(last_28_bits, SHIFT[itr]);

        cout<<"\n\nRound - " << itr << " : First 28 bits of key after left rotation : \n";
        cout<<left_rotated_first_28_bits;
        cout<<"\n\nRound - " << itr << " : Last 28 bits of key after left rotation : \n";
        cout<<left_rotated_last_28_bits;

        key_in_round[itr] = left_rotated_first_28_bits + left_rotated_last_28_bits;
        cout << "\n\nkey in round " << itr <<" after shifting \n";
        cout<<key_in_round[itr]<<endl;

        ///we now transpose the shifted key using CP_2
        for(int i=0; i< 48; i++)
        {
            modified_key_2[i] = key_in_round[itr][CP_2[i]-1];
        }

        string temp;
        ///printing shifted and CP_2 transposed modified key
        cout<<"\n\nmodified key after using CP_2 in round " << itr << "\n";
        for(int j=0; j< 48; j++)
        {
            temp += modified_key_2[j];

            cout << modified_key_2[j];
        }
        K_I[itr] = temp;
        cout<<endl;
    }
cout<<"out of generate key " <<endl;

}

void print_all_keys()
{
    cout << ".............. Printing ALL KEYS .................\n";

    for(int i=0; i< 2; i++)
    {
        cout << "\n\n......KEY " <<i << " ........\n";
        for(int j=0; j< 56; j++)
        {
            cout << K_I[i][j];
        }
        cout<<endl;
    }

}
int main()
{


    input_key = "megabuck";
    plain_text = "Hello world";

    for(int i=0; i<16; i++)
    {
        //K_I[i] = "";
    }

    add_padding_at_end();

    cout << "plain text with padding is : " << plain_text << endl;

    ///plain test to binary
    string return_binary_str = strToBinary(plain_text);
    cout<< return_binary_str <<endl;

    binary_str_to_64_bit_block(return_binary_str);
    printMatrix();

    ///key string to binary
    string return_binary_str_of_key = strToBinary(input_key);
    cout<< "\nBinary string of key :\n";
    cout << return_binary_str_of_key << endl;

    ///transposition of original key using CP_1
    generate_key(return_binary_str_of_key);


    print_all_keys();

    return 0;
}
