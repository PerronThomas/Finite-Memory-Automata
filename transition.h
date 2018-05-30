#include <string>
#include "etat.h"

using namespace std;

class Transition{

	public:

	Transition();
	Transition(string nom, Etat& initial, Etat& fin, int lecture);
	~Transition();
	void afficheTransition();
	int actionTransition(char input, int indice, int tour);

//	private:
	string name;
	Etat* etatInitial;
	Etat* etatFinal;
	int read;

};
