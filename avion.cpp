#include <iostream>
#include <algorithm>
#include "avion.h"

using namespace std;

avion::avion(int x, int y, int z, string team, int id){
  position = {x, y, z};
  this->team = team;
  canonCharge = true;
  this->id = id;
}

avionUser::avionUser(int x, int y, int z, string team, int id) : avion(x,y,z,team,id){};

void avionUser::strategy(monde world){
  int nb_zero = 0;
  //On regarde le nombre de zéros
  for(int i=0; i<3; i++){
    if (cap[i]==0) {
      nb_zero+=1;
    }
  }
  //cas 00X
  switch (nb_zero) {
    case 2:
      //la coordonnée non nul reste nul
      {
      vector<int>dir;
      dir.push_back(-1);
      dir.push_back(0);
      dir.push_back(1);
      for(int i=0; i<3; i++){
        int coord = random()%3;
        if (cap[i] != 1){
          cap[i] = dir[coord];
        }
      }
    }
  //cas0XX
      case 1:
      {
      int ajout=random()%4;
      for(int j=0; j<3; j++){
        switch (cap[j]) {
          case 0:
            cap[j]=(random()%3)-1;
            break;
          case 1:
            ajout-=1;
            if (ajout==0){
              cap[j]-=1;
            }
            break;
          case -1:
            ajout-=1;
            if (ajout==0){
              cap[j]+=1;
            }
            break;
      }


      }
    }
      //case XXX
      case 0:
      {
        int a=cap[0],b=cap[1],c=cap[2];
        vector<vector<int> > possibilite {{a,b,c},{a,0,0},{0,b,0},{0,0,c},{a,b,0},{a,0,c},{0,b,c}}; // liste de tous les veteurs possibles
        cap=possibilite[random()%7]; //on en choisit un au hasard

    }
  }
    if (canonCharge){
      shot();
    }

  }

  bool avion::cap_valide(vector<int> nouv_cap){
    int nb_zero = 0;
    //On regarde le nombre de zéros
    for(int i=0; i<3; i++){
      if (cap[i]==0) {
        nb_zero+=1;
      }
    }
    //disjonctionde cas en fonction du nb de zeros
    switch (nb_zero) {
      case 2:
        // cas avec 2 zéros
        //On cherche la seule coordonnée non nul
        {
        for(int i=0; i<3; i++){
          if (cap[i] != 0){
            return(cap[i]==nouv_cap[i]); //cap valide si la seule coordonnée non nul reste constante
          }
        }
        break;
      }


      case 1:
        //cas avec 1 zéros
        {
        int nb_changement=0; //compte le nombre de changement sur les coordonnées non nulles
        for(int i=0; i<3; i++){
          switch (cap[i]) {
            //On cherche les coordonnées non nulles
            case 1:
              if (abs(cap[i]-nouv_cap[i])>1){ // cas de retournement (inclure cstdlib si abs pas reconnu)
              return(false);
            }
            if (abs(cap[i]-nouv_cap[i])==1){ //changement sans retournement
              nb_changement+=1; //on le compte dans les changements
            }
            break;
            case -1:
            if (abs(cap[i]-nouv_cap[i])>1){ // cas de retournement (inclure cstdlib si abs pas reconnu)
              return(false);
            }
            if (abs(cap[i]-nouv_cap[i])==1){ //changement sans retournement
              nb_changement+=1; //on le compte dans les changements
            }
            break;

            }
          }
          return(nb_changement<2);// si on arrive jusqu'ici, on a pas trouvé de retournement donc le changement est valide si et seulement si il y a moins de deux changements.
          break;
        }


        case 0:
        {
          int a=cap[0],b=cap[1],c=cap[2];
          vector<vector<int>> possibilite= {{a,b,c},{a,0,0},{0,b,0},{0,0,c},{a,b,0},{a,0,c},{0,b,c}}; // liste de tous les veteurs possibles
          return(possibilite.end() != find(possibilite.begin(), possibilite.end(), nouv_cap));//include algorithm
          //on retourn vrai si le nouveau cap appartient aux possibilités
        }
  }
}

void avionIA::strategy(monde mondeAvions){
//chercher l'avion le plus proche
  vector<avion*> listeAvions=mondeAvions.getListe();
  int n=mondeAvions.getTailleListe();
  float mindist=100000.0f;
  int avionproche=0;
  for(int i=0;i<n;i++){
    //vérifie si l'avion est pas dans ta team
    if (team!="ordi"){
      float distance=norm(listeAvions[i].getPosition()-position);  //renvoie la distance entre la target et l'IA
      if (distance<mindist){
        mindist=distance;
        avionproche=i;
      }
      //on a notre avion ennemi le plus proche, calculons le cap
    }
  }
  vector <vector<int> > v=vectorvalide();  // pas encore défini
  float minparcours=100000.0f;   //on va regarder quel cap va minimiser la norme
  int mincap;
  for (int i = 0; i < count; i++) {
    float norme = norm(listeAvions[avionproche].getPosition()-(position+v[i]));
    if (norme<minparcours) {
      minparcours=norme;
      mincap=i;    //on a le meilleur cap
    }
  }
  cap=v[mincap];
}

float norm(vector<int> v1, vector<int> v2){
  return(sqrt(pow((v1[0]-v2[0]),2)+pow((v1[1]-v2[1]),2)+pow((v1[2]-v2[2]),2)));
}

vector <vector<int> > avion::vectorvalide(){
  vector v;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      for (int k = -1; k < 2; k++) {   //on regarde TOUS les vecteurs
        vector<int> jm(i,j,k);
        if(cap_valide(jm)){    //si jm est un cap valide pour le mouvement suivant
          v.push_back(jm);
        }
      }
    }
  }
  return(v);
}
//bonne chance pour compiler les gros nazes


ostream& operator<<(ostream& s, avion& avion)
{
  s << "Team : " << avion.getTeam() << ", " << "Avion n°" << avion.getId() << ", " << "Position : " << avion.getPosition()[0] << " " << avion.getPosition()[1] << " " << avion.getPosition()[2];
  return s;
}
