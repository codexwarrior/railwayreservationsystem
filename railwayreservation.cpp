//HEADER FILES USED IN PROJECT
//*********************************

#include<iostream>
#include<stdio.h>
#include<process.h>
#include<conio.h>
#include<fstream>
using namespace std;

//CLASS USED IN THE PROJECT
//******************************  

class product
{ 
  int pno;
  char name[50];
  float price,qty,tax,dis;
 public:
  void create_product()
  {
    cout<<"Please enter the product no. of the product:";
    cin>>pno;
    cout<<endl<<"Please enter the name of the product:";
    gets(name);
    cout<<endl<<"Please enter the price of the product:";
    cin>>dis;
  }
  void show_product()
  {
     cout<<endl<<"The product no. of the product:"<<pno;
     cout<<endl<<"The name of the product:";
     puts(name);
     cout<<endl<<"The price of the product:"<<price;
     cin>>price;
     cout<<endl<<"Discount:"<<dis;
  }
  int retpno()
  {return pno;}
  float retprice()
  {return price;}
  char* retname()
  {return name;}
  int retdis()
  {return dis;}
};  //class ends here
//GLOBAL DECLARATION  FOR STREAM OBJECT, OBJECT
//******************************************************

fstream fp;
product pr;

//FUNCTION TO WRITE IN FILE
//*****************************


void write_product()
{
   fp.open("shop.dat",ios::out|ios::app);
   pr.create_product();
   fp.write((char*)&pr,sizeof(product));
   fp.close();
   cout<<endl<<"The Product Has Been Created";
   getch();
}

//FUNCTION TO READ ALL RECORDS FROM FILE
//**********************************************//
void display_all()
{ 
   system("cls");
   cout<<endl<<"\t"<<"DISPLAY ALL RECORDS!!!"<<endl;
   fp.open("shop.dat", ios::in);
   while(fp.read((char*)&pr,sizeof(product)))
   {
      pr.show_product();
      cout<<"\n\n=======================================\n";
      getch();
   }
   fp.close();
   getch();
}
  

//FUNCTION TO READ SPECIFIC RECORD FROM FILE
//***************************************************


void display_sp(int n)
{
   int flag=0;
   fp.open("shop.dat",ios::in);
   while(fp.read((char*)&pr,sizeof(product)))
   {
      if(pr.retpno()==n)
      {
         system("cls");
         pr.show_product();
         flag=1;
      }
   }
   fp.close();
   if(flag==0)
   cout<<endl<<"Record not exist";
   getch();
}

//FUNCTION TO MODIFY RECOED OF FILE
//*****************************************

void modify_product()
{
    int no,found=0;
    system("cls");
    cout<<endl<<"To modify";
    cout<<endl<<"Please enter the product no. of the product";
    cin>>no;
    fp.open("shop.dat",ios::in|ios::out);
    while(fp.read((char*)&pr,sizeof(product))&&found==0)
    {
       if(pr.retpno()==no)
       { 
       pr.show_product();
       cout<<endl<<"Please enter the new details of the        product"<<endl;
       pr.create_product();
       int pos=-1*sizeof(pr);
       fp.seekp(pos,ios::cur);
       fp.write((char*)&pr,sizeof(product));
       cout<<endl<<"Record updated";
       found=1;
    }
 }
 fp.close();
 if(found==0)
 cout<<endl<<"Record not found";
 getch();
}
 

//FUNCTION TO DELETE RECORD OF FILE 
//*****************************************
void delete_product()
{ 
  int no;
  system("cls");
  cout<<endl<<"Please enter the product no. of the product you want to delete";
  cin>>no;
  fp.open("shop.dat",ios::in|ios::out);
  fstream fp2;
  fp2.open("Temp.dat",ios::out);
  fp.seekg(0,ios::beg);
  while(fp.read((char*)&pr,sizeof(product)))
  { 
    if(pr.retpno()!=no)
    {
      fp2.write((char*)&pr,sizeof(product));
    }
  }
  fp2.close();
  fp.close();
  remove("Shop.dat");
  rename("Temp.dat","Shop.dat");
  cout<<endl<<"Record delated..";
  getch();
}
  
//FUNCTION TO DISPLAY ALL PRODUCT PRICE LIST
//**************************************************

