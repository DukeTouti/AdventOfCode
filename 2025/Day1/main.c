#include <stdlib.h>
#include <stdio.h>

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
		
		printf("Position initiale : %d\n", pos);
		
		while(fscanf(f, " %c%d", &sens, &pas_rotation) == 2) {
			
			switch(sens) {
				case 'L':
					pos = gauche(pas_rotation, pos);
					printf("nouvelle position : %d\n", pos);
					code_coffre += verification(pos);
					break;
				case 'R':
					pos = droite(pas_rotation, pos);
					printf("nouvelle position : %d\n", pos);
					code_coffre += verification(pos);
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
