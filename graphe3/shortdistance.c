#include <stdio.h>
#include "graphe.h"
#include <stdlib.h>

typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];

void 
graphe2visuPlusCourtsChemins
(tGraphe graphe, char *outfile,tNumeroSommet depart, tNumeroSommet pred[MAX_SOMMETS) {
	strcat(dotfile, ".dot");
	fic = fopen(dotfile, "w");
	if (fic==NULL){
		halt ("Ouverture du fichier %s en  ́ecriture impossible\n", dotfile);
	}
	/*algo d'affichage*/
	

	fclose(fic);
  sprintf(commande, "dot -Tps %s -o %s", dotfile, outfile);
  ret = system(commande);
  if (WEXITSTATUS(ret))
	halt("La commande suivante a  ́echou ́e\n%s\n", commande); 


};

void
plusCourteChaine
(tGraphe graphe,tNumeroSommet s,int d[MAX_SOMMETS],tNomSommet pred[MAX_SOMMETS]) {

	int i,j,voisin;
	tTabCouleurs tab;
	tNumeroSommet x;
	tFileSommets file;

	for (i = 0; i < grapheNbSommets(graphe); ++i)
	{
		if (i != s) {
			tab[i] = BLEU;
		}
	}

	d[s] = 0;
	tab[s] = VERT;
	file = fileSommetsAlloue();
	fileSommetsEnfile(file,s);

	while (!fileSommetsEstVide(file)) {
		x = fileSommetsDefile(file);

		for (j =0 ; j < grapheNbVoisinsSommet(graphe,x); j++) {

			voisin = grapheVoisinSommetNumero(graphe,x,j);
			if (tab[voisin] == BLEU) {
				tab[voisin] = VERT;
				fileSommetsEnfile(file,voisin);
				d[voisin] = d[x] +1;
				grapheRecupNomSommet(graphe,x,pred[voisin]);
			}
		}
		tab[x] = ROUGE;

	}
}

int main(int argc, char *argv[])
{
	tGraphe graphe;
	tNomSommet pred[MAX_SOMMETS];
	int d[MAX_SOMMETS],i,j;

	if (argc <2) {
		halt("wrong input");
	}

	graphe = grapheAlloue();
	grapheChargeFichier(graphe,argv[1]);

	plusCourteChaine(graphe,0,d,pred);

	printf("d :");
	for (i = 0; i < grapheNbSommets(graphe); ++i)
	{
		printf("%d ;",d[i]);
	}
	printf("\n pred :");
	for (j=0; j < grapheNbSommets(graphe); j++) {
		printf("%s ;",pred[j]);
	}

	grapheLibere(graphe);
	exit(EXIT_SUCCESS);
}
