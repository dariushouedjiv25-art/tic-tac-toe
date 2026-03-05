#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void vider_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

//--------- fontion est nombre------
int ESTNOMBRE(const char s[]) {
  int np = 0;
  int len = strlen(s);
  if (len == 0) {
    return 1;
  }
  for (int i = 0; i < len; i++) {
    if (s[i] == '-') {
      if (i != 0) {
        return 1;
      }
    } else if ((s[i] == '.') || (s[i] == ',')) {
      np += 1;
      if ((np > 1) || (i == len) || (i == 0)) {
        return 1;
      }
    } else {
      if ((s[i] < '0') || (s[i] > '9')) {
        return 1;
      }
    }
  }
  return 0;
}

int victoire(char tab[]) {
  for (int i = 0; i < 3; i++) {
    if (tab[i * 3] != ' ' && tab[i * 3] == tab[i * 3 + 1] &&
        tab[i * 3 + 1] == tab[i * 3 + 2])
      return 1;
    if (tab[i] != ' ' && tab[i] == tab[i + 3] && tab[i + 3] == tab[i + 6])
      return 1;
  }
  if (tab[0] != ' ' && tab[0] == tab[4] && tab[4] == tab[8])
    return 1;
  if (tab[2] != ' ' && tab[2] == tab[4] && tab[4] == tab[6])
    return 1;
  return 0;
}

// fonction pour jouer contre ordinateur

void ordinateur(char tab[]) {
  srand(time(NULL));
  int pos_vides[9];
  int nb_vides = 0;
  for (int i = 0; i < 9; i++) {
    if (tab[i] == ' ') {
      pos_vides[nb_vides++] = i;
    }
  }
  if (nb_vides > 0) {
    int k = pos_vides[rand() % nb_vides];
    tab[k] = 'o';
  }
}

int jouer_coup_strategique(char tab[], char c) {
  for (int i = 0; i < 3; i++) {
    if (tab[i * 3] == c && tab[i * 3 + 1] == c && tab[i * 3 + 2] == ' ') {
      tab[i * 3 + 2] = 'o';
      return 1;
    }
    if (tab[i * 3] == c && tab[i * 3 + 2] == c && tab[i * 3 + 1] == ' ') {
      tab[i * 3 + 1] = 'o';
      return 1;
    }
    if (tab[i * 3 + 1] == c && tab[i * 3 + 2] == c && tab[i * 3] == ' ') {
      tab[i * 3] = 'o';
      return 1;
    }

    if (tab[i] == c && tab[i + 3] == c && tab[i + 6] == ' ') {
      tab[i + 6] = 'o';
      return 1;
    }
    if (tab[i] == c && tab[i + 6] == c && tab[i + 3] == ' ') {
      tab[i + 3] = 'o';
      return 1;
    }
    if (tab[i + 3] == c && tab[i + 6] == c && tab[i] == ' ') {
      tab[i] = 'o';
      return 1;
    }
  }

  if (tab[0] == c && tab[4] == c && tab[8] == ' ') {
    tab[8] = 'o';
    return 1;
  }
  if (tab[0] == c && tab[8] == c && tab[4] == ' ') {
    tab[4] = 'o';
    return 1;
  }
  if (tab[4] == c && tab[8] == c && tab[0] == ' ') {
    tab[0] = 'o';
    return 1;
  }

  if (tab[2] == c && tab[4] == c && tab[6] == ' ') {
    tab[6] = 'o';
    return 1;
  }
  if (tab[2] == c && tab[6] == c && tab[4] == ' ') {
    tab[4] = 'o';
    return 1;
  }
  if (tab[4] == c && tab[6] == c && tab[2] == ' ') {
    tab[2] = 'o';
    return 1;
  }

  return 0;
}

void ordinateurM(char tab[]) {
  if (jouer_coup_strategique(tab, 'o') == 1) {
    return;
  } else if (jouer_coup_strategique(tab, 'x') == 1) {
    return;
  } else {
    ordinateur(tab);
    return;
  }
}

int evaluer(char tab[]) {
  // Lignes
  for (int ligne = 0; ligne < 3; ligne++) {
    if (tab[ligne * 3] != ' ' && tab[ligne * 3] == tab[ligne * 3 + 1] &&
        tab[ligne * 3 + 1] == tab[ligne * 3 + 2]) {
      if (tab[ligne * 3] == 'o')
        return 10;
      if (tab[ligne * 3] == 'x')
        return -10;
    }
  }
  // Colonnes
  for (int col = 0; col < 3; col++) {
    if (tab[col] != ' ' && tab[col] == tab[col + 3] &&
        tab[col + 3] == tab[col + 6]) {
      if (tab[col] == 'o')
        return 10;
      if (tab[col] == 'x')
        return -10;
    }
  }
  // Diagonales
  if (tab[0] != ' ' && tab[0] == tab[4] && tab[4] == tab[8]) {
    if (tab[0] == 'o')
      return 10;
    if (tab[0] == 'x')
      return -10;
  }
  if (tab[2] != ' ' && tab[2] == tab[4] && tab[4] == tab[6]) {
    if (tab[2] == 'o')
      return 10;
    if (tab[2] == 'x')
      return -10;
  }
  return 0;
}

