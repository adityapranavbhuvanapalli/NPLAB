#include<iostream>
using namespace std;

int main()
{
	int i,j,flag=0;
	string dataWord,codeWord,augWord,div,recCode;
	string genWord="10001000000100001";	//x^16 + x^12 + x^5 +1 
 	
	//Sender's End
	cout<<"Sender's End :"<<endl;
	cout<<"Gen Word : "<<genWord<<" i.e.,  x^16 + x^12 + x^5 +1"<<endl;
	
	cout<< "Enter the data word : "; cin>>dataWord;
	augWord=dataWord+"0000000000000000";	//appending 16 zeroes
	cout<<"Aug Data Word = " << augWord <<endl;	

	codeWord=augWord;
	for(i=0;i<dataWord.length();i++)
	{
		div = (codeWord[i]=='1') ? genWord : "00000000000000000" ;
		for(j=0;j<genWord.length();j++)
			codeWord[i+j] = ( codeWord[i+j]==div[j] ) ? '0' : '1' ;
	}

	for(i=0;i<dataWord.length();i++)
		codeWord[i]=dataWord[i];

	cout<<endl<<"Code Word = "<<codeWord<<endl;

	//Receiver's End
	cout<<endl<<"Receiver's End :"<<endl;
	cout<<"Enter the received code word : "; cin>>recCode;
	//recCode=codeWord;	
	
	for(i=0;i<dataWord.length();i++)
	{
		div = (recCode[i]=='1') ? genWord : "00000000000000000" ;
		for(j=0;j<genWord.length();j++)
			recCode[i+j] = ( recCode[i+j]==div[j] ) ? '0' : '1' ;
	}

	cout<<endl<<"Syndrome = "<<recCode<<endl;

	for(i=0;i<recCode.length();i++)
		if(recCode[i]!='0') 
			flag=1;
	
	if(flag==1) cout<<"Invalid"<<endl;
	else
	{
		cout<<"Valid"<<endl;
		cout<<"Message = "<<dataWord<<endl;
	}


	return 0;
}

/*******************************************************

Output:
1.

Sender's End :
Gen Word : 10001000000100001 i.e.,  x^16 + x^12 + x^5 +1
Enter the data word : 11110001
Aug Data Word = 111100010000000000000000

Code Word = 111100011111111100111110

Receiver's End :
Enter the received code word : 111100011111111100111110

Syndrome = 000000000000000000000000
Valid
Message = 11110001


*********************************
2.

Sender's End :
Gen Word : 10001000000100001 i.e.,  x^16 + x^12 + x^5 +1
Enter the data word : 11110001
Aug Data Word = 111100010000000000000000

Code Word = 111100011111111100111110

Receiver's End :
Enter the received code word : 111100011111111100111111            

Syndrome = 000000000000000000000001
Invalid

**********************************************************/

