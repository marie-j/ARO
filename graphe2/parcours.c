#include <stdio.h>
#include "graphe.h"
#include <string.h>
#include <stdlib.h>


/*Couleurs*/
typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];



char* associeCouleurAChaine(tCouleur couleur) {
	switch(couleur) {
		case BLEU : 
			return "blue";

		case VERT :
			return "green";

		case ROUGE :
			return "red";
	}
}

void graphe2visu(tGraphe graphe, char *outfile, tTabCouleurs tabCouleurs) {
	FILE *fic;
	char commande[80];
	char dotfile[80];
	int ret,i,j;
	tArc arc;
	tNomSommet origine,destination,sommet;
/* on va cr ́eer un fichier pour graphviz, dans le fichier "outfile".dot */ strcpy(dotfile, outfile);
	strcat(dotfile, ".dot");
	fic = fopen(dotfile, "w");
	if (fic==NULL){
		halt ("Ouverture du fichier %s en  ́ecriture impossible\n", dotfile);
	}

/*algo d'affichage dans le fichier */

	if (grapheEstOriente(graphe)) {
		fprintf(fic, "digraph {\n");
	}
	else {
		fprintf(fic, "graph { \n");
	}

	for (j =0 ; j <grapheNbSommets(graphe);j++) {
		grapheRecupNomSommet(graphe,j,sommet);
		fprintf(fic, "%s[color=%s];\n",sommet,associeCouleurAChaine(tabCouleurs[j]));
	}

	for (i = 0; i < grapheNbArcs(graphe); ++i)
	{
		arc = grapheRecupArcNumero(graphe,i);
		grapheRecupNomSommet(graphe,arc.orig,origine);
		grapheRecupNomSommet(graphe,arc.dest,destination);

		if (grapheEstOriente(graphe))
		{
			fprintf(fic, "%s -> %s;\n",origine,destination);
		}
		else {
			fprintf(fic, "%s -- %s;\n",origine,destination);
		}
	}

	fprintf(fic, "}");

/*
on parcourt le graphe pour en tirer les informations n ́ecessaires pour graphviz.
Pour  ́ecrire dans le fichier, on utilise 


fprintf (qui s’utilise comme printf mais on mettant en plus fic comme premier param`etre). Ex :
fprintf(fic, "graph {\n");
ou
fprintf(fic, " %s -> %s\n", origine, destination);
  */

  fclose(fic);
  sprintf(commande, "dot -Tps %s -o %s", dotfile, outfile);
  ret = system(commande);
  if (WEXITSTATUS(ret))
	halt("La commande suivante a  ́echou ́e\n%s\n", commande); 
}

void
parcours_largeur(tGraphe graphe,tNumeroSommet s) {
	tTabCouleurs tab;
	int i;
	tFileSommets file;	
	tNumeroSommet tmp;
	for (i = 0; i < grapheNbSommets(graphe); ++i)
	{
		if (i != s) {
			tab[i] = BLEU;
			graphe2visu(graphe,"graphe",tab);
		}	
	}
	file = fileSommetsAlloue();
	tab[s] = VERT;
	graphe2visu(graphe,"graphe",tab);
	fileSommetsEnfile(file,s);
	while (!(fileSommetsEstVide(file))) {
		tmp = fileSommetsDefile(file);
		for (i = 0; i < grapheNbVoisinsSommet(graphe,tmp); ++i)
		{
			int voisin = grapheVoisinSommetNumero(graphe,tmp,i);
			if(tab[voisin] == BLEU) {
				tab[voisin] = VERT;
				graphe2visu(graphe,"graphe",tab);
				fileSommetsEnfile(file,voisin);
			}
		}
		tab[tmp] = ROUGE;
		graphe2visu(graphe,"graphe",tab);
	}

}

int main(int argc, char * argv[])
{
	tGraphe graphe;

	if (argc <2) {
		halt("wrong input");
	}

	graphe = grapheAlloue();
	grapheChargeFichier(graphe,argv[1]);

	parcours_largeur(graphe,0);

	grapheLibere(graphe);
	exit(EXIT_SUCCESS);
}
