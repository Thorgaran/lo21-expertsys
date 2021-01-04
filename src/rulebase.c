#include <stdlib.h>
#include <stdbool.h>
#include "rulebase.h"

bool is_premise_empty(Rule rule) {
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
