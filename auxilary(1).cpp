#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<iomanip>
#include<ctime>
using namespace std;
void admin_menu()
{
    cout<<"\nPress 1 for add new player\n";
    cout<<"Press 2 for remove existing player\n";
    cout<<"Press 3 for display player information\n";
    cout<<"Press 4 for search player\n";
    cout<<"Press 5 for add employee\n";
    cout<<"Press 6 for delete employee\n";
    cout<<"Press 7 for display employee information\n";
    cout<<"Press 8 for search emolyee\n";
    cout<<"Press 9 for squad information\n";
    cout<<"Press 10 for play match\n";
    cout<<"Press 11 for squad report\n";
    cout<<"Press 12 for Top Scorer\n";
    cout<<"Press 13 for fixtures \n";
    cout<<"Press 14 for main menu\n";
    cout<<"Press 0 for exit\n";
    cout<<"Enter choice : ";
}

void attendee_menu()
{
     cout<<"Press 1 for Register\n";
     cout<<"Press 2 for Login\n";
     cout<<"Press 3 for Main Menu\n";
     cout<< "Press 0 for Exit\n";
}
void attendee_menu2 ()
{
    cout << "Press 1 to Explore the Location of different butterfly species\n";
    cout << "Press 2 to Explore the Transportation options available for the fair\n";
    cout << "Press 3 to Explore Characteristics of different butterfly species present in the fair\n";
    cout << "Press 4 to Explore your Contribution in butterfly conservation\n";
    cout << "Press 5 to Go Back\n";
}
void formation()
{
    cout << "Choose Where you want to go first\n";
    cout << "1. Jahir Rayhan Auditorium\n";
    cout << "2. Department of Zoology\n";
    cout << "3. Butterfly Park\n";
}
/// @brief /////////////////////// REGISTER CLASS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
class  Register {
    private:
    string regname;
    string regpass;
    string logname;
    string logpass;
    public:
    void reg()
    {
        cout<<"Registration\nEnter user name : "; cin>>regname;
        this->regname = regname;
        cout<<"Enter password : "; cin>>regpass;
        this->regpass = regpass;
        ofstream reg("database.txt", ios:: app);
        reg << regname << ' ' << regpass << endl;
        cout<<"Registration successfull\n";


    }

    int login()
    {
        int exist;
        string u,p;
         cout<<"Login\nEnter user name : "; cin>>logname;
         cout<<"Enter password : "; cin>>logpass;
         ifstream input("database.txt");
         while(input >> u >> p)
         {
            if(u == logname && p == logpass)
            {
                exist = 1;
                break;
            }
         }
         input.close();
         if(exist == 1)
            {
                cout<<"Hello "<< logname << " Welcome to Attendee Panel\n";
                return 1;
            }
        else
           { cout<<"Incorrect Log in Info!!\nTry again\n";
           return 0;
           }
    }

};
/////////////////////////////////// PERSON CLASS //////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Person :  public Register{
    public:
    long double salary;
    public:
    string name;
    string age;
    string nationality;
    public:                         //////// VIRTUAL FUNCTIONS
    virtual void getdata(int=0)=0;
    virtual void showdata()=0;
    virtual void Delete()=0;
    virtual void search()=0;
    virtual void top_Scorer()=0;
    virtual void fixture()=0;
    virtual int show_squad()=0;
};
/////////////////////////////////// EMPLOYEE CLASS //////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
class employee : public Person {
    public:
    string ID;
    string Job;
    public:
    void getdata(int t)     /////////   WRITE TO FILE
    {
        cout<<"Enter ID : "; cin>>ID;
        cin.ignore(1, '\n');
        cout<<"Enter name : "; getline(cin,name);
        cout<<"Enter age : "; cin>>age;
        cout<<"Enter nationality : "; cin>>nationality;
        cin.ignore(1, '\n');
        cout<<"Enter Job title : "; getline(cin,Job);
        cout<<"Set salary : "; cin>>salary;

        fstream employee_information("employee_information.txt", ios::app);
        employee_information << ID << setw(10-ID.size()) << ' ' << name << setw(25-name.size()) << ' ' << age << setw(10) << ' ' << nationality << setw(17-nationality.size()) << ' ' << Job << setw(18-Job.size()) << ' '<< salary << endl;
    }
    void showdata()
    {
        cout<<"ID : " << ID << endl;
        cout<<"Name : " << name << endl;
        cout<<"Age : " << age << endl; cin>>age;
        cout<<"Nationality : " << nationality << endl;
        cout<<"Job title : " << Job << endl;
    }
    void search()
    {

        int x=0;
        fstream d;
        d.open("employee_information.txt", ios::in);
        string empID;
        cout<<"Enter ID number to search : ";
        cin>>empID;
        while (!d.eof())        ///////// READ FILE
        {
             d >> ID >> name >> age >> nationality >> Job >> salary;
            if(empID == ID)
         {
                cout << "ID" << setw(12) << "Name" << setw(24) << "Age" << setw(20) << "Nationality" << setw(15) << "Job Title" << setw(15) << "Salary" << endl;
                 cout << ID << setw(10-ID.size()) << ' ' << name << setw(25-name.size()) << ' ' << age << setw(10) << ' ' << nationality << setw(17-nationality.size()) << ' ' << Job << setw(18-Job.size()) << ' '<< salary << endl;
                x=1;
                break;
            }
        }
        d.close();
        if (x==0)
            cout << "Not found!!" <<endl;
     }

