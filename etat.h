#include <string>
#include <vector>
#include "token.h"

using namespace std;

class Etat{

	public:

	Etat();
	Etat(string nom, bool debut, bool fin);
	Etat(string nom, bool debut, bool fin, int ecrit);
	Etat(string nom);
	void afficheEtat();
	void afficheNomEtat();
	void afficheIdenToken(Token* jeton);
	void afficheToken();
	int tailleToken();
	int returnWrite();
	void ajoutTokenInitial(Token* jeton);
	int ajoutToken(Token* jeton);
	int ajoutTokenEpsilon(Token* jeton,int tour);
	void supprToken(int indice);

	//private:

	string name;
	bool start;
	bool end;
	vector<Token*> tabToken;
	int write;


};
