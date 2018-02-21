//SAMPLE PROGRAM FOR C++ ON BANKING
#include <fstream.h>
#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <process.h>
#include <stdio.h>
#include <dos.h>
    void
    password(void)
{
      int counter = 0;
      char username[20];
      char password[15];
      char str[20];
      fstream user;
      fstream pass;
      user.open("username.dat", ios::binary | ios::in | ios::out);
      pass.open("password.dat", ios::binary | ios::in | ios::out);
      do
      {
            clrscr();
            cout << "\n\n\n\n\n\t\t\t USERNAME ";
            cout << "\n\n\t\t  ";
            gets(username);
            user.read((char *)&str, sizeof(str));
            user.close();
            if (strcmp(str, username) == 0)
            {
                  clrscr();
                  cout << "\n\n\n\n\n\t\t\tPASSWORD ";
                  cout << "\n\n\t\t  ";
                  gets(password);
                  pass.read((char *)&str, sizeof(str));
                  pass.close();
                  if (strcmp(str, password) == 0)
                  {
                        clrscr();
                        cout << "\n\n\n\n\t\t\tACCESS ALLOWED....";
                        delay(1500);
                        return;
                  }
                  else
                  {
                        cout << "\n\n\t\t\tACCESS DENIED!!!!";
                        delay(2500);
                        continue;
                  }
            }
            counter++;
      } while (counter < 3);
      clrscr();
      cout << "\n\n\n\n\n\n\t\t\t";
      char arr[35] = {"CLOSING DUE TO SECURITY THREAT"};
      for (int i = 0; i < 35; i++)
      {
            cout << arr[i];
            delay(50);
      }
      cout << "....";
      delay(2500);
      exit(0);
}
class account
{
      char first_name[50], last_name[50], address[100], city[50], state[50];
      char phone_number[25], pincode[25];
      int accno, acctno;
      float amount, deposit, rate;

