#include<iostream>
#include<cmath>
#include<stdlib.h>
using namespace std;

typedef struct
{
    string data;
    int randNo;
    int seqNo;
    int size;
}frame;

void insertSort(frame f[],int n,char ch)
{
    int i,j;
    frame v;
    for(i=1;i<n;i++)
    {
        v=f[i];
        j=i-1;    
        while(j>=0 && ((f[j].randNo>v.randNo &&  ch=='r') || (f[j].seqNo>v.seqNo &&  ch=='s')))
        {
            f[j+1]=f[j];
            j--;
        }   
		f[j+1]=v; 
    }
}

void display(frame f[],int n)
{
	int i;
	cout<<"Sequence\tRandom\tLength\tPacket"<<endl;
	cout<<"------------------------------------------"<<endl;
    for(i=0;i<n;i++)
        cout<<f[i].seqNo<<"\t\t"<<f[i].randNo<<"\t"<<f[i].size<<"\t"<<f[i].data<<endl;	
	cout<<"------------------------------------------"<<endl;
}

int main()
{
    string msg,recMsg="";
    int maxFrLen;
    int i=0,j=0,n=0;
	cout<<"Enter msg : ";cin>>msg;
	cout<<"Enter len : ";cin>>maxFrLen;	
    frame f[msg.length()];
	
	//Dividing message into frames
    while(j<msg.length())
    {
        f[n].randNo=rand()%100;
        f[n].seqNo=n+1;
        f[n].size=rand()%maxFrLen+1;
        f[n].data=msg.substr(j,f[n].size);
        j+=f[n].size;
        n++;
    }

	//Displaying Results
	cout<<"***Divided into Frames***"<<endl;
	display(f,n);

	insertSort(f,n,'r');		//'r' indicates randomised sort

	cout<<"***Received as***"<<endl;
    display(f,n);

	insertSort(f,n,'s');		//'s' indicates sequential sort
	
	cout<<"***Frame Reconstruction***"<<endl;
	cout<<"Receiver End"<<endl;
    display(f,n);
	
	for(i=0;i<n;i++)
		recMsg.append(f[i].data);
	cout<<"Received Message = "<<recMsg<<endl;	

    return 0;
}
