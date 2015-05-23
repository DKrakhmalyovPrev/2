#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class Point
{
	friend class Segment;
	friend class ALotOfSegm;	
	private:		
		double x,y;
	public:
		Point(){};

		Point(double j,double k): x(j), y(k){};
		
		void ScanPoint()
		{
			cin>>x>>y;
		}
		
		void PrintPoint()
		{
			cout<<x<<" "<<y;
		}
		
		double Getx(){return(x);};
		double Gety(){return(y);};
		void Sety(double j){y=j;};
		void Setx(double j){x=j;};
	
		
		
};

class Segment
{
	friend class Point;
	friend class ALotOfSegm;	
	private:		
		Point fst, snd; double A, B, C;
	public:
		Segment(){}
		
		Segment(const Point& i,const Point& j): fst(i), snd(j){};
	

		void ScanSegment()
		{
			cin>>fst.x>>fst.y>>snd.x>>snd.y;
		}
		
		void PrintSegment()
		{
			cout<<fst.x<<" "<<fst.y<<" "<<snd.x<<" "<<snd.y;
		}

		void Lane()
		{
			double k=(snd.y-fst.y)/(snd.x-fst.x);
			double b=(snd.x*fst.y-fst.x*snd.y)/(snd.x-fst.x);
			A=k;
			B=-1;
			C=-b;
		}
		
		bool SegmentCut(Segment& r, Segment& s)
		{
			double x,y;
			r.Lane();
			s.Lane();
			if( ((r.fst.x*s.A+r.fst.y*s.B-s.C) * (r.snd.x*s.A+r.snd.y*s.B-s.C) >= 0) 
				|| ((s.fst.x*r.A+s.fst.y*r.B-r.C) * (s.snd.x*r.A+s.snd.y*r.B-r.C) >= 0)) 
			{return(0);} 
			else {return(1);};
		}	
		
		const bool SegmentPoint(Segment& seg, Point& po)
		{
			seg.Lane();
			if( (seg.A*po.x + seg.B*po.y == seg.C) && ( (po.x-seg.fst.x) * (po.x-seg.snd.x) <= 0) )
				return(1);
			else
				return(0);
		} 
		
		const int LanePoint(Segment& seg, Point po)
		{
			seg.Lane();
			if( seg.A*po.x + seg.B*po.y > seg.C) return(-1);//Выше
			if( seg.A*po.x + seg.B*po.y < seg.C) return(1); //Ниже
			if( seg.A*po.x + seg.B*po.y == seg.C) return(0);//На прямой
		}

			
		Point SegtoSeg(Segment& r, Segment& s)
		{
			double x,y;
			r.Lane();
			s.Lane();
			y=( (s.C-r.C * (s.A/r.A)) / (s.B-r.B * (s.A/r.A)) );
			x=( r.C - r.B*y ) / r.A;
			Point q(x,y);
			 
			return(q);
		}
		
	
		
};	

class ALotOfSegm
{
	friend class Point;	
	friend class Segment;
	private:
		vector<Segment> alot;
		vector<Point> all;
	public:
		ALotOfSegm(){};
		ALotOfSegm(const ALotOfSegm& a)
		{
			alot=a.alot;
		}
		
		void AddSegm(const Segment& a)
		{
			alot.push_back(a);
		}

		void AddNow()
		{
			Segment a;
			a.ScanSegment();
			alot.push_back(a);
		}

		void DoThat()
		{
			for(int i=0; i<alot.size(); i++)
				for(int j=i+1;j<alot.size(); j++)
				{
					if( alot[i].SegmentCut(alot[i], alot[j]) )
					{
						all.push_back(alot[i].SegtoSeg(alot[i],alot[j]) );
					}
				}
		}
			
		void PrintDots()
		{
			for(int i=0;i<all.size(); i++)
				cout<<"( "<<all[i].x<<" , "<<all[i].y<<" )"<<"\n";
		}
};

int main()
{
	ALotOfSegm a;
	for(int i=0;i<3; i++)
		a.AddNow();
	a.DoThat();
	a.PrintDots();
	return(0);
}
	
