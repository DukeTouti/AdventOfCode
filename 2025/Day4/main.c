#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Enum pour les orientations */
typedef enum {
	NORD,
	SUD,
	EST,
	OUEST,
	NORD_EST,
	NORD_OUEST,
	SUD_EST,
	SUD_OUEST,
	NB_ORIENTATIONS
} Orientation;

/* Structure pour le robot */
typedef struct {
	int x;
	int y;
} Robot;

/* Obtenir le déplacement selon une orientation */
void obtenir_deplacement(Orientation orient, int *dx, int *dy) {
	switch(orient) {
		case NORD:
			*dx = -1;
			*dy = 0;
			break;
		case SUD:
			*dx = 1;
			*dy = 0;
			break;
		case EST:
			*dx = 0;
			*dy = 1;
			break;
		case OUEST:
			*dx = 0;
			*dy = -1;
			break;
		case NORD_EST:
			*dx = -1;
			*dy = 1;
			break;
		case NORD_OUEST:
			*dx = -1;
			*dy = -1;
			break;
		case SUD_EST:
			*dx = 1;
			*dy = 1;
			break;
		case SUD_OUEST:
			*dx = 1;
			*dy = -1;
			break;
	}
}

/* Compte les voisins @ autour du robot */
int compter_voisins(char **grille, Robot *robot, int hauteur, int largeur) {
	int compteur = 0;
	
	for (int i = 0; i < NB_ORIENTATIONS; i++) {
		int dx, dy;
		obtenir_deplacement(i, &dx, &dy);
		
		int nouveau_x = robot->x + dx;
		int nouveau_y = robot->y + dy;
		
		if (nouveau_x >= 0 && nouveau_x < hauteur && nouveau_y >= 0 && nouveau_y < largeur) {
			if (grille[nouveau_x][nouveau_y] == '@') {
				compteur++;
			}
		}
	}
	
	return compteur;
}

/* Le robot parcourt la grille et compte les rouleaux accessibles */
int robot_parcourir(char **grille, int hauteur, int largeur) {
	int rouleaux_accessibles = 0;
	Robot robot;
	
	for (robot.x = 0; robot.x < hauteur; robot.x++) {
		for (robot.y = 0; robot.y < largeur; robot.y++) {
			if (grille[robot.x][robot.y] == '@') {
				int voisins = compter_voisins(grille, &robot, hauteur, largeur);
				
				if (voisins < 4) {
					rouleaux_accessibles++;
				}
			}
		}
	}
	
	return rouleaux_accessibles;
}

int main(int argc, char** argv) {
	FILE* f;
	char **grille = NULL;
	int hauteur = 0;
	int largeur = 0;
	int capacite = 100;
	
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <fichier>\n", argv[0]);
		exit(1);
	}
	
	f = fopen(argv[1], "r");
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier");
		exit(2);
	}
	
	/* Allocation initiale */
	grille = malloc(capacite * sizeof(char*));
	if (grille == NULL) {
		perror("Erreur d'allocation mémoire");
		exit(3);
	}
	
	/* Chargement de la grille */
	char ligne[10000];
	while (fgets(ligne, sizeof(ligne), f) != NULL) {
		ligne[strcspn(ligne, "\n")] = '\0';
		
		int longueur = strlen(ligne);
		if (longueur > 0) {
			if (largeur == 0) {
				largeur = longueur;
			}
			
			/* Réallocation si nécessaire */
			if (hauteur >= capacite) {
				capacite *= 2;
				grille = realloc(grille, capacite * sizeof(char*));
				if (grille == NULL) {
					perror("Erreur de réallocation mémoire");
					exit(3);
				}
			}
			
			/* Allocation de la ligne */
			grille[hauteur] = malloc((largeur + 1) * sizeof(char));
			if (grille[hauteur] == NULL) {
				perror("Erreur d'allocation mémoire pour la ligne");
				exit(3);
			}
			
			strcpy(grille[hauteur], ligne);
			hauteur++;
		}
	}
	fclose(f);
	
	printf("Grille chargée : %d x %d\n", hauteur, largeur);
	
	/* Le robot fait tout le boulot */
	int resultat = robot_parcourir(grille, hauteur, largeur);
	
	printf("Nombre de rouleaux accessibles : %d\n", resultat);
	
	/* Libération de la mémoire */
	for (int i = 0; i < hauteur; i++) {
		free(grille[i]);
	}
	free(grille);
	
	return 0;
}
