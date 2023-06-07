//Schneider Clément et Lerosier Alexandre SAE 1.
#include <stdio.h>
#include "board.h"

int tour(int joueur){
	int choix = 0;
	printf("Au tour du joueur %d :\n", joueur);
	printf("Si vous voulez placer une pièce, entrez 1\n");
	printf("Si vous voulez déplacer une pièce, entrez 2\n");
	scanf("%d", &choix);
	if(choix != 1 && choix != 2){
		while(choix != 1 && choix != 2){
			printf("Vous n'avez pas entré un caractère valide, réessayez :");
			//fonctionne avec int, bug avec un char.
			scanf("%d", &choix);
		}
	}
	return choix;
}

void partie(board game){
	int choix = 0;
	int colonne = 0;
	int ligne = 0;
	int taille = 0;
	int ligne_cible = 0;
	int colonne_cible = 0;
	while(get_winner(game) != 1 && get_winner(game) != 2){
		choix = tour(next_player(game));
		if(choix == 1){
			printf("En quelle ligne voulez vous placer votre pièce ? ");
			scanf("%d", &ligne);
			printf("En quelle colonne voulez vous placer votre pièce ? ");
			scanf("%d", &colonne);
			printf("Sélectionnez la taille de votre pièce (1 pour petit, 2 pour moyen et 3 pour grand) : ");
			scanf("%d", &taille);
			while(taille <= 0 || taille >= 4){
				printf("La taille que vous avez séléctionné n'est pas valide !\n");
				printf("Sélectionnez la taille de votre pièce (1 pour petit, 2 pour moyen et 3 pour grand) : ");
				scanf("%d", &taille);
			}
			int res =place_piece(game, taille, ligne - 1, colonne - 1);
			if(res == OK){
				printf("La piece a été placée avec succès.\n");
			}
			else if(res == SOURCE){
				if(get_place_holder(game, ligne, colonne) == next_player(game)){
					printf("Vous avez déjà une pièce ici !\n");
				}
				else{
					printf("Vous n'avez pas assez de pièces de cette taille !\n");
				}
			}
			else if(res == TARGET){
				printf("Il y a déjà une pièce plus grande ici !\n");
			}
			else{
				printf("Il n'y à pas de case à ces coordonnées !");
			}
		}
		if(choix == 2){
			printf("En quelle ligne se trouve la pièce à déplacer ? ");
			scanf("%d", &ligne);
			printf("En quelle colonne se trouve la pièce à déplacer ? ");
			scanf("%d", &colonne);
			printf("En quelle ligne voulez vous placer votre pièce ? ");
			scanf("%d", &ligne_cible);
			printf("En quelle colonne voulez vous placer votre pièce ? ");
			scanf("%d", &colonne_cible);
			while((ligne > 3 || ligne < 1) && (colonne > 3 || ligne < 1) && get_place_holder(game, ligne, colonne) == NO_PLAYER){
				printf("Vos coordonnées ne sont pas dans le plateau ! ");
				printf("En quelle ligne se trouve la pièce à déplacer ? ");
				scanf("%d", &ligne);
				printf("En quelle colonne se trouve la pièce à déplacer ? ");
				scanf("%d", &colonne);
				printf("En quelle ligne voulez vous placer votre pièce ? ");
				scanf("%d", &ligne_cible);
				printf("En quelle colonne voulez vous placer votre pièce ? ");
				scanf("%d", &colonne_cible);
			}
			move_piece(game, ligne - 1, colonne - 1, ligne_cible - 1, colonne_cible - 1);
		}
	}
	printf("Vainqueur : joueur %d", get_winner(game));
}


int main(){
	board game = new_game();
	printf("Début d'une nouvelle partie ...\n");
	partie(game);
	return 0;
}
