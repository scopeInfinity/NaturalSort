#include <iostream>
#include <vector>
#include "../natural_sort.hpp"


int main(int argc, char const *argv[])
{
	std::vector<std::string> v;
	std::string s;
	while(getline(std::cin,s))
		v.push_back(s);
	
	SI::natural_sort(v);
	for (std::vector<std::string>::iterator it = v.begin(); it!=v.end(); ++it)
		std::cout<<*it<<std::endl;
	
	return 0;
}