    public:
      account()
      {
            amount = 0.00;
            deposit = 0.00;
            rate = 0.0;
            ifstream fin;
            fin.open("acctno.dat", ios::in);
            fin >> acctno;
            fin.close();
      }
      void addnewrecord();
      void viewrecord();
      void updaterecord();
      void read();
      int get_acctno();
      void display();
};
/*
This method is for adding a new account record. The details are added in the dat file 
accountdets.dat.
*/
void account::addnewrecord()
{
      ofstream outfile;
      outfile.open("accountdets.dat", ios::out | ios::binary | ios::app);
      account person;
      cout << endl
           << "Enter first name : ";
      gets(person.first_name);
      cout << endl
           << "Enter last name : ";
      gets(person.last_name);
      cout << endl
           << "Enter address : ";
      gets(person.address);
      cout << endl
           << "Enter city : ";
      gets(person.city);
      cout << endl
           << "Enter state : ";
      gets(person.state);
      cout << endl
           << "Enter pin : ";
      gets(person.pincode);
      cout << endl
           << "Enter phone number : ";
      gets(person.phone_number);
      cout << endl
           << "Your PERMANENT ACCOUNT NO: is : " << (acctno++);
      cout << endl
           << "\nEnter deposit (min Rs.250) : ";
      cin >> person.deposit;
      ofstream fout;
      fout.open("acctno.dat", ios::out);
      fout << acctno;
      fout.close();
      outfile.write((char *)&person, sizeof(person));
      outfile.close();
}
/*
This method is used for reading the account number input from the user.
*/
void account::read()
{
      cout << "\nEnter the account number : ";
      cin >> accno;
}
/*
This method returns the account number that is input by the user.
*/ int
account::get_acctno()
{
      return accno;
}
/*
This method is used for viewing the account details from the dat file, given a 
specific account number as input.
*/
void account::viewrecord()
{
      ifstream f2;
      account t2, t02;
      t02.read();
      f2.open("accountdets.dat", ios::binary | ios::in);
      f2.seekg(0, ios::beg);
      int j = 0;
      while (!f2.eof())
      {
            f2.read((char *)&t2, sizeof(t2));
            if (t2.acctno == t02.get_acctno())
            {
                  j = 1;
                  t2.display();
                  break;
            }
      }
      if (j != 1)
            cout << "\nRecord not found...";
      f2.close();
      cout << "\n\n\t\t\t(Press any key to return to MAIN MENU..)";
      getch();
}
/*
This method is used by the viewrecord method to output the specific account record 
details.
*/
void account::display()
{
      cout << "\n";
      cout << "First name   : " << first_name << "\n"
           << "Last  name   : " << last_name << "\n"
           << "Address      : " << address << "\n"
           << "City         : " << city << "\n"
           << "State        : " << state << "\n"
           << "Phone Number : " << phone_number << "\n"
           << "Deposit   : " << deposit << "\n";
}
/*
This method is used for updating an account record based on various options.
*/ void
account::updaterecord()
{
      int ch2, debit, credit;
      do
      {
            clrscr();
            cout << "\n\nPlease";
            cout << "\n\tEnter 1 to debit \n"
                 << "\tEnter 2 to credit \n"
                 << "\tEnter 3 to view account balance \n"
                 << "\tEnter 4 to calculate interest and view balance after the 
                calculations\n "
                 << "\tEnter 5 to close transactions\n";
            cout << "\nEnter choice : ";
            cin >> ch2;
            clrscr();
            switch (ch2)
            {
            case 1:
            {
                  fstream f3;
                  account t3, t03;
                  int j = 0, count = 0;
                  t03.read();
                  cout << "\nPlease enter the amount to be debited : ";
                  cin >> debit;
                  f3.open("accountdets.dat", ios::binary | ios::in | ios::out);
                  f3.seekg(0, ios::beg);
                  while (!f3.eof())
                  {
                        f3.read((char *)&t3, sizeof(t3));
                        if (t3.acctno == t03.get_acctno())
                        {
                              j++;
                              break;
                        }
                        count++;
                  }
                  if (j != 0)
                  {
                        if (debit <= t3.deposit)
                        {
                              t3.deposit -= debit;
                              f3.seekp(count * sizeof(t3), ios::beg);
                              f3.write((char *)&t3, sizeof(t3));
                        }
                        if (t3.deposit >= 250)
                              cout << "Your account balance is 
                                  Rs "<<t3.deposit;
                                  else cout
                                   << "Your Balance is not sufficient to 
                                  debit this amount ";
                  }
                  else
                  {
                        cout << "\nRecord NOT found";
                  }
                  f3.close();
cout<<"\n\n\n\n\t\t(Press any key to return to previous 
menu..)";
getch();
break;
            } //case 1
            case 2:
            {
                  fstream f4;
                  account t4, t04;
                  int j = 0, count = 0, credit;
                  t04.read();
                  cout << "\nPleaseenter the amount to be credited  ";
                  cin >> credit;
                  f4.open("accountdets.dat", ios::binary | ios::in | ios::out);
                  f4.seekg(0, ios::beg);
                  while (!f4.eof())
                  {
                        f4.read((char *)&t4, sizeof(t4));
                        if (t4.acctno == t04.get_acctno())
                        {
                              j++;
                              break;
                        }
                        count++;
                  }
                  if (j != 0)
                  {
                        t4.deposit += credit;
                        f4.seekp(count * sizeof(t4), ios::beg);
                        f4.write((char *)&t4, sizeof(t4));
                  }
                  else
                  {
                        cout << "\nRecord NOT found";
                  }
                  cout << "Your account balance is Rs " << t4.deposit;
                  f4.close();
cout<<"\n\n\n\n\t\t(Press any key to return to previous 
menu..)";
getch();
break;
            } //case 2
            case 3:
            {
                  fstream f6;
                  account t6, t06;
                  int j = 0;
                  t06.read();
                  f6.open("accountdets.dat", ios::binary | ios::in | ios::out);
                  f6.seekg(0, ios::beg);
                  while (!f6.eof())
                  {
                        f6.read((char *)&t6, sizeof(t6));
                        if (t6.acctno == t06.get_acctno())
                        {
                              j++;
                              break;
                        }
                  }
                  if (j != 0)
                  {
                        cout << "\n\nTheACCOUNT BALANCE is  Rs 
                                "<<t6.deposit;
                  }
                  else
                  {
                        cout << "\nRecord NOT found";
                  }
                  f6.close();
cout<<"\n\n\n\n\t\t(Press any key to return to previous 
menu..)";
getch();
break;
            } //case 3
            case 4:
            {
                  fstream f5;
                  account t5, t05;
                  int timeperiod, j = 0;
                  float interest;
                  t05.read();
                  f5.open("accountdets.dat", ios::binary | ios::in | ios::out);
                  f5.seekg(0, ios::beg);
                  while (!f5.eof())
                  {
                        f5.read((char *)&t5, sizeof(t5));
                        if (t5.acctno == t05.get_acctno())
                        {
                              cout << "\nPlease enter the time period : ";
                              cin >> timeperiod;
                              rate = 1.5 * timeperiod;
                              interest = t5.deposit * timeperiod * (rate / 100.0);
                              cout << "\nInterest is Rs " << interest;
                              amount = t5.deposit + interest;
                              cout << "\nAmount is Rs " << amount;
                              if (amount == 0)
                                    cout << "Sorry!The interest rate for the 
                                        time period you have entered is not specified ";
                                        j = 1;
                              break;
                        }
                  }
                  if (j == 0)
                        cout << "\nRecord not found";
cout<<"\n\n\n\n\t\t(Press any key to return to previous 
menu..)";getch();
break;
            } //case 4
            case 5:
                  cout << "\n\n\n\n\n\t\tModifications are SAVED to your 
                          account.....";
                          cout
                       << "\n\n\t\t\t(Press any key..)";
                  getch();
                  ch2 = 6;
                  break;
            default:
                  cout << "\n\n\t\t\tinvalid entry!!!!";
