#include <iostream>

#include <stdio.h>

#include <cstdlib>

#include <math.h>

#include <vector>

#include <string.h>


using namespace std;


	

class BigInt
{
	private:
		vector<int> value;
		int sign;
	
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
				value.push_back(s/i);
				s%=i;
			}
			if(q<0)
				sign=-1;
			else
				sign=1;
		}
		
		BigInt(const BigInt& q)
		{
			for(int i=0; i< q.value.size(); i++)
				value.push_back(q.value[i]);
			sign=q.sign;
		}
		
		BigInt(const char* q)
		{	
			if(q[0]=='-')
				sign=-1;
			else
			{
				sign=1;
				value.push_back(q[0]-'0');
			}
			for(int i=1; i< strlen(q); i++)
				value.push_back(q[i]-'0');
		}
		const int size()
		{
			return(value.size());
		}
	
		const void PrintInt()
		{
			//FILE* output=fopen("output.txt", "w");
			if(sign==-1) 
				//fprintf(output,"-");
				cout<<"-";
			for(int i=0;i<value.size(); i++)
				cout<<value[i];
				//fprintf(output,"%d", value[i]);
			cout<<"\n";
		}
		
		friend istream& operator>>(istream&, BigInt&);
		friend BigInt operator+(BigInt&, BigInt&);
		friend BigInt operator*(BigInt&, BigInt&);
		friend BigInt operator/(BigInt&, BigInt&);
		friend BigInt operator%(BigInt&, BigInt&);
		friend BigInt operator-(BigInt&, BigInt&);
		friend const int Cmp(const BigInt&, const BigInt&);
		
		

		BigInt Sum(const BigInt& bsl, const BigInt& msl )
		{
			int maxs=bsl.value.size();
			int mins=msl.value.size();
			int os=0; 
			int* ti;
			ti=new int[maxs+1];
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
			s.sign=bsl.sign;
			return(s) ;
		}

		BigInt Dif(const BigInt& bsl, const BigInt& msl )
		{
			int maxs=bsl.value.size();
			int mins=msl.value.size();
			int os=0; 
			int* ti;
			ti=new int[maxs+1];
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
			s.sign=bsl.sign;
			return(s) ;
		}
		
		BigInt Mult(const BigInt& bsl, const BigInt& msl )
		{
			int maxs=bsl.value.size();
			int mins=msl.value.size();
	
			int* result;
			result=new int[maxs+mins+1];
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
			jack.sign=bsl.sign*msl.sign;
			return(jack);
		}
		
		BigInt Div(const BigInt& a,const BigInt& b)
		{
			BigInt k(a);
			BigInt l(b);
			int i;
			i=0;
			while(Cmp(k,l)>=0)
			{	
				k=k.Dif(k,l);
				i++;
			}
			BigInt s(i);
			s.sign=a.sign*b.sign;
			return(s);
		}
				
		BigInt Mod(const BigInt& a,const BigInt& b)
		{		
			BigInt q;
			BigInt s(0);
			
			q=q.Div(a,b);
			q=q.Mult(q,b);
			q=q.Dif(a,q);
			q.sign=a.sign*b.sign;
			return(q);
		}
};


istream& operator>>(istream& is,BigInt& s)
{
	char c;
	c=getchar();
	s.sign=1;
	if(c=='-')
	{
		s.sign=-1;
		c=getchar();
	}
	while((c<='9')&&(c>='0'))
	{
		s.value.push_back((c-'0'));
		c=getchar();
	}		
	return(is);
}

BigInt operator+(BigInt& bsl,BigInt& msl )
{
	if((bsl.sign==msl.sign)&&(Cmp(bsl,msl)==1)) return(bsl.Sum(bsl,msl));
	if((bsl.sign==msl.sign)&&(Cmp(bsl,msl)!=1)) return(bsl.Sum(msl,bsl));
	if((bsl.sign!=msl.sign)&&(Cmp(bsl,msl)==1)) return(bsl.Dif(bsl,msl));
	if((bsl.sign!=msl.sign)&&(Cmp(bsl,msl)!=1)) return(bsl.Dif(msl,bsl));
}

BigInt operator-(BigInt& bsl, BigInt& msl )
{
	if((bsl.sign==msl.sign)&&(Cmp(bsl,msl)==1)) return(bsl.Dif(bsl,msl));
	if((bsl.sign==msl.sign)&&(Cmp(bsl,msl)!=1))
	{
		BigInt temp(bsl.Dif(msl,bsl));
		temp.sign*=-1;
		return(temp);
	}
	
	if((bsl.sign!=msl.sign)&&(Cmp(bsl,msl)==1)) return(bsl.Sum(bsl,msl));
	if((bsl.sign!=msl.sign)&&(Cmp(bsl,msl)!=1))
	{
		BigInt temp(msl.Sum(msl,bsl));
		temp.sign*=-1;
		return(temp);
	}
		
}

BigInt operator*(BigInt& bsl,BigInt& msl)
{
	if(Cmp(bsl,msl)==1) return(bsl.Mult(bsl,msl));
	else return(bsl.Mult(msl,bsl));
}

BigInt operator/(BigInt& bsl,BigInt& msl)
{
	return(bsl.Div(bsl,msl));
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
		if(a.value[i]==b.value[i]) return(0);
	}
	
}

void test1()
{
	BigInt t1;
	BigInt t2;
	cin>>t1;
	cin>>t2;
	(t1+t2).PrintInt();
	(t2-t1).PrintInt();
	(t1*t2).PrintInt();
	(t1/t2).PrintInt();
	(t2%t1).PrintInt(); 
	
}
	
	
			
		
int main()
{
	test1();

	return(0);
}	
