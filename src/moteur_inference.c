#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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

MIinput lire_fichier(char *nom_fichier) {
    FILE *input_file;
    char *fgetsReturnPtr = NULL;
    char line[256], premise_str[256], conlu_str[256];
    char descs[64][2][256];
    Fact new_fact;
    Rule new_rule;
    FactBase all_facts = FB_new();
    FactBase true_facts = FB_new();
    RuleBase rb = RB_new();
    int fact_count = 0;
    bool fact_declaration = true;

    input_file = fopen(nom_fichier, "r"); //ouvrir le fichier "nom_fichier" en lecture seule

    if (input_file == NULL) { //si l'ouverture du fichier a échoué
        printf("Le fichier \"%s\" est introuvable ou inaccessible.", nom_fichier);
        exit(EXIT_FAILURE);
    }
    else {
        do {
            fgetsReturnPtr = fgets(line, 257, input_file);  //Essaie de lire une ligne du fichier
            if (fgetsReturnPtr != NULL) {                   //Si la fonction a réussi à lire une ligne
                //If the file ptr is still reading the fact declaration part
                if (fact_declaration == true) {
                    //Parser le fait
                    if (sscanf(line, "%[^;];%[^\r\n]", descs[fact_count][0], descs[fact_count][1]) != 2) {
                        if (strcmp(line, "\r\n") != 0) {
                            printf("Impossible de parser ce fait:\n\"%s\"", line);
                            exit(EXIT_FAILURE);
                        }
                        else {
                            fact_declaration = false;
                            fgetsReturnPtr = fgets(line, 257, input_file);  //Essaie de lire une ligne du fichier

                            if (fgetsReturnPtr != NULL) {
                                char *ptr = strtok(line, ";");
                                while(ptr != NULL){
                                    if (strcmp(ptr, "\r\n") != 0) {
                                        new_fact = fact_get_from_desc(all_facts, ptr);
                                        for (int i = 0; i < fact_count; i++) {
                                            if (strcmp(descs[i][0], ptr) == 0) {
                                                strcpy(new_fact.desc, descs[i][1]);
                                            }
                                        }
                                        true_facts = FB_insert_tail(true_facts, new_fact);
                                    }
                                    ptr = strtok(NULL, ";");
                                }
                            }
                        }
                    }
                    else {
                        all_facts = FB_insert_tail(all_facts, fact_new(descs[fact_count][0]));
                        fact_count++;
                    }
                }
                //The file ptr is at the rule declaration part
                else {
                    //Parser la règle
                    if (sscanf(line, "%[^;];%[^\r\n]", premise_str, conlu_str) != 2) {
                        printf("Impossible de parser cette règle:\n\"%s\"", line);
                        exit(EXIT_FAILURE);
                    }

                    new_fact = fact_get_from_desc(all_facts, conlu_str);
                    for (int i = 0; i < fact_count; i++) {
                        if (strcmp(descs[i][0], conlu_str) == 0) {
                            strcpy(new_fact.desc, descs[i][1]);
                        }
                    }
                    new_rule = rule_new(new_fact);
                    char *ptr = strtok(premise_str, ",");
                    while(ptr != NULL){
                        new_fact = fact_get_from_desc(all_facts, ptr);
                        for (int i = 0; i < fact_count; i++) {
                            if (strcmp(descs[i][0], ptr) == 0) {
                                strcpy(new_fact.desc, descs[i][1]);
                            }
                        }
                        new_rule = rule_add_fact(new_rule, new_fact);
                        ptr = strtok(NULL, ",");
                    }

                    rb = RB_insert_head(rb, new_rule);
                }
            }
        } while (fgetsReturnPtr != NULL);
        //tant que la fin du fichier n'est pas atteinte

        MIinput input;
        input.fb = true_facts;
        input.rb = rb;

        return input;
    }
}
