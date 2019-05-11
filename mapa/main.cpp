#include <iostream>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

struct order {
	int order_id ,user_id ,dish_id ,factory_id ,class_id ,date;
	string user_name ,dish_name ,factory_name;
}data[100];

int main(int argc, char** argv) {
	map<int ,map<int ,map<int ,vector<order> > > > category;
	
	int i;
	int n;
	
	for(cin >> n ,i = 0;i != n;i++) 
		cin >> data[i].order_id
			>> data[i].user_id
			//>> data[i].user_name
			>> data[i].dish_id											
			//>> data[i].dish_name
			>> data[i].factory_id
			//>> data[i].factory_name
			>> data[i].date
			>> data[i].class_id;
	
	for(i = 0;i != n;i++)
		category[data[i].factory_id][data[i].class_id][data[i].date].push_back(data[i]);
	
	for(auto j = category.begin();j != category.end();j++)
		for(auto k = (*j).second.begin();k != (*j).second.end();k++)
			for(auto l = (*k).second.begin();l != (*k).second.end();l++)	
				for(i = 0;i != (*l).second.size();i++)
				{
					order tmp = (*l).second[i];
					cout << tmp.order_id << "\t"
						<< tmp.user_id << "\t"
						<< tmp.user_name << "\t"
						<< tmp.dish_id << "\t"								
						<< tmp.dish_name << "\t"
						<< tmp.factory_id << "\t"
						<< tmp.factory_name << "\t"
						<< tmp.date << "\t"
						<< tmp.class_id << endl; 
				}																																																																																						
}
