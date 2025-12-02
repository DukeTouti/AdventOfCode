#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* First Star */
int est_invalide(long long n) {
	char string[1000];
	
	sprintf(string, "%lld", n);
	
	int taille = strlen(string);
	
	if (string[0] == 0) {
		return 1;
	}
	
	if ((taille % 2) != 0) {
		return 0 ;
	}
	
	int moitie = taille / 2;
	
	for (long long i = 0 ; i < moitie ; i++) {
		if (string[i] != string [i + moitie]) {
			return 0 ;
		}
	}
	
	return 1;
}


/* Second Star */
int est_invalide2(long long n) {
	char string[1000];
	
	sprintf(string, "%lld", n);
	
	int taille = strlen(string);
	int moitie = taille / 2;
	
	if (string[0] == 0) {
		return 1;
	}
	
	for (long long motif = 1 ; motif <= moitie ; motif++) {
	
		if ((taille % motif) != 0) {
			continue ;
		}
		
	
		int valide = 1;
		for (long long i = motif ; i < taille ; i++) {
			if (string[i] != string [i % motif]) {
				valide = 0;
				continue ;
			}
		}
		
		if (valide) {
			return 1;
		}
	}
	
	return 0;
}



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
		
		long long start;
		long long end;
		char c;
		
		while (fscanf(f, "%lld-%lld%c", &start, &end, &c) == 3) {
		
			printf("Range : %lld à %lld\n", start, end);
			
			for (long long i = start ; i <= end ; i++) {
				/* ============================================ FIRST STAR ============================================ 
				 *
				 *	if (est_invalide(i)) {
				 *		somme += i ;
				 *		printf ("%lld est invalide, voici la nouvelle valeur de la somme : %lld\n", i, somme);
				 *	}
				 *
				 */
			
				/* ============================================ SECOND STAR ============================================ */
				if (est_invalide2(i)) {
					somme += i ;
					printf ("%lld est invalide, voici la nouvelle valeur de la somme : %lld\n", i, somme);
				}
				
			}
			
			if (c == '\n') {
				break ;
			}
		}
	}
	
	printf("\nLe resultat de la somme de tous les nombres invalides est : %lld\n\n", somme);
	
	return 0;
}
