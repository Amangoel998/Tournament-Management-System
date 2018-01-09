#include<iostream>
#include<conio.h>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;
int operator==(string &t,string &s){
	if(strcmp(&t[0],&s[0])!=0)return 0;
	return 1;
}
bool exit()
{
	bool q=false;
	cout<<"\nPress 1 to Continue..";cin>>q;
	if(q!=true)cout<<"Exiting...";
	return q;
}
string Teams[8]={"AUS","POR","UK","GER","BRZ","CAN","SPN","ARG"};
class Match
{
	public:
	string Date,Team1,Team2,Winner;
		void set(Match& m){
			cout<<"Enter details of the match\n"<<flush;
			cout<<"Date: ";cin>>m.Date;cin.clear();
			cout<<"Team 1: ";cin>>m.Team1;cin.clear();
			cout<<"Team 2: ";cin>>m.Team2;cin.clear();
			cout<<"Winner: ";cin>>m.Winner;cin.clear();
		}
		void get(string& m){
			cout<<"\nDate\t"<<"\tTeam 1""\tTeam 2"<<"\tWinner"<<endl;
			cout<<m<<"\n";
		}
		void AddMatch(fstream &f)
		{
			Match m,s;
			set(m);
			f.write(&m.Date[0],2*sizeof(m.Date));
			fflush(0);
			f.write(&m.Team1[0],sizeof(m.Team1));
			fflush(0);
			f.write(&m.Team2[0],sizeof(m.Team2));
			fflush(0);
			f.write(&m.Winner[0],m.Winner.length()-1);
			fflush(0);
		}
		void DisplayMatch()
		{
			string m;
			fstream f("Football Tournament.txt",ios::binary | ios::in);
			getline(f,m);
			while(!f.eof()){
				getline(f,m);
				if(m[0]!=' ')get(m);
			}
			f.close();
		}
		void DeleteMatch()
		{
			string d;
			fstream f1("Football Tournament.txt",ios::binary | ios::in);
			fstream f2("Football Tournament1.txt",ios::out);
			cout<<"Enter Date: ";cin>>d;
			string m="";
			while(!f1.eof())
			{
				int k=0;
				getline(f1,m);
				for(int i=0;i<d.length();i++){
				if(d[i]!=m[i]){k=1;break;}}
				if(k!=1){continue;}
				else{
				f2.write(&m[0],m.length()-1);
				f2.write("\n",1);}
			}
			f1.close();f2.close();
			remove("Football Tournament.txt");
			rename("Football Tournament1.txt","Football Tournament.txt");
		}
		void MatchOnDate(){
			string d;int l=0;
			fstream f("Football Tournament.txt",ios::in);
			cout<<"Enter Date: ";cin>>d;
			string m="";
			while(!f.eof())
			{
				int k=0;
				getline(f,m);
				for(int i=0;i<d.length();i++){
				if(d[i]!=m[i]){k=1;break;}}
				if(k==1){continue;}
				else{
					get(m);l=1;
				}
			}
			if(l!=1)cout<<"No record on date found";
			f.close();
		}
};
class Team
{
	string name,Total,Win,Lose;
	public:
		void set(Team& m,string& d){
			cout<<"\nEnter details of the team\n"<<flush;
			strcpy(&m.name[0],&d[0]);cin.clear();
			cout<<"Wins: ";cin>>m.Win;cin.clear();
			cout<<"Loses: ";cin>>m.Lose;cin.clear();
			cout<<"Total: ";cin>>m.Total;
			cin.clear();
		}
		void get(string& m){
			cout<<"\nName  "<<"  Won   "<<"  Lost  "<<"  Total Matches"<<endl;
			cout<<m<<"\n";
		}
		void ChooseTeam()
		{
			cout<<"Enter Teams\n";
			for(int i=0;i<3;i++)cout<<Teams[i]<<"	";
			cout<<endl;
			for(int i=3;i<5;i++)cout<<Teams[i]<<"	";
			cout<<endl;
			for(int i=5;i<7;i++)cout<<Teams[i]<<"	";
			cout<<endl;
		}
		void AddTeamDetails(fstream &f){
			Team t;string d;
			ChooseTeam();cin>>d;
			cout<<"\nYou choose Team :"<<d<<endl;set(t,d);
			f.write(&t.name[0],sizeof(t.name));
			f.write(&t.Win[0],sizeof(t.name));
			f.write(&t.Lose[0],sizeof(t.name));
			f.write(&t.Total[0],sizeof(t.name));
		}
		void UpdateTeamDetails()
		{
			Team t;string d;
			fstream f1("Team Details.txt",ios::binary | ios::in);
			fstream f2("Team Details1.txt",ios::out);
			ChooseTeam();cin>>d;
			cout<<"\nYou choose Team :"<<d<<endl;
			set(t,d);
			string m="";
			while(!f1.eof())
			{
				int k=0;
				getline(f1,m);
				for(int i=0;i<d.length();i++)
				{
				if(d[i]!=m[i]){k=1;break;}
				}
				if(k==1){f2.write(&m[0],m.length()-1);f2<<"\n";}
				else{
				f2.write(&t.name[0],sizeof(t.name));
				f2.write(&t.Win[0],sizeof(t.name));
				f2.write(&t.Lose[0],sizeof(t.name));
				f2.write(&t.Total[0],sizeof(t.name));f2<<"\n";
				}
			}
			f1.close();f2.close();
			remove("Team Details.txt");
			rename("Team Details1.txt","Team Details.txt");
		}
		void DisplayTeam()
		{
			ChooseTeam();
			string d;cin>>d;
			Team t;
			string m="";
			fstream f("Team Details.txt",ios::binary | ios::in);
			getline(f,m);
			while(!f.eof())
			{
				int k=0;
				getline(f,m);
				for(int i=0;i<d.length();i++){
				if(d[i]!=m[i]){k=1;break;}}
				if(k!=1){get(m);break;}
			}
			f.close();
		}
		void DisplayAllTeam()
		{
			string m="";
			fstream f("Team Details.txt",ios::binary | ios::in);
			getline(f,m);
			while(!f.eof())
			{
				int k=0;
				getline(f,m);get(m);
			}
			f.close();
		}
};
class Admin:public Team,public Match
{
	string name,password;
	public:
		Admin()
		{
			ifstream f("Admin.input",ios::in);
			getline(f,name);
			getline(f,password);
			f.close();
		}
		int login()
		{
			string n,p;
			char t;short int i=0;
			cout<<"\nEnter Username And Password:\n";
			cin>>n;
			if(n==name)
			{
				t=getch();
				while(++i<=5){
					cout<<"*";
					p+=t;
					t=getch();
				}
				if(p==password)
				{
					cout<<"\n\nYou are Logged in Successfully!!\n\n";
					return 1;
				}
			}
			cout<<"\nWrong password or admin name...Exiting\n";
			return 0;
		}
		int choices()
		{
			int x;
			cout<<"1.To add new matches\n";
			cout<<"2.To add details of a team\n";
			cout<<"3.To delete a record of a match\n";
			cout<<"4.To Update Team details\n";
			cout<<"\nEnter your Choice\n";cin>>x;
			return x;
		}
};
class User:public Match,public Team
{
	public:
		int choices()
		{
			cout<<"\n1.To see details of all matches\n2.To see match on a date\n3.To see details of matches played by a team\n";
			cout<<"4.To see all Teams details\n";
			short int i;
			cout<<"\nEnter your Choice\n";cin>>i;
			return i;
		}
};
int main()
{
	cout<<"\t\t\t\t Welcome to Tournament Management Sysytem!!!\n\n";
	cout<<"1.To login as User\t2.To login as Admin\n\n";int q=0;cin>>q;
	if(q==1){
		User U;
		do{
		switch(U.choices())
		{
			case 1:
				U.DisplayMatch();
				break;
			case 2:
				U.MatchOnDate();
				break;
			case 3:
				U.DisplayTeam();
				break;
			case 4:
				U.DisplayAllTeam();
				break;
			default :
				cout<<"You Entered nothing\n";
				break;
		}}while(exit()==true);
		return 0;
	}
	else if(q==2){
	Admin A;
	if(A.login()==1)
	{	bool x;
		do{
		int c;
		c=A.choices();
			if(c==1)
			{
				short int n;
				cout<<"How many new Matches you want to add?\n";cin>>n;
				fstream f("Football Tournament.txt",ios::app);
				while(--n>=0){
				f<<"\n";
				A.AddMatch(f);}
				f.close();
			}
			else if(c==2)
			{
				short int n;
				cout<<"How many Team you want to add?\n";cin>>n;
				fstream f("Team Details.txt",ios::app);
				while(--n>=0){
				f<<"\n";
				A.AddTeamDetails(f);}
				f.close();
			}
			else if(c==3)
			{
				A.DeleteMatch();
				A.DisplayMatch();
			}
			else if(c==4)
			{
				A.UpdateTeamDetails();
				A.DisplayAllTeam();
			}
			cout<<"\nPress 1 to continue...";cin>>x;
		}while(x==true);
		cout<<"You have logged out";
		return 0;
	}}
}
