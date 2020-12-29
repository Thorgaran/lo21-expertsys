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

typedef struct FactBase {
    FactBaseElem *first;
    FactBaseElem *last;
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

#endif // MAIN_H