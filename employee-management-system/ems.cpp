/*
It's an menu driven program which is used to manage employee records in an small company.
The project is implemented in the intend of learning the concepts of cpp.
*/

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>

using namespace std;

//Employee.txt file stores the data entered by the user and is used to retrive back when display option is invoked.
const char* fileName="Employee.txt";

//Employee class used to implement all the features of an employee and the functions which are used to performed various funtionality on employee records.
class Employee
{
  private:
  int EmpID;
  char EmpName[50],Post[50],Department[10];
  float Salary;

  public:
  void ReadData();
  int GetID();
  void DisplayRecord();
  char* GetDepartment();
};

//this function is used for input of data from used 
void Employee::ReadData()
{
  cout<<endl<<"Employee ID :";
  cin>>EmpID;
  cout<<"Employee Name :";
  cin>>EmpName;
  cout<<"Employee’s Post :";
  cin>>Post;
  cout<<"Employee’s Department :";
  cin>>Department;
  cout<<"Salary :";
  cin>>Salary;
}

//this function is used for output of data from storage
void Employee::DisplayRecord()
{
  cout<<endl<<"________________________________________________________________";
  cout<<endl<<setw(5)<<EmpID<<setw(15)<<EmpName<<setw(15)<<Post<<setw(15)<<Department<<setw(8)<<Salary;
}

//this fuction returns the employee id
int Employee::GetID()
{
  return EmpID;
}

//this funcition returns the employee department
char* Employee::GetDepartment()
{
  return Department;
}

