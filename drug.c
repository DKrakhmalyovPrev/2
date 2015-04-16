#include <iostream>

#include <stdlib.h>

#include <string.h>

#include <stdio.h>

#include <vector>

using namespace std;
void GetVector(vector<char>& a)
{
	char c;
			
	c=getchar();
	while(c!='\n')
	{
	a.push_back(c);
	c=getchar();
	}
}

const void PrintVector(vector<char>& a)
{
	for(int i=0; i<a.size(); i++)
		cout<<a[i];
	cout<<"\n";
}

class Drug
{
	private:
		vector<char> name;
		vector<char> maker;
		vector<char> sub;
		double dose;
		vector<char> form;
	public:
		
		Drug(){};
		
		Drug(const Drug& a)
		{
			name=a.name;
			maker=a.maker;
			sub=a.sub;
			dose=a.dose;
			form=a.form;
		}
		
		void ScanDrug()
		{
			GetVector(name);
			GetVector(maker);
			GetVector(sub);
			GetVector(form);
			cin>>dose;
			
		}

		const void PrintDrug()
		{
			PrintVector(name);
			PrintVector(maker);
			PrintVector(sub);
			PrintVector(form);
			cout<<dose;
			
		}
		
		friend const void PrintVector(vector<char>&);
		friend void GetVector(vector<char>&);
};

int main()
{
	Drug n;
	n.ScanDrug();
	Drug s(n);
	s.PrintDrug();
	return(0);
}
			
