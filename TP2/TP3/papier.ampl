set P

/*parametres*/
param prix_jour {PROD} >=0;
param p_inf{PROD} >=0;
param p_moy >=0;
param p_sup >=0;

/*variables*/
var nb_jours >=0

/*objectif*/
maximize prod : 
	sum {p in PROD} nb_jours[p] * prix_jour[p];

/*contraintes*/

subject to qte_min : 
	sum {p in PROD} 


/*valeur des paramètres*/
data;
param : PROD : prix_jour p_inf p_moy p_sup 
	A 1000 8 1 2
	B 2000 2 1 7