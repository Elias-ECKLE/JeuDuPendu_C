
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

//procedures dessins pantin ;
void PotenceVerti();
void PotenceInter();
void PotenceHorizon();
void Corde();
void Tete();
void TroncCorps();
void BrasG();
void BrasD();
void JambeD();


//var globales :
//var pour stocker les mots
char motATrouver[TAILLE]="";
char motMystere[TAILLE]="";
//var pour d�placer le curseur et faire le dessin du pendu
int hauteur=1;
int ligne=1;
const int taillePend=11;
int cptVie=taillePend;



//Prog principal______________________________________________
int main()
{

    int i;
    char car='-';
    int lettreEstAjoutee=0; //si une lettre est trouv�e par le joueur, alors la variable passe � 1 (bool ne fonctionnait pas)

    //init :
    printf("Bienvenue dans le jeu du pendu :\n");
    ChoixMotATrouver(); //on demande au joueur de choisir un mot en d�but de partie
    //init du mot myst�re avec des tirets
    RemplacCar(car);
    AfficherMot();



    //jeu : Afficher et demander une lettre
    do{

        car=DemanderLettre();
        lettreEstAjoutee=RemplacCar(car);

        AfficherMot();
        cptVie=consequenceManche(cptVie,lettreEstAjoutee); //on regarde s'il faut enlever un pt au comteur de vie ou non
        //et met � jour le dessin du pendu


    }while(CondFinDePartie(cptVie,lettreEstAjoutee)==0);

    //on affiche une derni�re fois le pendu :
    DessinerPendu(cptVie);

    return 0;
}





//Procedures :_________________________________________________

// Fonction qui permet de placer le curseur � la position x,y
//GOTO
void gotoxy(short x, short y)
{
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos={x,y};
	SetConsoleCursorPosition(hConsole,Pos);
}


void ChoixMotATrouver (){
//BUT:Choisir en d�but de partie le mot myst�re
//ENTREE:tableau de caract�res
//SORTIE:tableau de caract�res

    printf("Afin de commencer une partie, veuillez entrer un mot\n");
    scanf("%s",motATrouver);
}


char DemanderLettre(){
//BUT:Demander au joueur d'entrer un caract�re
//ENTREE:rien
//SORTIE:caractere

    char lettre=' ';
    printf("Veuillez entrer un caractere : \n");
    getchar();
    scanf("%c",&lettre);

    return lettre;
}



int RemplacCar(char car){
//BUT:Remplacer les caract�re du motATrouver par soit des underscore en d�but de partie, soit des lettres le reste du jeu
//ENTREE:le mot a trouver, le caract�re que l'on veut mettre, le mot myst�re
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
//BUT:Afficher l'�tat du motmyst�re
//ENTREE:motmystere
//SORTIE:rien

    system("cls");
    printf("%s\n",motMystere);

}


int CondFinDePartie(int cptVie,int lettreEstAjoutee){

     gotoxy(1,15);
    if(cptVie==0){
        printf("Dommage, vous avez perdu la partie, le pendu est complet\n\n");
        return 1;
    }
    else if(strcmp(motATrouver,motMystere) == 0){ //fct qui permet de ccomparer deux chaines, si �gales la fct renvoie 0
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






//DESSIN PENDU :DIFFERENTS PROCEDURE
void PotenceVerti(){
    int i;
    hauteur=1;
    ligne=1;
    for(i=0;i<taillePend;i++){
        hauteur++;
        gotoxy(ligne,hauteur);
        printf("|");
    }
}
void PotenceInter(){
    hauteur=1;
    ligne=1;
    ligne++;
    hauteur++;
    gotoxy(ligne,hauteur);
    printf("/");
}
void PotenceHorizon(){
    hauteur=1;
    ligne=1;
    int i;
    int taillePendDouble=taillePend*2;
    for (i=0;i<taillePendDouble-2;i++){
        ligne++;
        gotoxy(ligne,hauteur);
        printf("-");
    }
}
void Corde(){
    int i;
    for (i=0;i<(taillePend/4);i++){
        hauteur++;
        gotoxy(ligne,hauteur);
        printf("|");
    }
}
void Tete(){



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
}

void TroncCorps(){
    int i;
    hauteur++;
    ligne++;
    for (i=0;i<taillePend-8;i++){
        hauteur++;
        gotoxy(ligne,hauteur);
        printf("|");
    }
}

void BrasG(){
    ligne--;
    ligne--;
    gotoxy(ligne, hauteur);
    printf("/");
}
void BrasD(){
    ligne=ligne+4;
    gotoxy(ligne, hauteur);
    printf("\\");
}
void JambeD(){
    hauteur=hauteur+2;
    gotoxy(ligne, hauteur);
    printf("\\");
}
void JambeG(){
    ligne=ligne-1;
    gotoxy(ligne, hauteur);
    write("/");
}


void DessinerPendu(int cptVie){

    int i;


    switch(cptVie){

    //potence verti :
        case 10:
            PotenceVerti();
        break;

    //potence Inter
        case 9:
            PotenceVerti();
            PotenceInter();
        break;

    //potence horizontale :
        case 8:
            PotenceVerti();
            PotenceInter();
            PotenceHorizon();
    //Corde
        break;
       case 7:
            PotenceVerti();
            PotenceInter();
            PotenceHorizon();
            Corde();
        break;

    //tete
       case 6:
            PotenceVerti();
            PotenceInter();
            PotenceHorizon();
            Corde();
            Tete();
        break;

    //troncCorps
       case 5:
            PotenceVerti();
            PotenceInter();
            PotenceHorizon();
            Corde();
            Tete();
            TroncCorps();
        break;

    //brasG
        case 4:
            PotenceVerti();
            PotenceInter();
            PotenceHorizon();
            Corde();
            Tete();
            TroncCorps();
            BrasG();
        break;

    //brasD
        case 3:
            PotenceVerti();
            PotenceInter();
            PotenceHorizon();
            Corde();
            Tete();
            TroncCorps();
            BrasG();
            BrasD();
        break;

    //jambeD
       case 2:
            PotenceVerti();
            PotenceInter();
            PotenceHorizon();
            Corde();
            Tete();
            TroncCorps();
            BrasG();
            BrasD();
            JambeD();
        break;

    //jambeG
        case 1:
            PotenceVerti();
            PotenceInter();
            PotenceHorizon();
            Corde();
            Tete();
            TroncCorps();
            BrasG();
            BrasD();
            JambeD();
            JambeG();
        break;

    //Tout afficher � la fin de partie si on perd :

        case 0:
            PotenceVerti();
            PotenceInter();
            PotenceHorizon();
            Corde();
            Tete();
            TroncCorps();
            BrasG();
            BrasD();
            JambeD();
            JambeG();
        break;
    }

}



int consequenceManche(int cptVie, int lettreEstAjoutee){

    //on enl�ve un pt au compteur de vie si on n'arrive pas � trouver une lettre se trouvant ds le mot mystere
    if(lettreEstAjoutee==0){
          cptVie--;
          //on met � jour le dessin du pendu
    }
      DessinerPendu(cptVie);
    return cptVie;
}

