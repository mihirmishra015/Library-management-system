#include<fstream.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<iomanip.h>
#include<stdio.h>

class book
{
	char bno[6];
	char bname[50];
	char aname[20];
public:
	void createbook()
	{
		cout<<"\nNew Book Entry...\n";
		cout<<"\n Enter the book no.";
		cin>>bno;
		cout<<"\n Enter the book name";
		gets(bname);
		cout<<"\n Enter the author's name ";
		gets(aname);
		cout<<"\n\n\nBook Created...";

	}
	void showbook()
	{
		cout<<"\nBook Number :" <<bno;
		cout<<"Book Name : ";
		puts(bname);
		cout<<"Author's Name : ";
		puts(aname);
	}

	void modifybook()
	{ 
        cout<<"\nBook Number : "<< bno;
        cout<<"\nModify Book Name : ";
	gets(bname);
        cout<<"\nModify Author's Name : ";
        gets(aname);
	}

	char* retbno()
	{
		return bno;
	}

	void report()
	{
		cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;
	}
};//class ends here

int tokken;

class student
{
	char admno[6];
	char name[20];
	char stbno[6];
	int token;
public:
	void createstudent()
	{
        clrscr();
        cout<<"\nNew Student Entry...\n";
        cout<<"\nEnter Addmission No. : ";
        cin>>admno;
        cout<<"\nEnter Student's Name : ";
	gets(name);
	int  tokken =0;
	char* stbno="\0";
        cout<<"\n\nStudent Record created...";

	}
	void showstudent()
	{
		cout<<"\nAdmission No. : "<< admno;
		cout<<"\nStudent Name : ";
		puts(name);
		cout<<"\n No of book issued : "<<token;
		if (tokken==1)
		{
			cout<<"\nBook Number : "<< stbno;
		}
	}

	void modifystudent()
	{
		cout<<"\nAdmission No. : "<< admno;
		cout<<"\nModify Student Name : ";
		gets(name);
	}

	char* retadmno()
	{
		return admno;
	}

    char* retstbno()
	{
		return stbno;
	}
	int rettokken()
	{
		return tokken;
	}
	void addtokken()
	{
		tokken=1;
	}
    void resettokken()
    {
    	tokken=0;
    }
    void getstbno(char t[])
    {
    	strcpy(stbno,t);
    }
	void report()
	{
		cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<tokken<<endl;
	}
};//class ends here.


fstream fp ,fp1;
book bk;
student st;

void writebook()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do{
         clrscr();
         bk.createbook();
         fp.write((char*)&bk,sizeof(book));
         cout<<"\n\nDo you want to add more record...(y/n)?";
         cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void writestudent()
{
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do{
         clrscr();
         st.createstudent();
         fp.write((char*)&st,sizeof(student));
         cout<<"\n\nDo you want to add more record...(y/n)?";
         cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void displayspb(char n[])
{
	cout<<"\nBook details\n";
	int flag=0;
	fp.open("book.dat",ios::in);
	while(fp.read((char *)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.showbook();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
	{
		cout<<"Book does not exists..";
		getch();
	}
}

void displaysps(char n[])
{
	cout<<"\nStudent details\n";
	int flag=0;
	fp.open("student.dat",ios::in);
	while(fp.read((char *)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.showstudent();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
	{
		cout<<"Student does not exists..";
		getch();
	}
}

void modifybook()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n\nModify book record...";
	cout<<"\n\nEnter the book no.";
	cin>>n;
	fp.open("book.dat",ios::in||ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found == 0)
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
            bk.showbook();
            cout<<"\nEnter the new details of book"<<endl;
            bk.modifybook();
            int pos = -1*sizeof(bk);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&bk,sizeof(book));
            cout<<"\n\n\tRecord updated";
            found = 1;
		}
	}
	fp.close();
	if(found==0)
	{
		cout<<"\n\nRecoed not found";
	}
	getch();
}

void modifystudent()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n\nModify student record...";
	cout<<"\n\nEnter the admission no.";
	cin>>n;
	fp.open("student.dat",ios::in||ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found == 0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
            st.showstudent();
            cout<<"\nEnter the new details of student"<<endl;
            st.modifystudent();
            int pos = -1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
	    cout<<"\n\n\tRecord updated";
            found = 1;
		}
	}
	fp.close();
	if(found==0)
	{
		cout<<"\n\nRecord not found";
	}
	getch();
}

void deletestudent()
{
	char n[6];
	int flag=0;
	clrscr();
	cout<<"\n\n\tDelete student...";
	cout<<"Enter the admission No.";
	cin>>n;
	fp.open("student.dat",ios::in||ios::out);
	fstream fp2;
	fp2.open("temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)!=0)
		{
            fp2.write((char*)&st,sizeof(student));
		}
		else
		{
			flag=1;
		}
	}
	fp2.close();
	fp.close();
	remove("student.dat");
	rename("temp.dat","student.dat");
	if(flag=1)
	{
		cout<<"\n\n\tRecord Deleted";
	}
	else
	{
		cout<<"\n\n\tRecord not found";
		getch();
	}
}

void deletebook()
{
	char n[6];
	int flag=0;
	clrscr();
	cout<<"\n\n\tDelete Book...";
	cout<<"Enter the book No.";
	cin>>n;
	fp.open("book.dat",ios::in||ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)!=0)
		{
            fp2.write((char*)&bk,sizeof(student));
		}
		else
		{
			flag=1;
		}
	}
	fp2.close();
	fp.close();
	remove("book.dat");
	rename("Temp.dat","book.dat");
	if(flag=1)
	{
		cout<<"\n\n\tRecord Deleted";
	}
	else
	{
		cout<<"\n\n\tRecord not found";
		getch();
	}
}


