#include <iostream>

#include <stdlib.h>

#include <string.h>

#include <stdio.h>

#include <vector>

#include <map>

using namespace std;

template <typename T>
bool Cmp(const T a, const T b)
{
    return a < b ? 1 : 0;
};


template<typename key, typename value>

class TopResult
{
	private:	
		map<key, value> Top;
		int maxsize;
		
	public:

		TopResult(){};
		
		TopResult(int l): maxsize(l){};
		
		void SetMaxSize(int l)
		{
			maxsize=l;
		}
		
		void AddElement(const key& q,const  value& h)
		{
			
			if(Top.size()<maxsize)
			{
				Top[q]=h;
			}
			else		
			{
				
				value minv=h;
				key mink=q;		
				for(auto it = Top.begin(); it != Top.end(); it++)
				{
					if (it->second<minv)
					{
						minv=it->second;
						mink=it->first;
					}
				}
	
				if(Cmp(minv,h))
				{
					Top.erase(mink); 
					Top[q]=h;
				}
			}
		}

		int GetMaxSize(){return(maxsize);}

		void PrintMap()
		{
			for(auto it = Top.begin(); it != Top.end(); ++it)
				cout<<"["<<it->first<<"] = "<<it->second<<'\n';
		}				
};



int main()
{
		
	TopResult <int, string> mytop(1);
	string mystr;
	int q;
	mystr= new char[20];
	for(int i=0;i<3;i++)
	{
		cin>>q>>mystr;
		mytop.AddElement(q,mystr);
	} 
	mytop.PrintMap();
	return(0);
}

// g++ top.cpp -std=c++11 -o top
