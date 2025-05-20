#include <stdio.h>
#include <string.h> 

#define MAX 100

//Structure d'une classe
typedef struct {
    char code[10];
    char nom[40];
    char niveau[40];
    int eff;
} classe;

// Fonction pour gerer la mise a jour apres suppression et modifcation 
void Miseajour(classe classes[], int nbclasses){
    FILE *maj = fopen("/home/general-tech/Documents/PROJECT-C/Classes.txt", "w") ;
    if (maj == NULL) {
        printf("Erreur : impossible de réécrire le fichier.\n");
        return;
    }
    for (int i = 0; i < nbclasses; i++) {
        fprintf(maj, "%s %s %s %d\n",
                classes[i].code,
                classes[i].nom,
                classes[i].niveau,
                classes[i].eff) ;
    }
    fclose(maj);
}


// Ajouter une classe et enregistrement dans fichier
void AjouterClasse(classe classes[], int *nbClasses) {
    int n;
    printf("Combien de classes voulez-vous ajouter ? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\n--- Classe %d ---\n", i + 1);

        classe nouvelle;
        printf("Code : ");
        scanf("%s", nouvelle.code);

        // Vérifier si le code existe déjà
        int existe = 0;
        for (int j = 0; j < *nbClasses; j++) {
            if (strcmp(classes[j].code, nouvelle.code) == 0) {
                printf("Erreur : code déjà existant.\n");
                existe = 1;
                break;
            }
        }
        if (existe) {
            i--; // pour redemander la même position
            continue;
        }

        printf("Nom : ");
        scanf("%s", nouvelle.nom);
        printf("Niveau : ");
        scanf("%s", nouvelle.niveau);
        printf("Effectif : ");
        scanf("%d", &nouvelle.eff);

        classes[*nbClasses] = nouvelle;
        (*nbClasses)++;

        // Enregistrer immédiatement dans le fichier
        FILE *cla = fopen("/home/general-tech/Documents/PROJECT-C/Classes.txt", "a");
        if (cla == NULL) {
            printf("Erreur : impossible d'ouvrir le fichier.\n");
            return;
        }
        fprintf(cla, "%s %s %s %d\n", nouvelle.code, nouvelle.nom, nouvelle.niveau, nouvelle.eff);
        fclose(cla);

        printf("Classe ajoutée et enregistrée avec succès.\n");
    }
}

    
    
// Afficher toutes les classes
void AfficherClasse(classe classes[], int nbClasses) {
    if (nbClasses == 0) {
        printf("Aucune classe enregistree.\n");
        return;
    }
    for (int i = 0; i < nbClasses; i++) {
        printf("\nClasse %d :\n", i + 1);
        printf("Code    : %s\n", classes[i].code);
        printf("Nom     : %s\n", classes[i].nom);
        printf("Niveau  : %s\n", classes[i].niveau);
        printf("Effectif: %d\n", classes[i].eff);
    }
}

//Rechercher une classe à partir de son code
void RechercherClasse(classe classes[], int nbclasses){
    char codeRecherche [10] ;
    int trouve = 0 ;

    printf("Entrez le code de la classe à rechercher :\n ");
    scanf("%s", codeRecherche);
    for(int i =0; i < nbclasses; i++){
        if(strcmp(classes[i].code, codeRecherche)==0){
            printf("Classe Trouvee avec succes !!\n") ;
            printf("Code : %s\n", classes[i].code) ;
            printf("Nom : %s\n", classes[i].nom) ;
            printf("Niveau : %s\n", classes[i].niveau) ;
            printf("Effectif : %d\n", classes[i].eff) ;

            trouve =1 ;
            break ;
        }
    }
    if(!trouve){
        printf("Classe non trouvee") ;
    }
} 

void ModifierClasse(classe classes[], int nbclasses) {
    char codeRecherche[10];
    int trouve = 0;

    printf("Entrez le code de la classe à modifier : ");
    scanf("%s", codeRecherche);

    for (int i = 0; i < nbclasses; i++) {
        if (strcmp(classes[i].code, codeRecherche) == 0) {
            printf("Classe trouvée.\n");

            int choixModif;
            printf("\nQue voulez-vous modifier ?\n");
            printf("0. Annuler\n");
            printf("1. Nom\n");
            printf("2. Niveau\n");
            printf("3. Effectif\n");
            printf("4. Tous les champs\n");
            printf("Votre choix : ");
            scanf("%d", &choixModif);

            switch (choixModif) {
                case 0:
                    printf("Modification annulée.\n");
                    return;
                case 1:
                    printf("Nouveau nom : ");
                    scanf("%s", classes[i].nom);
                    break;
                case 2:
                    printf("Nouveau niveau : ");
                    scanf("%s", classes[i].niveau);
                    break;
                case 3:
                    printf("Nouvel effectif : ");
                    scanf("%d", &classes[i].eff);
                    break;
                case 4:
                    printf("Nouveau nom : ");
                    scanf("%s", classes[i].nom);
                    printf("Nouveau niveau : ");
                    scanf("%s", classes[i].niveau);
                    printf("Nouvel effectif : ");
                    scanf("%d", &classes[i].eff);
                    break;
                default:
                    printf("Choix invalide. Aucune modification.\n");
                    return;
            }

            printf("Modification effectuée avec succès.\n");
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Classe non trouvée.\n");
    } else {
         ModifierClasse(classes, nbclasses);
    }
}


void SupprimerClasse(classe classes [], int *nbclasses){
    char codeRecherche [10] ;
    int trouve = 0 ;

    printf("Entrer le code a supprimer") ;
    scanf("%s",codeRecherche) ;
    for(int i= 0; i < *nbclasses; i++ ){
        if(strcmp(classes[i].code,codeRecherche)==0){
            for(int j = 1; j< *nbclasses-1; j++){
                classes[j] = classes[j+1] ;
            }
            (*nbclasses)-- ;

            printf("Classe Suppimee avec success!!\n") ;
            trouve = 1;
            break;
        }
    }
    if (!trouve) {
        printf("Classe non trouvée.\n") ;
    } else {
        Miseajour(classes, *nbclasses);
    }
}


// Charger les classes depuis un fichier au démarrage
void ChargerClasses(classe classes[], int *nbClasses) {
    FILE *cla = fopen("/home/general-tech/Documents/PROJECT-C/Classes.txt", "r");
    if (cla == NULL) {
        printf("Aucune donnée trouvée.\n");
        return;
    }
    while (fscanf(cla, "%s %s %s %d", classes[*nbClasses].code,
                  classes[*nbClasses].nom,
                  classes[*nbClasses].niveau,
                  &classes[*nbClasses].eff) == 4) {
        (*nbClasses)++;
    }
    fclose(cla);
    printf("Données chargées depuis le fichier.\n");
}

// Menu principal
int main() {
    classe classes[MAX];
    int nbClasses = 0;
    int choix;

    ChargerClasses(classes, &nbClasses);

    do {
        printf("\n===== MENU =====\n");
        printf("1. Ajouter une classe\n");
        printf("2. Afficher toutes les classes\n");
        printf("3. Rechercher une classe\n");
        printf("4. Modifier une classe\n");
        printf("5. Supprimer une classe\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                AjouterClasse(classes, &nbClasses);
                break;
            case 2:
                AfficherClasse(classes, nbClasses);
                break;
            case 3:
            RechercherClasse(classes, nbClasses);
                break;
            case 4: 
            ModifierClasse(classes, nbClasses) ;
                break;
            case 5:
            SupprimerClasse(classes, &nbClasses) ;
                break;
            case 0:
                printf("Fermeture du programme...\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}
