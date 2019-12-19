#include <iostream>
#include <vector>
#include <string>
#include "monde.h"

class monde;

class avion {

protected:
  std::vector<int> position;
  std::vector<int> cap;
  bool canonCharge;
  std::string team;
  std::vector<int> attitude; // roulis tangage lacet
  int id; // 1 ou 2 pour identifier l'avion dans l'équipe

public:
  // Constructeur
  avion(int x, int y, int z, std::string team, int id);

  // accesseurs
  std::vector<int> getPosition(){return position;};
  std::vector<int> getCap(){return cap;};
  bool getCanonCharge(){return canonCharge;};
  std::string getTeam(){return team;};
  int getId(){return id;};

  // Mutateurs
  void setPosition(std::vector<int> position){this->position = position;};
  void setCap(std::vector<int> cap){this->cap = cap;};
  void setAttitude(std::vector<int> attitude){this->attitude = attitude;};
  void setCanonCharge(bool canonCharge){this->canonCharge = canonCharge;};

  //mouvement & FEUUU !
  void avancer(); // change la position : nouvelle_position = ancienne_position + cap
  virtual void strategy(monde world)=0; // Permet de modifier le cap (2 méthodes différentes si l'avion est controlé par l'ordi ou l'utilisateur)
  bool shot(); // renvoie 1 si  a tiré sur un ennemi
               // dans ce cas il faut destroy l'avion visé et le supprimer de la liste des avion du monde
  bool cap_valide(std::vector<int> nouv_cap);
  std::vector <std::vector<int>> vectorvalide();

  // Destructeur
  ~avion(){};
};

// operateurs
std::ostream& operator<<(std::ostream& s, avion& avion);

class avionUser : public avion {
public:
  avionUser(int x, int y, int z, std::string team, int id);
  void strategy(monde);
};

class avionIA : public avion {
  avionIA(int x, int y, int z, std::string team, int id);
  void strategy(monde);
};

float norm(std::vector<int>, std::vector<int>);
