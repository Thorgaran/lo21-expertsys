#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "moteur_inference.h"

int main(int argc, char *argv[]){

	MIinput input = lire_fichier("test.txt");

	printf("Rules:\n");
	RB_display(input.rb);

	printf("\nFacts before:\n");
	FB_display(input.fb, "\n");

	input.fb = moteur_inference(input.rb, input.fb);

	printf("\n\nFacts after:\n");
	FB_display(input.fb, "\n");

    getchar();

    return EXIT_SUCCESS;
}
