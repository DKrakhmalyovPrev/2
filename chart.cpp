#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <map>
#include <string.h>
#include <algorithm>
#include <functional>
#include <fstream>

using namespace std;

class Chart
{
	private:
	
	map<string, map<int,int> > U_T; //Пользователь, песня, сколько раз слушал
	
	public:
		
	void VoteRecord(string username, int trackID)//Пользователь прослушал песню
	{
		if( U_T.find(username) == U_T.end() )
			U_T[username][trackID] = 1;
		else
		if( U_T.find(username)->second.find(trackID)==U_T.find(username)->second.end()  )
			U_T[username][trackID] = 1;
		else
			U_T[username][trackID]++;
	}

	vector<int> GetTop(string username, int topSize) //возвращает topSize самых популярных песен, прослушанных пользователем username 
	{
		vector<pair<int, int>> top;
		
			for(auto it=U_T[username].begin(); it!=U_T[username].end(); it++)
				top.push_back(*it);
		//for(int i=0; i<top.size(); i++)
		//	cout<<top[i].first<<" песню прослушали раз:"<<top[i].second<<"\n";
		struct 
		{
        		bool operator()(pair<int,int>& a, pair<int, int>& b)
        		{   
        		    return a.second > b.second;
        		}   
		} customLess;

		std::sort(top.begin(), top.end(), customLess);
		vector<int> a;
		for(int i=0; (i<topSize) && (i<U_T[username].size()); i++)
			a.push_back(top[i].first);
		return(a);					
	}

	int GetHistorySize(string username)
	{
		int q=0;
		for(auto it=U_T[username].begin(); it!=U_T[username].end(); it++)
			q+=(*it).second;
		return(q);
	}

	int GetDistinctTrackSize(string username) //возвращает число различных песен, прослушанных пользователем username
	{
		int q=0;
		for(auto it=U_T[username].begin(); it!=U_T[username].end(); it++)
			q++;
		return(q);	
	}

};

void Run()
{	
	int i;
	Chart a;	
	ifstream input("input.txt");
	input>>i;
	for(int j=0; j<i;j++)
	{
		string s;
		input>>s;
		if(s=="VOTE")
		{
			string s1;
			int q;
			input>>s1>>q;
			a.VoteRecord(s1,q);
		}
		if(s=="TOP")
		{
			string s1;
			int q;
			input>>s1>>q;
			vector<int> b;
			b=a.GetTop(s1,q);
			cout<<"Топ для "<<s1<<":\n";
			for(int i=0;i<b.size();i++)
				cout<<b[i]<<" ";
			cout<<"\n";
		}
		if(s=="HISTORY_SIZE")
		{	
			string s1;
			input>>s1;
			cout<<a.GetHistorySize(s1)<<"\n";
		}
		if(s=="DISTINCT")
		{
			string s1;
			input>>s1;
			cout<<a.GetDistinctTrackSize(s1)<<"\n";
			
		}
	}
}
		
int main()
{
	
	Run();
	return(0);
}
