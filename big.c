#include <iostream>

#include <stdio.h>

#include <cstdlib>

#include <math.h>

#include <vector>

using namespace std;


	

class BigInt
{
	private:
		vector<int> value;
	
	public:
		BigInt(){}
		
		BigInt(int q)
		{
			int s=q;
			int j=1;
			if(s==0)
				value.push_back(0);
			while(s>=j)
			{
				j*=10;
			}
			j/=10;
			for(int i=j;i>0;i/=10)
			{
				value.push_back(q/i);
				q%=i;
			}
		}
		
		BigInt(const BigInt& q)
		{
			for(int i=0; i< q.value.size(); i++)
				value.push_back(q.value[i]);
		}
		
		const int size()
		{
			return(value.size());
		}

		const void PrintInt()
		{
			for(int i=0;i<value.size(); i++)
				cout<<value[i];
		}
		
		friend istream& operator>>(istream&, BigInt&);
		friend BigInt operator+(BigInt&, BigInt&);
		friend BigInt operator*(BigInt&, BigInt&);
		friend BigInt operator/(BigInt&, BigInt&);
		friend BigInt operator%(BigInt&, BigInt&);
		friend const int Cmp(const BigInt&, const BigInt&);
		
		

		const BigInt Sum(const BigInt& bsl, const BigInt& msl )
		{
			int maxs=bsl.value.size();
			int mins=msl.value.size();
			int os=0; 
			int ti[maxs+1];
			int rs=maxs-mins;
			
			for(int i=maxs; i>rs; i--)
			{
				ti[i]=(bsl.value[i-1]+msl.value[i-1-rs]+os)%10;
				os=(bsl.value[i-1]+msl.value[i-1-rs]+os)/10;
			}		
			for(int i=rs; i>0;i--)
			{
				ti[i]=(bsl.value[i-1]+os)%10;
				os=(bsl.value[i-1]+os)/10;
			}
			ti[0]=os;
			BigInt s;
			if(ti[0]==0)
				os=1;
			else
				os=0;
			for(int i = os; i<=maxs;i++)
				s.value.push_back(ti[i]);
			return(s) ;
		}

		const BigInt Dif(const BigInt& bsl, const BigInt& msl )
		{
			int maxs=bsl.value.size();
			int mins=msl.value.size();
			int os=0; 
			int ti[maxs+1];
			int rs=maxs-mins;
			
			for(int i=maxs; i>rs; i--)
			{
				ti[i]=(bsl.value[i-1]-msl.value[i-1-rs]+os)%10;
				if(ti[i]<0)
				{
					ti[i]=10+ti[i];
					os=-1;
				}
			}		
			for(int i=rs; i>0;i--)
			{
				ti[i]=(bsl.value[i-1]+os)%10;
				if(ti[i]<0)
				{
					ti[i]=10+ti[i];
					os=-1;
				}
			}
			BigInt s;
			int q=1;
			if(ti[1]==0)
				q=2;			
			for(int i = q; i<=maxs;i++)
				s.value.push_back(ti[i]);
			return(s) ;
		}
		
