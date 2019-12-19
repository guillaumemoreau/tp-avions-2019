#include <iostream>
#include "avion.h"
#include "monde.h"

using namespace std;

int main()
{
  int x = 0;
  int y = 0;
  int z = 0;
  string team = "User";
  int id = 1;
  avionUser myAvion(x,y,z, team, id);

  cout << myAvion << endl;

  return 0;
}
