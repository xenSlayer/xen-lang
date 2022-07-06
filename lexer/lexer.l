%{
    /* definitions */
%}

numbers ([0-9])+

/* rules */
%%

"def"|"return"|"if"|"else"|"int" {printf("keyword ");}

([a-zA-Z_])([a-zA-Z0-9_])* {printf("identifier ");}

([0-9])+ {printf("numbers ");}
([0-9])+(.)([0-9])+ {printf("double numbers ");}

[{] {printf("open-paran ");}
[}] {printf("close-paran ");}
[(] {printf("open-bracket ");}
[)] {printf("close-bracket ");}

 "+"|"-"|"*"|"/"|"=" {printf("operator");}

(:) {printf("colon ");}
(,) {printf("separator ");}

#(.)+ {printf("comment-line ");}

%%

yywrap() {return 0;}

int main() {
    printf("Enter a string: ");
    yylex();
    return 0;
}