     void Delete()
     {
        cout<<"Enter ID to delete : ";
        string deleteID;
        cin>> deleteID;
        ifstream d;
        d.open("employee_information.txt");
        ofstream e;
        e.open("new.txt");
        d >> ID >> name >> age >> nationality >> Job >> salary;
        while (!d.eof())
        {
            if (ID != deleteID)
            {
               e << ID << setw(10-ID.size()) << ' ' << name << setw(25-name.size()) << ' ' << age << setw(10) << ' ' << nationality << setw(17-nationality.size()) << ' ' << Job << setw(18-Job.size()) << ' '<< salary << endl;
            }
            else cout << "Employee deleted\n";
             d >> ID >> name >> age >> nationality >> Job >> salary;
        }
        e.close();
        d.close();
        remove("employee_information.txt");
        rename("new.txt","employee_information.txt");
     }
     void top_Scorer(){ }
     void fixture() {   }
     int show_squad() {  return 0 ; }
};
/////////////////////////////////// PLAYER CLASS //////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class player : public Person  {
     public:
     string jerseynumber;
     string position;
     int goal;
     int assist;
     public:        ///////// CONSTRUCTOR .///////////
     player(string name, string age, string nationality, string position, string jerseynumber,long double salary )
     {
        this->name = name;              //////// THIS POINTER //////////
        this->age = age;
        this->nationality = nationality;
        this->position = position;
        this->jerseynumber = jerseynumber;
        this->salary = salary;
        this->goal = 0;
        this->assist = 0;

        fstream player_information("Player_Information.txt", ios::app);
        player_information << name << setw(25-name.size()) << ' ' << age << setw(10) << ' ' << nationality << setw(15-nationality.size()) << ' ' << position << setw(10-position.size())<<' ' << jerseynumber << setw(10-jerseynumber.size())<< ' '<< salary << endl;
     }
     player(){}

     void getdata(int t)
     {
        cin.ignore(1, '\n');
        cout<<"Enter name : ";
        getline(cin,name);
        cout<<"Enter age : "; cin>>age;
        cout<<"Enter nationality : "; cin>>nationality;
        cout<<"Enter position : "; cin>>position;
        cout<<"Enter Jersey number : "; cin>>jerseynumber;
        if (t==1)
        {
        cout<<"Set salary : "; cin>>salary;
        }
        else
        {
            srand (time(NULL));
            salary = rand() % 1234;
        }
        fstream player_information("Player_Information.txt", ios::app);
        player_information << name << setw(25-name.size()) << ' ' << age << setw(10) << ' ' << nationality << setw(15-nationality.size()) << ' ' << position << setw(10-position.size())<<' ' << jerseynumber << setw(10-jerseynumber.size())<< ' '<< salary << endl;
     }
     void showdata()
     {
        cout<<"Name : " << name << endl;
        cout<<"Age : " << age << endl;
        cout<<"Nationality : " << nationality << endl;
        cout<<"Position : " << position << endl;
     }
     void Delete()
     {
        cout<<"Enter name to delete : ";
        string deletename;
        cin>> deletename;
        ifstream d;
        d.open("player_information.txt");
        ofstream e;
        e.open("new.txt");
        d >> name >> age >> nationality >> position >> jerseynumber >> salary;
        while (!d.eof())
        {
            if (name != deletename)
            {
          //     e << name << ' ' << age << ' ' << nationality << ' ' << position << ' ' << jerseynumber << ' ' << salary << endl;
               e << name << setw(25-name.size()) << ' ' << age << setw(10) << ' ' << nationality << setw(15-nationality.size()) << ' ' << position << setw(10-position.size())<<' ' << jerseynumber << setw(10-jerseynumber.size())<< ' '<< salary << endl;
            }
            else cout << "Player deleted\n";
            d >> name >> age >> nationality >> position >> jerseynumber >> salary;
        }
        e.close();
        d.close();
        remove("player_information.txt");
        rename("new.txt","player_information.txt");
     }
     void search()
     {

        int x=0;
        fstream d;
        d.open("player_information.txt", ios::in);
        string jnum;
        cout<<"Jersey number to search : ";
        cin>>jnum;
        while (!d.eof())
        {
             d >> name >> age >> nationality >> position >> jerseynumber >> salary;
            if(jnum == jerseynumber)
            {
                cout<<"Player"<<setw(22)<<"Age"<<setw(20)<<"Nationality"<<setw(10)<<"Position"<<setw(10)<<"Jersey"<<setw(10)<<"Salary"<<endl;
                cout << name << setw(25-name.size()) << ' ' << age << setw(10) << ' ' << nationality << setw(15-nationality.size()) << ' ' << position << setw(10-position.size())<<' ' << jerseynumber << setw(10-jerseynumber.size())<< ' '<< salary << endl;
                x=1;
                break;
            }
        }
        d.close();
        if (x==0)
            cout<<"Not found!!";
     }
     void top_Scorer()
     {
        fstream d;
        d.open("Top_scorer.txt", ios::in);
        int maxgoal=0;
        int assi = 0;
        string top_scorer;
        while (!d.eof())
        {
             d >> name >>  goal >> assist;
            if(goal > maxgoal)
            {
                maxgoal = goal;
                top_scorer = name ;
                assi = assist;
            }
        }
        d.close();
        cout << "Top scorer\n";
        cout << "Player             Goal             Assist\n";
        cout << top_scorer << "               " << maxgoal << "                 " << assi << endl;
        cout << "Ballon D'OR winner is " << top_scorer << "!!!"<<endl;
     }
     ~player()      //////////////  POLYMORPHISM
     {
        string deletename;
        deletename = name;
        ifstream d;
        d.open("player_information.txt");
        ofstream e;
        e.open("new.txt");
        d >> name >> age >> nationality >> position >> jerseynumber >> salary;
        while (!d.eof())
        {
            if (name != deletename)
            {
              e << name << setw(25-name.size()) << ' ' << age << setw(10) << ' ' << nationality << setw(15-nationality.size()) << ' ' << position << setw(10-position.size())<<' ' << jerseynumber << setw(10-jerseynumber.size())<< ' '<< salary << endl;
            }
            d >> name >> age >> nationality >> position >> jerseynumber >> salary;
        }
        e.close();
        d.close();
        remove("player_information.txt");
        rename("new.txt","player_information.txt");
     }
     void fixture() {   }
     int show_squad() {  return 1;  }
};

