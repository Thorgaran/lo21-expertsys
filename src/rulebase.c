#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "rulebase.h"

bool rule_is_premise_empty(Rule rule) {
	//vérifie si la premisse d'une règle est vide
	return FB_is_empty(rule.premise);
}

Rule rule_new(Fact conclu) {
	//crée une règle avec une prémisse vide
    Rule emp_rule;
	emp_rule.premise = FB_new();
	emp_rule.conclusion = conclu;

	return emp_rule;
}

Fact rule_get_conclu(Rule rule) {
    return rule.conclusion;
}

Rule rule_add_fact(Rule rule, Fact fact) {
    rule.premise = FB_insert_tail(rule.premise, fact);

    return rule;
}

Rule rule_remove_premise_fact(Rule rule, Fact fact) {
    rule.premise = FB_remove_fact(rule.premise, fact);

    return rule;
}

void rule_display(Rule rule) {
    printf("\"");
    FB_display(rule.premise, "\" ET \"");
    printf("\" -> \"%s\"", rule.conclusion.desc);
}

RuleBase RB_new() {
    RuleBase emp_RB = NULL;
    return emp_RB;
}

bool RB_is_empty(RuleBase rb) {
    if(rb == NULL) {
        return true;
    }
    else {
        return false;
    } 
}

RuleBase RB_insert_head(RuleBase rb, Rule rule) {

	RuleBaseElem* new_el;
	new_el = (RuleBaseElem*)malloc(sizeof(RuleBaseElem));
    new_el->rule = rule;
    new_el->prev = NULL;

	if (RB_is_empty(rb)) {
		new_el->next = NULL;
	}
    else {
        rb->prev = new_el;
		new_el->next = rb;
	}
	rb = new_el;

	return rb;
}

//this works regardless of rb->prev
RuleBase RB_remove_head(RuleBase rb) {
    if(RB_is_empty(rb)) {
        return NULL;
    }
    else {
        RuleBase new_rb = rb->next;
        
        if (rb->next != NULL) {
            new_rb->prev = rb->prev;
        }
        free(rb);
        return new_rb;
    }
}

//elem MUST be an element of rb and both must not be empty
RuleBase RB_remove_middle(RuleBase rb, RuleBaseElem *elem) {
    RuleBase new_rb = rb;
    
    if (elem->prev != NULL) {
        elem->prev->next = elem->next;
    }
    else {
        new_rb = elem->next;
    }
    RB_remove_head(elem);

    return new_rb;
}

void RB_display(RuleBase rb) {
    RuleBaseElem *cur_rule = rb;
        while (cur_rule != NULL) {
            rule_display(cur_rule->rule);
            printf("\n");
            cur_rule = cur_rule->next;
        }
}
