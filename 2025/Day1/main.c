#include <stdlib.h>
#include <stdio.h>

/* First Star */
int gauche(int pas, int pos) {
	int nouvelle_pos = (pos - pas) % 100;
	
	if (nouvelle_pos < 0) {
		nouvelle_pos += 100;
	}
	
	return nouvelle_pos;
}

int droite(int pas, int pos) {
	return (pos + pas) % 100;
}

int verification(int position) {
	if (position == 0) {
		return 1;
	}
	
	return 0;
}

/* Second Star (methode, pas par pas) */

int compte_zero_gauche(int pas, int pos, int* code) {
	*code = 0;
	
	for (int i = 0 ; i < pas ; i++) {
		pos = (pos - 1 + 100) % 100;
		
		if (pos == 0) {
			(*code)++;
		}
	}
	
	return pos;
}

int compte_zero_droite(int pas, int pos, int* code) {
	*code = 0;
	
	for (int i = 0 ; i < pas ; i++) {
		pos = (pos + 1) % 100;
		
		if (pos == 0) {
			(*code)++;
		}
	}
	
	return pos;
}


int main(int argc, char** argv) {
	
	FILE* f;
	int cadran_init = 50;
	int nb_zero = 0;
	int pos = 50;
	int code_coffre = 0;
	
	if (argc != 2) {
		perror("Nombre d'argument incorrect\n");
		exit(1);
	} else {
		f = fopen(argv[1], "r");
		if (f == NULL) {
			perror("Erreur lors de l'ouverture du fichier en mode lecture\n");
			exit(2);
		}
		
		char sens;
		int pas_rotation;
		int nb_zeros;
		
		printf("Position initiale : %d\n", pos);
		
		while(fscanf(f, " %c%d", &sens, &pas_rotation) == 2) {
			
			switch(sens) {
				case 'L':
					/* ====================================== FIRST STAR ====================================== 
					 *
					 *	pos = gauche(pas_rotation, pos);
					 *	printf("L%d -> nouvelle position %d (passé par 0 : %d fois)\n", pas_rotation, pos);
					 *	code_coffre += verification(pos);
					 *
					 */
					
					/* ====================================== SECOND STAR ====================================== */
					pos = compte_zero_gauche(pas_rotation, pos, &nb_zeros);
					printf("L%d -> nouvelle position %d (passé par 0 : %d fois)\n", pas_rotation, pos, nb_zeros);
					code_coffre += nb_zeros;
					break;
				case 'R':
					/* ====================================== FIRST STAR ====================================== 
					 *
					 *	pos = droite(pas_rotation, pos);
					 *	printf("R%d -> nouvelle position %d (passé par 0 : %d fois)\n", pas_rotation, pos);
					 *	code_coffre += verification(pos);
					 *
					 */
					
					/* ====================================== SECOND STAR ====================================== */
					pos = compte_zero_droite(pas_rotation, pos, &nb_zeros);
					printf("R%d -> nouvelle position %d (passé par 0 : %d fois)\n", pas_rotation, pos, nb_zeros);
					code_coffre += nb_zeros;
					break;
				default:
					printf("Sens inconnu: %c\n", sens);
					break;
			}
		}
	}
	
	fclose(f);
	
	printf("Le code pour ouvrir le coffre fort est : %d\n", code_coffre);

	return 0;
}