/////////////////////////////////// PLAYERS AS OBJECT //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

   player valdes("Valdes","31","Spain","GK","1",5241.456);
   player messi("Messi","21","Argentina","CF","10",7898.546);
   player alves("Alves","30","Brazil","RB","2",3578.546);
   player pique("Pique","26","Spain","CB","3",7898.546);
   player fabregas("Fabregas","26","Spain","CM","4",2164.546);
   player puyol("Puyol","33","Spain","CM","6",7898.546);
   player xavi("Xavi","24","Spainish","GK","1",154.456) ;
   player ineasta("Ineasta","29","Spain","CM","8",3946.546);
   player villa("Villa","31","Spain","LW","10",7823.546);
   player sanchez("Sanchez","24","Chille","FW","9",7898.546);
   player thiago("Thiago","22","Spain","CM","17",3459.546);
   player busquest("Busquest","24","Spain","CDM","16",7898.546);
   player pedro("Pedro","25","Spain","RW","10",7898.546);
   player alba("ALba","24","Spain","LB","18",8641.546);
   player adriano("Adriano","28","Brazil","LB","2",3845.546);
   player abidal("Abidal","33","France","LB","22",65466.546);
   player mascherano("Mascherano","28","Argentina","LCB","14",7898.546);

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////// Location CLASS //////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class squad : public player {


        public:
        void showdata()
        {

            formation();
            int x; cin >> x;
            int choice;
            while (x!=0)
          {
            if (x == 1)
            {
            cout << "4-3-3\n\n";
            cout << "         " << villa.name << "                           " << pedro.name << "                                  "            << endl;
            cout << "                         " << messi.name << "                                                     "                      << endl;
            cout << "                                                                                                                        \n";
            cout << "                                                                                            \n";
            cout << "             " << ineasta.name << "                  " << xavi.name << "                                         "         << endl;
            cout << "                        " << busquest.name << "                                                  "                         << endl;
            cout << "                                                                                     \n";
            cout << "                                                                                     \n";
            cout << "    "<< abidal.name << "          " << pique.name << "        " <<  puyol.name <<"(c)" << "          " << alves.name << "                    " << endl;
            cout << "                                                                                     \n";
            cout << "                                                                                     \n";
            cout << "                           " << valdes.name << "                                                                             " <<endl;

            cout << "Press 1 to change formation \nPress 2 to select this formation\n";
            cin >> choice;
            if(choice == 1)
                formation();
            else
                {
                cout << "Formation selected\n";
                admin_menu();
                return;
                }
            }
            if (x==2)
            {
                cout << "4-4-2\n\n";
            cout << "                  " << villa.name << "            " << pedro.name << "              "            << endl;
            cout << "                                                                                                  " << endl;
            cout << "                                                                                                                        \n";
            cout << "                                                                                                                     " << endl;
            cout << "    " << ineasta.name << "         " << messi.name << "           " << xavi.name << "       " << busquest.name << endl;
            cout << "                                                                          "                         << endl;
            cout << "                                                                                                                       "<<endl;
            cout << "                                                                                                                               \n";
            cout << "    "<< abidal.name << "          " << pique.name << "        " <<  puyol.name <<"(c)" << "          " << alves.name << "                    " << endl;
            cout << "                                                                                     \n";
            cout << "                                                                                     \n";
            cout << "                           " << valdes.name << "                                                                             " <<endl;

             cout << "Press 1 to change formation \nPress 2 to select this formation\n";
            cin >> choice;
            if(choice == 1)
                formation();
            else
                {
                cout << "Formation selected\n";
                admin_menu();
                return;
                }
            }


          if (x==3)
            {
            cout << "5-3-2\n\n";
            cout << "                  " << villa.name << "            " << messi.name << "              "            << endl;
            cout << "                                                                                                  " << endl;
            cout << "                                                                                                                        \n";
            cout << "                                                                                                                     " << endl;
            cout << "        " << ineasta.name << "                           " << xavi.name << endl;
            cout << "                       " << fabregas.name << "                                              "                         << endl;
            cout << "                                                                                                                       "<<endl;
            cout << "    " << abidal.name << "                                         " << alves.name << endl;
            cout << "    " "          " << pique.name << "     " <<  puyol.name <<"(c)" << "      " << mascherano.name << endl;
            cout << "                                                                                     \n";
            cout << "                                                                                     \n";
            cout << "                           " << valdes.name << "                                                                             " <<endl;

             cout << "Press 1 to change formation \nPress 2 to select this formation\n";
            cin >> choice;
            if(choice == 1)
                formation();
            else
                {
                cout << "Formation selected\n";
                admin_menu();
                return;
                }
            }
            cin >> x;
        }

        }
        int show_squad()
        {
            formation();


        }



    ///////////////////////////////////////////////////////////
    void fixture()
    {
        char teams [12][20] = {"Athletico Madrid","Real Madrid","Villareal","Getafe","Granada","Real Sociadad","Celta Vigo","Mayorca","Mallacora","Malaga","Sevilla","Espanyol"};
        srand(time(0));
        cout << "            Date                                                    Match\n";
        int i=0;
        while (i < 20)
        {
        int match = rand() %12;
        int date = rand() % 27 + 1 ;
        int month = rand() % 12 + 1;
            cout <<setw(10)<< date << "/" << month << "/" << 2023 << "                                      " <<setw(20)<< "Barcelona Vs " << teams[match] << endl;
            i++;
        }
    }


};

