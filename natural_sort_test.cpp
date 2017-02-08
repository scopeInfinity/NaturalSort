#include <iostream>
#include <vector>
#include <string>
#include "natural_sort.hpp"

int main()
{	
	std::vector<std::string> v;
	std::string s;
	std::cout<<"Comparision of \"Hello 32\" and \"Hello 023\" : "<<(SI::natural::compare<std::string>("Hello 32","Hello 023"))<<" (Expected: 0)"<<std::endl;
	std::cout<<"Comparision of \"Hello 32a\" and \"Hello 32\" : "<<(SI::natural::compare<std::string>("Hello 32a","Hello 32"))<<" (Expected: 0)"<<std::endl;
	std::cout<<"Comparision of \"Hello 32\" and \"Hello 32a\" : "<<(SI::natural::compare<std::string>("Hello 32","Hello 32a"))<<" (Expected: 1)"<<std::endl;
	std::cout<<"Comparision of \"Hello 32.1\" and \"Hello 32\" : "<<(SI::natural::compare<std::string>("Hello 32.1","Hello 32"))<<" (Expected: 0)"<<std::endl;
	std::cout<<"Comparision of \"Hello 32\" and \"Hello 32.1\" : "<<(SI::natural::compare<std::string>("Hello 32","Hello 32.1"))<<" (Expected: 1)"<<std::endl;
	std::cout<<"Comparision of \"Hello 32\" and \"Hello 32\" : "<<(SI::natural::compare<std::string>("Hello 32","Hello 32"))<<" (Expected: 0)"<<std::endl;
	while(getline(std::cin,s))
		v.push_back(s);
	std::vector<char *> v2;
	for (std::vector<std::string>::iterator it = v.begin(); it!=v.end(); ++it)
		v2.push_back((char*)it->c_str());
	

	SI::natural::sort(v);
	std::cout<<"Output Using std::string\n";
	for (std::vector<std::string>::iterator it = v.begin(); it!=v.end(); ++it)
		std::cout<<*it<<std::endl;
	

	SI::natural::sort(v2);
	std::cout<<"Output Using char*\n";
	for (std::vector<char*>::iterator it = v2.begin(); it!=v2.end(); ++it)
		std::cout<<*it<<std::endl;


	std::cout<<"Output Using array As Container\n";
	std::string array[5]={"Hello 1","Hello 2","Hello 10","Hello 10.3","Hello 10.23"};
	SI::natural::sort<std::string,5>(array);

	for(int i=0;i<5;i++)
		std::cout<<array[i]<<std::endl;
	return 0;
}
