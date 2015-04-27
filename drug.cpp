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
			GetVector(name);
			GetVector(maker);
			GetVector(sub);
			GetVector(form);
			cin>>dose;
			price=0;
		}

		const void PrintDrug()
		{
			PrintVector(name);
			PrintVector(maker);
			PrintVector(sub);
			PrintVector(form);
			cout<<dose;
		}
		
		void AddPrice(double a)
		{
			price=a;
		}
		
		double GetPrice()
		{
			return(price);
		}
		
		friend const void PrintVector(vector<char>&);
		friend void GetVector(vector<char>&);
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
		
		DrugStore SearchByLetter(char a)
		{
			DrugStore q;
			for(int i=0; i< store.size(); i++)
				if(store[i].name[0]==a)
					q.store.push_back(store[i]);
			return(q);
		}
		
		DrugStore SearchByName(char* a)
		{
			DrugStore q;
			for(int i=0; i<store.size(); i++)
			{
				int k=0;
				while( (a[k]==store[i].name[k]) && (k<strlen(a)) && (k<store[i].name.size()) )
					k++;
				if( (k==strlen(a)-1) && (k==store[i].name.size()-1) )
					q.store.push_back(store[i]);
			}
			return(q);
		}

		double SearchPriceByName(char* a)
		{
			for(int i=0; i<store.size(); i++)
			{
				int k=0;
				while( (a[k]==store[i].name[k]) && (k<strlen(a)) && (k<store[i].name.size()) )
					k++;
				if( (k==strlen(a)-1) && (k==store[i].name.size()-1) )
					return(store[k].price);
			}	
			return(0);
		}
		
		DrugStore SearchByMaker(char* a)
		{
			DrugStore q;
			for(int i=0; i<store.size(); i++)
			{
				int k=0;
				while( (a[k]==store[i].maker[k]) && (k<strlen(a)) && (k<store[i].maker.size()) )
					k++;
				if( (k==strlen(a)-1) && (k==store[i].maker.size()-1) )
					q.store.push_back(store[i]);
			}
			return(q);
		}
		
		DrugStore SearchBySub(char* a)
		{
			DrugStore q;
			for(int i=0; i<store.size(); i++)
			{
				int k=0;
				while( (a[k]==store[i].sub[k]) && (k<strlen(a)) && (k<store[i].sub.size()) )
					k++;
				if( (k==strlen(a)-1) && (k==store[i].sub.size()-1) )
					q.store.push_back(store[i]);
			}
			return(q);
		}
		
		
		DrugStore SearchByMakerNSub(char* a, char* b)
		{
			DrugStore q;
			q=this->SearchByMaker(a);
			q=q.SearchBySub(b);	
			return(q);
		}
		
		DrugStore SearchByForm(char* a)
		{
			DrugStore q;
			for(int i=0; i<store.size(); i++)
			{
				int k=0;
				while( (a[k]==store[i].form[k]) && (k<strlen(a)) && (k<store[i].form.size()) )
					k++;
				if( (k==strlen(a)-1) && (k==store[i].form.size()-1) )
					q.store.push_back(store[i]);
			}
			return(q);
		}

		DrugStore SearchBySubNForm(char* a, char* b)
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
		
		void PrintOrder(DrugStore& a)
		{
			for(int i=0; i<a.store.size(); i++)
				a.store[i].PrintDrug();
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
		
int main()
{
	
	return(0);
}
			
