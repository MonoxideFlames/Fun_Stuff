//
//  ShuntingYard.hpp
//  CPPProject
//
//  Created by Adith Talupuru on 11/21/22.
//

#ifndef ShuntingYard_hpp
#define ShuntingYard_hpp

#include "DoubleStack.h"
#include "RegexScanner.h"

class ShuntingYard {
	DoubleStack<RegexToken> stack;
	RegexToken currentToken;
	RegexScanner stream;
public:
	ShuntingYard(RegexScanner tokenStream);
	~ShuntingYard(){
		
	}
	RegexToken getNext();
};
#endif /* ShuntingYard_hpp */
