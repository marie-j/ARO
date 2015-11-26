#include <stdio.h>
#include "graphe.h"
#include <stdlib.h>
#include <string.h>
#include "sys/wait.h"


void graphe2visu(tGraphe graphe, char *outfile) {
	FILE *fic;
	char commande[80];
	char dotfile[80];
	int ret,i;
	tArc arc;
	tNomSommet origine,destination;
/* on va cr ́eer un fichier pour graphviz, dans le fichier "outfile".dot */ strcpy(dotfile, outfile);
	strcat(dotfile, ".dot");
	fic = fopen(dotfile, "w");
	if (fic==NULL){
		halt ("Ouverture du fichier %s en  ́ecriture impossible\n", dotfile);
	}

	if (grapheEstOriente(graphe)) {
		fprintf(fic, "digraph {\n");
	}
	else {
		fprintf(fic, "graph { \n");
	}

	for (i = 0; i < grapheNbArcs(graphe); ++i)
	{
		arc = grapheRecupArcNumero(graphe,i);
		grapheRecupNomSommet(graphe,arc.orig,origine);
		grapheRecupNomSommet(graphe,arc.dest,destination);

		if (grapheEstOriente(graphe))
		{
			fprintf(fic, "%s -> %s\n",origine,destination );
		}
		else {
			fprintf(fic, "%s -- %s\n",origine,destination);
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

int
main 
(int argc, char *argv[]) {

	tGraphe graphe; 
	tNomSommet sommet; 
	int i,nb,tmp; 


	if (argc <2) {
		halt("No file specified");
	}

	graphe = grapheAlloue(); 
	nb = 0; 

	grapheChargeFichier(graphe, argv[1]);

	for (i = 0; i < grapheNbSommets(graphe); i++) {

		if ( !grapheNbVoisinsSommet(graphe,i)) {
			grapheRecupNomSommet(graphe,i,sommet);

			printf("%s n'a pas de voisins \n",sommet );
		}
	}

	for(i=0 ; i <grapheNbSommets(graphe);i++) {
		tmp = grapheNbVoisinsSommet(graphe,i);

		if (tmp > nb) {
			nb = tmp;
		}

	}

	for (i=0; i<grapheNbSommets(graphe);i++) {

		if (grapheNbVoisinsSommet(graphe,i) == nb) {

			grapheRecupNomSommet(graphe,i,sommet);

			printf("%s a le nombre maximum soit %d voisins \n",sommet,nb );
		}
		
	}

	grapheLibere(graphe);
	exit(EXIT_SUCCESS);


}
