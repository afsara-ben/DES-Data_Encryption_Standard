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
#define ITERATIONS 16

using namespace std;
//GLOBAL
string input_key;
string plain_text;
char chunk_of_64[100][64];
int num_row;
char K_I[16][48]; ///stores key generated in each roung


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

/*char strToChar(const char* str) {
    char parsed = 0;
    for (int i = 0; i < 8; i++) {
        if (str[i] == '1') {
            parsed |= 1 << (7 - i);
        }
    }
    return parsed;
}*/


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

/*Function to left Rotate arr[] of size n by 1*/
char* leftRotatebyOne(char arr[], int n) 
{ 
    char temp = arr[0], i; 
    for (i = 0; i < n - 1; i++) 
        arr[i] = arr[i + 1]; 
  
    arr[i] = temp;
return arr; 
} 

/*Function to left rotate arr[] of size n by d*/
char* leftrotate(char arr[], int d, int n) 
{ 
    for (int i = 0; i < d; i++) 
        return leftRotatebyOne(arr, n); 
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

    char modified_key[100];
        modified_key[56] = '\0';
    char modified_key_for_transposition_with_CP_2[100];
        modified_key_for_transposition_with_CP_2[56] = '\0';

    //transposition of original key using CP_1
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


    //initialize
    char key_in_round[16][100]; //key_in_round is input key for each round
    for(int i=0; i< 16; i++)
    {
        key_in_round[i][56] = '\0';
    }
    
    char first_28_bits[28];
        first_28_bits[28] = '\0';
    char last_28_bits[28];
        last_28_bits[28] = '\0'; 
    
    char* left_rotated_first_28_bits = new char [28];
        left_rotated_first_28_bits[28] = '\0';
    char* left_rotated_last_28_bits = new char[28] ;
        left_rotated_last_28_bits[28] = '\0';

    for(int j=0; j< 56; j++)
    {
        key_in_round[0][j] = modified_key[j];
    }
    cout<<"\n\n..............Input key for round 0 ..............\n";
    printString(key_in_round[0]);


    ///16 iterations should start from here
    for(int itr=0; itr < ITERATIONS; itr++)
    {

        if(itr != 0)
        {

            for(int i=0; i<56; i++)
            {
                key_in_round[itr][i] = key_in_round[itr-1][i];
            }
            cout<<"\n\n..............Input key for round "<<itr << "..............\n";
            printString(key_in_round[itr]);
        }


       cout<<"\nRound - " << itr << " : First 28 bits of key : \n";
        for(int i = 0; i<28; i++)
        {
            first_28_bits[i] = key_in_round[itr][i];
        }

        printString(first_28_bits);

        cout<<"\nRound - " << itr << " : Last 28 bits of key : \n";
        for(int j = 0; j<28; j++)
        {
            last_28_bits[j] = key_in_round[itr][28+j];
        }
        printString(last_28_bits);

        left_rotated_first_28_bits = leftrotate(first_28_bits, SHIFT[itr], 28);
        left_rotated_last_28_bits = leftrotate(last_28_bits, SHIFT[itr], 28);

        cout<<"\n\nRound - " << itr << " : First 28 bits of key after left rotation : \n";
        cout<<left_rotated_first_28_bits;
        cout<<"\n\nRound - " << itr << " : Last 28 bits of key after left rotation : \n";
        cout<<left_rotated_last_28_bits;

        for(int i=0; i<28; i++)
        {
            key_in_round[itr][i] = left_rotated_first_28_bits[i];
            key_in_round[itr][28 + i] = left_rotated_last_28_bits[i];
        }

            cout << "\n\nkey in round " << itr <<" after shifting \n";
        for(int i=0; i<56; i++)
        {
                cout<<key_in_round[itr][i];
        }
        cout<<endl;
        

        ///we now transpose the shifted key using CP_2
        for(int i=0; i< 48; i++)
        {
            modified_key_for_transposition_with_CP_2[i] = key_in_round[itr][CP_2[i]-1];
        }

        
        ///printing shifted and CP_2 transposed modified key
        cout<<"\n\nmodified key after using CP_2 in round " << itr;
        cout<< "\n....... K_I : " << itr <<" ...........\n";
        for(int j=0; j< 48; j++)
        {
        K_I[itr][j] = modified_key_for_transposition_with_CP_2[j];
            cout << modified_key_for_transposition_with_CP_2[j];
        }
        
        cout<<endl;
    }
cout<<"out of generate key " <<endl;

}

