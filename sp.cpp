#include <iostream>
#include <unordered_map>
#include <string>
#include <stdlib.h>
using namespace std;

class StringPool
{
	private:
		unordered_map<int, std::string> data;
	public:
		StringPool(){};
      
    
		int GetId(const string& word)
		{
			data[(int)hash<string>()(word)] = word;
			return (int)hash<string>()(word);
		}
    
		string GetWord(int id)
		{
			return data[id];
		}
};
    

int main()
{
	StringPool s;
	s.GetId("lala");
	s.GetId("house");
	s.GetId("home");
	int i;
	i=s.GetId("house");
	cout << s.GetWord(i) << "\n";
	return 0;
}