int main()
{
  Employee emp,e;
  char option,ch,Dept[50];
  int ID,isFound;

  fstream file;
  file.open(fileName,ios::ate|ios::in|ios::out|ios::binary);
  
  //menu driven text which asks for the options to the users and waits for the response
  //all the options are implemented using the functions from the class employee and embedded into switch case statement
  do
  {
    cout<<"********Menu********";
    cout<<endl<<"Enter your option";
    cout<<endl<<"1 => Add a new record";
    cout<<endl<<"2 => Search record from employee ID";
    cout<<endl<<"3 => List Employee of particular department";
    cout<<endl<<"4 => Display all employee";
    cout<<endl<<"5 => Update record of an employee";
    cout<<endl<<"6 => Delete record of particular employee";
    cout<<endl<<"7 => Exit from the program"<<endl;
    cout<<"********************************************"<<endl;
    cin>>option;

    switch(option)
    {
      case '1':
      {
        emp.ReadData();
        isFound=0;
        file.read((char*)&e,sizeof(e));
        while(!file.eof())
        {
          if(e.GetID()==emp.GetID())
          {
            cout<<"This ID already exist.Try for another ID";
            isFound=1;
            break;
          }
          file.read((char*)&e,sizeof(e));
        }
        if(isFound==1)
        break;
        file.clear();
        file.seekp(0,ios::end);
        file.write((char*)&emp, sizeof(emp));
        cout<<endl<<"New record has been added successfully !";
      }
      break;

      case '2':
      {
        isFound=0;
        cout<<endl<<"Enter ID of an employee to be searched :";
        cin>>ID;
        file.seekg(0,ios::beg);
        file.read((char*)&e,sizeof(e));
        while(!file.eof())
        {
          if(e.GetID()==ID)
          {
            cout<<endl<<"The record found !"<<endl;
            cout<<endl<<setw(5)<<"ID"<<setw(15)<<"Name"<<setw(15)<<"Post"<<setw(15)<<"Department"<<setw(8)<<"Salary";
            e.DisplayRecord();
            isFound=1;
            break;
          }
          file.read((char*)&e,sizeof(e));
        }
        file.clear();
        if(isFound==0)
        cout<<endl<<"Data not found for employee ID "<<ID;
      }
      break;

      case '3':
      {
        isFound=0;
        cout<<"Enter department name to list employee within it :";
        cin>>Dept;
        file.seekg(0,ios::beg);
        file.read((char*)&e,sizeof(e));
        while(!file.eof())
        {
          if(strcmp(e.GetDepartment(),Dept)==0)
          {
            cout<<endl<<"The record found for this department"<<endl;
            cout<<endl<<setw(5)<<"ID"<<setw(15)<<"Name"<<setw(15)<<"Post"<<setw(15)<<"Department"<<setw(8)<<"Salary";
            e.DisplayRecord();
            isFound=1;
            break;
          }
          file.read((char*)&e,sizeof(e));
        }
        file.clear();
        if(isFound==0)
        cout<<endl<<"Data not found for department !"<<Dept;
      }
      break;

      case '4':
      {
        cout<<endl<<"Record for employee";
        file.clear();
        file.seekg(0,ios::beg);
        int counter=0;
        file.read((char*)&e,sizeof(e));
        while(!file.eof())
        {
          counter++;
          if(counter==1)
          {
            cout<<endl<<setw(5)<<"ID"<<setw(15)<<"Name"<<setw(15)<<"Post"<<setw(15)<<"Department"<<setw(8)<<"Salary";
          }
          e.DisplayRecord();
          file.read((char*)&e,sizeof(e));
        }
        cout<<endl<<counter<<"Records found !" ;
        file.clear();
      }
      break;

      case '5':
      {
        int recordNo=0;
        cout<<endl<<"File is being under process....... !";
        cout<<endl<<"Enter employee ID to be updated :";
        cin>>ID;
        isFound=0;
        file.seekg(0,ios::beg);
        file.read((char*)&e,sizeof(e));
        while(!file.eof())
        {
          recordNo++;
          if(e.GetID()==ID)
          {
            cout<<"The old record of employee having ID "<<ID<<"is :";
            e.DisplayRecord();
            isFound=1;
            break;
          }
          file.read((char *)&e,sizeof(e));
        }
        if(isFound==0)
        {
          cout<<endl<<"Data not found for employee ID "<<ID;
          break;
        }
        file.clear();
        int location=(recordNo-1)*sizeof(e);
        file.seekp(location,ios::beg);
        cout<<endl<<"Enter new record for employee having ID "<<ID;
        e.ReadData();
        file.write((char*)&e, sizeof(e));
      }
      break;

      case '6':
      {
        int recordNo=0;
        cout<<endl<<"Enter employment ID to be deleted :";
        cin>>ID;
        isFound=0;
        file.seekg(0,ios::beg);
        file.read((char*)&e,sizeof(e));
        while(!file.eof())
        {
          recordNo++;
          if(e.GetID()==ID)
          {
            cout<<"The old record of employee having ID "<<ID<<" is : ";
            e.DisplayRecord();
            isFound=1;
            break;
          }
          file.read((char*)&e,sizeof(e));
        }
        char tempFile[]="temp.txt";
        fstream temp(tempFile,ios::out|ios::binary);
        if(isFound==0)
        {
          cout<<endl<<"Data not found for employee ID "<<ID<<" !";
          break;
        }
        else
        {
          file.clear();
          file.seekg(0,ios::beg);
          file.read((char*)&e,sizeof(e));
          while(!file.eof())
          {
            if(e.GetID()!=ID)
            temp.write((char*)&e,sizeof(e));
            file.read((char*)&e,sizeof(e));
          }
          file.close();
          temp.close();
          temp.open(tempFile,ios::in|ios::binary);
          file.open(fileName,ios::out|ios::binary);
          temp.read((char*)&e,sizeof(e));
          while(!temp.eof())
          {
            file.write((char*)&e,sizeof(e));
            temp.read((char*)&e,sizeof(e));
          }
        }
        temp.close();
        file.close();
        remove(tempFile);
        file.open(fileName,ios::ate|ios::in|ios::out|ios::binary);

      }
      break;

      case '7':
        exit(0);

      default:
      cout<<"Invalid Options";
    }

    cout<<"\nDo you want to continue...?(Y/N)";
    cin>>ch;
  }while(ch!='n');

  return 0;

}
