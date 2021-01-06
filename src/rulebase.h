#ifndef RULEBASE_H
#define RULEBASE_H

#include "factbase.h"

typedef struct Rule {
    FactBase premise;
    Fact conclusion;
} Rule;

typedef struct RuleBaseElem {
    Rule rule;
    struct RuleBaseElem *next;
    struct RuleBaseElem *prev;
} RuleBaseElem;

typedef RuleBaseElem* RuleBase;

bool rule_is_premise_empty(Rule rule);

Rule rule_new();

Fact rule_get_conclu(Rule rule);

Rule rule_add_fact(Rule rule, Fact fact);

Rule rule_remove_premise_fact(Rule rule, Fact fact);

void rule_display(Rule rule);

RuleBase RB_new();

bool RB_is_empty(RuleBase rb);

RuleBase RB_insert_head(RuleBase rb, Rule rule);

RuleBase RB_remove_head(RuleBase rb);

RuleBase RB_remove_middle(RuleBase rb, RuleBaseElem *elem);

void RB_display(RuleBase rb);

#endif // RULEBASE_H
