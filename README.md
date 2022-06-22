# **XEN LANG DOCS**

```txt

                          .__                         
___  ___ ____   ____      |  | _____    ____    ____  
\  \/  // __ \ /  _ \     |  | \__  \  /    \  / ___\ 
 >    <\  ___/|  | | \    |  |__/ __ \|   |  \/ /_/  >
/__/\_ \\___  >__| | /    |____(____  /___|  /\___  / 
      \/    \/     \/               \/     \//_____/  

```

&nbsp;

## **1.1 Lexer**

xen lang comprises of simple lexer that reads the content of the console single charachter at a time. It is not ideal lexer which later needs to be updated to read the whole content of a file rather than the content of the console.

TODO

❓ build a lexer that reads whole content of a file

&nbsp;

## **1.2 The Abstract Syntax Tree (AST)**

The AST for a program captures its behavior in such a way that it is easy for later stages of the compiler (e.g. code generation) to interpret. We basically want one object for each construct in the language, and the AST should closely model the language. In xen lang, we have

<https://en.wikipedia.org/wiki/Abstract_syntax_tree/>

&nbsp;

**A. Expressions.**

An expression is a combination of operators, constants and variables. An expression may consist of one or more operands, and zero or more operators to produce a value.

Example:

```txt
a+b
c
s-1/7*f
a = 20
(a + b)
```

<https://www.geeksforgeeks.org/what-is-an-expression-and-what-are-the-types-of-expressions/>

&nbsp;

**B. Prototype.**

.....

&nbsp;

**C. A function object.**

&nbsp;
&nbsp;

## **Expression AST - ExprAST**

AST node representation for the expression types. Consists a base class **ExprAST**. In xen lang, functions are typed with just a count of their arguments. Since all values are double precision floating point, the type of each argument doesn’t need to be stored anywhere. In a more aggressive and realistic language, the “ExprAST” class would probably have a type field.

```c++
// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
  virtual ~ExprAST() {}
};
```

&nbsp;

### **A. NumberExprAST**

NumberExprAST - Expression class for numeric literals like "1.0".

- **Stores the number value in its node.**

&nbsp;

### **B. VariableExprAST**

VariableExprAST - Expression class for referencing a variable, like "a".

- **Stores variable name**

&nbsp;

### **C. BinaryExprAST**

BinaryExprAST - Expression class for a binary operator. examples:

```txt
a + b
a = 20
20 - 30
a + b * c
```

- **Stores the opcode (e.g. +), LHS, RHS values**

&nbsp;

### **D. CallExprAST**

CallExprAST - Expression class for function calls.
example:

```text
function(arg1, arg2) # function calls
```

- **Stores callee '()' and arguments list passed**

&nbsp;

### **E. PrototypeAST**

PrototypeAST - This class represents the "prototype" for a function, which captures its name, and its argument names (thus implicitly the number of arguments the function takes)

```text
def function(arg1, arg2):
```

&nbsp;

### **F. FunctionAST**

FunctionAST - This class represents a function definition itself. It contains the 'PrototypeAST' and the body of the function.

```text
def function(arg1, arg2):            
      ... # body
```

&nbsp;

## **1.3 Parser**

Now that we have an AST to build, we need to define the parser code to build it. The idea here is that we want to parse something like “x+y” (which is returned as three tokens by the lexer) into an AST that could be generated with calls like this:

```c++
auto LHS = std::make_unique<VariableExprAST>("x");
auto RHS = std::make_unique<VariableExprAST>("y");
auto Result = std::make_unique<BinaryExprAST>('+', std::move(LHS),
                                              std::move(RHS));
```

&nbsp;

## **Basic Expression Parsing**

We start with numeric literals, because they are the simplest to process. For each production in our grammar, we’ll define a function which parses that production. For numeric literals, we have:

```c++
static std::unique_ptr<ExprAST> ParseNumberExpr() {
  auto Result = std::make_unique<NumberExprAST>(NumVal);
  getNextToken(); // consume the number
  return std::move(Result);
}
```

There are some interesting aspects to this. The most important one is that this routine eats all of the tokens that correspond to the production and returns the lexer buffer with the next token (which is not part of the grammar production) ready to go. This is a fairly standard way to go for recursive descent parsers. For a better example, the parenthesis operator is defined like this:

```c++
/// parenexpr ::= '(' expression ')'
static std::unique_ptr<ExprAST> ParseParenExpr() {
  getNextToken(); // eat (.
  auto V = ParseExpression();
  if (!V)
    return nullptr;

  if (CurTok != ')')
    return LogError("expected ')'");
  getNextToken(); // eat ).
  return V;
}
```

&nbsp;

## **Binary Expression Parsing - Operator Precedence Parsing**

Binary expressions are significantly harder to parse because they are often ambiguous. For example, when given the string “x+y*z”, the parser can choose to parse it as either “(x+y)*z” or “x+(y*z)”. With common definitions from mathematics, we expect the later parse, because “*” (multiplication) has higher precedence than “+” (addition).

There are many ways to handle this, but an elegant and efficient way is to use Operator-Precedence Parsing. This parsing technique uses the precedence of binary operators to guide recursion. To start with, we need a table of precedences:

```c++
/// BinopPrecedence - This holds the precedence for each binary operator that is
/// defined.
static std::map<char, int> BinopPrecedence;

/// GetTokPrecedence - Get the precedence of the pending binary operator token.
static int GetTokPrecedence() {
  if (!isascii(CurTok))
    return -1;

  // Make sure it's a declared binop.
  int TokPrec = BinopPrecedence[CurTok];
  if (TokPrec <= 0) return -1;
  return TokPrec;
}

int main() {
  // Install standard binary operators.
  // 1 is lowest precedence.
  BinopPrecedence['<'] = 10;
  BinopPrecedence['+'] = 20;
  BinopPrecedence['-'] = 20;
  BinopPrecedence['*'] = 40;  // highest.
  ...
}
```

&nbsp;

The basic idea of operator precedence parsing is to break down an expression with potentially ambiguous binary operators into pieces. Consider, for example, the expression 

```text
a+b+(c+d)*e*f+g
```

Operator precedence parsing considers this as a stream of primary expressions separated by `binary operators`. As such, `it will first parse the leading primary expression “a”`, then it will see the pairs,

```text
[+, b] [+, (c+d)] [*, e] [*, f] and [+, g]
```

Note that because parentheses are primary expressions, the binary expression parser doesn’t need to worry about nested subexpressions like (c+d) at all.

To start, an expression is a primary expression potentially followed by a sequence of [binop,primaryexpr] pairs:

&nbsp;

```c++
/// expression
///   ::= primary binoprhs
///
static std::unique_ptr<ExprAST> ParseExpression() {
  auto LHS = ParsePrimary();
  if (!LHS)
    return nullptr;

  return ParseBinOpRHS(0, std::move(LHS));
}
```
