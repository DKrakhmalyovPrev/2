#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "point.h"

using namespace std;




class Shell
{
	friend class Point;
	private:
		vector<Point> var;
	
	public:
	
		Shell(){};

		Shell(const Shell& a)
		{
			var=a.var;
		}
		
		void AddPoint()
		{
			Point a;
			a.ScanPoint();	
			var.push_back(a);
			cout<<"ПРочитано и добавлено";
		}

		void PrintShell()
		{
			for(int i=0; i<var.size(); i++)
				cout<<"x"<<i<<"="<<var[i].x<<"  y"<<i<<"="<<var[i].y<<"\n";
		}
			

		void DeletePoint(int i)
		{
			for(int j=i;j<var.size()-1;j++)
				var[j]=var[j+1];
			var.pop_back();
		}
		
		Shell DoTheShell()
		{
			Shell a;
			Shell b(*this);
			double minx=var[0].x;
			double miny=var[0].y;
			int j=0;
			for(int i=1; i<b.var.size(); i++)
			{	
				if( (b.var[i].y < b.var[j].y) || ( (b.var[i].y == b.var[j].y) && (b.var[i].x < b.var[j].x) ) )
				{
					j=i;
				}
			}
			
			a.var.push_back(b.var[j]);
			
			int l=j+1;
		
			minx=b.var[j].x;
			miny=b.var[j].y;
			while(j!=l)
			{	
				double s=minx * b.var[l+1].y - miny * b.var[l+1].x;
				for(int k=0; k<b.var.size(); k++)
				{
					double r =minx * b.var[k].y- miny * b.var[k].x;
					if( (r!=0) && (r<s) )
					{
						l=k;
						s=r;
					}
					else
					if(  ( r==0 ) && (k!=l) && (b.var[k].x>b.var[l].x) )
					{
						l=k;
						s=r;
					}
				}

				a.var.push_back(b.var[l]);	
				minx=b.var[l].x;
				miny=b.var[l].y;
			} 
			
			return(a);
		}
};

int main()
{
	
	return(0);
}
	