void displayalls()
{
	clrscr();
	fp.open("student.dat",ios::in);
	if(!fp)
	{
		cout<<"File could not be open";
		getch();
		return;
	}
	cout<<"\n\n\t\tStudent List\n\n";
	cout<<"===================================================================\n";
	cout<<"\tAdmiddion No. "<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
	cout<<"===================================================================\n";
	while(fp.read((char*)&st,sizeof(student)))
	{
		st.report();
	}
	fp.close();
	getch();
}

void displayallb()
{
	clrscr();
	fp.open("book.dat",ios::in);
	if (!fp)
	{
	    cout<<"file could not be open";
	    getch();
	    return;
	}
	cout<<"\n\n\tBook List\n\n";
cout<<"=========================================================================\n";
cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
cout<<"=========================================================================\n";
while(fp.read((char*)&bk,sizeof(book)))
{
	bk.report();
}
fp.close();
getch();
}

void bookissue()
{
	char sn[6],bn[6];
	int found=0,flag=0;
	clrscr();
	cout<<"\n\nBook Issue...";
	cout<<"\n\n\tEnter Admission no of student";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettokken()==0)
			{
				cout<<"\n\n\tEnter the book no.";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book)) && flag==0)
				{
					if(strcmpi(bk.retbno(),bn)==0)
					{
						flag=1;
						st.addtokken();
						st.getstbno(bk.retbno());
						int pos = -1*sizeof(st);
						fp.seekg(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\n\tBook issued Sucessfully\n\nPlease Note:write the book date in Backside of your bookand return within 15 days, fine Rs 1 for each day after 15 days";

					}
				}
				if(flag==0)
				{
					cout<<"Book no. does not exist";
				}
			}
			else
			{
				cout<<"You have not returned the last Book";
			}
		}
	}
	if(found==0)
	{
		cout<<"Student record not exist";
	}
	getch();
	fp.close();
	fp1.close();
}

void bookdeposite()
{
	char sn[6],bn[6];
	int found=0,flag=0;
	clrscr();
	cout<<"\n\nBook Deposite...";
	cout<<"\n\n\tEnter Admission no of student";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettokken()==1)
			{
				
				while(fp1.read((char*)&bk,sizeof(book)) && flag==0)
				{
					if(strcmpi(bk.retbno(),st.retstbno())==0)
					{       int day,fine;
						flag=1;
						bk.showbook();
						cout<<"\n\nBook deposited in no. of days";
						cin>>day;
						if(day>15)
						{
							fine=(day-15)*1;
							cout<<"\n\nFine has to be collected Rs. "<<fine;
						}
						st.resettokken();
						int pos = -1*sizeof(st);
						fp.seekg(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\n\tBook Deposited Sucessfully\n\n";
					}
				}
				if(flag==0)
				{
					cout<<"Book no. does not exist";
				}
			}
			else
			{
				cout<<"No book is issued...";
			}
		}
	}
	if(found==0)
	{
		cout<<"Student record not exist";
	}
	getch();
	fp.close();
	fp1.close();
}

void start()
{
	clrscr();
	gotoxy(35,11);
	cout<<"Library";
	gotoxy(35,14);
	cout<<"Management";
	gotoxy(35,17);
	cout<<"System";
	

	getch();
}

void adminmenu()
{
     clrscr();
     int ch2;
     cout<<"\n\n\n\tADMINISTRATOR MENU";
     cout<<"\n\n\t1.Create Student record";
     cout<<"\n\n\t2.Display all Students record";
     cout<<"\n\n\t3.Display specific Student record";
     cout<<"\n\n\t4.Modify Student record";
     cout<<"\n\n\t5.Delete Student record";
     cout<<"\n\n\t6.Create Book";
     cout<<"\n\n\t7.Display all books";
     cout<<"\n\n\t8.Display specific book";
     cout<<"\n\n\t9.Modify Book record";
     cout<<"\n\n\t10.Delete Book record";
     cout<<"\n\n\t11.Back to main menu\n";
     cout<<"\n\n\tPlease enter your choice (1-11)";
     cin>>ch2;
     switch(ch2)
     {
     	
     	case 1:
	writestudent();
     	break;
     	case 2:
	displayalls();
     	break;
     	case 3:
     	char num[6];
     	cout<<"\n\n\tPlease enter Addmission No.";
     	cin>>num;
	displaysps(num);
     	break;
     	case 4:
	modifystudent();
     	break;
     	case 5:
	deletestudent();
     	break;
     	case 6:
	writebook();
     	break;
     	case 7:
	displayallb();                 
     	break;
     	case 8:
     	char num2[6];
     	cout<<"\n\n\tPlease enter Book No.";
     	cin>>num;
	displayspb(num2);
     	break;
     	case 9:
	modifybook();
     	break;
     	case 10:
	deletebook();
     	case 11:
     	return;
     	default : cout<<"Invalid Choice Try Again";
     }


 }


void main()
{
	char ch;
	
	start();

	do
	{
		clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t1. BOOK ISSUE";
		cout<<"\n\n\t2. BOOK DEPOSIT";
		cout<<"\n\n\t3. ADMINISTRATOR MENU";
		cout<<"\n\n\t4. EXIT";
		cout<<"\n\n\tPlease Select Option(1-4)";
		ch = getche();
		switch(ch)
		{
			case '1':
			bookissue();
			break;
			case '2':
			bookdeposite();
			break;
			case '3':
			adminmenu();
			break;
			case '4':
			exit(0);
			break;
			default:
			cout<< "Invalid Choice Try Again";
		}

	}while(ch!=4);
	
}