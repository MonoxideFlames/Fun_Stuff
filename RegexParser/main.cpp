//
//  main.cpp
//  ExpressionEvaluator
//
//  Created by Adith Talupuru on 10/22/22.
//
#include "RegexScanner.h"
#include "ShuntingYard.hpp"
#include <iostream>
int main(int argc, const char** argv){
	const char* str;// = "(a|b)c*([\\?z]+e?)+";
	std::string string;
	std::cout << "Enter REGEX: \n";
	std::cin >> string;
	str = string.c_str();
	
	RegexScanner res = RegexScanner(str);
	
	ShuntingYard parser = ShuntingYard(res);
	
	RegexToken next = parser.getNext();
	while(next.type != RegexToken::ERROR){
		print(next);
		next = parser.getNext();
	}
   return 0;
}
