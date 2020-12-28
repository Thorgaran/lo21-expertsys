#ifndef MAIN_H
#define MAIN_H

typedef struct Fact {
    unsigned int id;
    char* desc;
} Fact;

typedef struct FactBaseElem {
    Fact fact;
    struct FactBaseElem *prev;
    struct FactBaseElem *next;
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
} RuleBaseElem;

typedef struct RuleBase {
    RuleBaseElem *first;
} RuleBase;

bool test_fact_equality(Fact fact1, Fact fact2);

FactBase FB_insert_head(FactBase premise, Fact fact);

FactBase FB_insert_tail(FactBase premise, Fact fact);

FactBase FB_remove_head(FactBase premise);

FactBase FB_remove_fact(FactBase premise, Fact fact_to_remove);

#endif // MAIN_H