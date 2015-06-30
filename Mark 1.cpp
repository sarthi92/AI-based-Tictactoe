#include<iostream>
#include<fstream>
#include<vector>
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
}R,M;
HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
COORD C;
ifstream F;
ofstream W;
int mx[3][3];
int flag;
void init(Node*,int);
void learn(Node*);
void visit(Node*,int);
void expand(int,int);
void print(int,int);
void skeleton();
void endp();
int winlose();
int exists(int);
int main()
{
  system("TITLE AI Mark I By Xenocoder");
  srand(time(NULL));

  Node* root;
  root=new Node;
  root->data=0;
  root->prob=0;

  cout<<"WAIT...";
  init(root,0);
  learn(root);

  while(!0)
  {
  system("CLS");
  for(int i=0;i<3;++i)
  fill(mx[i],mx[i]+3,100);
  skeleton();

  flag=0;
  M.data=0;
  visit(root,0);
  endp();
  }
}
void init(Node* P,int level)
{
    int avoid_stack[9];
    if(level==9){return;}
    Node* L[10];
    int i,j,top=-1,temp=P->data;
    while(temp!=0)
    {
        avoid_stack[++top]=temp%10;
        temp/=10;
    }
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
        init(L[i],level+1);
        }
    }
}
void learn(Node* T)
{
  Node* Q;
  int temp;
  F.open("mind.ptt",ios::in|ios::binary);
  while(F.good())
  {
      F.read((char*)&R,8);
      if(F.eof()){F.close();break;}
      temp=0;
      Q=T;
      while(R.data!=0)
      {
          temp=temp*10+R.data%10;
          R.data/=10;
      }
      R.data=temp;
      while(R.data!=0)
      {
          Q=Q->next[R.data%10];
          if(R.result==1){Q->prob++;}
          else{Q->prob--;}
          R.data/=10;
      }
  }
}
void visit(Node* P,int level)
{
    int z,i,max;
    vector<int>v;
    if(winlose()==3)
    {
    F.open("mind.ptt",ios::in|ios::binary);
    while(F.good())
    {
        F.read((char*)&R,8);
        if(F.eof()){F.close();break;}
        if(R.data==M.data){flag=1;break;}
    }
    if(flag==0)
    {
    W.open("mind.ptt",ios::out|ios::app|ios::binary);
    M.result=1;
    W.write((char*)&M,8);
    P->prob++;
    W.close();
    }
    return;
    }
    else if(winlose()==0)
    {
    F.open("mind.ptt",ios::in|ios::binary);
    while(F.good())
    {
        F.read((char*)&R,8);
        if(F.eof()){F.close();break;}
        if(R.data==M.data){flag=1;break;}
    }
    if(flag==0)
    {
    W.open("mind.ptt",ios::out|ios::app|ios::binary);
    M.result=0;
    W.write((char*)&M,8);
    P->prob--;
    W.close();
    }
    return;
    }
    else if(winlose()==5){return;}
    if(level%2==0)//AI Turn
    {
        max=0;
        for(i=1;i<=9;++i)
        {
            if(!exists(i))
            {
                if(max==0){max=i;}
                else if(P->next[i]->prob>P->next[max]->prob){max=i;};
            }
        }
        for(i=1;i<=9;++i)
        {
            if(!exists(i))
            {
                if(P->next[i]->prob==P->next[max]->prob){v.push_back(i);}
            }
        }
        i=rand()%v.size();
        max=v[i];
        if(level==0){max=rand()%9+1;}//to make less boring
        print(max,1);
        M.data=M.data*10+max;
        visit(P->next[max],level+1);
    }
    else//Player Turn
    {
    C.X=5;
    C.Y=5;
    while(!0)
    {
    SetConsoleCursorPosition(H,C);
    cin>>z;
    if(!exists(z)&&z>=1&&z<=9){break;}
    }
    print(z,0);
    M.data=M.data*10+z;
    visit(P->next[z],level+1);
    }
    if(winlose()==3&&flag==0){P->prob++;}
    else if(winlose()==0&&flag==0){P->prob--;}
}
void endp()
{
    C.X=5;
    C.Y=20;
    SetConsoleCursorPosition(H,C);
    system("PAUSE");
}
void expand(int x,int y)
{
    --x;
    mx[x/3][x%3]=y;
}
int exists(int x)
{
    --x;
    if((mx[x/3][x%3]==1)||(mx[x/3][x%3]==0))
    {return 1;}
    return 0;
}
void print(int x,int y)
{
    expand(x,y);
    switch(x)
    {
        case 1: C.X=10;C.Y=5;break;
        case 2: C.X=20;C.Y=5;break;
        case 3: C.X=30;C.Y=5;break;
        case 4: C.X=10;C.Y=10;break;
        case 5: C.X=20;C.Y=10;break;
        case 6: C.X=30;C.Y=10;break;
        case 7: C.X=10;C.Y=15;break;
        case 8: C.X=20;C.Y=15;break;
        case 9: C.X=30;C.Y=15;break;
    }
    SetConsoleCursorPosition(H,C);
    if(y==1){cout<<"X";}
    else{cout<<"O";}
}
void skeleton()
{
    for(C.X=15;C.X<=25;C.X+=10)//vertical margins
    for(C.Y=4;C.Y<=17;++C.Y)
    {
        SetConsoleCursorPosition(H,C);
        cout<<char(219);
    }
    for(C.Y=8;C.Y<=13;C.Y+=5)//horizontal margins
    for(C.X=8;C.X<=32;++C.X)
    {
        SetConsoleCursorPosition(H,C);
        cout<<char(219);
    }
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
