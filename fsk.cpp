#include<iostream>
#include<fstream>
#include<windows.h>
using namespace std;
struct Reader
{
    int data;
    int result;
}R;
int main()
{
    ifstream F;
    system("CLS");
    while(!0)
    {
    cout<<"Enter data to search: ";
    int x;
    cin>>x;
    F.open("mind.ptt",ios::in|ios::binary);
    if(!F){cout<<"mind.ptt not found!"<<endl;continue;}
    while(F.good())
    {
        F.read((char*)&R,8);
        if(F.eof()){cout<<"No Match!"<<endl;F.close();break;}
        if(x==R.data){cout<<R.result<<endl;F.close();break;}
    }
    }
}
