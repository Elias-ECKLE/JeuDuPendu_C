
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
#define TAILLE 25 //valeur pour les tableaux de caractères : motMYSTERE et MotATrouver



//Prototypes :
void gotoxy(short x, short y);
void ChoixMotATrouver(char motATrouver[]);
void RemplacCar(int *lettreEstAjoutee, char car,char motATrouver[], char motMystere[]);
void AfficherMot(char motMystere[]);
void DemanderLettre(char *car);
int CondFinDePartie(int,int,char motATrouver[],char motMystere[]);
void consequenceManche(int *cptVie,int lettreEstAjoutee);
void DessinerPendu(int cptVie,int taillePend, int *ligne, int *hauteur);

//procedures dessins pantin ;
void PotenceVerti(int taillePend,int *ligne,int *hauteur);
void PotenceInter(int *ligne,int *hauteur);
void PotenceHorizon(int taillePend, int *ligne, int *hauteur);
void Corde(int taillePend, int *ligne, int *hauteur);
void Tete(int *ligne, int *hauteur);
void TroncCorps(int taillePend, int *ligne, int *hauteur);
void BrasG(int *ligne, int *hauteur);
void BrasD(int *ligne, int *hauteur);
void JambeD(int *ligne, int *hauteur);


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



    //init :
    printf("Bienvenue dans le jeu du pendu :\n");
    ChoixMotATrouver(motATrouver); //on demande au joueur de choisir un mot en début de partie
    //init du mot mystère avec des tirets
    RemplacCar(&lettreEstAjoutee,car,motATrouver,motMystere);
    AfficherMot(motMystere);



    //jeu : Afficher et demander une lettre
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





//Procedures :_________________________________________________

// Fonction qui permet de placer le curseur à la position x,y
//GOTO
void gotoxy(short x, short y)
{
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos={x,y};
	SetConsoleCursorPosition(hConsole,Pos);
}


void ChoixMotATrouver(char motATrouver[]){
//BUT:Choisir en début de partie le mot mystère
//ENTREE:tableau de caractères
//SORTIE:tableau de caractères

    printf("Afin de commencer une partie, veuillez entrer un mot\n");
    scanf("%s",motATrouver);

}


void DemanderLettre(char *car){
//BUT:Demander au joueur d'entrer un caractère
//ENTREE:rien
//SORTIE:caractere

    char lettre=' ';
    printf("Veuillez entrer un caractere : \n");
    getchar();
    scanf("%c",&lettre);
    *car=lettre;
}



void RemplacCar(int *lettreEstAjoutee, char car, char motATrouver[],char motMystere[]){
//BUT:Remplacer les caractère du motATrouver par soit des underscore en début de partie, soit des lettres le reste du jeu
//ENTREE:le mot a trouver, le caractère que l'on veut mettre, le mot mystère
//SORTIE:Le mot mystere

    int i=0;
    *lettreEstAjoutee=0;

    if (car=='-'){ // si c'est l'underscore c'est pour init la chaine
        for(i=0;i<strlen(motATrouver);i++){
            motMystere[i]=car;
        }
    }
    else{
        for(i=0;i<strlen(motATrouver);i++){
            if(motATrouver[i]==car){
                motMystere[i]=car;
                *lettreEstAjoutee=1;
            }
        }
    }
}


void AfficherMot(char motMystere[]){
//BUT:Afficher l'état du motmystère
//ENTREE:motmystere
//SORTIE:rien

    system("cls");
    printf("%s\n",motMystere);

}


