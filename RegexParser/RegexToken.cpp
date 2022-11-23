//
//  RegexToken.cpp
//  CPPProject
//
//  Created by Adith Talupuru on 11/21/22.
//
#include "RegexToken.hpp"
#include <iostream>
void print(RegexToken tok){
	std::cout << "{ ";
	char type = tok.type;
	switch(type){
		case RegexToken::DELIMITER: {
			if(tok.id == RegexToken::OPENPAREN)
				std::cout << "Delim: (";
			else
				std::cout << "Delim: )";
			break;
		}
		case RegexToken::ERROR: {
			if(tok.id == RegexToken::END){
				std::cout << "Control: EOF";
			}
			else if(tok.id == RegexToken::UNRECOGNIZED){
				std::cout << "Control: ERROR";
			}
			break;
		}
		case RegexToken::LITERAL: {
			if(tok.id == RegexToken::ASCIIRANGE){
				std::cout << "Range: (" << tok.min << ", " << (char)(tok.min + tok.range) << ")";
			}
			else{
				std::cout << "Literal: " << (char)tok.id;
			}
			break;
		}
		case RegexToken::OPERATOR: {
			switch(tok.id){
				case RegexToken::KCLOSURE: {
					std::cout << "Quantifier: *";
					break;
				}
				case RegexToken::CLOSURE: {
					std::cout << "Quantifier: +";
					break;
				}
				case RegexToken::OPTIONAL: {
					std::cout << "Quantifier: ?";
					break;
				}
				case RegexToken::UNION: {
					std::cout << "Operator: |";
					break;
				}
				case RegexToken::CONCATENATE: {
					std::cout << "Operator: .";
					break;
				}
			}
			break;
		}
	}
	std::cout << " } ";
}
RegexToken::RegexToken(char _type, char _id, unsigned char _min, unsigned char _max): type(_type), id(_id), min(_min), range(_max){
	if(id == ASCIIRANGE){
		range = range - min;
	}
}
RegexToken::RegexToken(): type(LITERAL), min(0), range(0){
	if(type == ASCIIRANGE){
		range = range - min;
	}
}
