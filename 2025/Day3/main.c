#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* First Star */
long long string_to_int_array(const char *ligne, long long *tab) {
    long long cmpt = 0;
    
    for (long long i = 0 ; ligne[i] != '\0'; i++) {
        if (isdigit(ligne[i])) {
            tab[cmpt] = ligne[i] - '0';
            cmpt++;
        }
    }
    
    return cmpt;
}

int max(long long *tab, long long taille) {
	int max = 10 * tab[0] + tab[1];
	
	for (long long i = 0 ; i < taille - 1 ; i++) {
		for (long long j = i + 1 ; j < taille ; j++) {
			int nombre = 10 * tab[i] + tab[j];
			
			if (nombre > max) {
				max = nombre ;
			}
		}
	}
	
	return max;
}

/* Second Star */

int main(int argc, char** argv) {
	
	FILE* f;
	long long somme = 0;
	
	if (argc != 2) {
		perror("Nombre d'argument incorrect\n");
		exit(1);
	} else {
		f = fopen(argv[1], "r");
		if (f == NULL) {
			perror("Erreur lors de l'ouverture du fichier en mode lecture\n");
			exit(2);
		}
		
		char ligne[10000];
		long long tab[10000];
		
		while(fscanf(f, "%s", ligne) == 1) {
			/* ============================================ FIRST STAR ============================================= */ 
			long long taille = string_to_int_array(ligne, tab);
			
			int res = max(tab, taille);
			printf("Max de cette ligne : %d\n", res);
			
			somme += res;
			/* ============================================ SECOND STAR ============================================ */
			
		}
		
		fclose(f);
	}
	
	printf("Somme totale : %lld\n", somme);
	
	return 0;
}
