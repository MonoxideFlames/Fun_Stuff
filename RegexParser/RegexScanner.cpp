#include "RegexScanner.h"
RegexScanner::RegexScanner(const char* str){
   input = str;
   current = 0;
}
RegexScanner::RegexScanner(){}
RegexToken RegexScanner::next(){
//we expect a character operand first, either a range or literal or parenthetical subexpression. Anything after an operand, we expect an operator. (The concatenate is made explicit)
   char c = input[current];
   switch(c) {
      case '[':{
         if(expectingOperator){
            expectingOperator = false;
            return RegexToken(RegexToken::OPERATOR,RegexToken::CONCATENATE, 150, RegexToken::LEFT);//if we are expecting an operator, and find an operand, assume an implicit concatenate operator.
         }
         expectingOperator = true;
         return range();
      }
      case '\\':{
         char c = escapeSequence();
         return returnLiteralToken(c);
      }
      case '*':{
         if(expectingOperator){
            current++;
            return RegexToken(RegexToken::OPERATOR,RegexToken::KCLOSURE, 200, RegexToken::LEFT);
         }
         current++;
         return RegexToken(RegexToken::OPERATOR,RegexToken::UNRECOGNIZED);
      }
      case '+':{
         if(expectingOperator){
            current++;
            return RegexToken(RegexToken::OPERATOR,RegexToken::CLOSURE, 200, RegexToken::LEFT);
         }
         current++;
         return RegexToken(RegexToken::ERROR, RegexToken::UNRECOGNIZED);
      }
      case '?':{
         if(expectingOperator){
            current++;
            return RegexToken(RegexToken::OPERATOR,RegexToken::OPTIONAL, 200, RegexToken::LEFT);
         }
         current++;
         return RegexToken(RegexToken::ERROR, RegexToken::UNRECOGNIZED);
      }
      case '(':{
         if(expectingOperator){
            expectingOperator = false;
            return RegexToken(RegexToken::OPERATOR,RegexToken::CONCATENATE, 150, RegexToken::LEFT);
         }
         current++;
         return RegexToken(RegexToken::DELIMITER,RegexToken::OPENPAREN, 50);
      }
      case ')':{
         expectingOperator = true;
         current++;
         return RegexToken(RegexToken::DELIMITER,RegexToken::CLOSEPAREN, 255, RegexToken::LEFT);
      }
      case '|': {
         if(expectingOperator){
            current++;
            expectingOperator = false;
            return RegexToken(RegexToken::OPERATOR, RegexToken::UNION, 100, RegexToken::LEFT);
         }
         return RegexToken(RegexToken::ERROR, RegexToken::UNRECOGNIZED);
      }
      case '\0' : {
         return RegexToken(RegexToken::ERROR, RegexToken::END);
      }
      default:{
         return returnLiteralToken(c);
      }
   }
}

RegexToken RegexScanner::returnLiteralToken(char c){
   if(expectingOperator){
      expectingOperator = false;
      return RegexToken(RegexToken::OPERATOR,RegexToken::CONCATENATE, 150, RegexToken::LEFT);
   }
   current++;
   expectingOperator = true;
   return RegexToken(RegexToken::LITERAL, c);
}
char RegexScanner::escapeSequence(){
	char next = input[current + 1];
	current += 2; // ./e -> /e.
	switch(next) {
		case 's':
			return ' ';
		case 'a':
			return '\a';
		case 'b':
			return '\b';
		case 'f':
			return '\f';
		case 'n':
			return '\n';
		case 'r':
			return '\r';
		case 't':
			return '\t';
		case 'v':
			return '\v';
		default:
			return next;   //eg \\ is backslash; and \? is question mark.
								//It escapes the optional character postix quantifier
	}
}
//determines the character literal from an escape sequence, and makes a "Literal" token out of it. It reads and advances to the character right after the lexeme.

RegexToken RegexScanner::range(){
   current++;//advances .[az] -> [.az]
   char min;
   char max;
   if(input[current] == '\\'){//if the current char is a backslash,
      min = escapeSequence();
   }
   else {
      min = input[current];
      current++;
   }
   if(input[current] == '\\'){//if the current char is a backslash,
      max = escapeSequence();
   }
   else {
      max = input[current];
      current++;
   }
   current++;  // [abcd.] -> [abcd].
   return RegexToken(RegexToken::LITERAL, RegexToken::ASCIIRANGE, min, max);
}
//evaluates and tokenizes an ascii range, advances to the character behind the corresponding lexeme

void RegexScanner::removeWhitespace(){
   char c = input[current];
   while((c == ' ' || c == '\t') || ((c == '\r' || c == '\n') || (c == '\v' || c == '\f'))){
      current++;
      c = input[current];
   }
}
//removes whitespace in the expression. advances to the first nonwhitespace character after.
