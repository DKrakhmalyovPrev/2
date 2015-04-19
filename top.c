#include <iostream>

#include <stdlib.h>

#include <string.h>

#include <stdio.h>

#include <vector>

using namespace std;

template<typename key, typename value>
class TopResult
{
	private:
		vector<key> keys;
		vector<value> values;
		int k;
		
	public:

		TopResult(){};
		
		TopResult(int l): k(l){};
		
		void SetK(int l)
		{
			k=l;
		}
			
		void AddElement(key q, value h)
		{
			if(values.size()<k)
			{
				int i=0;
				while(q>keys[i])
					i++;
				values.push_back(values[values.size()-1]);
				keys.push_back(keys[keys.size()-1]);
				for(int j=values.size()-2; j>i+1; i--)
				{
					values[j]=values[j-1];		
					keys[j]=keys[j-1];
				}
				values[i]=h;
				keys[i]=q;
			}
			else		
			{
				int i=0;	
				int minv=values[0];
				for(int j=0;j<k;j++)
					if(values[j]<minv)
					{
						i=j;		
						minv=values[j];
					}
				keys[i]=q;
				values[i]=h;
				while( (keys[i+1]>keys[i]) && (i<keys.size()-1) )
				{
					i++;
					key co;
					value con;
					co=keys[i+1]; keys[i+1]=keys[i]; keys[i]=co;
					con=values[i+1]; values[i+1]=values[i]; values[i]=con;
				}
				
				while( (keys[i-1]<keys[i]) && (i>1) )
				{
					i--;
					key co;
					value con;
					co=keys[i-1]; keys[i-1]=keys[i]; keys[i]=co;
					con=values[i]; values[i-1]=values[i]; values[i]=con;
				}
			}
		}

		
		key ReturnKey(int i)
		{
			return(keys[i]);
		};
			
		value ReturnValue(int i)
		{
			return(values[i]);
		};	

};

int main()
{
	return(0);
}
