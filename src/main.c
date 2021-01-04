#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "rulebase.h"

int main(int argc, char *argv[]){
    printf("hello world");

    Fact fact1, fact2, fact3;
    fact1.id = 1;
    fact2.id = 2;
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