void menu()
{
  system("cls");
  fp.open("Shop.dat",ios::in);
  if(!fp)
  { 
    cout<<"ERROR!!! FILE COUND NOY BE OPEN\n\n\n Go To Admin Menu To Create Filr";
    cout<<"\n\n\n Progrsm id closind...";
    getch();
    exit(0);
  }
  cout<<"\n\n\t\tProduct MENU\n\n";
  cout<<"=======================================================================\n";
  cout<<"P.NO.\t\tNAME\t\tPRICE\n";
  cout<<"=======================================================================\n";
  while(fp.read((char*)&pr,sizeof(product)))
  { 
   cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
  }
  fp.close();
}
  
 
//FUNCTION TO PLACE ORDER AND GENERATING BILL FOR PRODUCTS
//**********************************************************************
 
void place_order()
{
   int order_arr[50],quan[50],c=0;
   float amt,damt,total=0;
   char ch='Y';
   menu();
   cout<<"\n=======================================";
   cout<<"\n PLACE YOUR ORDER";
   cout<<"\n========================================\n";
   do{ 
    cout<<"\n\nEnter The Product No. Of The Product:";
    cin>>order_arr[c];
    cout<<"\nQuantuty in number:";
    cin>>quan[c];
    c++;
    cout<<"\nDo You Want To order Another Product?(y/n)";
    cin>>ch;
   }while(ch=='y'||ch=='Y');
   cout<<"\n\nthank You For Placing the order";
   getch();
   system("cls");
   cout<<"\n\n************************************INVOICE******************************\n";
   cout<<"\nPr no.\t Pr Name \t Quantity \t Price \t Amount \t Amount after discount\n";
   for(int x=0;x<=c;c++)
   { 
     fp.open("Shop.dat",ios::in);
     fp.read((char*)&pr,sizeof(product));
     while(!fp.eof())
     {
       if(pr.retpno()==order_arr[x])
       {
         amt=pr.retprice()*quan[x];
         damt=amt-(amt*pr.retdis()/100);
         cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
         total+=damt;
       }
       fp.read((char*)&pr,sizeof(product));
     }
     fp.close();
   }
   cout<<"\n\n\t\t\t\t\tTOTAL="<<total;
   getch();
}
 


//INTODUCTION FUNCTION
//***************************
  

void intro()
{
   system("cls");
   //get(31,14);
   cout<<"SUPER MARKET";
  // get(35,14);
   cout<<"PROJECT";
   cout<<"\n\n MADE BY : Anjali Gupta";
   cout<<"\n\n SCHOOL: Vikrant University Gwailor";
   getch();
}

//ADMINISTRATOR MENU FUNCTION
//************************************
 
void admin_menu() 
{
   system("cls");
   char ch2;
   cout<<"\n\n\n \t ADMIN MENU";
   cout<<"\n\n \t 1.CREATE PRODUCT";
   cout<<"\n\n \t 2.DISPLAY ALL PRODUCT";
   cout<<"\n\n \t 3.QUERY";
   cout<<"\n\n \t 4.MODIFY PRODUCT";
   cout<<"\n\n \t 5. DELETE PRODUCT";
   cout<<"\n\n \t 6.VIEW PRODUCT MENU";
   cout<<"\n\n \t 7.BACK TO MAIN MENU";
   cout<<"\n\n \t Please Enter Your Choice(1-7)";
   ch2=getchar();
   switch(ch2)
   {  
     case'1':system("cls");
               write_product();
               break;
    case'2':display_all();
               break;
    case'5':modify_product();
               break;
    case'6':delete_product();
               break;
    case'7':menu();
               getch();
    case'8':break;
    default: cout<<"a";
                 admin_menu();
   }
}


//THE MAIN FUNCTION OF PROGRAM
//*************************************

int main()
{
    char ch;
    intro();
    do
    { 
    system("cls");
      cout<<"\n\n\n\tMAIN MENU";
      cout<<"\n\n\t01. CUSTOMER";
      cout<<"\n\n\t02. ADMINISTRATOR";
      cout<<"\n\n\t03. EXIT";
      cout<<"\n\n\tPlease select your option(1-3)";
      ch=getch();
      switch(ch)
      {
        case '1':system("cls");
                    place_order();
                    getch();
                    break;
        case '2':admin_menu();
                    break;
        case'3':  exit(0);
        default:  cout<<"\a";
      }
    }while(ch!='3');
    return 0;
    
}

//-----------------------END OF CODING-----------------
