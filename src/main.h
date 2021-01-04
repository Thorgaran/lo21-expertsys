#ifndef MAIN_H
#define MAIN_H

typedef struct Fact {
    unsigned int id;
    char* desc;
} Fact;

typedef struct FactBaseElem {
    Fact fact;
    struct FactBaseElem *next;
    struct FactBaseElem *prev;
} FactBaseElem;

/* The FactBase datatype contains a pointer to both the first and the last fact in the list */
typedef struct FactBase {
    FactBaseElem *head;
    FactBaseElem *tail;
} FactBase;

typedef struct Rule {
    FactBase premise;
    Fact conclusion;
} Rule;

typedef struct RuleBaseElem {
    Rule rule;
    struct RuleBaseElem *next;
    struct RuleBaseElem *prev;
} RuleBaseElem;

typedef struct RuleBase {
    RuleBaseElem *first;
} RuleBase;

Rule set_conclu(Rule rule, Fact conclu);

Rule new_rule();

bool is_premise_empty(Rule rule);

bool test_fact_equality(Fact fact1, Fact fact2);

FactBase FB_new();

FactBase FB_insert_head(FactBase premise, Fact fact);

FactBase FB_insert_tail(FactBase premise, Fact fact);

FactBase FB_remove_head(FactBase premise);

FactBase FB_remove_fact(FactBase premise, Fact fact_to_remove);

#endif // MAIN_H