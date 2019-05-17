#include <iostream>
#include <bitset>
#include <sstream>
using namespace std;

char* BinaryStringToText(string binaryString) {
    char* text = new char[16];
    stringstream sstream(binaryString);
    while (sstream.good())
    {
        bitset<8> bits;
        sstream >> bits;
        text += char(bits.to_ulong());
    }
	cout<<"printing: \n";
    	for(int i =0; i<16; i++)
	{
		cout<<text[i];
	}
	cout<<endl;
    	return text;
}

int main()
{
    char binaryString[16] = {0,1,0,0,1,0,0,0,0,1,1,0,0,1,0,1};
	
    cout << "\n\nBinary string: \n";
	for(int i =0; i<16; i++)
	{
		cout<<(int)binaryString[i];
	}
	cout<<endl;

    BinaryStringToText(binaryString);

    return 0;
}
