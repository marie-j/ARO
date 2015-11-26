/*ce qu'on cherche à optimiser*/
set PROD;

/*les paramètres {la variable à optimiser} */
param heures_ouvrees >= 0;
param vitesse_production{PROD} >= 0;
param prix_vente {PROD} >=0; 
param vente_max {PROD} >=0; 
param vente_min {PROD} >=0;

/*declaration des variables et leur conditions */
var qte_produite {p in PROD} >=0, <=vente_max[p];

/*objectif  : somme des éléments contenus dans prod */
maximize profit : 
	sum {p in PROD} qte_produite[p] * prix_vente[p];

/*contraintes*/
subject to production_limitee : 
	sum {p in PROD}
		(qte_produite[p]/vitesse_production[p]) <= heures_ouvrees;

data;

/*définition de la production*/ 
set PROD := bandes rouleaux poutres ;

/*ajustement des paramètres*/
param heures_ouvrees:= 40;
param : vitesse_production prix_vente vente_max :=
bandes	200		25	6000
rouleaux 140 30 4000
poutres 160 29 3500;
