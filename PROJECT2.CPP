#include<conio.h>
#include<process.h>
#include<fstream>
#include<iomanip>
#include<iostream>
using namespace std;

class calc;

class payroll
{
 public:
	double empid,hrsworked,hrlypay,bonus,due;
	char empname[20],marstat;

	friend class calc;
	void create_emprecord(double);
	void create_modify();
	void show();
	double retid();
	char* retname();
 };


	void payroll:: create_emprecord(double id)
	{
	 empid=id+1;
	 cout<<"\nEnter Employee Name     =";
	 cin>>empname;
	 cout<<"\nEnter Worked Hours      =";
	 cin>>hrsworked;
	 cout<<"\nEnter Hourly Pay        =";
	 cin>>hrlypay;
	 cout<<"\nEnter Marital Status    =";
	 cin>>marstat;
	 cout<<"\nEnter Bonus             =";
	 cin>>bonus;
	 cout<<"\nEnter Previous Due      =";
	 cin>>due;
	}

	void payroll:: create_modify()
	{
	 cout<<"\nEnter Worked Hours      =";
	 cin>>hrsworked;
	 cout<<"\nEnter Hourly Pay        =";
	 cin>>hrlypay;
	 cout<<"\nEnter Marital Status    =";
	 cin>>marstat;
	 cout<<"\nEnter Bonus             =";
	 cin>>bonus;
	 cout<<"\nEnter Previous Due      =";
	 cin>>due;
	}

	void payroll:: show()
	{
	 cout<<"\n\n\nEmployee ID      ="<<empid;
	 cout<<"\nEmployee Name    ="<<empname;
	 cout<<"\nWorked Hours     ="<<hrsworked;
	 cout<<"\nBonus            ="<<bonus;
	 cout<<"\nDue              ="<<due;
	}

       inline double payroll:: retid()
	{
	 return empid;
	}

       inline char* payroll:: retname()
	{
	 return empname;
	}


 class calc
 {
   double overtime,regpay,otpay,grosspay,netpay,taxrate,tax;

   public:
	   void calc_grosspay(payroll &p);
	   void calc_netpay(payroll &p);
	   void print(payroll &p);

};


	   void calc:: calc_grosspay(payroll &p)
	   {
	    if(p.hrsworked>40)
	    {
	     overtime=p.hrsworked-40;
	    }
	    else
	    {
	     overtime=0;
	    }
	    regpay=p.hrsworked*p.hrlypay;
	    otpay=overtime*(p.hrlypay*1.5);
	    grosspay=regpay+otpay;
	   }

	   void calc:: calc_netpay(payroll &p)
	   {
	    if(grosspay>500)
	    {
	     taxrate=0.30;
	    }
	    else if(grosspay>300)
	    {
	     taxrate=0.20;
	    }
	    else
	    {
	     taxrate=0.10;
	    }
	    if(p.marstat=='s'||p.marstat=='S')
	    {
	     taxrate=taxrate+0.05;
	    }
	    tax=grosspay*taxrate;
	    netpay=grosspay+p.bonus-tax-p.due;
	   }

	   void calc:: print(payroll &p)
	   {
	    p.show();
	    cout<<"\nGross Pay        ="<<grosspay;
	    cout<<"\nTax              ="<<tax;
	    cout<<"\nNetpay           ="<<netpay;
	   }

   fstream fp;
   payroll p1;
   calc c1;


   void write_record()
   {
    double id;
    fp.open("pay.dat",ios::in);
    if(fp)
    {  int k=100;
       while(fp.read((char*)&p1,sizeof(payroll)))
	{

	 if(p1.retid()==k)
	 {
	  id=p1.retid();

	  k++;
	 }
	 else
	 {
	  id=k-1;
	 }
	}

    }
    else
    {
     id=99;
    }
    fp.close();
    fp.open("pay.dat",ios::out|ios::app);
    p1.create_emprecord(id);
    fp.write((char*)&p1,sizeof(payroll));
    fp.close();
    cout<<"\n\nThe Employee record has been created ";
    getch();
   }


void display_all()
{
    clrscr();
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("pay.dat",ios::in);
    while(fp.read((char*)&p1,sizeof(payroll)))
	{
	 c1.calc_grosspay(p1);
	 c1.calc_netpay(p1);
	 c1.print(p1);
	 cout<<"\n\n====================================\n";
	 getch();
	 }
    fp.close();


}



void search(double n)
{
    int flag=0;
    fp.open("pay.dat",ios::in);
    while(fp.read((char*)&p1,sizeof(payroll)))
	{
	 if(p1.retid()==n)
		{
		 clrscr();
		 c1.calc_grosspay(p1);
		 c1.calc_netpay(p1);
		 c1.print(p1);
		 flag=1;
		}
	}
    fp.close();
if(flag==0)
 cout<<"\n\nRecord Not Exist";
 getch();

}


