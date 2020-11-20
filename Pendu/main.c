
//FEATURES :
/*
-Demander un mot qui deviendra le mot mystere à trouver
-Remplacer les lettres du mot par des underscore et l'afficher : indiquer au joueur la longueur du mot
-Demander au joueur d'entrer une lettre
-Afficher le résultat : mot mystere avec les lettres trouvées
-Victoire ou défaite : défaite si le nb d'essai est dépassé, sinon victoire si le joueur a complété tout le mot
*/


//ALGORITHME :____________________________________________________________________________________________________
/*

FONCTION ChoixMotATrouver () : CHAINE
//BUT:Choisir en début de partie le mot mystère
//ENTREE:tableau de caractères
//SORTIE:tableau de caractères

VAR : motATrouver :CHAINE
DEBUT

    ECRIRE "Afin de commencer une partie, veuillez entrer un mot"
    LIRE motATrouver
    ChoixMotATrouver<-- motATrouver

FINFONCTION




FONCTION DemanderLettre():CARACTERE
//BUT:Demander au joueur d'entrer un caractère
//ENTREE:rien
//SORTIE:caractere

VAR car:CARACTERE

DEBUT
    ECRIRE : "Veuillez entrer un caractère
    LIRE car
    DemanderLettre<--car
FIN





FONCTION remplacCar(motATrouver:CHAINE, car:caractere,motMystere:CHAINE):CHAINE
//BUT:Remplacer les caractère du motATrouver par soit des underscore en début de partie, soit des lettres le reste du jeu
//ENTREE:le mot a trouver, le caractère que l'on veut mettre, le mot mystère
//SORTIE:Le mot mystere

VAR:i:ENTIER
DEBUT
    SI (car='_') //en gros si c'est l'underscore c'est pour init la chaine
        ALORS POUR i DE 1 A LONGUEUR(motATrouver)
                    motMystere[i]<--car
              FINPOUR
    SINON
        POUR i DE 1 A LONGUEUR(motATrouver)
                SI motATrouver[i]=car
                ALORS motMystere[i]<--car
                FINSI
        FINPOUR
    FINSI

FINFONCTION





FONCTION CondFinDePartie(cptVie:ENTIER, motMystere:CHAINE, motATrouver:CHAINE):BOOLEEN
DEBUT
    SI (cptVie=0)
        ALORS ECRIRE "Dommage, vous avez perdu la partie, le pendu est complet
        CondFInDePartie<--VRAI
    SINON SI (motMystere=motAtrouver)
        ALORS ECRIRE "Félicitation vous avez gagné la partie, le mot mystère était bien : ",motATrouver
        CondFinDePartie<--VRAI
    SINON
        ECRIRE "Il vous reste",cptVie," d'essais avant la fin de la partie"
        CondFinDePartie <--FAUX
    FINSI
FINFONCTION




PROCEDURE AfficherMot (motMystere:CHAINE)
//BUT:Afficher l'état du motmystère
//ENTREE:motmystere
//SORTIE:rien
DEBUT
    ECRIRE motMystere
FINPROCEDURE




-------------------------------

VAR :motMystere:CHAINE
     motATrouver:CHAINE
    car:CARACTERE
    finDePartie:BOOLEEN
    cptVie=5

DEBUT

    FAIRE

        //init :
        cptVie<--cptVie-1
        car<--'_'
        motATrouver<--ChoixMotATrouver()
        motMystere<--RemplacCar(motATrouver,car,motMystere)

        //jeu : afficher et demander une lettre
        AfficherMot(motMystere)
        car<--DemanderLettre()
        motMystere<--RemplacCar(motATrouver,car,motMystere)
        finDePartie<--CondVictoire()

    TANTQUE finDePartie=FAUX

FIN


*/




//PROGRAMMATION EN C :____________________________________________________________________________________________


#include "header.h"
#define TAILLE 25 //valeur pour les tableaux de caractères : motMYSTERE et MotATrouver
const int taillePend=11;  //taille du pendu et valeur déterminant le nb de vie possible du joueur


//Prog principal______________________________________________
int main()
{
     //var pour stocker les mots
    char motATrouver[TAILLE]="";
    char motMystere[TAILLE]="";
    //var pour déplacer le curseur et faire le dessin du pendu
    int cptVie=taillePend;
    int i;
    char car='-';
    int lettreEstAjoutee=0; //si une lettre est trouvée par le joueur, alors la variable passe à 1 (bool ne fonctionnait pas)
    int hauteur=1;
    int ligne=1;




    //init -----------------------------------------------------------------------------------------------:
    printf("Bienvenue dans le jeu du pendu :\n");
    ChoixMotATrouver(motATrouver); //on demande au joueur de choisir un mot en début de partie
    //init du mot mystère avec des tirets
    RemplacCar(&lettreEstAjoutee,car,motATrouver,motMystere);
    AfficherMot(motMystere);



    //jeu -------------------------------------------------------------------------------------------------:
    //Afficher et demander une lettre
    do{
        DemanderLettre(&car);
        RemplacCar(&lettreEstAjoutee,car,motATrouver,motMystere);
        AfficherMot(motMystere);
        consequenceManche(&cptVie,lettreEstAjoutee); //on regarde s'il faut enlever un pt au comteur de vie ou non
        //et met à jour le dessin du pendu
        DessinerPendu(cptVie,taillePend,&ligne,&hauteur);

    }while(CondFinDePartie(cptVie,lettreEstAjoutee,motATrouver, motMystere)==0);





    return 0;
}


