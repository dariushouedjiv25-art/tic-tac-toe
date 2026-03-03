#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  if (tab[0] == 'x' && tab[1] == 'x' && tab[2] == 'x') {
    return 1;
  } else if (tab[0] == 'o' && tab[1] == 'o' && tab[2] == 'o') {
    return 1;
  } else if (tab[0] == 'x' && tab[3] == 'x' && tab[6] == 'x') {
    return 1;
  } else if (tab[1] == 'x' && tab[4] == 'x' && tab[7] == 'x') {
    return 1;
  } else if (tab[2] == 'x' && tab[5] == 'x' && tab[8] == 'x') {
    return 1;
  } else if (tab[0] == 'x' && tab[4] == 'x' && tab[8] == 'x') {
    return 1;
  } else if (tab[2] == 'x' && tab[4] == 'x' && tab[6] == 'x') {
    return 1;
  } else if (tab[3] == 'x' && tab[4] == 'x' && tab[5] == 'x') {
    return 1;
  }
  return 0;
}


int main() {

  char R[4] = "oui";
  while (strcmp(R, "oui") == 0 || strcmp(R, "o") == 0) {
    // variable
    char saisie[30];
    int posx;
    int poso;
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

    printf("| 1| 2| 3|\n");
    printf("| 4| 5| 6|\n");
    printf("| 7| 8| 9|\n");

    for (int i = 0; i < 9; i++) {
      tab[i] = ' ';
    }

    while (nb_coups < 9 && !victoire_ou_egalite) {
      /* ----- Joueur 1 ----- */
      do {
        printf("%s veuillez saisir la valeur correspondante a la case ou "
             "vous voulez vous deplacer\n", joueur1);
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

            printf("| %c| %c| %c|                | 1| 2| 3|\n", tab[0], tab[1],
                   tab[2]);
            printf("| %c| %c| %c|                | 4| 5| 6|\n", tab[3], tab[4],
                   tab[5]);
            printf("| %c| %c| %c|                | 7| 8| 9|\n", tab[6], tab[7],
                   tab[8]);

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
             "vous voulez vous deplacer\n", joueur2);
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

            printf("| %c| %c| %c|                | 1| 2| 3|\n", tab[0], tab[1],
                   tab[2]);
            printf("| %c| %c| %c|                | 4| 5| 6|\n", tab[3], tab[4],
                   tab[5]);
            printf("| %c| %c| %c|                | 7| 8| 9|\n", tab[6], tab[7],
                   tab[8]);

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

    do {
      printf("Voulez-vous rejouer ? (oui/non)\n");
      gets(R);
    } while (strcmp(R, "oui") != 0 && strcmp(R, "non") != 0 &&
             strcmp(R, "o") != 0 && strcmp(R, "n") != 0);

    if (strcmp(R, "non") == 0 || strcmp(R, "n") == 0) {
      printf("Au revoir\n");
      return 0;
    }
  }
  return 0;
}
