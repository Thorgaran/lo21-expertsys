#include <stdlib.h>
#include <stdbool.h>
#include "moteur_inference.h"

FactBase moteur_inference(RuleBase rb, FactBase fb) {
    FactBaseElem *cur_fact = fb.head;
    
    while (cur_fact != NULL) {
        RuleBaseElem *cur_rule = rb;

        while (cur_rule != NULL) {
            RuleBaseElem *next_rule = cur_rule->next;

            if (fact_test_eq(cur_rule->rule.conclusion, cur_fact->fact)) {
                rb = RB_remove_middle(rb, cur_rule);
            }
            else {
                cur_rule->rule = rule_remove_premise_fact(cur_rule->rule, cur_fact->fact);

                if (rule_is_premise_empty(cur_rule->rule)) {
                    fb = FB_insert_tail(fb, rule_get_conclu(cur_rule->rule));
                    
                    rb = RB_remove_middle(rb, cur_rule);
                }
            }
            cur_rule = next_rule;
        }
        cur_fact = cur_fact->next;
    }

    return fb;
}
