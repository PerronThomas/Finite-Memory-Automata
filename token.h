#include <string>
#include <iostream>

using namespace std;

class Token{

	public:

	Token();
	Token(int id);
	Token(int id,int taille,string memoireInitial);
	Token(int id,int taille,string memoireInitial,int tour);
	~Token();
	void afficheToken();
	void afficheIdToken();
	void addMemoire(char caractere);
	int modifMemoire(int idMemoire,char lettre);

	//private:
	int idToken;
	int tailleMemoire;
	int nbTour;
	char* memoire;//tableau 


};
