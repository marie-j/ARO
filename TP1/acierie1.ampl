/* déclaration des variables et leurs contraintes*/
var x1 >=0;
var x2 >=0;

/*objectif */
maximize z : 
	25*x1 + 30*x2;

/*contraintes*/
subject to bandes : 
	x1 <= 6000;
subject to rouleaux : 
	x2 <=4000;
subject to production : 
	(1/200)*x1 + (1/140)*x2 <=40;

solve; 