void print_all_keys()
{
    cout << "\n.............. Printing ALL KEYS .................\n";

    for(int i=0; i< 16; i++)
    {
        cout << "\n\n......KEY " <<i << " ........\n";
        for(int j=0; j< 48; j++)
        {
            cout << K_I[i][j];
        }
        cout<<endl;
    }

}

char* transpose_data_with_PI(string data_block)
{
    int PI[64] = {58, 50, 42, 34, 26, 18, 10, 2,
      60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6,
      64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25, 17, 9, 1,
      59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5,
      63, 55, 47, 39, 31, 23, 15, 7};

    char* transposed_data = new char[64];
        transposed_data[64] = '\0';

    for(int i=0; i< 64; i++)
    {
        transposed_data[i] = data_block[PI[i]-1];
    }

    //printing transposed data
    cout<<"\n\ntransposed data after using PI \n";
    for(int j=0; j< 64; j++)
    {
        cout << transposed_data[j];
    }
    cout<<endl;
    return transposed_data;
}


char* iteration_steps(string data)
{
    cout<<"\n\nin iteration step" <<endl;

    char* previous_leftmost_32_bits = new char [32];
    char* previous_rightmost_32_bits = new char [32];
    char* next_leftmost_32_bits = new char [32];
    char* next_rightmost_32_bits = new char [32];

    for(int i =0; i<32; i++)
    {
        previous_leftmost_32_bits[i] = data[i]; //this applies only for round 0
        previous_rightmost_32_bits[i] = data[32+i]; //this applies only for round 0
    }

    //16 iterations should start from here
    for(int itr =0; itr<ITERATIONS; itr++)
    {   
        cout << "\n\n.................. ITERATION " << itr << ".................. \n";
        for(int i =0; i<32; i++)
        {
            next_leftmost_32_bits[i] = previous_rightmost_32_bits[i]; //L(i) = R(i-1)
            
        }
        
        int E[48] = {32, 1, 2, 3, 4, 5,
                 4, 5, 6, 7, 8, 9,
                 8, 9, 10, 11, 12, 13,
                 12, 13, 14, 15, 16, 17,
                 16, 17, 18, 19, 20, 21,
                 20, 21, 22, 23, 24, 25,
                 24, 25, 26, 27, 28, 29,
                 28, 29, 30, 31, 32, 1};

        int PI_2[32] = {35, 38, 46, 6, 43, 40, 14, 45,
            33, 19, 26, 15, 23, 8, 22, 10, 
            12, 11, 5, 25, 27, 21, 16, 31,
            28, 32, 34, 24, 9, 37, 2, 1};

        int P[32] = {16, 7, 20, 21, 29, 12, 28, 17,
                 1, 15, 23, 26, 5, 18, 31, 10,
                 2, 8, 24, 14, 32, 27, 3, 9,
                 19, 13, 30, 6, 22, 11, 4, 25};

            
        //leftmost 32 bit expanded to 48 bit using E array
        char expanded_bit[48];
        for(int i =0; i<48; i++)
        {
            expanded_bit[i] = next_leftmost_32_bits[E[i]-1]; 
        }

        //this 48 bit is xor-ed with K_I
        char result_XOR[48];
        char shorten_result[32];
        char p_box[32];

        cout<<"\n\nexpanded 48 bits \n";    
        for(int i =0; i<48; i++)
        {
            cout<<expanded_bit[i];
        }
        cout<<endl;

        cout<<"\n\nK_I \n"; 
        for(int i =0; i<48; i++)
        {
            cout<<K_I[itr][i];
        }
        cout<<endl;
        
        cout<<"\n\nXOR-ed K_I and expanded 48 bit\n"; //R'(i) = e ^ K_I
        for(int i =0; i<48; i++)
        {
            result_XOR[i] = (expanded_bit[i] ^ K_I[itr][i]);
            next_rightmost_32_bits[i] = result_XOR[i];
            cout<<static_cast<int>(result_XOR[i]);
        }
        cout<<endl;

        cout<<"\n\nshortening xor result - Sample 32 bits from the result according to PI_2 array\n";
        for(int i =0; i<32; i++)
        {
            shorten_result [i] = result_XOR[PI_2[i]];
            cout<<static_cast<int>(shorten_result[i]);
        }
        cout<<endl;

        //32 bits now passed through the P box
        cout<<"\n\nafter passing 32 bits through P BOX\n";
        for(int i =0; i<32; i++)
        {
            p_box[i] = shorten_result [P[i]];
            cout<<static_cast<int>(p_box[i]);
        }
        cout<<endl;

        cout<<"\n\nleftmost 32 bit\n"; 
        for(int i =0; i<32; i++)
        {
            cout<<(next_leftmost_32_bits[i]);
        }
        cout<<endl;
        

        //now xor-ing previous left most 32 bit with this p_box value, we get R(i)
        cout<<"\n\nXOR-ed P box val with leftmost 32 bit\n"; 
        for(int i =0; i<32; i++)
        {
            next_rightmost_32_bits[i] = (char)(next_leftmost_32_bits[i] ^ p_box[i]);
            cout<<(next_rightmost_32_bits[i]);
        }
        cout<<endl;

        //now L(i-1) = this leftmost 32 bit and R(i-1) = this rightmost 32 bit
        cout<<"\n\nprevious leftmost 32 bit of itr " << itr <<"\n"; 
        for(int i =0; i<32; i++)
        {
            previous_leftmost_32_bits[i] = next_leftmost_32_bits[i]; 
            previous_rightmost_32_bits[i] = next_rightmost_32_bits[i];
            cout<< previous_leftmost_32_bits[i];
        }
        cout<<endl;
        
        cout<<"\n\nprevious rightmost 32 bit of itr " << itr <<"\n"; 
        for(int i =0; i<32; i++)
        {
            cout<< previous_rightmost_32_bits[i];   
        }
        cout<<endl;

    
    }

    //After iteration stops, swap the left-most 32 bits and rightmost 32 bits
    
    cout<<"\n\ndata block after 16 iterations and swapping\n"; 
    char* data_block_after_iteration_step = new char[64];       
    for(int i =0; i<32; i++)
    {
        data_block_after_iteration_step[i] = next_rightmost_32_bits[i];
        data_block_after_iteration_step[32+i] = next_leftmost_32_bits[i]; 
        
    }
    //print 
    for(int i =0; i<64; i++)
    {
        cout<<data_block_after_iteration_step[i];
    }
    cout<<endl;

return data_block_after_iteration_step;

}
char* transpose_with_PI_1(string data_to_transpose)
{
    int PI_1[64] = {40, 8, 48, 16, 56, 24, 64, 32,
            39, 7, 47, 15, 55, 23, 63, 31,
            38, 6, 46, 14, 54, 22, 62, 30,
            37, 5, 45, 13, 53, 21, 61, 29,
            36, 4, 44, 12, 52, 20, 60, 28,
            35, 3, 43, 11, 51, 19, 59, 27,
            34, 2, 42, 10, 50, 18, 58, 26,
            33, 1, 41, 9, 49, 17, 57, 25};
    
    char *transposed_data = new char[64];
    cout<<"\n\nafter transposing with PI_1\n"; 
    for(int i =0; i<64; i++)
    {
        transposed_data[i] = data_to_transpose[PI_1[i]-1];
        cout<<transposed_data[i];   
    }
    cout<<endl;
return transposed_data;
}