		const BigInt Mult(const BigInt& bsl, const BigInt& msl )
		{
			int maxs=bsl.value.size();
			int mins=msl.value.size();
			/*int os=0; 
			int ti[mins][maxs+1];
			for(int i=0;i<mins;i++)
			{
				for(int j=maxs;j>0;j--)
				{
					ti[i][j]=(bsl.value[i]*msl.value[j-1]+os)%10;
					os=(bsl.value[i]*msl.value[j-1]+os)/10;			
				}
				
				ti[i][0]=os;
			}
			
			int ta[mins+maxs+1];
			for(int i=0; i<=mins+maxs; i++)
				ta[i]=0;

			for(int k=maxs+mins; k>=0; k--)
				for(int j = 0; j<=maxs; j++)
				{
					int i=k-j;
					if((i>=0)&&(i<mins))
					ta[k]+=ti[i][j];
				}
			os=0;
			for(int k=maxs+mins-1; k>0; k--)
			{
				int l=(ta[k+1]+os)%10;
				os=(ta[k+1]+os)/10;
				ta[k+1]=l;
			}
			ta[0]=os;

			BigInt s;
			int i=0;
			while(ta[i]==0) i++;	
			for(int j=i; j<mins+maxs; j++)
				s.value.push_back(ta[j]);
			return(s);*/
			
			int result[maxs+mins+1];
			for(int i=0;i<maxs+mins+1;i++)
				result[i]=0;
			BigInt jack;
			for(int i=maxs-1; i>=0; i--)
			{
				for(int j=mins-1; j>=0; j--)
				{
					result[i+j+1]+=(bsl.value[i]*msl.value[j]);
					result[i+j]+=(result[i+j+1]/10);
					result[i+j+1]=result[i+j+1]%10;
				}
			}
			int j=0;
			while(result[j]==0)
				j++;
			for(int i=j;i<=maxs+mins-1;i++)
				jack.value.push_back(result[i]);
			
			return(jack);
		}
		
		const BigInt Div(const BigInt& a,const BigInt& b)
		{
			BigInt s(0);
			BigInt o(1);
			BigInt k(a);
			BigInt l(b);
			while(Cmp(k,l)>=0)
			{	
				k=k.Dif(k,l);
				s=k.Sum(s,o);
			}
			return(s);
		}
				
		const BigInt Mod(const BigInt& a,const BigInt& b)
		{		
			BigInt q(a);
			BigInt r(b);
			BigInt s(0);
			while((Cmp(q,s)!=0)&&(Cmp(r,s)!=0))
			{
				if(Cmp(q,r)>0)
					q=q.Dif(q,r);
				else
					r=q.Dif(r,q);
			}
			if(Cmp(q,s)==0)
				return(r);
			else
				return(q);
		}
};


istream& operator>>(istream& is,BigInt& s)
{
	char c;
	c=getchar();
	while((c<='9')&&(c>='0'))
	{
		s.value.push_back(c-'0');
		c=getchar();
	}		
	return(is);
}

BigInt operator+(BigInt& bsl,BigInt& msl )
{
	if(bsl.size()>msl.size())
		return(bsl.Sum(bsl,msl));		
	else	
		return(msl.Sum(msl,bsl));
}

BigInt operator-(BigInt& bsl, BigInt& msl )
{
	if(bsl.size()>msl.size())
		return(bsl.Dif(bsl,msl));		
	else	
		return(msl.Dif(msl,bsl));
}

BigInt operator*(BigInt& bsl,BigInt& msl)
{
	if(bsl.size()>msl.size())
		return(bsl.Mult(bsl,msl));		
	else	
		return(msl.Mult(msl,bsl));
}

BigInt operator/(BigInt& bsl,BigInt& msl)
{
	if(bsl.size()>msl.size())
		return(bsl.Div(bsl,msl));		
	else	
		return(msl.Div(msl,bsl));
}

BigInt operator%(BigInt& bsl,BigInt& msl)
{	
	return(bsl.Mod(bsl,msl));		
}

const int Cmp(const BigInt& a, const BigInt& b)
{
	int i=0;
	if(a.value.size()>b.value.size()) return(1);
	else if (a.value.size()<b.value.size()) return(-1); 
	else
	{
	while((a.value[i]==b.value[i]) && (i<a.value.size()) && (i<b.value.size())) i++;
	if(a.value[i]>b.value[i]) return(1);
	if(a.value[i]<b.value[i]) return(-1);		
	if((a.value[i]==b.value[i]) && (a.value.size()==b.value.size())) return(0);
	}
}
int main()
{
	BigInt s(12),q(5);
	//cin>>s;
	//cin>>q;
	s.PrintInt();
	return(0);
}	
