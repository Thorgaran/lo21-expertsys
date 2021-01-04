#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include <stdbool.h>

int main(int argc, char *argv[]){
    printf("hello world");

    Fact fact1, fact2, fact3;
    fact1.id = 1;
    fact2.id = 1;
    fact3.id = 4;

    FactBase test_base;
    test_base.head = NULL;
    test_base.tail = NULL;

    test_base = FB_insert_tail(test_base, fact1);
    test_base = FB_insert_tail(test_base, fact2);
    test_base = FB_insert_tail(test_base, fact3);

    test_base = FB_remove_fact(test_base, fact2);

    getchar();

    return EXIT_SUCCESS;
}

Rule set_conclu(Rule rule, Fact conclu) {
	rule.conclusion = conclu;

	return rule;
}

Rule new_rule() {
	//crée une règle vide
    Rule emp_rule;
	emp_rule.premise = FB_new();
	emp_rule.conclusion.id = 0;
	emp_rule.conclusion.desc = NULL;

	return emp_rule;
}


bool is_premise_empty(Rule rule) {
	//vérifie si la premisse d'une règle est vide
	if (rule.premise.head == NULL) {
		return true;
	}
	else {
		return false;
	}
}

bool test_fact_equality(Fact fact1, Fact fact2) {
    if (fact1.id == fact2.id) {
        return true;
    }
    else {
        return false;
    }
}

FactBase FB_new() {
	//crée une base de faits vide
	FactBase emp_fb;
	emp_fb.head = NULL;
	emp_fb.tail = NULL;

	return emp_fb;
}

FactBase FB_insert_head(FactBase premise, Fact fact) {
	FactBaseElem* new_el;
	new_el = (FactBaseElem*)malloc(sizeof(FactBaseElem));
    new_el->fact = fact;
	new_el->next = premise.head;
	new_el->prev = NULL;

	if(premise.head == NULL) { // REMPLACER PAR ISEMPTY()
		premise.tail = new_el;
	}
    else {
		premise.head->prev = new_el;
	}
	premise.head = new_el;

	return premise;
}

FactBase FB_insert_tail(FactBase premise, Fact fact) {
	FactBaseElem* new_el;
	new_el = (FactBaseElem*)malloc(sizeof(FactBaseElem));
	new_el->fact = fact;
	new_el->next = NULL;
	new_el->prev = premise.tail;

	if(premise.head == NULL) { // REMPLACER PAR ISEMPTY()
		premise.head = new_el;
	}
	else {
		premise.tail->next = new_el;
	}
    premise.tail = new_el;

	return premise;
}

FactBase FB_remove_head(FactBase premise) {
	FactBase new_premise;
	if (premise.head == NULL) { // REMPLACER PAR ISEMPTY()
		new_premise = FB_new();
	}
	else {
		new_premise.head = premise.head->next;
		if (new_premise.head != NULL) { // REMPLACER PAR ISEMPTY() (use brain pls don't invert the thing)
			new_premise.head->prev = NULL;
		}
        else {
            new_premise.tail = NULL;
        }
		free(premise.head);
	}
	return new_premise;
}

FactBase FB_remove_fact(FactBase premise, Fact fact_to_remove) {
    FactBase new_premise;
    if (premise.head == NULL) { // REMPLACER PAR ISEMPTY()
        new_premise = FB_new();
    }
    else {
        if (test_fact_equality(premise.head->fact, fact_to_remove)) {
            new_premise = FB_remove_fact(FB_remove_head(premise), fact_to_remove);
        }
        else {
            FactBase smaller_premise = premise;
            smaller_premise.head = smaller_premise.head->next;
            new_premise = FB_insert_head(FB_remove_fact(smaller_premise, fact_to_remove), premise.head->fact);
        }
    }
    return new_premise;
}
