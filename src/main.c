#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "moteur_inference.h"

int main(int argc, char *argv[]){

    Fact fact1 = fact_new("C'est un avion");
	Fact fact2 = fact_new("Ca a des ailes");
	Fact fact3 = fact_new("Ca vole!!!");
	Fact fact4 = fact_new("C'est une souris");
	Fact fact5 = fact_new("C'est chauve");
	Fact fact6 = fact_new("C'est une chauve souris");
	Fact fact7 = fact_new("C'est un Airbus A320");

	Rule rule1 = rule_new(fact3);
	rule1 = rule_add_fact(rule1, fact1);
	rule1 = rule_add_fact(rule1, fact2);

	Rule rule2 = rule_new(fact6);
	rule2 = rule_add_fact(rule2, fact4);
	rule2 = rule_add_fact(rule2, fact5);
	rule2 = rule_add_fact(rule2, fact3);

	Rule rule3 = rule_new(fact1);
	rule3 = rule_add_fact(rule3, fact7);

	RuleBase rb = RB_new();
	rb = RB_insert_head(rb, rule1);
	rb = RB_insert_head(rb, rule3);
	rb = RB_insert_head(rb, rule2);

	FactBase fb = FB_new();
	fb = FB_insert_tail(fb, fact1);
	fb = FB_insert_tail(fb, fact2);
	fb = FB_insert_tail(fb, fact4);
	fb = FB_insert_tail(fb, fact5);

	printf("Rules:\n");
	RB_display(rb);

	printf("\nFacts before:\n");
	FB_display(fb, "\n");

	fb = moteur_inference(rb, fb);

	printf("\n\nFacts after:\n");
	FB_display(fb, "\n");

    getchar();

    return EXIT_SUCCESS;
}