int resteCasesVides(char tab[]) {
  for (int i = 0; i < 9; i++) {
    if (tab[i] == ' ')
      return 1;
  }
  return 0;
}

int minimax(char tab[], int profondeur, int estMaximisant) {
  int score = evaluer(tab);

  if (score == 10)
    return score - profondeur;

  if (score == -10)
    return score + profondeur;

  if (resteCasesVides(tab) == 0)
    return 0;

  if (estMaximisant) {
    int meilleur = -1000;
    for (int i = 0; i < 9; i++) {
      if (tab[i] == ' ') {
        tab[i] = 'o';
        int valeur_actuelle = minimax(tab, profondeur + 1, 0);
        if (valeur_actuelle > meilleur) {
          meilleur = valeur_actuelle;
        }
        tab[i] = ' '; // Annuler
      }
    }
    return meilleur;
  } else {
    int meilleur = 1000;
    for (int i = 0; i < 9; i++) {
      if (tab[i] == ' ') {
        tab[i] = 'x';
        int valeur_actuelle = minimax(tab, profondeur + 1, 1);
        if (valeur_actuelle < meilleur) {
          meilleur = valeur_actuelle;
        }
        tab[i] = ' '; // Annuler
      }
    }
    return meilleur;
  }
}

void ordinateurDifficile(char tab[]) {
  int meilleurScore = -1000;
  int meilleurCoup = -1;

  for (int i = 0; i < 9; i++) {
    if (tab[i] == ' ') {
      tab[i] = 'o'; // Essayer ce coup
      int score_coup = minimax(tab, 0, 0);
      tab[i] = ' '; // Annuler

      if (score_coup > meilleurScore) {
        meilleurScore = score_coup;
        meilleurCoup = i;
      }
    }
  }
  if (meilleurCoup != -1) {
    tab[meilleurCoup] = 'o';
  }
}

