//*
//                   HEADER FILE USED IN PROJECT
//*

#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<vector>
using namespace std;
//*
//    	function declaration
//*
void write_account();	//function to write record in binary file
void display_all();		//function to display all account details
void all_items(); //function to display  all items
void intro();	//introductory screen function
void add_item();//add item in the  item list
void edit_item(); //edit item in list
void delete_item(); //delete item in item list
struct Items
    {
        string itemname;
        int price;
    };
vector<Items> item;

//*
//                   CLASS USED IN PROJECT
//*


class account
{
	int age;
	char roll[50];
	char type;
    int total=0;
public:
	void create_account();	//function to get data from user
	void show_account() const;	//function to show data on screen
	friend void report(account &);	//function to show data in tabular format
};        
//class ends here

void account::create_account()
{
    int i=1,x=1;
	cout<<"\n\nEnter The Roll of customer : ";
	cin.ignore();// to clear input buffer
	cin.getline(roll,50);
	cout<<"\nEnter The age :";
	cin>>age;
	cout<<"\nEnter gender of customer (m/f) : ";
	cin>>type;
	type=toupper(type);// converts character to upper
	cout<<"\n\n\n Customer Created.."<<endl<<endl;
	all_items();
	cout<<endl;
	while(1)
    {
        cout<<"press 0 to submit"<<endl<<endl;
        cout<<"enter the item id you want to purchase"<<endl;
        if(i<=item.size())
        {
        cin>>i;
        if(i==0)
            break;
        cout<<"enter the number of quantity you want of that  item"<<endl;
        cin>>x;
        total=total+(item[i-1].price*x);
        }
        else
            cout<<"invalid entry"<<endl;

    }
    cout<<"your bill is "<<total<<endl;

}

void account::show_account() const
{
	cout<<"\nAge : "<<age;
	cout<<"\ncustomer Roll : ";
	cout<<roll;
	cout<<"\ngender of customer : "<<type;
}


void report(account &obj)
{
	cout<<obj.age<<setw(10)<<" "<<obj.roll<<setw(10)<<" "<<obj.type<<setw(6)<<obj.total<<endl<<endl;
}






//*
//    	THE MAIN FUNCTION OF PROGRAM
//*


int main()
{
	char ch;
    item.push_back({"chips",20});
    item.push_back({"kurkure",50});
	intro();
	do
	{
		system("cls");//in stdlib.h
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW CUSTOMER";
		cout<<"\n\n\t02. ALL ITEMS";
		cout<<"\n\n\t03. ADD NEW ITEMS";
		cout<<"\n\n\t04. EDIT ITEM";
		cout<<"\n\n\t05. ALL CUSTOMERS LIST";
		cout<<"\n\n\t06. DELETE ITEM";
		cout<<"\n\n\t07. EXIT";
		cout<<"\n\n\tSelect Your Option (1-7) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
		    all_items();
            break;
		case '3':
            add_item();
			break;
		case '4':
            edit_item();
			break;
		case '5':
			display_all();
			break;
		case '6':
            delete_item();
			break;
		case '7':
			cout<<"\n\n\tThanks for using canteen management system";
			break;
		default :cout<<"\a"; // visible alert
		}
		cin.ignore();
		cin.get();
	}while(ch!='7');
	return 0;
}


//*
//    	function to write in file
//*

void write_account()
{
	account ac;
	ofstream outFile; // opens a file for writing
	outFile.open("account.dat",ios::binary|ios::app);// generic data file
	//ios :: app all output operations are performed at the
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();

}

//*
//    	function to display all items
//*

void  all_items()
{
    int i=0;
    cout<<"item id"<<"\t"<<"itemname"<<"\t"<<"price"<<endl<<endl;
    for(i=0;i<item.size();i++)
    {
        cout<<i+1<<"\t"<<item[i].itemname<<"\t\t"<<item[i].price<<endl;
    }

}

//*
//    	function to modify record of file
//*
void add_item()
{
    string a;
    int b;
    cout<<"enter the item name"<<endl;
    cin>>a;
    cout<<"enter the item price"<<endl;
    cin>>b;
    item.push_back({a,b});
    cout<<"item added successfully"<<endl<<endl;
    all_items();
}
//*
//    	function to edit item in list
//*
void edit_item()
{
    int j;
    cout<<"enter the id of item"<<endl;
    cin>>j;
    if(j<=item.size()){
    cout<<"enter the item name"<<endl;
    cin>>item[j-1].itemname;
    cout<<"enter the item price"<<endl;
    cin>>item[j-1].price;
    cout<<endl<<"item edited successfully"<<endl;
    }
    else
    {
        cout<<"invalid entry";
    }
}
void delete_item()
{
    int j;
    cout<<"enter the id of item"<<endl;
    cin>>j;
    if(j<=item.size()){
    item.erase(item.begin()+j-1);
    cout<<endl<<"item deleted successfully"<<endl;
    }
    else
    {
        cout<<"invalid entry";
    }
}

//*
//    	function to display all customers bill list
//*

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);//ios::binary makes sure the data is read or written without translating new line characters to and from \r\n on the fly. In other words, exactly what you give the stream is exactly what's written.
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tCUSTOMER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"Age     	ROLL           Type      Bill\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		report(ac);
	}
	inFile.close();
}

//*
//    	INTRODUCTION FUNCTION
//*


void intro()
{
	cout<<"\n\n\n\tDTU     CANTEEN";
	cout<<"\n\n\t  MANAGEMENT";
    cout<<"\n \n";
	cin.get();
}

