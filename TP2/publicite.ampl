set MOYENS;

/*paramètres*/
param budget >= 0;
param consommateurs_touches {MOYENS} >=0;
param prix_unitaire {MOYENS} >=0;
param nb_personnes {MOYENS} >=0, ;
param qte_min {MOYENS} >=0; 


/*variables*/
var qte_publicitaire {m in MOYENS} >= qte_min[m]; 

/*objectif */

maximize vues : 
	sum {m in MOYENS} consommateurs_touches[m] * qte_publicitaire[m];

/*contraintes*/
subject to qte_limitee : 
	sum {m in MOYENS}
		qte_publicitaire * prix_unitaire[m] <= budget;

subject to personne_limitee : 
	sum {m in MOYENS}
		(nb_personnes[m] * qte_publicitaire) <= 100; 




/*valeurs des paramètres*/
data; 
budget := 1000000;
param : MOYENS : prix_unitaire consommateurs_touches qte_min nb_personnes :=
		TV 		20000 180000 10 1
		Radio 2000 250000 120 1
		Magazine 10000 100000 2 3;

