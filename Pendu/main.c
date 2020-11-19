
//FEATURES :
/*
-Demander un mot qui deviendra le mot mystere � trouver
-Remplacer les lettres du mot par des underscore et l'afficher : indiquer au joueur la longueur du mot
-Demander au joueur d'entrer une lettre
-Afficher le r�sultat : mot mystere avec les lettres trouv�es
-Victoire ou d�faite : d�faite si le nb d'essai est d�pass�, sinon victoire si le joueur a compl�t� tout le mot
*/


//ALGORITHME :____________________________________________________________________________________________________
/*

FONCTION ChoixMotATrouver () : CHAINE
//BUT:Choisir en d�but de partie le mot myst�re
//ENTREE:tableau de caract�res
//SORTIE:tableau de caract�res

VAR : motATrouver :CHAINE
DEBUT

    ECRIRE "Afin de commencer une partie, veuillez entrer un mot"
    LIRE motATrouver
    ChoixMotATrouver<-- motATrouver

FINFONCTION




FONCTION DemanderLettre():CARACTERE
//BUT:Demander au joueur d'entrer un caract�re
//ENTREE:rien
//SORTIE:caractere

VAR car:CARACTERE

DEBUT
    ECRIRE : "Veuillez entrer un caract�re
    LIRE car
    DemanderLettre<--car
FIN





FONCTION remplacCar(motATrouver:CHAINE, car:caractere,motMystere:CHAINE):CHAINE
//BUT:Remplacer les caract�re du motATrouver par soit des underscore en d�but de partie, soit des lettres le reste du jeu
//ENTREE:le mot a trouver, le caract�re que l'on veut mettre, le mot myst�re
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
        ALORS ECRIRE "F�licitation vous avez gagn� la partie, le mot myst�re �tait bien : ",motATrouver
        CondFinDePartie<--VRAI
    SINON
        ECRIRE "Il vous reste",cptVie," d'essais avant la fin de la partie"
        CondFinDePartie <--FAUX
    FINSI
FINFONCTION




PROCEDURE AfficherMot (motMystere:CHAINE)
//BUT:Afficher l'�tat du motmyst�re
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define TAILLE 25 //valeur pour les tableaux de caract�res : motMYSTERE et MotATrouver
const int taillePend=11;  //taille du pendu et valeur d�terminant le nb de vie possible du joueur


//Prog principal______________________________________________
int main()
{
     //var pour stocker les mots
    char motATrouver[TAILLE]="";
    char motMystere[TAILLE]="";

    //var pour d�placer le curseur et faire le dessin du pendu
    int cptVie=taillePend;
    int i;
    char car='-';
    int lettreEstAjoutee=0; //si une lettre est trouv�e par le joueur, alors la variable passe � 1 (bool ne fonctionnait pas)
    int hauteur=1;
    int ligne=1;



    //init :
    printf("Bienvenue dans le jeu du pendu :\n");
    ChoixMotATrouver(motATrouver); //on demande au joueur de choisir un mot en d�but de partie
    //init du mot myst�re avec des tirets
    RemplacCar(&lettreEstAjoutee,car,motATrouver,motMystere);
    AfficherMot(motMystere);



    //jeu : Afficher et demander une lettre
    do{
        DemanderLettre(&car);
        RemplacCar(&lettreEstAjoutee,car,motATrouver,motMystere);
        AfficherMot(motMystere);
        consequenceManche(&cptVie,lettreEstAjoutee); //on regarde s'il faut enlever un pt au comteur de vie ou non
        //et met � jour le dessin du pendu
        DessinerPendu(cptVie,taillePend,&ligne,&hauteur);

    }while(CondFinDePartie(cptVie,lettreEstAjoutee,motATrouver, motMystere)==0);


    return 0;
}


