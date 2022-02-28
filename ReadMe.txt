Projet Emulateur MIPS - Documentation
ESISAR - 2021 2022
---
Léo VALETTE - Nino MONTOYA
---  


FONCTIONNALITES:

- I - Mode Interactif
    Ligne de commande attendue :
	"./emul-mips"

    Dans ce mode, l'émulateur demande à l'utilisateur de rentrer des lignes de commande une par une et de les valider avec `ENTER`.  
    Pour utiliser l'émulateur il faut entrer la ligne de commande suivante `./emul-mips` sans option  après.  
    Pour quitter le programme il faut entrer la commande `EXIT`.  
    Dans ce mode, toutes les fonctions modifiant le program counter (jumps conditionnels ou non), n'ont aucun effet.

- II - Mode Non-Interactif
    Ligne de commande attendue :
	"./emul-mips entree_1 sortie_hex sortie_reg [OPTIONS]"

    Dans ce mode, l'émulateur prend en entrée un fichier .txt contenant des instructions en langages assembleur MIPS.
    En sortie le programme fournira 2 fichiers qu'il placera dans des dossiers dédiés :
        - Un fichier contenant la traduction du code assembleur en hexa-décimal.
        - Un fichier contenant la valeur des registres à la fin de l'exécution du programme.
    OPTIONS :
    -afficher : Cette option permet d'afficher tout les détails de l'étape de traduction avant de lancer le programme.
    -pas : Cette option permet de passer en mode pas à pas. l'utilisateur doit presser ENTRER pour passer à l'instruction suivante.



SYNTAXE :
    -Les instructions doivent être écrites en majuscule.
Il est possible de :
    -Sauter des lignes
    -Ajouter des espaces entre les différents opérandes
    -Utiliser les noms mnémoniques ou décimaux des registres
    -Ajouter des commentaires avec le symbole '#'


ADDITIONAL FEATURES :
    -Si jamais une ligne de commande est considérée comme incorrecte par le compilateur le programme va simplement ignorer la ligne et passer à la suivante.
    -La fonction SYSCALL (partiellement implémentée) permet d'afficher dans la console des variables de type "int" et "char". Pour savoir comment faire, il faut consulter la doc suivante : https://courses.missouristate.edu/kenvollmar/mars/help/syscallhelp.html*
    Seul les codes 1 et 11 sont fonctionnels.
    
Quelques tests sont fournis afin de tester les principales fonctionnalités de notre application.