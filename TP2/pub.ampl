set MOYENS; 

/*paramètres*/
param budget >=0;
param prix_unitaire{MOYENS} >=0;
param consommateurs_touches{MOYENS} >=0;
param nb_personnes{MOYENS} >=0;
param qte_min{MOYENS} >=0;

/*variables */
var qte_pub {m in MOYENS} >= qte_min[m];

/*objectif*/
maximize vues : 
	sum {m in MOYENS} qte_pub[m] * prix_unitaire[m];

/*contraintes*/


subject to qte_limitee : 
	sum {m in MOYENS} prix_unitaire[m] * qte_pub[m] <= budget;

subject to personnel_limite : 
	sum {m in MOYENS} nb_personnes[m]* qte_pub[m] <= 100; 



/*valeurs paramètres*/
data; 
param budget:= 1000000;
param : MOYENS : prix_unitaire consommateurs_touches nb_personnes qte_min :=
	TV	20000 1800000 1 10
	Magazines 10000 1000000 3 2
	Radio  2000 250000 1 120;