void modify()
{
    int found=0;
    double no;
    cout<<"\n\n\t MODIFY RECORD ";
    cout<<"\n\nEnter Employee ID Number\t=";
    cin>>no;
    clrscr();
    fp.open("pay.dat",ios::in|ios::out);
    while(fp.read((char*)&p1,sizeof(payroll)) && found==0)
	   {
	    if(p1.retid()==no)
		   {
		    c1.calc_grosspay(p1);
		    c1.calc_netpay(p1);
		    c1.print(p1);
		    cout<<"\n\n\nEnter The New Details of Employee\n"<<endl;
		    p1.create_modify();
		    int pos=-1*sizeof(p1);
		    fp.seekp(pos,ios::cur);
		    fp.write((char*)&p1,sizeof(payroll));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		   }
	     }
    fp.close();
    if(found==0)
    cout<<"\n\n Record Not Found ";
    getch();
}


void deleter()
   {
    double no;
    int flag=0;
    cout<<"\n\n\n\tDELETE RECORD";
    cout<<"\n\nEnter Employee ID Number\t=";
    cin>>no;
    fp.open("pay.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&p1,sizeof(payroll)))
	{
	 if(p1.retid()==no)
	 {
	  flag=1;
	 }
	 if(p1.retid()!=no)
		{
		 fp2.write((char*)&p1,sizeof(payroll));
		 }
	 }
    fp2.close();
    fp.close();
    remove("pay.dat");
    rename("Temp.dat","pay.dat");
    if(flag==1)
    cout<<"\n\n\tRecord Deleted ..";
    else
    cout<<"\n\n\tRecord Does Not Exist";
    getch();
    }


    void menu()
    {
     clrscr();
     fp.open("pay.dat",ios::in);
     if(!fp)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPENED\n\n\n GO TO ADMIN MENU TO CREATE A RECORD";
       cout<<"\n\n\n PROGRAM IS CLOSING ....";
       getch();
       exit(0);
     }
	cout<<"\n\n\tEMPLOYEE MENU\n\n";
	  cout<<"=================================\n";
	  cout<<"ID.NO.\t\tNAME\n";
	  cout<<"=================================\n";

      while(fp.read((char*)&p1,sizeof(payroll)))
	 {
	   cout<<p1.retid()<<"\t\t"<<p1.retname()<<endl;
	}
     fp.close();

}

void empchoice()
{
  double id;
  cout<<"\n\n\nEnter your ID Number\t=";
     cin>>id;
     search(id);
}

void admin_menu()
{

  char ch2;
  do
  {
  clrscr();

  cout<<"\n\n\n\t\tADMIN MENU";
  cout<<"\n\n\t1.CREATE RECORD";
  cout<<"\n\n\t2.DISPLAY ALL ";
  cout<<"\n\n\t3.QUERRY";
  cout<<"\n\n\t4.MODIFY ";
  cout<<"\n\n\t5.DELETE ";
  cout<<"\n\n\t6.VIEW EMPLOYEE MENU";
  cout<<"\n\n\t7.BACK TO MAIN MENU";
  cout<<"\n\n\n\tENTER YOUR CHOICE (1-7) ";
  ch2=getche();
  switch(ch2)
  {
    case '1': clrscr();
	      write_record();
	      break;
    case '2': display_all();
	      break;
    case '3':
	       double num;
	       clrscr();
	       cout<<"\n\nEnter Employee ID Number ";
	       cin>>num;
	       search(num);
	       break;
      case '4': menu();
		modify();
		break;
      case '5': menu();
		deleter();
		break;
      case '6': menu();
		empchoice();
		break;
      case '7': break;
      default:cout<<"\a";admin_menu();
   }
   }while(ch2!='7');
}


int main()
{
  char ch;
  textcolor(WHITE);
  textbackground(BLUE);
  do
    {
	  clrscr();
	  cout<<"\n\n\n\t\tMAIN MENU";
	  cout<<"\n\n\t01. EMPLOYEE";
	  cout<<"\n\n\t02. ADMINISTRATOR";
	  cout<<"\n\n\t03. EXIT";
	  cout<<"\n\n\n\tENTER YOUR OPTION (1-3) ";
	  ch=getche();
	  switch(ch)
	  {
		 case '1': clrscr();
			   menu();
			   empchoice();
			   break;
		  case '2': admin_menu();
			    break;
		  case '3':exit(0);
		  default :cout<<"\a";
	}
    }while(ch!=3);
return 0;
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************

