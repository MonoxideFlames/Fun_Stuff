//
//  RegexToken.hpp
//  CPPProject
//
//  Created by Adith Talupuru on 11/21/22.
//

#ifndef RegexToken_hpp
#define RegexToken_hpp
class RegexToken {
public:
	enum tokenTypes {
		LITERAL,    ASCIIRANGE,  OPENPAREN,
		CLOSEPAREN, KCLOSURE,    CLOSURE,
		OPTIONAL,   UNION,       CONCATENATE,
		END,        UNRECOGNIZED,LEFT,
		RIGHT, DELIMITER, OPERATOR, ERROR
	};
	unsigned char type;
	char id;
	union {
		struct {
			unsigned char min;      //minimum ascii value
			unsigned char range;    //number of characters above that
		};
		struct {
			unsigned char precedence; //precedence of operator
			unsigned char associativity;//associativity
		};
	};
	RegexToken(char type, char id, unsigned char min = 0, unsigned char max = 0);
	RegexToken();
};
void print(RegexToken tok);
#endif /* RegexToken_hpp */
