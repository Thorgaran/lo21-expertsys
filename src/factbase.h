#ifndef FACTBASE_H
#define FACTBASE_H

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

Fact fact_new(char* desc);

char* fact_get_desc(Fact fact);

bool fact_test_eq(Fact fact1, Fact fact2);

FactBase FB_new();

bool FB_is_empty(FactBase fb);

FactBase FB_insert_head(FactBase fb, Fact fact);

FactBase FB_insert_tail(FactBase fb, Fact fact);

FactBase FB_remove_head(FactBase fb);

FactBase FB_remove_fact(FactBase fb, Fact fact_to_remove);

#endif // FACTBASE_H
