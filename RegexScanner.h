#ifndef RegexScanner_hpp
#define RegexScanner_hpp
#include "RegexToken.hpp"
class RegexScanner {
   const char* input;
   int current;
   bool expectingOperator = false;
public:
   RegexScanner(const char* str);
	RegexScanner();
   RegexToken next();
   char escapeSequence();   //determines the character literal from an escape sequence, and makes a "Literal" token out of it. It reads and advances to the character right after the lexeme.
   inline void advance();        //advances the current pointer
   RegexToken range();           //evaluates and tokenizes an ascii range, advances to the character behind the corresponding lexeme
   void removeWhitespace();
   //removes whitespace in the expression. advances to the first nonwhitespace character after.
   RegexToken returnLiteralToken(char c);
};
#endif
