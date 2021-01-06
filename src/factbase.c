#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "factbase.h"

Fact fact_new(char* desc) {
    //choix d'utiliser une variable statique pour la simplicité du code, ce numéro n'est utilisé que pour des comparaisons
    static unsigned int ID = 0;
    Fact new_fact;

    new_fact.id = ID;
    ID++;
    strcpy(new_fact.desc, desc);

    return new_fact;
}

char* fact_get_desc(Fact fact) {
    char* return_desc = "";
    strcpy(return_desc, fact.desc);
    return return_desc;
}

Fact fact_get_from_desc(FactBase fb, char* desc) {
    Fact searched_fact;

    if (FB_is_empty(fb)) {
        searched_fact = fact_new(desc);
    }
    else {
        FactBaseElem *cur_fact = fb.head;
        bool found_fact = false;

        while (cur_fact != NULL && found_fact == false) {
            //si les chaines sont égales (et donc on a trouvé le fait cherché)
            if (strcmp(cur_fact->fact.desc, desc) == 0) {
                found_fact = true;
                searched_fact = cur_fact->fact;
            }
            cur_fact = cur_fact->next;
        }
    }

    return searched_fact;
}

bool fact_test_eq(Fact fact1, Fact fact2) {
    if (fact1.id == fact2.id) {
        return true;
    }
    else {
        return false;
    }
}

FactBase FB_new() {
	//crée une base de faits vide
	FactBase emp_fb;
	emp_fb.head = NULL;
	emp_fb.tail = NULL;

	return emp_fb;
}

bool FB_is_empty(FactBase fb) {
    if (fb.head == NULL) {
        return true;
    }
    else {
        return false;
    }
}

FactBase FB_insert_head(FactBase fb, Fact fact) {
	FactBaseElem* new_el;
	new_el = (FactBaseElem*)malloc(sizeof(FactBaseElem));
    new_el->fact = fact;
	new_el->next = fb.head;
	new_el->prev = NULL;

	if (FB_is_empty(fb)) {
		fb.tail = new_el;
	}
    else {
		fb.head->prev = new_el;
	}
	fb.head = new_el;

	return fb;
}

FactBase FB_insert_tail(FactBase fb, Fact fact) {
	FactBaseElem* new_el;
	new_el = (FactBaseElem*)malloc(sizeof(FactBaseElem));
	new_el->fact = fact;
	new_el->next = NULL;
	new_el->prev = fb.tail;

	if(FB_is_empty(fb)) {
		fb.head = new_el;
	}
	else {
		fb.tail->next = new_el;
	}
    fb.tail = new_el;

	return fb;
}

FactBase FB_remove_head(FactBase fb) {
	FactBase new_fb;
	if (FB_is_empty(fb)) {
		new_fb = FB_new();
	}
	else {
		new_fb.head = fb.head->next;
		if (!FB_is_empty(new_fb)) {
			new_fb.head->prev = NULL;
            new_fb.tail = fb.tail;
		}
        else {
            new_fb.tail = NULL;
        }
		free(fb.head);
	}
	return new_fb;
}

FactBase FB_remove_fact(FactBase fb, Fact fact_to_remove) {
    FactBase new_fb;
    if (FB_is_empty(fb)) {
        new_fb = FB_new();
    }
    else {
        if (fact_test_eq(fb.head->fact, fact_to_remove)) {
            new_fb = FB_remove_fact(FB_remove_head(fb), fact_to_remove);
        }
        else {
            FactBase smaller_fb = fb;
            smaller_fb.head = smaller_fb.head->next;
            if (FB_is_empty(smaller_fb)) {
                smaller_fb.tail = NULL;
            }
            new_fb = FB_insert_head(FB_remove_fact(smaller_fb, fact_to_remove), fb.head->fact);
        }
    }
    return new_fb;
}

void FB_display(FactBase fb, char* sep) {
    if (FB_is_empty(fb)) {
        printf("-");
    }
    else {
        FactBaseElem *cur_fact = fb.head;
        while (cur_fact->next != NULL) {
            printf("%s%s", cur_fact->fact.desc, sep);
            cur_fact = cur_fact->next;
        }
        printf("%s", cur_fact->fact.desc);
    }
}
