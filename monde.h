#pragma once
//#include "avion.h"
class avion;

class monde {

protected:
  std::vector <avion*> listeAvions; //contient la liste des avions présent dans le monde
  int tailleMonde;

public:
  monde(int taille);
  void supprimerAvion(avion* Avion); //methode a utiliser quand un avion a ete touche
  void depassementLimite(avion* Avion);
  int getTailleMonde(){return tailleMonde;};
  int getTailleListe(){return getListe().size();}
  std::vector <avion*> getListe() { return listeAvions; };
  void setTailleMonde(int t) { tailleMonde = t; };
  void setListeAvions(std::vector <avion*> Liste) { listeAvions = Liste; };
  void affichageMonde();
};
