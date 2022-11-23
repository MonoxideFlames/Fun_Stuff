*\*This parses a Regex, It doesnt have any extra bells and whistles, such as curly brackets or min max counts. It only works for regexes specifying regular languages\**

The parser emits tokens in the order of a postfix expression. This can easily be converted to an AST by means of a stack.