int main() {
  int choix;
  char R[4] = "oui";

  while (strcmp(R, "oui") == 0 || strcmp(R, "o") == 0) {
    do {
      printf("quelle est votre choix ?\n");
      printf("1 - deux joueurs\n");
      printf("2 - contre ordinateur\n");
      scanf("%d", &choix);
      vider_buffer();

      switch (choix) {
      case 1: {
        // variable
        char saisie[30];
        int posx;
        char joueur1[100];
        char joueur2[100];

        char tab[9];

        int victoire_ou_egalite = 0; /* 0 = en cours, 1 = victoire */
        int nb_coups = 0;            /* nombre de coups joues (max 9) */

        printf("| 1| 2| 3|\n");
        printf("| 4| 5| 6|\n");
        printf("| 7| 8| 9|\n");

        printf("joueur 1 : x\n");
        printf("joueur 2 : o\n");

        printf("joueur 1 veuillez entrer votre nom\n");
        gets(joueur1);
        printf("joueur 2 veuillez entrer votre nom\n");
        gets(joueur2);

        printf("\n| 1| 2| 3|\n");
        printf("| 4| 5| 6|\n");
        printf("| 7| 8| 9|\n\n");

        for (int i = 0; i < 9; i++) {
          tab[i] = ' ';
        }

        while (nb_coups < 9 && !victoire_ou_egalite) {
          /* ----- Joueur 1 ----- */
          do {
            printf("%s veuillez saisir la valeur correspondante a la case ou "
                   "vous voulez vous deplacer\n",
                   joueur1);
            gets(saisie);
            if (ESTNOMBRE(saisie) == 0) {
              posx = atoi(saisie);
              if ((posx < 1) || (posx > 9)) {
                printf("votre choix n'a pas de correspondance\n");
              } else if (tab[posx - 1] == 'o' || tab[posx - 1] == 'x') {
                printf("la case est deja occupee\n");
              } else {
                tab[posx - 1] = 'x';
                nb_coups++;

                printf("| %c| %c| %c|                | 1| 2| 3|\n", tab[0],
                       tab[1], tab[2]);
                printf("| %c| %c| %c|                | 4| 5| 6|\n", tab[3],
                       tab[4], tab[5]);
                printf("| %c| %c| %c|                | 7| 8| 9|\n", tab[6],
                       tab[7], tab[8]);

                if (victoire(tab) == 1) {
                  printf("%s a gagne\n", joueur1);
                  victoire_ou_egalite = 1;
                }
                break;
              }
            } else if (ESTNOMBRE(saisie) == 1) {
              printf("veuillez entrer un nombre valide\n");
            }
          } while (1);

          if (victoire_ou_egalite)
            break;
          if (nb_coups >= 9)
            break;

          /* ----- Joueur 2 ----- */
          do {
            printf("%s veuillez saisir la valeur correspondante a la case ou "
                   "vous voulez vous deplacer\n",
                   joueur2);
            gets(saisie);
            if (ESTNOMBRE(saisie) == 0) {
              posx = atoi(saisie);
              if ((posx < 1) || (posx > 9)) {
                printf("votre choix n'a pas de correspondance avec la case\n");
              } else if (tab[posx - 1] == 'x' || tab[posx - 1] == 'o') {
                printf("la case est deja occupee\n");
              } else {
                tab[posx - 1] = 'o';
                nb_coups++;

                printf("| %c| %c| %c|                | 1| 2| 3|\n", tab[0],
                       tab[1], tab[2]);
                printf("| %c| %c| %c|                | 4| 5| 6|\n", tab[3],
                       tab[4], tab[5]);
                printf("| %c| %c| %c|                | 7| 8| 9|\n", tab[6],
                       tab[7], tab[8]);

                if (victoire(tab) == 1) {
                  printf("%s a gagne\n", joueur2);
                  victoire_ou_egalite = 1;
                }
                break;
              }
            } else if (ESTNOMBRE(saisie) == 1) {
              printf("veuillez entrer un nombre valide\n");
            }
          } while (1);

          if (victoire_ou_egalite)
            break;
        }

        if (victoire_ou_egalite == 0) {
          printf("match nul\n");
        }
      } break;

      case 2: {
        // jouer contre ordinateur
        char saisie[30];
        int posx;
        char joueur1[100];
        int difficulte = 0;

        char tab[9];

        int victoire_ou_egalite = 0; /* 0 = en cours, 1 = victoire */
        int nb_coups = 0;            /* nombre de coups joues (max 9) */

        printf("| 1| 2| 3|\n");
        printf("| 4| 5| 6|\n");
        printf("| 7| 8| 9|\n");

        printf("joueur 1 : x\n");
        printf("ordinateur : o\n");

        do {
          printf("\nChoisissez le niveau de difficulte :\n");
          printf("1 - Facile (Aleatoire)\n");
          printf("2 - Moyen (Strategique)\n");
          printf("3 - Difficile (Imbattable)\n");
          scanf("%d", &difficulte);
          vider_buffer();
        } while (difficulte < 1 || difficulte > 3);

        printf("joueur 1 veuillez entrer votre nom\n");
        gets(joueur1);

        printf("\n| 1| 2| 3|\n");
        printf("| 4| 5| 6|\n");
        printf("| 7| 8| 9|\n\n");

        for (int i = 0; i < 9; i++) {
          tab[i] = ' ';
        }

        while (nb_coups < 9 && !victoire_ou_egalite) {
          /* ----- Joueur 1 ----- */
          do {
            printf("%s veuillez saisir la valeur correspondante a la case ou "
                   "vous voulez vous deplacer\n",
                   joueur1);
            gets(saisie);
            if (ESTNOMBRE(saisie) == 0) {
              posx = atoi(saisie);
              if ((posx < 1) || (posx > 9)) {
                printf("votre choix n'a pas de correspondance\n");
              } else if (tab[posx - 1] == 'o' || tab[posx - 1] == 'x') {
                printf("la case est deja occupee\n");
              } else {
                tab[posx - 1] = 'x';
                nb_coups++;

                printf("| %c| %c| %c|                | 1| 2| 3|\n", tab[0],
                       tab[1], tab[2]);
                printf("| %c| %c| %c|                | 4| 5| 6|\n", tab[3],
                       tab[4], tab[5]);
                printf("| %c| %c| %c|                | 7| 8| 9|\n", tab[6],
                       tab[7], tab[8]);

                if (victoire(tab) == 1) {
                  printf("%s a gagne\n", joueur1);
                  victoire_ou_egalite = 1;
                }
                break;
              }
            } else if (ESTNOMBRE(saisie) == 1) {
              printf("veuillez entrer un nombre valide\n");
            }
          } while (1);

          if (victoire_ou_egalite)
            break;
          if (nb_coups >= 9)
            break;

          /* ----- ordinateur ----- */
          if (difficulte == 1) {
            ordinateur(tab);
          } else if (difficulte == 2) {
            ordinateurM(tab);
          } else if (difficulte == 3) {
            ordinateurDifficile(tab);
          }
          nb_coups++;

          printf("l'ordinateur a joue :\n");
          printf("| %c| %c| %c|                | 1| 2| 3|\n", tab[0], tab[1],
                 tab[2]);
          printf("| %c| %c| %c|                | 4| 5| 6|\n", tab[3], tab[4],
                 tab[5]);
          printf("| %c| %c| %c|                | 7| 8| 9|\n", tab[6], tab[7],
                 tab[8]);

          if (victoire(tab) == 1) {
            printf("vous avez perdu !\n");
            victoire_ou_egalite = 1;
          }
          if (victoire_ou_egalite) {
            break;
          }
        }

        if (victoire_ou_egalite == 0) {
          printf("match nul\n");
        }
        break;
      }
      default:
        printf("choix incorrespondant\n");
        break;
      }
    } while ((choix != 1) && (choix != 2));

    do {
      printf("Voulez-vous rejouer ? (oui/non)\n");
      gets(R);
    } while (strcmp(R, "oui") != 0 && strcmp(R, "non") != 0 &&
             strcmp(R, "o") != 0 && strcmp(R, "n") != 0);

    if (strcmp(R, "non") == 0 || strcmp(R, "n") == 0) {
      printf("Au revoir\n");
    }
  }
  return 0;
}