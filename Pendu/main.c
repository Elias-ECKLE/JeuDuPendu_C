
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //biblio pr gotoxy
#define TAILLE 255

//Prototypes :
void gotoxy(short x, short y);
void ChoixMotATrouver ();
int RemplacCar(char);
void AfficherMot();
char DemanderLettre();
int CondFinDePartie(int,int);
void DessinerPendu(int);
int consequenceManche(int,int);




//var globales :
//var pour stocker les mots
char motATrouver[TAILLE]="";
char motMystere[TAILLE]="";
//var pour déplacer le curseur et faire le dessin du pendu
int hauteur=1;
int ligne=1;
int taillePend=10;



//Prog principal______________________________________________
int main()
{
    int cptVie=taillePend;
    int i;
    char car='-';
    int lettreEstAjoutee=0; //si une lettre est trouvée par le joueur, alors la variable passe à 1 (bool ne fonctionnait pas)

    //init :
    printf("Bienvenue dans le jeu du pendu :\n");
    ChoixMotATrouver(); //on demande au joueur de choisir un mot en début de partie
    //init du mot mystère avec des tirets
    RemplacCar(car);
    AfficherMot();



    //jeu : Afficher et demander une lettre
    do{

        car=DemanderLettre();
        lettreEstAjoutee=RemplacCar(car);

        AfficherMot();
        cptVie=consequenceManche(cptVie,lettreEstAjoutee);


    }while(CondFinDePartie(cptVie,lettreEstAjoutee)==0);



    return 0;
}





//Procedures :_________________________________________________

// Fonction qui permet de placer le curseur à la position x,y
void gotoxy(short x, short y)
{
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos={x,y};
	SetConsoleCursorPosition(hConsole,Pos);
}

void ChoixMotATrouver (){
//BUT:Choisir en début de partie le mot mystère
//ENTREE:tableau de caractères
//SORTIE:tableau de caractères

    printf("Afin de commencer une partie, veuillez entrer un mot\n");
    scanf("%s",motATrouver);
}


char DemanderLettre(){
//BUT:Demander au joueur d'entrer un caractère
//ENTREE:rien
//SORTIE:caractere

    char lettre=' ';
    printf("Veuillez entrer un caractere : \n");
    getchar();
    scanf("%c",&lettre);

    return lettre;
}



int RemplacCar(char car){
//BUT:Remplacer les caractère du motATrouver par soit des underscore en début de partie, soit des lettres le reste du jeu
//ENTREE:le mot a trouver, le caractère que l'on veut mettre, le mot mystère
//SORTIE:Le mot mystere

    int i=0;
    int lettreEstAjoutee=0;

    if (car=='-'){ // si c'est l'underscore c'est pour init la chaine
        for(i=0;i<strlen(motATrouver);i++){
            motMystere[i]=car;
        }
    }
    else{
        for(i=0;i<strlen(motATrouver);i++){
            if(motATrouver[i]==car){
                motMystere[i]=car;
                lettreEstAjoutee=1;
            }
        }
    }
    return lettreEstAjoutee;
}


void AfficherMot(){
//BUT:Afficher l'état du motmystère
//ENTREE:motmystere
//SORTIE:rien

    system("cls");
    printf("%s\n",motMystere);

}


int CondFinDePartie(int cptVie,int lettreEstAjoutee){

    if(cptVie==0){
        printf("Dommage, vous avez perdu la partie, le pendu est complet\n\n");
        return 1;
    }
    else if(strcmp(motATrouver,motMystere) == 0){ //fct qui permet de ccomparer deux chaines, si égales la fct renvoie 0
        printf("Felicitation vous avez gagne la partie, le mot mystere etait bien : %s\n\n",motATrouver);
        return 1;
    }
    else{
        if(lettreEstAjoutee==1){
            printf("Vous avez trouve au moins une lettre du mot mystere. Vous disposez actuellement de %d essais\n\n",cptVie);
        }
        else{
            printf("Vous vous etes trompe, il ne vous reste plus que %d essais avant que le pendu soit complet\n\n",cptVie);
        }
        return 0;
    }
}



void DessinerPendu(int cptVie){

    /*switch(cptVie){


    int i;

    //potence verti :
        case 10:
            for(i=0;i<taillePend;i++){
                hauteur++;
                gotoxy(ligne,hauteur);
                printf("|");
            }
        break;

    //potence Inter
        case 9:
            ligne++;
            hauteur++;
            gotoxy(ligne, hauteur);
            printf("/");
        break;

    //Potence horizontale
        case 8:
            taillePend=taillePend*2;
            for (i=0;i<taillePend-2;i++){
                ligne++;
                gotoxy(ligne, hauteur);
                printf('-');
            }
        break;

    //Corde
        case 7:
            for (i=0;i<(taillePend/4);i++){
                hauteur++;
                gotoxy(ligne,hauteur);
                printf("|");
            }
        break;

    //tete
        case 6:
            hauteur=hauteur+2;
            //g a d
            hauteur++;
            gotoxy(ligne, hauteur);
            printf("-");
            // h vers b
            hauteur++;
            ligne++;
            gotoxy(ligne, hauteur);
            printf("|");
            //d vers g
            hauteur++;
            ligne--;
             gotoxy(ligne, hauteur);
            printf("-");
            //b vers h
            ligne--;
            hauteur--;
             gotoxy(ligne, hauteur);
            printf("|");
        break;

    //troncCorps
        case 5:
            hauteur++;
            for (i=0;i<taillePend-8;i++){
                hauteur++;
                gotoxy(ligne,hauteur);
                printf("|");
            }
        break;

    //brasG
        case 4:
            hauteur= hauteur+2;
            ligne--;
            gotoxy(ligne, hauteur);
            printf("\'");
        break;

    //brasD
        case 3:
            hauteur=hauteur+2;
            ligne++;
            gotoxy(ligne, hauteur);
            printf("/");
        break;

    //jambeG
        case 2:
            hauteur++;
            ligne--;
            gotoxy(ligne, hauteur);
            printf("/");
        break;

    //jambeD
        case 1:
            hauteur++;
            ligne++;
            gotoxy(ligne, hauteur);
            write("\'");
        break;

    }*/

}



int consequenceManche(int cptVie, int lettreEstAjoutee){

    //on enlève un pt au compteur de vie si on n'arrive pas à trouver une lettre se trouvant ds le mot mystere
    if(lettreEstAjoutee==0){
          cptVie--;
          //on met à jour le dessin du pendu
          DessinerPendu(cptVie);
    }

    return cptVie;
}

