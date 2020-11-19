#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED



//Prototypes :
extern void gotoxy(short x, short y);
extern void ChoixMotATrouver(char motATrouver[]);
extern void RemplacCar(int *lettreEstAjoutee, char car,char motATrouver[], char motMystere[]);
extern void AfficherMot(char motMystere[]);
extern void DemanderLettre(char *car);
extern int CondFinDePartie(int,int,char motATrouver[],char motMystere[]);
extern void consequenceManche(int *cptVie,int lettreEstAjoutee);
extern void DessinerPendu(int cptVie,int taillePend, int *ligne, int *hauteur);

//procedures dessins pantin ;
extern void PotenceVerti(int taillePend,int *ligne,int *hauteur);
extern void PotenceInter(int *ligne,int *hauteur);
extern void PotenceHorizon(int taillePend, int *ligne, int *hauteur);
extern void Corde(int taillePend, int *ligne, int *hauteur);
extern void Tete(int *ligne, int *hauteur);
extern void TroncCorps(int taillePend, int *ligne, int *hauteur);
extern void BrasG(int *ligne, int *hauteur);
extern void BrasD(int *ligne, int *hauteur);
extern void JambeD(int *ligne, int *hauteur);


#endif // HEADER_H_INCLUDED
