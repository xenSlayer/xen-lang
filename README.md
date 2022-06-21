```

                          .__                         
___  ___ ____   ____      |  | _____    ____    ____  
\  \/  // __ \ /  _ \     |  | \__  \  /    \  / ___\ 
 >    <\  ___/|  | | \    |  |__/ __ \|   |  \/ /_/  >
/__/\_ \\___  >__| | /    |____(____  /___|  /\___  / 
      \/    \/     \/               \/     \//_____/  

```

# **Documentation**
xen lang docs

<br>

# **Lexer**

xen lang comprises of simple lexer that reads the content of the console single charachter at a time. It is not ideal lexer which later needs to be updated to read the whole content of a file rather than the content of the console.

**To-do**
<li> build a lexer that reads whole content of a file


<br>

# **The Abstract Syntax Tree (AST)**

The AST for a program captures its behavior in such a way that it is easy for later stages of the compiler (e.g. code generation) to interpret. We basically want one object for each construct in the language, and the AST should closely model the language. In xen lang, we have

https://en.wikipedia.org/wiki/Abstract_syntax_tree

<br>

**A. Expressions.**

An expression is a combination of operators, constants and variables. An expression may consist of one or more operands, and zero or more operators to produce a value.

Example:

```
a+b
c
s-1/7*f
a = 20
(a + b)
```

https://www.geeksforgeeks.org/what-is-an-expression-and-what-are-the-types-of-expressions/

<br>

**B. Prototype.**

.....

<br>

**C. A function object.**

<br>


<br>

## **Expression AST - ExprAST**
AST node representation for the expression types. Consists a base class **ExprAST**. In xen lang, functions are typed with just a count of their arguments. Since all values are double precision floating point, the type of each argument doesn’t need to be stored anywhere. In a more aggressive and realistic language, the “ExprAST” class would probably have a type field.

```c++
// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
  virtual ~ExprAST() {}
};
```

<br>

**A. NumberExprAST**

NumberExprAST - Expression class for numeric literals like "1.0". **Stores the number value in its node.**

<br>

**B. VariableExprAST**

VariableExprAST - Expression class for referencing a variable, like "a". **Stores variable name**

<br>

**C. BinaryExprAST**

BinaryExprAST - Expression class for a binary operator. examples:

```txt
a + b
a = 20
20 - 30
a + b * c
```

**Stores the opcode (e.g. +), LHS, RHS values**

<br>

**D. CallExprAST**

CallExprAST - Expression class for function calls.
example:

```text
function(arg1, arg2) # function calls
```

**Stores callee '()' and arguments list passed**

<br>

**E. PrototypeAST**

PrototypeAST - This class represents the "prototype" for a function, which captures its name, and its argument names (thus implicitly the number of arguments the function takes)

```text
def function(arg1, arg2):
```

<br>

**F. FunctionAST**

FunctionAST - This class represents a function definition itself. It contains the 'PrototypeAST' and the body of the function.

```text
def function(arg1, arg2):            
      ... # body
```

<br>

# **Parser**

Now that we have an AST to build, we need to define the parser code to build it. The idea here is that we want to parse something like “x+y” (which is returned as three tokens by the lexer) into an AST that could be generated with calls like this:

```c++
auto LHS = std::make_unique<VariableExprAST>("x");
auto RHS = std::make_unique<VariableExprAST>("y");
auto Result = std::make_unique<BinaryExprAST>('+', std::move(LHS),
                                              std::move(RHS));
```

<br>

## **Basic Expression Parsing**

We start with numeric literals, because they are the simplest to process. For each production in our grammar, we’ll define a function which parses that production. For numeric literals, we have:

```c++
static std::unique_ptr<ExprAST> ParseNumberExpr() {
  auto Result = std::make_unique<NumberExprAST>(NumVal);
  getNextToken(); // consume the number
  return std::move(Result);
}
```
