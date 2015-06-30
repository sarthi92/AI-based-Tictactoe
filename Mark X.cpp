#include<iostream>
#include<fstream>
#include<ctime>
#include<windows.h>
using namespace std;
struct Node
{
    int data;
    int prob;
    Node* next[10];
};
struct Reader
{
    int data;
    int result;
}M;
ofstream F;
int mx[3][3];
int W,cwin,closs,cdraw;
void init(Node*);
void expand(int,int);
void mx_reset();
int winlose();
int main()
{
  system("TITLE Mark I Lister By Xenocoder");
  srand(time(NULL));

  Node* root;
  root=new Node;
  root->data=0;
  root->prob=0;

  cout<<"WAIT...";
  cwin=closs=cdraw=0;
  F.open("mind.ptt",ios::out|ios::binary);
  init(root);
  F.close();
  cout<<"\n\n*Win Paths: "<<cwin<<"\n*Loss Paths: "<<closs<<"\n*Draw Paths: "<<cdraw<<"\n\n";
  system("PAUSE");
}
void init(Node* P)
{
    int avoid_stack[9];
    int i,j=1,top=-1,temp=P->data;
    mx_reset();
    while(temp!=0)
    {
        avoid_stack[++top]=temp%10;
        temp/=10;
    }
    for(i=top;i>=0;--i)
    {
        expand(avoid_stack[i],j);
        if(j==1){j=0;}
        else{j=1;}
    }
    W=winlose();
    if(W==3)
    {
        ++cwin;
        M.data=P->data;
        M.result=1;
        F.write((char*)&M,8);
        return;
    }
    if(W==0)
    {
        ++closs;
        M.data=P->data;
        M.result=0;
        F.write((char*)&M,8);
        return;
    }
    if(W==5){++cdraw;return;}
    Node* L[10];
    for(i=1;i<=9;++i)
    {
        for(j=0;j<=top;++j)
        {
            if(i==avoid_stack[j]){break;}
        }
        if(j==top+1)
        {
            L[i]=new Node;
            P->next[i]=L[i];
            L[i]->data=P->data*10+i;
            L[i]->prob=0;
            init(L[i]);
        }
    }
}
void mx_reset()
{
    for(int i=0;i<3;++i)
    fill(mx[i],mx[i]+3,100);
}
void expand(int x,int y)
{
    --x;
    mx[x/3][x%3]=y;
}
int winlose()
{
    int i,j,sum;
    for(i=0;i<3;++i)//rows
    {
    sum=0;
    for(j=0;j<3;++j)
    {
        sum+=mx[i][j];
    }
    if(sum==3){return 3;}
    if(sum==0){return 0;}
    }

    for(i=0;i<3;++i)//cols
    {
    sum=0;
    for(j=0;j<3;++j)
    {
        sum+=mx[j][i];
    }
    if(sum==3){return 3;}
    if(sum==0){return 0;}
    }

    if((mx[0][0]+mx[1][1]+mx[2][2]==3)||(mx[0][2]+mx[1][1]+mx[2][0]==3)){return 3;}//dia1 sum
    if((mx[0][0]+mx[1][1]+mx[2][2]==0)||(mx[0][2]+mx[1][1]+mx[2][0]==0)){return 0;}//dia2 sum

    sum=0;
    for(i=0;i<3;++i)
    for(j=0;j<3;++j)
    {
        sum+=mx[i][j];
    }
    if(sum==5){return 5;}
    return 100;
}