char* decryption_iteration_steps(string data)
{
    cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~ in decryption iteration step ~~~~~~~~~~~~~~~~~~~~~~~~~~" <<endl;

    char* previous_leftmost_32_bits = new char [32];
    char* previous_rightmost_32_bits = new char [32];
    char* next_leftmost_32_bits = new char [32];
    char* next_rightmost_32_bits = new char [32];

    for(int i =0; i<32; i++)
    {
        previous_leftmost_32_bits[i] = data[i]; //this applies only for round 0
        previous_rightmost_32_bits[i] = data[32+i]; //this applies only for round 0
    }

    //16 iterations should start from here
    for(int itr =0; itr<ITERATIONS; itr++)
    {   
        cout << "\n\n.................. DECRYPTION ITERATION " << itr << ".................. \n";
        for(int i =0; i<32; i++)
        {
            next_leftmost_32_bits[i] = previous_rightmost_32_bits[i]; //L(i) = R(i-1)
            
        }
        
        int E[48] = {32, 1, 2, 3, 4, 5,
                 4, 5, 6, 7, 8, 9,
                 8, 9, 10, 11, 12, 13,
                 12, 13, 14, 15, 16, 17,
                 16, 17, 18, 19, 20, 21,
                 20, 21, 22, 23, 24, 25,
                 24, 25, 26, 27, 28, 29,
                 28, 29, 30, 31, 32, 1};

        int PI_2[32] = {35, 38, 46, 6, 43, 40, 14, 45,
            33, 19, 26, 15, 23, 8, 22, 10, 
            12, 11, 5, 25, 27, 21, 16, 31,
            28, 32, 34, 24, 9, 37, 2, 1};

        int P[32] = {16, 7, 20, 21, 29, 12, 28, 17,
                 1, 15, 23, 26, 5, 18, 31, 10,
                 2, 8, 24, 14, 32, 27, 3, 9,
                 19, 13, 30, 6, 22, 11, 4, 25};

            
        //leftmost 32 bit expanded to 48 bit using E array
        char expanded_bit[48];
        for(int i =0; i<48; i++)
        {
            expanded_bit[i] = next_leftmost_32_bits[E[i]-1]; 
        }

        //this 48 bit is xor-ed with K_I
        char result_XOR[48];
        char shorten_result[32];
        char p_box[32];

        cout<<"\n\ndecryption: expanded 48 bits \n";    
        for(int i =0; i<48; i++)
        {
            cout<<expanded_bit[i];
        }
        cout<<endl;

        cout<<"\n\ndecryption: K_I \n"; 
        for(int i =0; i<48; i++)
        {
            cout<<K_I[15-itr][i];
        }
        cout<<endl;
        
        cout<<"\n\ndecryption: XOR-ed K_I and expanded 48 bit\n"; //R'(i) = e ^ K_I
        for(int i =0; i<48; i++)
        {
            result_XOR[i] = (expanded_bit[i] ^ K_I[15-itr][i]);
            next_rightmost_32_bits[i] = result_XOR[i];
            cout<<static_cast<int>(result_XOR[i]);
        }
        cout<<endl;

        cout<<"\n\ndecryption: shortening xor result - Sample 32 bits from the result according to PI_2 array\n";
        for(int i =0; i<32; i++)
        {
            shorten_result [i] = result_XOR[PI_2[i]];
            cout<<static_cast<int>(shorten_result[i]);
        }
        cout<<endl;

        //32 bits now passed through the P box
        cout<<"\n\nafter passing 32 bits through P BOX\n";
        for(int i =0; i<32; i++)
        {
            p_box[i] = shorten_result [P[i]];
            cout<<static_cast<int>(p_box[i]);
        }
        cout<<endl;

        cout<<"\n\nleftmost 32 bit\n"; 
        for(int i =0; i<32; i++)
        {
            cout<<(next_leftmost_32_bits[i]);
        }
        cout<<endl;
        

        //now xor-ing previous left most 32 bit with this p_box value, we get R(i)
        cout<<"\n\ndecryption: XOR-ed P box val with leftmost 32 bit\n"; 
        for(int i =0; i<32; i++)
        {
            next_rightmost_32_bits[i] = (char)(next_leftmost_32_bits[i] ^ p_box[i]);
            cout<<(next_rightmost_32_bits[i]);
        }
        cout<<endl;

        //now L(i-1) = this leftmost 32 bit and R(i-1) = this rightmost 32 bit
        cout<<"\n\ndecryption: previous leftmost 32 bit of itr " << itr <<"\n"; 
        for(int i =0; i<32; i++)
        {
            previous_leftmost_32_bits[i] = next_leftmost_32_bits[i]; 
            previous_rightmost_32_bits[i] = next_rightmost_32_bits[i];
            cout<< previous_leftmost_32_bits[i];
        }
        cout<<endl;
        
        cout<<"\n\ndecryption: previous rightmost 32 bit of itr " << itr <<"\n"; 
        for(int i =0; i<32; i++)
        {
            cout<< previous_rightmost_32_bits[i];   
        }
        cout<<endl;

    
    }

    //After iteration stops, swap the left-most 32 bits and rightmost 32 bits
    
    cout<<"\n\ndecryption: data block after 16 iterations and swapping\n"; 
    char* data_block_after_iteration_step = new char[64];       
    for(int i =0; i<32; i++)
    {
        data_block_after_iteration_step[i] = next_rightmost_32_bits[i];
        data_block_after_iteration_step[32+i] = next_leftmost_32_bits[i]; 
        
    }
    //print 
    for(int i =0; i<64; i++)
    {
        cout<<data_block_after_iteration_step[i];
    }
    cout<<endl;

return data_block_after_iteration_step;

}