/////////////////////////////////// MATCH FUNCTION //////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static int total_goal=0;
void match()
{
    char teams [12][20] = {"Athletico Madrid","Real Madrid","Villareal","Getafe","Granada","Real Sociadad","Celta Vigo","Mayorca","Mallacora","Malaga","Sevilla","Espanyol"};
    srand (time(NULL));
    int match = rand() % 12;
    cout << "Barcelona Vs " << teams[match] << endl;
    int goal_concide = rand() % 7;
    int goal_for = rand() % 7;
    int goal = goal_for;
    int x = rand() % 7;
    total_goal = total_goal + goal_for;
    if ( goal_for > goal_concide)
    {
        cout << "Barcelona Wins\n";
    }
    else if (goal < goal_concide)
    {
        cout << "Barcelona Loose\n";
    }
    else
    cout << "Draw\n";
    while( goal !=0 )
    {
        if (x==5 || x==7 || x==10 || x==13 )
        {
            messi.goal++;
            ineasta.assist++;
            goal--;

        }
        if(x==2 || x==4 || x==0)
        {
            villa.goal++;
            messi.assist++;
            goal--;
        }
        if(x==3 || x==8 || x==11)
        {
            pedro.goal++;
            xavi.assist++;
            goal--;
        }
        if(x==1)
        {
            xavi.goal++;
            alves.assist++;
            goal--;
        }
        if(x==9)
        {
            ineasta.goal++;
            pedro.assist++;
            goal--;
        }
        if(x==12)
        {
            pique.goal++;
            villa.assist++;
            goal--;
        }
        if(x==1)
        {
            alba.goal++;
            puyol.assist++;
            goal--;
        }
        if(x==14)
        {
            sanchez.goal++;
            sanchez.assist++;
            goal--;
        }
        if(x==15)
        {
            fabregas.goal++;
            mascherano.assist++;
            goal--;
        }
        x++;
    }
    int shots_barcelona = rand() % 30 + 5;
    int shots_opponent = rand() % 30;
    int shots_onTarget_barcelona = abs ( shots_barcelona - rand() % 20 );
    int shots_onTarget_opponent = abs ( shots_opponent - rand() % 20 );
    int possition_barcelona = rand() % 100 + 1;
    int possition_oppnent = 100 - possition_barcelona;
    int pass_barcelona = rand() % 600;
    int pass_opponent = rand() % 600;
    if ( possition_barcelona > possition_oppnent && pass_barcelona < pass_opponent )
        swap ( pass_barcelona, pass_opponent);
    int pass_accuracy_barcelona = rand() % 100 + 1;
    int pass_accuracy_opponent = rand() % 100 + 1;
    int foul_barcelona = rand() % 20 + 1;
    int foul_opponent = rand() % 20 + 1;
    int yellow_barceolona = rand() % 5 + 1;
    int yellow_opponent = rand() % 5 + 1;
    int red_barceolona = rand() % 3;
    int red_opponent = rand() % 3;
    int offside_barcelona = rand() % 10;
    int offside_opponent = rand() % 10;
    int corner_barcelona = rand() % 10;
    int corner_opponent = rand() % 10;
    cout << "Barcelona "<< goal_for <<"-"<<goal_concide<<" "<< teams[match] << endl;

    cout<< "Barcelona" << setw(22) << "Team Stats" << setw(25) << teams[match] << endl;
    cout<< goal_for << setw(25) << "Goals" << setw(30-5) << "   " << goal_concide << endl;
    cout<< shots_barcelona << setw(24) << "Shots" << setw(30-5) << "   "  << shots_opponent << endl;
    cout<< shots_onTarget_barcelona << setw(34) << "Shots on target" << setw(30-15) << "   "  << shots_onTarget_opponent << endl;
    cout<< possition_barcelona << "%" << setw(27) << "Position" << setw(30-8) << "   "  << possition_oppnent << "%" << endl;
    cout<< pass_barcelona << setw(24) << "Passes" << setw(30-6) << "   "  << pass_opponent << endl;
    cout<< pass_accuracy_barcelona << setw(32) << "Pass accuracy" << setw(30-13) << "   "  << pass_accuracy_opponent << endl;
    cout<< foul_barcelona << setw(24) << "Fouls" << setw(30-5) << "   "  << foul_opponent << endl;
    cout<< yellow_barceolona << setw(32) << "Yellow cards" << setw(30-12) << "   "  << yellow_opponent << endl;
    cout<< red_barceolona << setw(29) << "Red cards" << setw(30-9) << "   "  << red_opponent << endl;
    cout<< offside_barcelona << setw(28) << "Offsides" << setw(30-8) << "   "  << offside_opponent << endl;
    cout<< corner_barcelona << setw(27) << "Corners" << setw(30-7) << "   "  << corner_opponent << endl;
}




