#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<process.h>
#include<conio.h>
using namespace std;
int res_book(int,int);
class book
{
protected:
int bookno,quant;
char bname[50]; 
char aname[50]; 
char pname[50]; 
public:
void createbook();
void showbook();
void showlist();
void assignbookno(int x) 
{ 
bookno=1001;
bookno+=x-1;
start1:
bookno+=1;
if(res_book(bookno,0))
goto start1;
}
void set_quantity()
{
quant-=1;
}
int quantity()
{
return quant;
}
void reset_quantity()
{
quant+=1;
}
int returnbookno()
{
return bookno;
} 
};
void book::createbook()
{
int i;
cout<<"\n\t\tEnter the details:-\n";
cout<<"\n\t\tEnter Book's Name: ";
char n[50];
cin.getline(n,50);
cin.getline(bname,50);
for(i=0;bname[i]!='\0';i++)
{
if(bname[i]>='a'&&bname[i]<='z')
bname[i]-=32;
}
cout<<"\n\t\tEnter Author's Name: ";
cin.getline(aname,50);
cout<<"\n\t\tEnter Publication Name: ";
cin.getline(pname,50);
cout<<"\n\t\tEnter Book's quantity: ";
cin>>quant;
}
void book::showbook()
{
cout<<"\n\t\tBook No.: "<<bookno<<"\n";
cout<<"\n\t\tBook Name: "<<bname<<"\n";
cout<<"\n\t\tBook's Author Name: "<<aname<<"\n";
cout<<"\n\t\tBook's Publication: "<<pname<<"\n";
cout<<"\n\t\tBook's Quantity: "<<quant<<"\n";
}
void book::showlist()
{
cout<<"\n\t"<<bookno<<"\t\t"<<bname<<"\t\t"<<aname<<"\t\t"<<quant;
}
class student
{
protected:
char name[25];
int bno;
int token;
public:
void creates();
void shows();
void showlist();
void settoken(int x)
{
bno=x;
token=1;
}
void resettoken()
{
bno=0;
token=0;
}
int retbno()
{
return bno;
}
int admno;
};
bool res_student(int);
void student::creates() 
{
int i;
plane:
system("CLS");
cout<<"\n\t\tEnter the details:-\n";
cout<<"\n\t\tEnter student's Admission no: ";
cin>>admno;
if(res_student(admno))
{
cout<<"\n\t\tRecord already exist with this admission no.";
cout<<"\n\t\tEnter a different admission no.\n";
system("PAUSE");
goto plane;
}
cout<<"\n\t\tEnter student's Name: ";
char n[50];
cin.getline(n,50);
cin.getline(name,25);
for(i=0;name[i]!='\0';i++)
{
if(name[i]>='a'&&name[i]<='z')
name[i]-=32;
}
bno=0;
token=0;
}
void student::shows() 
{
cout<<"\n\t\tStudent's Admission No.: "<<admno<<"\n";
cout<<"\n\t\tStudent's Name: "<<name<<"\n";
if(token==1)
{
cout<<"\n\t\tBook Issued (Book no): "<<bno;
}
}
void student::showlist() 
{
cout<<"\n\t"<<admno<<"\t\t"<<name<<"\t\t"<<bno;
}
void write_book()
{
book bk;
ofstream outf("book1.bin",ios::app|ios::binary);
outf.seekp(0,ios::end);
int x=outf.tellp()/sizeof(book);
bk.assignbookno(x);
bk.createbook();
bk.showbook();
outf.write(reinterpret_cast<char *>(&bk),sizeof(book));
cout<<"\n\t\tRecord added successfully";
outf.close();
}
void write_student()
{
student st;
ofstream outf("student.bin",ios::app|ios::binary);
outf.seekp(0,ios::end);
st.creates();
st.shows();
outf.write(reinterpret_cast<char *>(&st),sizeof(student));
cout<<"\n\t\tRecord added successfully";
outf.close();
}
void list_student()
{
system("CLS");
student st;
ifstream intf("student.bin",ios::in|ios::binary);
intf.seekg(0,ios::beg);
if(!intf)
cout<<"\n\t\tFile not found";
else
{
cout<<"\n\t*****Students Details*****\n\n";
cout<<"\n\tAdmission No:\tName: \tBook Issued:";
while(intf.read(reinterpret_cast<char *>(&st),sizeof(student)))
st.showlist();
}
intf.close();
}
void list_book()
{
book bk;
ifstream intf("book1.bin",ios::in|ios::binary);
intf.seekg(0,ios::beg);
if(!intf)
cout<<"\n\t\tFile not found";
else
{
cout<<"\n\t*****Books Details*****\n\n";
cout<<"\n\tBook No:\t\tName: \t\tAuthor's Name: \t\tQuantity: ";
while(intf.read(reinterpret_cast<char *>(&bk),sizeof(book)))
bk.showlist();
}
intf.close();
}
void search_student(int x)
{
student st;
int cnt=0;
ifstream intf("student.bin",ios::in|ios::binary);
intf.seekg(0,ios::beg);
if(!intf)
cout<<"\n\t\tFile not found";
else
{
while(intf.read(reinterpret_cast<char *>(&st),sizeof(student)))
{
if(st.admno==x)
{
cnt++;
cout<<"\n\t\tFILE FOUND!!!!";
st.shows();
break;
}
}
if(cnt==0)
cout<<"\n\t\tNo such record exists";
}
intf.close();
}
void search_book(int x)
{
book bk;
int cnt=0;
ifstream intf("book1.bin",ios::in|ios::binary);
intf.seekg(0,ios::beg);
if(!intf)
cout<<"\n\t\tFile not found";
else
{
while(intf.read(reinterpret_cast<char *>(&bk),sizeof(book)))
{
if(bk.returnbookno()==x)
{
cnt++;
cout<<"\n\t\tFILE FOUND!!!!";
bk.showbook();
break;
}
}
if(cnt==0)
cout<<"\n\t\tNo such record exists";
}
intf.close();
}
void modify_book(int x)
{
book bk;
int cnt=0;
fstream intf("book1.bin",ios::in|ios::out|ios::ate|ios::binary);
intf.seekg(0,ios::beg);
if(!intf)
cout<<"\n\t\tFile not found";
else
{
while(intf.read(reinterpret_cast<char *>(&bk),sizeof(book)))
{
if(bk.returnbookno()==x)
{
cnt++;
bk.createbook();
bk.showbook();
intf.seekp(intf.tellp()-sizeof(book));
intf.write(reinterpret_cast<char *>(&bk),sizeof(book));
cout<<"\n\t\tRecord Updated";
break;
}
}
if(cnt==0)
cout<<"\n\t\tNo such record exists";
}
intf.close();
}
void modify_student(int x)
{
student st;
int cnt=0;
fstream intf("student.bin",ios::in|ios::out|ios::ate|ios::binary);
intf.seekg(0,ios::beg);
if(!intf)
cout<<"\n\t\tFile not found";
else
{
while(intf.read(reinterpret_cast<char *>(&st),sizeof(student)))
{
if(st.admno==x)
{
cnt++;
st.creates();
st.shows();
intf.seekp(intf.tellp()-sizeof(student));
intf.write(reinterpret_cast<char *>(&st),sizeof(student));
cout<<"\n\t\tRecord Updated";
break;
}
}
if(cnt==0)
cout<<"\n\t\tNo such record exists";
}
intf.close();
}
void delete_student(int x)
{
student st;
int cnt=0;
ifstream intf("student.bin",ios::in|ios::binary);
intf.seekg(0,ios::beg);
if(!intf)
cout<<"\n\t\tFile not found";
else
{
ofstream outf("temp.bin",ios::app|ios::binary);
while(intf.read(reinterpret_cast<char *>(&st),sizeof(student)))
{
if(st.admno==x)
cnt++;
else
outf.write(reinterpret_cast<char *>(&st),sizeof(student));
}
intf.close();
outf.close();
if(cnt==0)
{
remove("temp.bin");
cout<<"\n\t\tNo such record exists";
}
else
{
remove("student.bin");
rename("temp.bin","student.bin");
cout<<"\n\t\tRecord deleted successfully";
}
}
}
void delete_book(int x)
{
book bk;
int cnt=0;
ifstream intf("book1.bin",ios::in|ios::binary);
intf.seekg(0,ios::beg);
if(!intf)
cout<<"\n\t\tFile not found";
else
{
ofstream outf("temp1.bin",ios::app|ios::binary);
while(intf.read(reinterpret_cast<char *>(&bk),sizeof(book)))
{
if(bk.returnbookno()==x)
cnt++;
else
outf.write(reinterpret_cast<char *>(&bk),sizeof(book));
}
intf.close();
outf.close();
if(cnt==0)
{
remove("temp1.bin");
cout<<"\n\t\tNo such record exists";
}
else
{
remove("book.bin");
rename("temp1.bin","book.bin");
cout<<"\n\t\tRecord deleted successfully";
}
}
}
bool res_student(int x)
{
student st;
int cnt=0,f=0;
ifstream intf("student.bin",ios::in|ios::binary);
intf.seekg(0,ios::beg);
if(!intf)
f=1;
else
{
while(intf.read(reinterpret_cast<char *>(&st),sizeof(student)))
{
if(st.admno==x)
{
cnt++;
break;
}
}
if(cnt==0)
f=1;
}
intf.close();
if(f)
return 0;
else
return 1;
}
int res_book(int x,int z)
{
book bk;
int cnt=0,f=1;
fstream intf("book1.bin",ios::in|ios::out|ios::ate|ios::binary);
intf.seekg(0,ios::beg);
if(!intf)
f=0;
else
{
while(intf.read(reinterpret_cast<char *>(&bk),sizeof(book)))
{
if(bk.returnbookno()==x)
{
cnt++;
if(z==1)
{
bk.showbook();
if(bk.quantity()>0)
{
bk.set_quantity();
intf.seekp(intf.tellp()-sizeof(book));
intf.write(reinterpret_cast<char 
*>(&bk),sizeof(book));
}
else
f=2;
}
else if(z==2)
{
bk.showbook();
bk.reset_quantity();
intf.seekp(intf.tellp()-sizeof(book));
intf.write(reinterpret_cast<char *>(&bk),sizeof(book));
}
break;
}
}
if(cnt==0)
f=0;
}
intf.close();
return f;
}
void book_issue()
{
int sn,bn;
system("CLS");
cout<<"\n\n\t\t*****BOOK ISSUE******";
cout<<"\n\n\t\tEnter the student's admission no: ";
cin>>sn;
int cnt=0;
student st;
fstream outf("student.bin",ios::in|ios::out|ios::ate|ios::binary);
outf.seekg(0,ios::beg);
if(!outf)
cout<<"\n\t\tFile not found\n";
else
{
while(outf.read(reinterpret_cast<char *>(&st),sizeof(student)))
{
if(st.admno==sn)
{
cnt++;
list_book();
cout<<"\n\n\t\tEnter the book no.:";
cin>>bn;
cout<<"\n";
int flag=res_book(bn,1);
if(flag==1)
{
st.settoken(bn);
outf.seekp(outf.tellp()-sizeof(student));
outf.write(reinterpret_cast<char *>(&st),sizeof(student));
cout<<"\n\t\tBook Issued";
cout<<"\n\t\tNote: Write the current date in backside of 
the book";
cout<<"\n\t\t Should be submitted within 15 days to 
avoid fine";
cout<<"\n\t\t The fine is Rs. 1 for each day after 15 days 
period\n";
break;
}
else if(flag==2)
{
cout<<"\n\t\tTHE BOOK IS OUT OF STOCK!!!";
break;
}
else
{
cout<<"\n\t\tNo such record exists\n";
break;
}
}
}
if(cnt==0)
cout<<"\n\t\tNo such record exists\n";
}
outf.close();
}
void book_deposit()
{
int sn,bn;
system("CLS");
cout<<"\n\n\t\t*****BOOK DEPOSIT******";
cout<<"\n\n\t\tEnter the student's admission no: ";
cin>>sn;
int cnt=0;
student st;
fstream outf("student.bin",ios::in|ios::out|ios::ate|ios::binary);
outf.seekg(0,ios::beg);
if(!outf)
cout<<"\n\t\tFile not found\n";
else
{
while(outf.read(reinterpret_cast<char *>(&st),sizeof(student)))
{
if(st.admno==sn)
{
cnt++;
bn=st.retbno();
bool flag=res_book(bn,2);
if(flag)
{
st.resettoken();
outf.seekp(outf.tellp()-sizeof(student));
outf.write(reinterpret_cast<char *>(&st),sizeof(student));
int days;
cout<<"\n\t\tBook deposited in no. of days:";
cin>>days;
if(days>15)
{
int fine=(days-15)*1;
cout<<"\n\n\t\tFine: "<<fine<<"\n";
}
cout<<"\n\t\tBook Deposited Successfully\n";
break;
}
else
{
cout<<"\n\t\tNo such record exists\n";
break;
}
}
}
if(cnt==0)
cout<<"\n\t\tNo such record exists\n";
}
outf.close();
}
void admin_menu()
{
fine:
system("PAUSE");
system("CLS");
int opt;
cout<<"\n\n\n\t\t\t******ADMINISTRATOR MENU******";
 cout<<"\n\n\t1.\tCREATE STUDENT RECORD";
 cout<<"\n\n\t2.\tDISPLAY ALL STUDENTS RECORD";
 cout<<"\n\n\t3.\tDISPLAY SPECIFIC STUDENT RECORD ";
 cout<<"\n\n\t4.\tMODIFY STUDENT RECORD";
 cout<<"\n\n\t5.\tDELETE STUDENT RECORD";
 cout<<"\n\n\t6.\tCREATE BOOK ";
 cout<<"\n\n\t7.\tDISPLAY ALL BOOKS ";
 cout<<"\n\n\t8.\tDISPLAY SPECIFIC BOOK ";
 cout<<"\n\n\t9.\tMODIFY BOOK ";
 cout<<"\n\n\t10.\tDELETE BOOK ";
 cout<<"\n\n\t11.\tBACK TO MAIN MENU";
 cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
 cin>>opt;
 if(opt==1)
 {
 system("CLS");
 write_student();
 cout<<"\n";
 goto fine;
}
else if(opt==2)
{
system("CLS");
 list_student();
 cout<<"\n";
 goto fine;
}
else if(opt==3)
{
system("CLS");
int ad;
cout<<"\n\n\n\t\tEnter the admission no. of the student";
cin>>ad;
search_student(ad);
cout<<"\n";
goto fine;
}
else if(opt==4)
{
system("CLS");
int ad;
cout<<"\n\n\n\t\tEnter the admission no. of the student";
cin>>ad;
modify_student(ad);
cout<<"\n";
goto fine;
}
else if(opt==5) 
{
system("CLS");
int ad;
cout<<"\n\n\n\t\tEnter the admission no. of the student";
cin>>ad;
delete_student(ad);
cout<<"\n";
goto fine;
}
else if(opt==6)
 {
 system("CLS");
 write_book();
 cout<<"\n";
 goto fine;
}
else if(opt==7)
{
system("CLS");
 list_book();
 cout<<"\n";
 goto fine;
}
else if(opt==8)
{
system("CLS");
int ad;
cout<<"\n\n\n\t\tEnter the book no. of the book";
cin>>ad;
search_book(ad);
cout<<"\n";
goto fine;
}
else if(opt==9)
{
system("CLS");
int ad;
cout<<"\n\n\n\t\tEnter the book no. of the book";
cin>>ad;
modify_book(ad);
cout<<"\n";
goto fine;
}
else if(opt==10)
{
system("CLS");
int ad;
cout<<"\n\n\n\t\tEnter the book no. of the book";
cin>>ad;
delete_book(ad);
cout<<"\n";
goto fine;
}
else if(opt==11)
return ;
else
{
cout<<"\n\t\tEnter correct option";
cout<<"\n";
goto fine;
}
}
bool passwords()
{
int i=0;
char ch,st[21],ch1[21]={"SRM123"};
cout<<"\n\n\t\tEnter Password : ";
while(1)
 {
 ch=getch();
 if(ch==13)
 {
 st[i]='\0';
 break;
 }
 else if(ch==8&&i>0)
 {
 i--;
 cout<<"\b \b";
 }
 else
 {
 cout<<"*";
 st[i]=ch;
 i++;
 }
 }
 for(i=0;st[i]==ch1[i]&&st[i]!='\0'&&ch1[i]!='\0';i++);
 if(st[i]=='\0'&&ch1[i]=='\0')
 return 1;
 else
 return 0;
}
int main()
{
cout<<"\n\n\t\t\t*******************************************";
cout<<"\n\t\t\t\tSRM - AP LIBRARY MANAGEMENT SYSTEM";
cout<<"\n\t\t\t*******************************************";
bool a=passwords();
if(!a)
{
for(int i=0;i<2;i++)
{
cout<<"\nWrong password";
cout<<"\nYou have "<<2-i<<"attempts left";
if(passwords())
goto last;
if(i==1)
{
cout<<"\n\n\n\t\t\t All attempts failed........";
cout<<"\n\n\t\t\t Sorry, but you can't login";
exit(0);
}
}
}
last:
cout<<"\n\n";
start:
system("PAUSE");
system("CLS");
int opt;
cout<<"\n\n\t\t\t------------------------------------------";
cout<<"\n\t\t\t\tLIBRARY MANAGEMENT SYSTEM";
cout<<"\n\t\t\t------------------------------------------";
cout<<"\n\n\t\t\tWhat do you want to do?";
cout<<"\n\t\t\t1.\tBOOK ISSUE";
cout<<"\n\t\t\t2.\tBOOK DEPOSIT";
cout<<"\n\t\t\t3.\tADMINISTRATOR MENU";
cout<<"\n\t\t\t4.\tExit";
cout<<"\n\n Choose your option: ";
cin>>opt;
if(opt==1)
{
system("CLS");
book_issue();
goto start;
}
else if(opt==2)
{
system("CLS");
book_deposit();
goto start;
}
else if(opt==3)
{
admin_menu();
goto start;
}
else if(opt==4)
exit(0);
else
{
cout<<"\n\t\tEnter correct option";
goto start;
}
}
