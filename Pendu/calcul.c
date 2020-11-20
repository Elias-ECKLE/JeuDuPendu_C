#include "header.h"
#include <windows.h> //biblio pr gotoxyd


//Procedures :_________________________________________________


// Fonction qui permet de placer le curseur à la position x,y
//GOTO
void gotoxy(short x, short y)
{
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos={x,y};
	SetConsoleCursorPosition(hConsole,Pos);
}



//___________________________________________________________________________________________________________________________________

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






//DESSIN PENDU :DIFFERENTS PROCEDURE____________________________________________________________________________________________________________
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

