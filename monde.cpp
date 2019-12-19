#include <vector>
#include "monde.h"
#include "avion.h"

using namespace std;


monde::monde(int taille){
  tailleMonde = taille;
  avion* user1 = new avionUser(0,5,0,1,{1,0,0});
  avion* user2 = new avionUser(0,8,0,2,{1,0,0});
  avion* ordi1 = new avionOrdi(13,5,13,1,{-1,0,0});
  avion* ordi2 = new avionOrdi(13,8,13,2,{-1,0,0});
  listeAvions = {user1,user2,ordi1,ordi2};
}

void monde::supprimerAvion(avion* Avion){
  for (int i=0; i<listeAvions.size();i++){
    if (listeAvions[i]==Avion){
      listeAvions.erase (listeAvions.begin()+i);
    }
  }
  // remarque GM: un destructeur ne peut être appelé que par delete 
  Avion->~avion();
}

void monde::depassementLimite(avion* Avion){
  vector<int> vecPos=Avion->getPosition();
  int x= vecPos.back();
  vecPos.pop_back();
  int y= vecPos.back();
  vecPos.pop_back();
  int z= vecPos.back();
  vecPos.pop_back();
  if ((x> tailleMonde || x <0 || y> tailleMonde || y <0 || z> tailleMonde || z <0) && (Avion->getTeam() == "User") )
  {
    this->supprimerAvion(Avion);
  }

}
