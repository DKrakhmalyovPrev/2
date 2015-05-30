#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <vector>
using namespace std;

class Graph
{
	private:
	
	vector<vector<int>> matr;
	
	public:
	
	Graph(){};

	Graph(int a)
	{
 		
		vector<int> q(a,0);	
		for(int j=0;j<a;j++)
			matr.push_back(q);
	};
			 
	Graph(const Graph& x)
	{
		matr=x.matr;
	}

	void ScanGraph()
	{
		for(int i=0; i<matr.size(); i++)
			for(int j=0; j<matr.size(); j++)
				cin>>matr[i][j];
	}

	void PrintGraph() const
	{
		for(int i=0; i<matr.size(); i++)
		{
			for(int j=0; j<matr.size(); j++)
				cout<<matr[i][j]<<" ";
			cout<<"\n";
		}
	}	
		
	Graph(const vector<vector<int>> x)
	{
		matr=x;
	}
	
	void SetRib(int a, int b, int s)
	{
		matr[a][b]=s;
	}
	
	
	
	void AddTop(vector<int>& inribs, vector<int>& outribs)
	{
		vector<int> t(matr.size()+1,0);
		matr.push_back(t);
		for(int i=0;i<t.size()-1;i++)
			matr[i].push_back(0);
		for(int i=0; i<inribs.size(); i++)
			SetRib(inribs[i], matr.size()-1,1);
		for(int i=0; i<inribs.size(); i++)
			SetRib(matr.size()-1, outribs[i],1);
	}

	int GetRib(int a, int b) const
	{
		return(matr[a][b]);
	}

	vector<int> Wentfrom(int a) const
	{
		vector<int> x;
		for(int i=0; i<matr.size(); i++)
			if(GetRib(a,i))
				x.push_back(i);
		return(x);
	}
	

	vector<int> Wentto(int a) const
	{
		vector<int> x;
		for(int i=0; i<matr.size(); i++)
			if(GetRib(i,a))
				x.push_back(i);
		return(x);
	}
	
	Graph Trans() const
	{
		Graph a(matr.size());
		for(int i=0; i<a.matr.size(); i++)
			for(int j=0; j<a.matr.size(); j++)
				a.SetRib(i,j, this->GetRib(j,i));
		return(a);	
	}
	

};

int main()
{
	Graph a(3);
	a.ScanGraph();
	int ia[2] = {0,1};
	vector< int > in( ia, ia+2 );
	int oa[2] = {0,2};
	vector< int > on( oa, oa+2 );
	a.AddTop(in, on);
	Graph b(a.Trans());
	b.PrintGraph();
	return(0);
}
	
