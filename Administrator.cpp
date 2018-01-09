#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
using namespace std;
class Admin
{
	string name,password;
	public:
		Admin(string n,string p)
		{
			name+=n;
			password+=p;
		}
		void Write(ofstream& f)
		{
			f.write(&name[0],name.size());
			f.write("\n",1);
			f.write(&password[0],password.size());
		}
		void Read(ifstream& f)
		{
			f.seekg(ios::beg);
			string s,p;
			getline(f,s,'\n');//f.read(&s[0],name.size());
			cout<<"\nAdmin name is: "<<s<<endl;
			getline(f,p);//f.read(&p[0],password.size());
			cout<<"Admin password is: "<<p<<endl;
		}
};
int main()
{
	string n,p;
	cin>>n;char c;
	c=getch();cout<<"*";
	while(1){
		if(c=='\\')break;
		else {
		p.push_back(c);
		c=getch();
		cout<<"*";}
	}
	Admin A(n,p);
	ofstream fout("D:\\Academics\\Programming\\C++ LOGICS\\Mini Project\\Admin.input",ios::binary | ios::out);
	A.Write(fout);fout.close();
	ifstream fin("D:\\Academics\\Programming\\C++ LOGICS\\Mini Project\\Admin.input",ios::binary | ios::in);
	if(fin.is_open()){A.Read(fin);fin.close();}
	else return 1;
	return 0;
}
