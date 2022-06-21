```

                          .__                         
___  ___ ____   ____      |  | _____    ____    ____  
\  \/  // __ \ /  _ \     |  | \__  \  /    \  / ___\ 
 >    <\  ___/|  | | \    |  |__/ __ \|   |  \/ /_/  >
/__/\_ \\___  >__| | /    |____(____  /___|  /\___  / 
      \/    \/     \/               \/     \//_____/  

```

# Documentation

## **1. Lexer**

xen lang comprises of simple lexer that reads the content of the console single charachter at a time. It is not ideal lexer which later needs to be updated to read the whole content of a file rather than the content of the console.

**To-do**
<li> build a lexer that reads whole content of a file


<br>

## **2. The Abstract Syntax Tree (AST)**

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

![example]("https://media.geeksforgeeks.org/wp-content/uploads/20190801154515/Types-of-Expressions.jpg")

https://www.geeksforgeeks.org/what-is-an-expression-and-what-are-the-types-of-expressions/

<br>

**B. Prototype.**

**C. A function object.**


