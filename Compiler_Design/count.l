%{
#include<stdio.h>
#include<string.h>
int lines_count=0,words_count=0,capital=0,small=0,num=0,digit=0,total=0,relative_op=0,operator=0,delimiters=0;
%}

%%
\n lines_count++;
[\t|' '] words_count++;
[A-Z] capital++;
[a-z] small++;
[0-9] digit++;
[0-9]+[0-9]* num++;
>|<|<=|>=|==|!= relative_op++;
\++|\--|\*|\/ operator++;
\;|\,|\'|\"|\`|\~ delimiters++;
. total++;

%%

int yywrap(){
return (1);
}

int main(void){
  yyin=fopen("example.txt","r");
  yylex();
  printf("\nMy example file had: \n");
  printf("%d Digits\n",digit);
  printf("%d numbers\n",num+digit);
  printf("%d lines\n",lines_count);
  printf("%d words\n",words_count);
  printf("%d Capital Letters\n",capital);
  printf("%d Small Letters\n",small);
  printf("%d Relative operator\n",relative_op);
  printf("%d Operator\n",operator+relative_op);
  printf("%d Delimiters\n",delimiters);
  //printf("%d total chars \n",total);


  return 0;
}
