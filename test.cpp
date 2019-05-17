#include <iostream>
#include <bitset>
#include <sstream>
#include<algorithm> 
using namespace std;

/*string BinaryStringToText(char* binaryString) {
    

	for(int i =0; i<16; i++)
	{
		cout<< (int)binaryString[i];
	}
	cout<<endl;


    //char* text = new char[16];
	string text="";
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
		cout<<(char)text[i];
	}
	cout<<endl;

    	return text;
}*/
string BinaryStringToText(string binaryString) {

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

int main()
{
    char binaryString[16] = {0,1,0,0,1,0,0,0,0,1,1,0,0,1,0,1};
	for(int i =0; i<16; i++)
	{
		binaryString[i] += '0';
	}
	cout<<endl;
	
   	 cout << "\n\nBinary string: \n";
	for(int i =0; i<16; i++)
	{
		cout<<(int)binaryString[i];
	}
	cout<<endl;
	string out = BinaryStringToText(binaryString);
 
    
	
    return 0;
}
