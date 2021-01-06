#ifndef MOTEUR_INFERENCE_H
#define MOTEUR_INFERENCE_H

#include "rulebase.h"

typedef struct MIinput {
    RuleBase rb;
    FactBase fb;
} MIinput;

FactBase moteur_inference(RuleBase rb, FactBase fb);

MIinput lire_fichier(char *nom_fichier);

#endif // MOTEUR_INFERENCE_H