/////////////////////////////////// MAIN FUNCTION //////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main()
{

   cout << "***************** WELCOME TO Butterfly Fair JU *****************\n";
   Person *personptr[200];
   int n=0;
   cout<<"Login as\n(1) Organizer\n(2) Attendee\n(3) Exit\n";
   int x; cin >> x;
   ////////////////////////// LOG IN AS ADMIN //////////////
   /////////////////////////////////////////////////////////
   if(x==1)
   {
    char  name[10],password[10];
    cout<<"Enter user name : "; cin >> name;
    cout<<"Enter password : "; cin >> password;
    if(  !(strcmp(name,"Boss") && strcmp(password,"admin"))  )
    {
        admin_menu();
    int choice; cin >> choice;
    while(x!=0)
    {
        if (choice==1)     //////   ADD NEW PLAYER
        {

        char ans;
        do {
        personptr[n] = new player;
        personptr[n]->getdata(1);
        n++;
        cout<<"Want to add another player? (y/n) : ";  cin>>ans;
        } while(ans!='n');
        admin_menu();
        }

        if (choice==2)      //////  DELETE PLAYER
        {
          personptr[n] = new player;
          personptr[n]->Delete();
          admin_menu();
        }
        if (choice==3)      /////// DISPLAY PLAYER INFORMATION
        {
            ifstream player_information("player_information.txt");
            char ch;
            cout<<"Player"<<setw(22)<<"Age"<<setw(20)<<"Nationality"<<setw(10)<<"Position"<<setw(10)<<"Jersey"<<setw(10)<<"Salary"<<endl;
            while (player_information)
            {
                player_information.get(ch);
                cout<<ch;
            }
            cout<<endl;
        admin_menu();
        }
        if (choice==4)  ///////     SEARCH PLAYER
        {
            personptr[n] = new player;
          personptr[n]->search();
          admin_menu();
        }
        if (choice==5)  //////      ADD NEW EMPLOYEE
        {
        char ans;
        do {
        personptr[n] = new employee;
        personptr[n]->getdata();
        n++;
        cout<<"Want to add another employee? (y/n) : ";  cin>>ans;
        } while(ans!='n');
        admin_menu();
        }
         if (choice==6)     //////////  DELETE EMPLOYEE
        {
          personptr[n] = new employee;
          personptr[n]->Delete();
          admin_menu();
        }
         if (choice==7)     /////   DISPLAY EMPLOYEE INFORMATION
        {
            ifstream employee_information("employee_information.txt");
            char ch;

            cout << "ID" << setw(12) << "Name" << setw(24) << "Age" << setw(20) << "Nationality" << setw(15) << "Job Title" << setw(15) << "Salary" << endl;
            while (employee_information)
            {
                employee_information.get(ch);
                cout<<ch;
            }
            cout<<endl;
        admin_menu();
        }
        if (choice==8)  //////////      SEARCH EMPLOYEE
        {
          personptr[n] = new employee;
          personptr[n]->search();
          admin_menu();
        }
        if (choice == 9)      //////    SQUAD INFORMATION
        {
          personptr[n] = new squad;
          personptr[n]->showdata();
          n++;
        }

        if (choice == 10)       /////// SIMULATE MATCH
        {
            char ans;
            int match_played=0;
            do{
            match();
            match_played++;
            cout <<"Want to play next match?(y/n)\n";
            cin >> ans;

            } while(ans != 'n' && match_played < 12);

            fstream squad_report("squad_report.txt", ios::app);
            squad_report << "Player" <<setw(20) << "Goal" << setw(10) << "Assist" << endl;
            squad_report << "Messi" << setw(20) <<messi.goal << setw(10) << messi.assist << endl;
            squad_report << "Villa" << setw(20) <<villa.goal << setw(10) << villa.assist << endl;
            squad_report << "Pedro" << setw(20) <<pedro.goal << setw(10) << pedro.assist << endl;
            squad_report << "Xavi" << setw(21) <<xavi.goal << setw(10) << xavi.assist << endl;
            squad_report << "Sanchez" << setw(18) <<sanchez.goal << setw(10) << sanchez.assist << endl;
            squad_report << "Fabregas" << setw(17) <<fabregas.goal << setw(10) << fabregas.assist << endl;
            squad_report << "Ineasta" << setw(18) <<ineasta.goal << setw(10) << ineasta.assist << endl;
            squad_report << "Busquest" << setw(17) <<busquest.goal << setw(10) << busquest.assist << endl;
            squad_report << "Alba" << setw(21) <<alba.goal << setw(10) << alba.assist << endl;
            squad_report << "Alves" << setw(20) <<alves.goal << setw(10) << alves.assist << endl;
            squad_report << "Pique" << setw(20) <<pique.goal << setw(10) << pique.assist << endl;
            squad_report << "Puyol" << setw(20) <<puyol.goal << setw(10) << puyol.assist << endl;
            squad_report << "Adriano" << setw(18) <<adriano.goal << setw(10) << adriano.assist << endl;
            squad_report << "Abidal" << setw(19) <<abidal.goal << setw(10) << abidal.assist << endl;
            squad_report << "Mascherano" << setw(15) <<mascherano.goal << setw(10) << mascherano.assist << endl;
            squad_report << "Thiago" << setw(19) <<thiago.goal << setw(10) << thiago.assist << endl;
            squad_report << "Valdes" << setw(19) <<valdes.goal << setw(10) << valdes.assist << endl;


            fstream Top_scorer("Top_scorer.txt", ios::app);

            Top_scorer << "Messi" <<' '<<messi.goal << ' '<<' '<<messi.assist << endl;
            Top_scorer << "Villa"  <<' '<<villa.goal << ' '<<villa.assist << endl;
            Top_scorer << "Pedro" <<' '<<pedro.goal << ' '<<pedro.assist << endl;
            Top_scorer << "Xavi"  <<' '<<xavi.goal << ' '<<xavi.assist << endl;
            Top_scorer << "Sanchez"  <<' '<<sanchez.goal << ' '<<sanchez.assist << endl;
            Top_scorer << "Fabregas"  <<' '<<fabregas.goal << ' '<<fabregas.assist << endl;
            Top_scorer << "Ineasta"  <<' '<<ineasta.goal << ' '<<ineasta.assist << endl;
            Top_scorer << "Busquest" <<' '<<busquest.goal <<' '<< busquest.assist << endl;
            Top_scorer << "Alba"  <<' '<<alba.goal <<' '<< alba.assist << endl;
            Top_scorer << "Alves"  <<' '<< alves.goal <<' '<< alves.assist << endl;
            Top_scorer << "Pique"  <<' '<<pique.goal << ' '<<pique.assist << endl;
            Top_scorer << "Puyol"  <<' '<<puyol.goal <<' '<< puyol.assist << endl;
            Top_scorer << "Adriano"  <<' '<<adriano.goal << ' '<<adriano.assist << endl;
            Top_scorer << "Abidal"  <<' '<<abidal.goal  <<' '<< abidal.assist << endl;
            Top_scorer << "Mascherano"  <<' '<<mascherano.goal  <<' '<< mascherano.assist << endl;
            Top_scorer << "Thiago"  <<' '<<thiago.goal  << ' '<<thiago.assist << endl;
            Top_scorer << "Valdes"  <<' '<<valdes.goal  << ' '<<valdes.assist << endl;

            admin_menu();
        }
        if(choice == 11)        //////      SQUAD REPORT
        {
            ifstream squad_report("squad_report.txt");
            char ch;
            while (squad_report)
            {
                squad_report.get(ch);
                cout<<ch;
            }
            cout<<endl;

        cout << "Total goal " << total_goal;
        admin_menu();
        }
        if ( choice == 12)     //////       TOP SCORER
        {
            personptr[n] = new player;
            personptr[n]->top_Scorer();
            n++;
            admin_menu();
        }
        if ( choice == 13 )       ///////   FIXTURE
        {
            personptr[n] = new squad;
            personptr[n] -> fixture();
            n++;
            admin_menu();
        }
        if (choice==14)     /////// MAIN MENU
        {
         main();
        }
        if (choice == 0)    /////   EXIT
        {

          //  remove("squad_report.txt");
            //remove("Top_scorer.txt");
            fstream ofs;
            ofs.open("Top_scorer.txt", ios::out | ios::trunc);
            ofs.close();
            ofs.open("squad_report1.txt", ios::out | ios::trunc);
            ofs.close();
             exit(0);
        }

    cin>>choice;
    }

   }
   else
   {
    cout<<"Error!!\nTry again\n";
    main();
   }

   }
   /////////////////////// LOG IN AS Attendee ///////////////////
   ///////////////////////////////////////////////////////////
   if (x==2)
   {

    b:
     attendee_menu();
     int choise;
     cin >> choise;
     while(choise != 50)
     {
        if(choise==1)           //////////  REGISTER
        {

        personptr[n] = new player;
        personptr[n]->reg();
        cout<<"Please fill up the form\n";
        personptr[n]->getdata(0);
        n++;
        cout << "Now login to see features\n";
        attendee_menu();
        }
        if(choise==2)       //////      LOG IN
         {

       int log = 0;
        while ( 1 )
        {
           personptr[n] = new player;
            int log = personptr[n]->login();
            n++;
            if ( log == 1)  break;
        }
         a:
        attendee_menu2();
        int y; cin >> y;
        if ( y == 1 )           ////////    VIEW Species Available
        {
            personptr[n] = new squad;
            personptr[n] ->show_squad();
            n++;
            goto a;

        }
        if ( y == 2 )       ////////////    FIXTURE
        {
            personptr[n] = new squad;
            personptr[n] ->fixture();
            n++;
            goto a;
        }
        if ( y == 3 )
        {

            personptr[n] = new player;
            personptr[n] ->top_Scorer();
            n++;
            goto a;
        }
        if ( y == 4)
        {
            goto b;
        }


        }
        if ( choise == 3)
            {
                main();
            }


        if ( choise == 0)   /////// EXIT
            {
                exit(0);
            }



    cin>>choise;
   }

   }  //// END OF LOG IN AS PLAYER
   else
   exit(0);
}

