#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <map>
#include <string.h>


using namespace std;

class Phone
{
	private:
	map<string, pair< vector<string> , string> > book;

	public:
	
	Phone(){};

	void AddUser(const string& name, const string& num) // Добавить пользователя или его номер
	{
		if( book.find(name) == book.end() )
			book[name].first.push_back(num);
		else
		{
			int q=0;
			for(int i=0; i<book[name].first.size(); i++)
				if(book[name].first[i]==name)
					q=1;
			if(q==0)
				book[name].first.push_back(num);
		}
	};
	
	void DeleteUser(const string& name)
	{
		book.erase(book.find(name));
	}

	void DeleteNum(const string& name)
	{
		book[name].first.pop_back();
	}

	void DeleteDetNum(const string& name, const string& num)
	{
		auto it=book[name].first.begin();
		while((*it)!=num)
			it++;
		book[name].first.erase(it);
	}

	void DeleteAll(const string& name)
	{
		book[name].first.clear();
	}
	
	void AddMail(const string& name, const string& mail)
	{
		book[name].second=mail;
	}

	void PrintPhone(const string& name) const
	{
		for(int i=0; i < book.find(name)->second.first.size(); i++)
			cout<<book.find(name)->second.first[i]<<"\n";
	}

	void PrintPhoneMail(const string& name) const
	{
		(*this).PrintPhone(name);
		cout<<book.find(name)->second.second<<"\n";
	}
	
	void PrintAll() const
	{
		for(auto it=book.begin(); it!=book.end(); it++)
			for(int i=0; i< (*it).second.first.size(); i++)
				cout<<(*it).first<<" "<<(*it).second.first[i]<<"\n";

	}

	void PrintName(const string& num) const
	{
		for(auto it=book.begin(); it!=book.end(); it++)
			for(int i=0; i< (*it).second.first.size(); i++)
				if((*it).second.first[i]==num)
					cout<<(*it).first<<"\n";
	}
};

int main()
{
	Phone a;
	a.AddUser("vasya", "+3819");
	a.AddUser("vasya", "+3512");
	a.AddUser("vasyan", "228");
	
	a.PrintPhone("vasya");
	a.PrintName("228");
	a.PrintAll();
	return(0);
}


		