string BinaryStringToText(string binaryString) {

    cout<<"in binaryStringTOText "<<endl;
    cout<<"received binary string : \n" << binaryString<<endl;

    int sz=binaryString.size()/8;
    string ans="";
    for(int i=sz-1;i>=0;i--){
        int start=8*i;
        int en=8*(i+1);
        int num=0;
        int power=1;
        for(int j=en-1;j>=start;j--){
            if(binaryString[j]!='0'){
                num+=power;
            }
            power*=2;
        }
        num%=256;
        ans.push_back(num);
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

void decryption(string recvd_data)
{
    char* de_transpose_data_with_PI = new char[64];
    de_transpose_data_with_PI = transpose_data_with_PI(recvd_data);

    //print 
    cout<< "\n\nDE- transposed data using PI \n";
    for(int i =0; i<64; i++)
    {
        cout<< de_transpose_data_with_PI[i];
    }
    cout<<endl;

        
    
    char *decrypted_str =  new char[64];
    decrypted_str = decryption_iteration_steps(de_transpose_data_with_PI);
    cout<<"\ndecryption: "; 
    char* deciphered_text = transpose_with_PI_1(decrypted_str);
    for(int i =0; i<64; i++)
    {
        //deciphered_text[i] += '0';
    }
    cout << "\n\n" << BinaryStringToText(deciphered_text) << "\n";


}


int main()
{


    input_key = "megabuck";
    plain_text = "Hello wo";

    for(int i=0; i<16; i++)
    {
        K_I[i][48] = '\0';
    }

    add_padding_at_end();

    cout << "plain text with padding is : " << plain_text << endl;

    ///plain text to binary
    string return_binary_str = strToBinary(plain_text);
    cout<< return_binary_str <<endl;

    binary_str_to_64_bit_block(return_binary_str);
    printMatrix();

    ///key string to binary
    string return_binary_str_of_key = strToBinary(input_key);
    cout<< "\nBinary string of key :\n";
    cout << return_binary_str_of_key << endl;

    ///generating 16 keys
    generate_key(return_binary_str_of_key);
    print_all_keys();
    
    //key generation done...above

/*  char* data_after_PI_transpose = new char[64];
    char* data_after_completing_16_iterations = new char[64];
    char* sent_data = new char[64];

    //ekhane shob gula block er jonne iteration hobe-apatoto first block hoche
    data_after_PI_transpose = transpose_data_with_PI(chunk_of_64[0]);
    data_after_completing_16_iterations = iteration_steps(data_after_PI_transpose);

    sent_data = transpose_with_PI_1(data_after_completing_16_iterations);
    cout << "\n\n" << BinaryStringToText(sent_data) << "\n";    
    cout<<"\n\n~~~~~~~~~~~~~~~~ ENCRYTION COMPLETE ~~~~~~~~~~~~~~~~~~~\n\n";

    print_all_keys();
    decryption(sent_data);

    cout<<"\n\noriginal binary was : \n" << return_binary_str <<endl;
*/

    return 0;
}