/*************************************************
	By Gagan Kumar(scopeInfinity)
		gagan1kumar@ymail.com

*************************************************/
/**********************************************************************
Calling Methods :

	//For Natural Sorting
	void SI::natural_sort(Container<String>);
	void SI::natural_sort(IteratorBegin<String>,IteratorEnd<String>);
	void SI::natural_sort<String,CArraySize>(CArray<String>);

	//For Natural Comparision
	bool SI::natural_comp<String>(String lhs,String rhs);
	bool SI::natural_comp<String>(char *const lhs,char *const rhs);

	Here we can have
		std::vector<std::string> 	as Container<String>
		String 						as std::string
		CArray<String>				as std::string[CArraySize]

***********************************************************************/
#ifndef SI_NATURAL_SORT_HPP
#define SI_NATURAL_SORT_HPP
#include <cctype>
#include <algorithm>
#include <vector>


namespace SI
{
	/********** Compare Two Character CaseInsensitive ********/
	template<typename T>
	bool natural_comp_element(const T &lhs,const T &rhs)
	{
		if(tolower(lhs)<tolower(rhs))
			return true;
		return false;
	}

	/****************************************************
	Comparing two SubString from (Begin,End Iterator each)
	with only digits.
	Usage :
		int natural_comp_num()(\
		FirstNumberBeginIterator,FirstNumberEndIterator,isFirstNumberFractionalPart\
		SecondNumberBeginIterator,SecondNumberEndIterator,isSecondNumberFractionalPart\
		);

	Returns : 
		-1  - Number1  <   Number2
		 0  - Number1  ==  Number2
		 1  - Number1  >   Number2

	***************************************************/

	template<typename Iterator>
	struct natural_comp_number
	{
	private:
		int fractional(Iterator first1,Iterator end1, Iterator first2,Iterator end2)
		{
			while(first1<end1 && first2<end2)
			{
				if(*first1<*first2)
					return -1;
				if(*first1>*first2)
					return +1;
				first1++;
				first2++;
			}
			while(first1<end1 && *first1=='0') first1++;
			while(first2<end2 && *first2=='0') first1++;
			if(first1==end1 && first2!=end2)
				return -1;
			else if(first1!=end1 && first2==end2)
				return +1;
			else //first1==end1 && first2==end2
				return 0;		
		}
		int non_fractional(Iterator first1,Iterator end1, Iterator first2,Iterator end2)
		{
			//Skip Inital Zero's
			while(first1<end1 && *first1=='0') first1++;
			while(first2<end2 && *first2=='0') first2++; \
	
			//Comparing By Length of Both String
			if(end1-first1<end2-first2)
				return -1;
			if(end1-first1>end2-first2)
				return +1;

			//Equal In length
			while(first1<end1)
			{
				if(*first1<*first2)
					return -1;
				if(*first1>*first2)
					return +1;
				first1++;
				first2++;
			}
			return 0;
		}


	public:
		int operator()(\
			Iterator first1,Iterator end1,bool isFractionalPart1,\
			Iterator first2,Iterator end2,bool isFractionalPart2)
		{
			if(isFractionalPart1 && !isFractionalPart2)
				return true;	//0<num1<1 && num2>=1
			if(!isFractionalPart1 && isFractionalPart2)
				return false;	//0<num2<1 && num1>=1

			//isFractionPart1 == isFactionalPart2
			if(isFractionalPart1)
				return fractional(first1,end1,first2,end2);
			else
				return non_fractional(first1,end1,first2,end2);
		}
	};
	

	template<typename T>
	bool is_not_digit(const T &x)
	{
		return !isdigit(x);
	}

	/***********************************************************************
	Natural Comparision of Two String using both's (Begin and End Iterator)

	Returns : 
		-1  - String1  <   String2
		 0  - String1  ==  String2
		 1  - String1  >   String2

	Suffix 1 represents for components of 1st String
	Suffix 2 represents for components of 2nd String
	************************************************************************/

	template<typename ValueType, typename Iterator>
	bool _natural_comp(Iterator first1,Iterator end1,Iterator first2,Iterator end2)
	{
		Iterator current1 = first1,current2 = first2;

		//Flag for Space Found Check
		bool flag_found_space1 = false,flag_found_space2 = false;


		while(current1!=end1 && current2!=end2)
		{
			//Ignore More than One Continous Space

			/******************************************
			For HandlingComparision Like
				Hello   9
				Hello  10
				Hello 123
			******************************************/
			while(flag_found_space1 && current1!=end1 && *current1==' ') current1++;
			flag_found_space1=false;
			if(*current1==' ') flag_found_space1 = true;
			
			while(flag_found_space2 && current2!=end2 && *current2==' ') current2++;
			flag_found_space2=false;
			if(*current2==' ') flag_found_space2 = true;
			

			if( !isdigit(*current1 ) && !isdigit(*current2))
			{
				//If Both Are Non Digits do Normal Comparision
				if(natural_comp_element(*current1,*current2))
					return true;
				if(natural_comp_element(*current2,*current1))
					return false;
				current1++;
				current2++;
			}
			else
			{
				/*********************************
				Capture Numeric Part of Both String
				and then using it to compare Both

				***********************************/
				Iterator last_nondigit1 = 	std::find_if(current1,end1,is_not_digit<ValueType>);
				Iterator last_nondigit2 = 	std::find_if(current2,end2,is_not_digit<ValueType>);
				
				int result = natural_comp_number<Iterator>()(\
					current1,last_nondigit1,(current1>first1 && *(current1-1)=='.'), \
					current2,last_nondigit2,(current2>first2 && *(current2-1)=='.'));
				if(result<0)
					return true;
				if(result>0)
					return false;
				current1 = last_nondigit1;
				current2 = last_nondigit2;
			}
		}

	}

	template<typename String>
	inline bool natural_comp(const String &first ,const String &second)
	{
		return _natural_comp<typename String::value_type>(first.begin(),first.end(),second.begin(),second.end());
	}
	template<>
	inline bool natural_comp(char *const &first ,char *const &second)
	{
		char* it1 = first;
		while(*it1!='\0')it1++;
		char* it2 = second;
		while(*it2!='\0')it2++;
		return _natural_comp<char>(first,it1,second,it2);
	}


	template<typename Container>
	inline bool natural_sort(Container &container)
	{
		std::sort(container.begin(),container.end(),natural_comp<typename Container::value_type>);
	}

	template<typename Iterator>
	inline bool natural_sort(Iterator first,Iterator end)
	{
		std::sort(first,end,natural_comp<typename Iterator::value_type>);
	}
	
	template<typename ValueType>
	inline bool natural_sort(ValueType* first,ValueType* end)
	{
		std::sort(first,end,natural_comp<ValueType>);
	}
	
	template<typename ValueType,int N>
	inline bool natural_sort(const ValueType *container)
	{
		std::sort(&container[0],&container[0]+N,natural_comp<ValueType>);
	}

	template<typename ValueType,int N>
	inline bool natural_sort(ValueType container[N])
	{
		std::sort(&container[0],&container[0]+N,natural_comp<ValueType>);
	}
	
}

#endif