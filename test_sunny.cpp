#include <iostream>
#include <bitset>
#include <sstream>
using namespace std;


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
    return ans;
}

int main()
{
    char binaryString[] = {'0','1','0','0','1','0','0','0','0','1','1','0','0','1','0','1',0};


    cout<<BinaryStringToText(binaryString);

    return 0;
}
