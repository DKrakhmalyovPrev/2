class Point
{
	friend class Shell;
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
		
		
};
