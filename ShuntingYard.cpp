//
//  ShuntingYard.cpp
//  CPPProject
//
//  Created by Adith Talupuru on 11/21/22.
//
#include "ShuntingYard.hpp"
/*
Stack will have one dummy parenthesis at the bottom, allowing the state of
 "Stack empty" to be a condition which need not be checked all the time.
 */
ShuntingYard::ShuntingYard(RegexScanner tokenStream){
	//the constructor gets called once already, calling it twice causes a few problems.
	stack.pushBack(RegexToken(RegexToken::DELIMITER, RegexToken::OPENPAREN, 0, 0));
	stream = tokenStream;
	currentToken = stream.next();
}

RegexToken ShuntingYard::getNext(){
	while(true){
		switch(currentToken.type){
			case RegexToken::LITERAL :{
				stack.pushBack(currentToken);
				currentToken = stream.next();
				return stack.popBack();
			}
			break;
			case RegexToken::DELIMITER :{
				if(currentToken.id == RegexToken::OPENPAREN){
					stack.pushBack(currentToken);
					currentToken = stream.next();
				}
				else{
					if(stack.getBack().type != RegexToken::DELIMITER){
						return stack.popBack();
					}
					else{
						currentToken = stream.next();//replace '(', since its job is done. we've popped off everything between the '()'
						stack.popBack();//pop off open paren as its job is also done.
					}
				}
			}
			break;
			case RegexToken::ERROR :{
				if(stack.backSize() == 1){
					return RegexToken(RegexToken::ERROR, RegexToken::END);//if our stack and input are empty, parsing is over: return 'end' token.
				}
				return stack.popBack();//otherwise, we return what's left on the stack.
			}
			break;
			case RegexToken::OPERATOR: {
				if(stack.getBack().precedence > currentToken.precedence){
					return stack.popBack();//if the stack has a higher precedence, return stack.
				}
				if(stack.getBack().precedence == currentToken.precedence){
					if(stack.getBack().associativity == RegexToken::LEFT){
						return stack.popBack();
					}
					else{
						stack.pushBack(currentToken);
						currentToken = stream.next();
					}
				}
				else{
					stack.pushBack(currentToken);
					currentToken = stream.next();
				}
			}
			break;
			default:
			break;
		}
	}
}
