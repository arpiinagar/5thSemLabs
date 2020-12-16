
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lxa.c"

void declarations();
void assign_stat();
void assign_stat_prime();
void data_type();
void identifier_list();
void identifier_list_prime();
void identifier_list_prime_prime();
void statement();
void statement_list();
void expn();
void eprime();
void simple_exp();
void seprime();
void term();
void tprime();
void factor();
void relop();
void relop_prime();
void addop();
void mulop();

struct token curr;

FILE *fa;
void untoken(){
      int len;
      if(curr.name[0]=='i'&&curr.name[1]=='d'&&curr.name[2]==' ')
           len=strlen(curr.name)-3;
      else len=strlen(curr.name);

      fseek(fa,-1*len,SEEK_CUR);
}

void Program(){
		curr=getnextToken(fa);
		if(strcmp(curr.name,"main")==0){
             curr=getnextToken(fa);
             if(strcmp(curr.name,"(")==0){
                    curr=getnextToken(fa);
                    if(strcmp(curr.name,")")==0){
                           curr=getnextToken(fa);
                           if(strcmp(curr.name,"{")==0){
                                 declarations();
                                 statement_list();
                                  curr=getnextToken(fa);
                                  if(strcmp(curr.name,"}")==0){
                                          return; 
                                  }
                                  else{
                                  	printf("error: missing '}' at line %d\n",curr.row);
                                    exit(1);
                                  }
                           }
                           else{
                           		printf("error: missing '{' at line %d\n",curr.row);
                              exit(1);
                           }
                    }
                    else{
                        printf("error: missing ')' at line %d\n",curr.row);
                        exit(1);
                    }
             }
             else{
             	printf("error: missing '(' at line %d\n",curr.row);
              exit(1);
             }
		}
		else{
			printf("missing main in line %d\n",curr.row);
      exit(1);
		}	

}

void declarations(){
   
	curr=getnextToken(fa);
	if(strcmp(curr.name,"int")==0||strcmp(curr.name,"char")==0){
			identifier_list();
	        curr=getnextToken(fa);
	        if(strcmp(curr.name,";")==0){
		      declarations();
	        }
	        else{
	        	printf("expected ';' at line %d\n",curr.row );
            exit(1);
	        }
	}
    else{
    	untoken();
    	
    }
}

void identifier_list(){
   
     curr=getnextToken(fa);
     if(curr.name[0]=='i'&& curr.name[1]=='d'&& curr.name[2]==' '){
           identifier_list_prime();
     }
     else{
     	printf("error : expected identifier ar line %d",curr.row);
      exit(1);
     }

}

void identifier_list_prime(){
     
     curr=getnextToken(fa);
     if(strcmp(curr.name,",")==0){
           identifier_list();
     }
     else if(strcmp(curr.name,"[")==0){
           identifier_list_prime_prime();
     }
     else{
       untoken();
     }

}

void identifier_list_prime_prime(){
     curr=getnextToken(fa);
     if(strcmp(curr.name,"num")==0){
          curr=getnextToken(fa);
          if(strcmp(curr.name,"]")==0){
              curr=getnextToken(fa);
              if(strcmp(curr.name,",")==0)
                    identifier_list();
              else{
                 untoken();
              }    
          }
          else{
            printf("error: expected ']' in line %d\n",curr.row);
            exit(1);
          }
     }
}

void statement_list(){
  curr=getnextToken(fa);
  if(curr.name[0]=='i'&&curr.name[1]=='d'&&curr.name[2]==' '){
        untoken();
        statement();
        statement_list();
     }
    else
      untoken();
}

void statement(){
  assign_stat();
  curr=getnextToken(fa);
  if(strcmp(curr.name,";")!=0){
    printf("error expecting ';' row %d col %d\n",curr.row,curr.col);
    exit(1);
  }
}


void assign_stat(){
     
     curr=getnextToken(fa);
     if(curr.name[0]=='i'&&curr.name[1]=='d'&&curr.name[2]==' '){
        curr=getnextToken(fa);
        if(strcmp(curr.name,"=")==0)
     	   expn();
     	else{
     		printf("error : missing '=' in line %d\n",curr.row);
        exit(1);
      }
     }
     else{
     	printf("error : missing identifier in line %d\n",curr.row);
      exit(1);
     }
}

void expn(){
   simple_exp();
   eprime();
}

void eprime(){
  curr=getnextToken(fa);
  if(strcmp(curr.name,"==")==0||strcmp(curr.name,"!=")==0||strcmp(curr.name,"<=")==0||strcmp(curr.name,">=")==0||strcmp(curr.name,"<")==0||strcmp(curr.name,">")==0){
    untoken();
    relop();
    simple_exp();
  }
  else
    untoken();
}

void simple_exp(){
  term();
  seprime();
}

void seprime(){
  curr=getnextToken(fa);
  if(strcmp(curr.name,"+")==0||strcmp(curr.name,"-")==0){
     untoken();
     addop();
     term();
     seprime();
  }
  else
    untoken(); 

}

void term(){
  factor();
  tprime();
}


void tprime(){
  curr=getnextToken(fa);
  if(strcmp(curr.name,"*")==0||strcmp(curr.name,"/")==0||strcmp(curr.name,"%")==0){
     untoken();
     mulop();
     factor();
     tprime();
  }
  else
    untoken(); 
}

void factor(){
  curr=getnextToken(fa);
   if((curr.name[0]=='i'&&curr.name[1]=='d'&&curr.name[2]==' ')||strcmp(curr.name,"num")==0){
       return;
   }
   else{
    printf("error : expected id or num in line %d\n",curr.row);
    exit(1);
  }
}

void relop(){
  curr=getnextToken(fa);
  if(strcmp(curr.name,"==")==0||strcmp(curr.name,"!=")==0||strcmp(curr.name,"<=")==0||strcmp(curr.name,">=")==0||strcmp(curr.name,"<")==0||strcmp(curr.name,">")==0){
    return;
  }
  else{
    printf("error: expected relational operator in line %d \n",curr.row);
    exit(1);
  }
}

void addop(){
  curr=getnextToken(fa);
  if(strcmp(curr.name,"+")==0||strcmp(curr.name,"-")==0){
    return;
  }
  else{
     printf("error: expected + or - operator in line %d \n",curr.row);
     exit(1);
  }
}

void mulop(){
  curr=getnextToken(fa);
  if(strcmp(curr.name,"*")==0||strcmp(curr.name,"/")==0||strcmp(curr.name,"%")==0){
    return;
  }
  else{
     printf("error: expected * or / or %% operator in line %d \n",curr.row);
     exit(1);
  }
}


int main(int argc, char const *argv[])
{
	fa=fopen("input.txt","r");
	if(fa==NULL){
		perror("fopen");
		exit(1);
	}
	  Program();
    curr=getnextToken(fa);
    if(strcmp(curr.name,"end")==0)
    printf("Successful Parsing.\n");

	return 0;
}