int CondFinDePartie(int cptVie,int lettreEstAjoutee,char motATrouver[], char motMystere[]){

     gotoxy(1,15);
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






//DESSIN PENDU :DIFFERENTS PROCEDURE
void PotenceVerti(int taillePend,int *ligne,int *hauteur){
    int i;
    *hauteur=1;
    *ligne=1;
    for(i=0;i<taillePend;i++){
        *hauteur=*hauteur+1;
        gotoxy(*ligne,*hauteur);
        printf("|");
    }
}

void PotenceInter(int *ligne,int *hauteur){
    *hauteur=1;
    *ligne=1;
    *ligne=*ligne+1;
    *hauteur=*hauteur+1;
    gotoxy(*ligne,*hauteur);
    printf("/");
}

void PotenceHorizon(int taillePend, int *ligne, int *hauteur){
    *hauteur=1;
    *ligne=1;
    int i;
    int taillePendDouble=taillePend*2;
    for (i=0;i<taillePendDouble-2;i++){
        *ligne=*ligne+1;
        gotoxy(*ligne,*hauteur);
        printf("-");
    }
}
void Corde(int taillePend, int *ligne, int *hauteur){
    int i;
    for (i=0;i<(taillePend/4);i++){
        *hauteur=*hauteur+1;
        gotoxy(*ligne,*hauteur);
        printf("|");
    }
}
void Tete(int *ligne, int *hauteur){

    //g a d
    *hauteur=*hauteur+1;
    gotoxy(*ligne,*hauteur);
    printf("-");
    // h vers b
    *hauteur=*hauteur+1;
    *ligne=*ligne+1;
    gotoxy(*ligne, *hauteur);
    printf("|");
    //d vers g
    *hauteur=*hauteur+1;
    *ligne=*ligne-1;
    gotoxy(*ligne,*hauteur);
    printf("-");
    //b vers h
    *ligne=*ligne-1;
    *hauteur=*hauteur-1;
    gotoxy(*ligne,*hauteur);
    printf("|");
}

void TroncCorps(int taillePend, int *ligne, int *hauteur){
    int i;
    *hauteur=*hauteur+1;
    *ligne=*ligne+1;
    for (i=0;i<taillePend-8;i++){
        *hauteur=*hauteur+1;
        gotoxy(*ligne,*hauteur);
        printf("|");
    }
}

void BrasG(int *ligne, int *hauteur){
    *ligne=*ligne-1;
    *ligne=*ligne-1;
     gotoxy(*ligne,*hauteur);
     printf("/");
}
void BrasD(int *ligne, int *hauteur){
    *ligne=*ligne+4;
    gotoxy(*ligne,*hauteur);
    printf("\\");
}
void JambeD(int *ligne, int *hauteur){
    *hauteur=*hauteur+2;
    gotoxy(*ligne, *hauteur);
    printf("\\");
}
void JambeG(int *ligne, int *hauteur){
    *ligne=*ligne-1;
    gotoxy(*ligne, *hauteur);
    write("/");
}


void DessinerPendu(int cptVie,int taillePend, int *ligne, int *hauteur){

    int i;
    switch(cptVie){

    //potence verti :
        case 10:
            PotenceVerti(taillePend,&*ligne,&*hauteur);
        break;

    //potence Inter
        case 9:
            PotenceVerti(taillePend,&*ligne,&*hauteur);
            PotenceInter(&*ligne,&*hauteur);
        break;

    //potence horizontale :
        case 8:
            PotenceVerti(taillePend,&*ligne,&*hauteur);
            PotenceInter(&*ligne,&*hauteur);
            PotenceHorizon(taillePend,&*ligne,&*hauteur);
        break;
    //Corde
        case 7:
            PotenceVerti(taillePend,&*ligne,&*hauteur);
            PotenceInter(&*ligne,&*hauteur);
            PotenceHorizon(taillePend,&*ligne,&*hauteur);
            Corde(taillePend,&*ligne,&*hauteur);
        break;

    //tete

       case 6:
            PotenceVerti(taillePend,&*ligne,&*hauteur);
            PotenceInter(&*ligne,&*hauteur);
            PotenceHorizon(taillePend,&*ligne,&*hauteur);
            Corde(taillePend,&*ligne,&*hauteur);
            Tete(&*ligne,&*hauteur);
        break;

    //troncCorps
       case 5:
            PotenceVerti(taillePend,&*ligne,&*hauteur);
            PotenceInter(&*ligne,&*hauteur);
            PotenceHorizon(taillePend,&*ligne,&*hauteur);
            Corde(taillePend,&*ligne,&*hauteur);
            Tete(&*ligne,&*hauteur);
            TroncCorps(taillePend,&*ligne,&*hauteur);
        break;

    //brasG
        case 4:
            PotenceVerti(taillePend,&*ligne,&*hauteur);
            PotenceInter(&*ligne,&*hauteur);
            PotenceHorizon(taillePend,&*ligne,&*hauteur);
            Corde(taillePend,&*ligne,&*hauteur);
            Tete(&*ligne,&*hauteur);
            TroncCorps(taillePend,&*ligne,&*hauteur);
            BrasG(&*ligne,&*hauteur);
        break;

    //brasD
        case 3:
            PotenceVerti(taillePend,&*ligne,&*hauteur);
            PotenceInter(&*ligne,&*hauteur);
            PotenceHorizon(taillePend,&*ligne,&*hauteur);
            Corde(taillePend,&*ligne,&*hauteur);
            Tete(&*ligne,&*hauteur);
            TroncCorps(taillePend,&*ligne,&*hauteur);
            BrasG(&*ligne,&*hauteur);
            BrasD(&*ligne,&*hauteur);
        break;

    //jambeD
       case 2:
            PotenceVerti(taillePend,&*ligne,&*hauteur);
            PotenceInter(&*ligne,&*hauteur);
            PotenceHorizon(taillePend,&*ligne,&*hauteur);
            Corde(taillePend,&*ligne,&*hauteur);
            Tete(&*ligne,&*hauteur);
            TroncCorps(taillePend,&*ligne,&*hauteur);
            BrasG(&*ligne,&*hauteur);
            BrasD(&*ligne,&*hauteur);
            JambeD(&*ligne,&*hauteur);
        break;

    //jambeG
        case 1:
            PotenceVerti(taillePend,&*ligne,&*hauteur);
            PotenceInter(&*ligne,&*hauteur);
            PotenceHorizon(taillePend,&*ligne,&*hauteur);
            Corde(taillePend,&*ligne,&*hauteur);
            Tete(&*ligne,&*hauteur);
            TroncCorps(taillePend,&*ligne,&*hauteur);
            BrasG(&*ligne,&*hauteur);
            BrasD(&*ligne,&*hauteur);
            JambeD(&*ligne,&*hauteur);
            JambeG(&*ligne,&*hauteur);
        break;

    //Tout afficher à la fin de partie si on perd :

        case 0:
            PotenceVerti(taillePend,&*ligne,&*hauteur);
            PotenceInter(&*ligne,&*hauteur);
            PotenceHorizon(taillePend,&*ligne,&*hauteur);
            Corde(taillePend,&*ligne,&*hauteur);
            Tete(&*ligne,&*hauteur);
            TroncCorps(taillePend,&*ligne,&*hauteur);
            BrasG(&*ligne,&*hauteur);
            BrasD(&*ligne,&*hauteur);
            JambeD(&*ligne,&*hauteur);
            JambeG(&*ligne,&*hauteur);

        break;
    }

}



void consequenceManche(int *cptVie, int lettreEstAjoutee){

    //on enlève un pt au compteur de vie si on n'arrive pas à trouver une lettre se trouvant ds le mot mystere
    if(lettreEstAjoutee==0){
          *cptVie=*cptVie-1;

    }

}

