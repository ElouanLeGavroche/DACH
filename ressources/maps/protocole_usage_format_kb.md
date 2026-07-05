# Protocle de rédaction des fichiers KB
*Kb pour kartenn Bed, ou carte du monde en Breton*


Le protocole devra être rédigé lorsque le jeu sera un peu plus avancé, pour le moment voilà comment je vais m'y prendre :

Ce sera un fichier binaire avec la syntaxe décrite ci-dessous.

```kb
[[model_id][pos][texture_id]]\n
[[model_id][pos][texture_id]]\n
[[model_id][pos][texture_id]]\n
[[model_id][pos][texture_id]]\n
``` 

- model_id : dans une en-tête, il y aura le code de chaque model dans un enum.
- pos : position en x,y,z.
- texture_id : l'id de la texture, trouvable elle-aussi via un enum.

Il est impératif de respecter cette structure, en cas d'erreur dans le fichier, le jeu n'aura d'autre choix que de se fermer pour éviter les comportement
indésirable.