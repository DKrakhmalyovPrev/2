#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;


class Drug
{
	private:
		string name;
		string maker;
		string sub;
		double dose;
		string form;
		double price;
	public:
		
		Drug()
		{
			price=0;			
		};
		
		Drug(const Drug& a)
		{
			name=a.name;
			maker=a.maker;
			sub=a.sub;
			dose=a.dose;
			form=a.form;
			price=a.price;
		}
		
		void ScanDrug()
		{
			cin>>name>>maker>>sub>>dose>>form;
			//scanf("%s %s %s %lf %s", name, maker, sub, &dose, form);
			price=0;
		}

		const void PrintDrug()
		{
			cout<<name<<' '<<maker<<' '<<sub<<' '<<dose<<' '<<form<<'\n';
			//printf("%s %s %s %lf %s", name, maker, sub, dose, form);
		}
		
		void AddPrice(double a)
		{
			price=a;
		}
		
		double GetPrice()
		{
			return(price);
		}
		
		friend class DrugStore;
};

class DrugStore
{
	private:
		vector<Drug> store;
	public:
		friend class Drug;

		DrugStore(){};
		
		DrugStore(const DrugStore& a)
		{
			store=a.store;
		}

		void AddDrug(const Drug& a)
		{
			store.push_back(a);
		}

		void AddDrugNow()
		{
			Drug a;
			a.ScanDrug();
			store.push_back(a);
		}
		
		DrugStore SearchBySubName(string a)
		{
			DrugStore q;
			for(int i=0; i<store.size(); i++)
			{
				if(store[i].name.find(a)==0)
					q.store.push_back(store[i]);
			}
			return(q);
		}

		DrugStore SearchByName(string a)
		{
			DrugStore q;
			for(int i=0; i<store.size(); i++)
			{
				if(a == store[i].name)
					q.store.push_back(store[i]);
			}
			return(q);
		}

		double SearchPriceByName(char* a)
		{
			for(int i=0; i<store.size(); i++)
			{
				if(a == store[i].name)
					return(store[i].price);
				
			}	
			return(0);
		}
		
		DrugStore SearchByMaker(string a)
		{
			DrugStore q;
			for(int i=0; i<store.size(); i++)
			{
				if(a == store[i].maker)
					q.store.push_back(store[i]);
			}
			return(q);
		}
		
		DrugStore SearchBySub(string a)
		{
			DrugStore q;
			for(int i=0; i<store.size(); i++)
			{
				if(a == store[i].sub)
					q.store.push_back(store[i]);
			}
			return(q);
		}
		
		
		DrugStore SearchByMakerNSub(string a, string b)
		{
			DrugStore q;
			q=this->SearchByMaker(a);
			q=q.SearchBySub(b);	
			return(q);
		}
		
		DrugStore SearchByForm(string a)
		{
			DrugStore q;
			for(int i=0; i<store.size(); i++)
			{
				if(a==store[i].form)
					q.store.push_back(store[i]);
			}
			return(q);
		}

		DrugStore SearchBySubNForm(string a, string b)
		{
			DrugStore q;
			DrugStore s;
			q=this->SearchBySub(a);
			s=q.SearchByForm(b);
			return(s);
		}
		
		//формировать и выводить заказ по названиям препаратов	
		
		
		DrugStore FormOrderByName(int l)
		{
			DrugStore q;
			DrugStore s;
			char* a;
			for(int i=0; i<l; i++)
			{
				cin>>a;
				q=this->SearchByName(a);
				s.store.push_back(q.store[0]);
			}
			return(s);
		}
		
		void PrintOrder()
		{
			for(int i=0; i<store.size(); i++)
				store[i].PrintDrug();
		}

		//формировать и выводить заказ по названиям действующих веществ, минимизируя его стоимость

		
		DrugStore FormOrderBySub(int l)
		{
			DrugStore q;
			DrugStore s;
			char* a;
			for(int i=0; i<l; i++)
			{
				cin>>a;
				q=this->SearchByName(a);
				int k = 0;
				double p=q.store[0].price;
				for(int j=1; j<q.store.size(); j++)
					if(q.store[j].price<p)
						k=j;
				s.store.push_back(q.store[k]);
			}	
			return(s);
		}

		void DeleteFromOrder(int s)
		{
			for(int i=s; i<store.size()-1; i++)
				store[i]=store[i+1];
			store.pop_back();
		}
		
		
		
};

bool operator==(const string& a, const string& b)
{
	auto ita=a.begin();
	auto itb=b.begin();
	bool q=1;
	while( (ita<a.end()) && (itb<b.end()) )
	{ 
		if( (*ita)!=(*itb) )
			q=0;
		ita++; itb++;
	} 	
	return(q);
}


		
int main()
{
	DrugStore a;
	a.AddDrugNow();
	a.AddDrugNow();
	DrugStore b;
	b=a.SearchByName("ab");
	b.PrintOrder();
	return(0);
}
			
