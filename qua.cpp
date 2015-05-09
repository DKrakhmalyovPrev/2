#include <iostream>

#include <stdio.h>

#include <cstdlib>

#include <math.h>

#include <ctime>


using namespace std;

class Quater
{	
	private:
		double mat[4][4];
	public:

		Quater(){};
		
		Quater(double a, double b, double c, double d)
		{
			mat[0][0]=a; mat[1][0]=b; mat[2][0]=c; mat[3][0]=d;
			mat[0][1]=-b; mat[1][1]=a; mat[2][1]=d; mat[3][1]=-c;
			mat[0][2]=-c; mat[1][2]=-d; mat[2][2]=a; mat[3][2]=b;
			mat[0][3]=-d; mat[1][3]=c; mat[2][3]=-b; mat[3][3]=a;
		}
		
		Quater(const Quater& a)
		{
			for(int i=0; i<4; i++)
				for(int j=0; j<4; j++)
					mat[i][j]=a.mat[i][j];
		}

		void ScanQua()
		{
			double a,b,c,d;
			cin>>a>>b>>c>>d;
			//fscanf(input, "%lf%lf%lf%lf", &a,&b,&c,&d);
			mat[0][0]=a; mat[1][0]=b; mat[2][0]=c; mat[3][0]=d;
			mat[0][1]=-b; mat[1][1]=a; mat[2][1]=d; mat[3][1]=-c;
			mat[0][2]=-c; mat[1][2]=-d; mat[2][2]=a; mat[3][2]=b;
			mat[0][3]=-d; mat[1][3]=c; mat[2][3]=-b; mat[3][3]=a;

		}

		void PrintQua()
		{
			FILE* output;
			output=fopen("output.txt", "ab");
			for(int i=0;i<4;i++)
				fprintf(output,"%lf ", mat[i][0]);
			fprintf(output,"\n");
			//cout<<mat[0][0]<<" "<<mat[1][0]<<" "<<mat[2][0]<<" "<<mat[3][0]<<"\n";
		}


		double operator[](int i)
		{
			return(mat[i][0]);
		};
	
		

		Quater Conj()
		{
			Quater b;
			for (int i=0;i<4;i++)
				for(int j=0;j<4;j++)
					b.mat[i][j]=mat[j][i];
			return(b);
		}
	
		void ToDiagUp()
		{	
			double co;
			for(int i=0;i<3;i++)
			{
				if(mat[i][i]==0)
				{
					int p=i;
					while((mat[p][i]==0)&&(p<4)){p++;};
					for(int k=0;k<4;k++)
					{
						co=mat[p][k];
						mat[p][k]=mat[i][k];
						mat[i][k]=co;
					};
				}	
				if(mat[i][i]!=0)
					for(int j=i+1;j<4;j++)
					{
						double b=mat[j][i]/mat[i][i];
						for(int k=i;k<4;k++)
						{	
							mat[j][k]-=b*mat[i][k];
						}
					}
				
			}
		}

		double Determ()
		{	
			double det=1;
			Quater table1(*this);
			table1.ToDiagUp();
			for(int i=0;i<4;i++)
				det*=table1.mat[i][i];
			return(det);
		}

		double Mod()
		{
			double q;
			q=this->Determ();
			q=sqrt(sqrt(q));
			return(q);
		}

		friend Quater const operator*(const Quater&, const Quater&);
		friend Quater const operator+(const Quater&, const Quater&);
		friend Quater const operator-(const Quater&, const Quater&);
		friend void operator+=(Quater&, const Quater&);
		friend void operator-=(Quater&, const Quater&);
		friend void operator*=(Quater&, const Quater&);
		
		friend bool operator==(const Quater&, const Quater&);
		
		void operator=(const Quater& a)
		{
			for(int i=0; i<4; i++)
				for(int j=0; j<4; j++)
					mat[i][j]=a.mat[i][j];
		};		
};

Quater const operator*(const Quater& a, const Quater& b)
{
	double q;
	Quater mult;
	for (int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			q=0;
			for(int r=0;r<4;r++)
				q+=a.mat[r][j]*b.mat[i][r];
			mult.mat[i][j]=q;
		};
	return(mult);
};

Quater const  operator+(const Quater& a, const Quater& b)
{
	Quater sum;
	for (int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			sum.mat[i][j]=a.mat[i][j]+b.mat[i][j];
	return(sum);
};

Quater const  operator-(const Quater& a, const Quater& b)
{
	Quater dif;
	for (int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			dif.mat[i][j]=a.mat[i][j]-b.mat[i][j];
	return(dif);
};

void operator+=(Quater& a, const Quater& b)
{
	for (int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			a.mat[i][j]=a.mat[i][j]+b.mat[i][j];
};

void operator-=(Quater& a, const Quater& b)
{
	for (int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			a.mat[i][j]=a.mat[i][j]-b.mat[i][j];
};

void operator*=(Quater& a, const Quater& b)
{
	double q;
	Quater mult;
	for (int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			q=0;
			for(int r=0;r<4;r++)
				q+=a.mat[r][i]*b.mat[j][r];
			mult.mat[j][i]=q;
		};
	for (int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			a.mat[i][j]=a.mat[i][j]+mult.mat[i][j];
};


bool operator==(const Quater& a, const Quater& b)
{	
	bool s=1;
	for(int i=0; i<4; i++)
		if(a.mat[i][0]!=b.mat[i][0])
		s=0;
	return(s);
}

int test()
{
	FILE* input;
	input=fopen("input.txt", "r");
	
	double x,y,z,r;
	fscanf(input, "%lf%lf%lf%lf", &x,&y,&z,&r);	
	Quater a(x,y,z,r);
	fscanf(input, "%lf%lf%lf%lf", &x,&y,&z,&r);	
	Quater b(x,y,z,r);
	Quater c;
	c=a*b;
	a+=b;
	b=c-a;
	a.PrintQua();
	b.PrintQua();
	c.PrintQua();
	return(0);
}
	
	
int main()
{
	test();
	return(0);
}
