#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include <stdbool.h>

int main(int argc, char *argv[]){
    printf("hello world");
    getchar();

    return EXIT_SUCCESS;
}



Rule empty_rule(){
	//crée une règle vide
    Rule emp_rule;
	emp_rule.premise.first=NULL;
	emp_rule.conclusion.id=NULL;
	emp_rule.conclusion.desc=NULL;

	return emp_rule;
}


void is_premise_empty(Rule rule){
	//vérifie si la premisse d'une règle est vide
	if(rule.premise.first==NULL){
		return true;

	}

	else{
		return false;
	}

}
