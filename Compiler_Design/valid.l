%{
#include<stdio.h>
#include<string.h>
int fv=0;
%}

opd [0-9]+
opr [\+|\-|\*|/]

%%
[{opd}{opr}]*{opd} fv++;
. {fv--;}

%%

int yywrap(){
return (1);
}

int main(){
  yyin=fopen("valid_exp.txt","r");
  yylex();
  if (fv==1){
  printf("Valid expression\n");
  }
  else{
  printf("Expression is not valid\n");
  }

  return 0;
}