cout<<"\n\n\n\n\t\t(Press any key to return to previous 
menu..)";
getch();
break;
            } //switch ch2
      } while (ch2 < 6);
} //updaterecord
void main()
{
      password();
      char crep, cstr[20];
      int irep;
l:
      clrscr();
      cout << "\nDo you want to change the USERNAME or PASSWORD (y/n) : ";
      cin >> crep;
      if (crep == 'y' || crep == 'Y')
      {
            ofstream of;
            cout << "\nEnter 1 to change username or 2 to change password\n";
            cin >> irep;
            switch (irep)
            {
            case 1:
                  of.open("username.dat", ios::binary | ios::out);
                  cout << "\nEnter new Username : ";
                  gets(cstr);
                  of.write((char *)&cstr, sizeof(cstr));
                  of.close();
                  break;
            case 2:
                  of.open("password.dat", ios::binary | ios::out);
                  cout << "\nEnter new password : ";
                  gets(cstr);
                  of.write((char *)&cstr, sizeof(cstr));
                  of.close();
                  break;
            default:
                  goto l;
            }
      }
      account obj;
      int ch;
      do
      {
            clrscr();
            cout << "\n\t\t\t ==========================";
            cout << "\n\t\t\t\t MAIN MENU";
            cout << "\n\t\t\t ==========================\n";
            cout << "\t1. Add record\n";
            cout << "\t2. View record\n";
            cout << "\t3. Update record / Transactions\n";
            cout << "\t4. Exit\n";
            cout << "\tEnter your choice: ";
            cin >> ch;
            clrscr();
            int in = 0;
            switch (ch)
            {
            case 1:
                  obj.addnewrecord();
                  break;
            case 2:
                  obj.viewrecord();
                  break;
            case 3:
                  obj.updaterecord();
                  break;
            case 4:
                  clrscr();
                  cout << "\n\n\n\n\n\t\t\tSaving Your Settings";
                  for (in = 0; in < 6; in++)
                  {
                        cout << '.';
                        delay(1500);
                  }
                  clrscr();
                  cout << "\n\n\n\n\n\t\t\t....Terminating....";
                  delay(2500);
                  exit(0);
            default:
                  cout << "\n\t\t\tinvalid entry!!!!";
                  cout << "\n\n\t\t\t(Press any key..)";
                  getch();
                  break;
            }
      } while (ch < 10);
}