#include <iostream>
#include "transition.h"


using namespace std;

//Constructeur par defaut
Transition::Transition():name("Defaut"), read(-1)
{

}

//Constructeur Name EtatInitial EtatFinal Read
Transition::Transition(string nom, Etat& initial, Etat& fin,int lecture):name(nom), read(lecture)
{
	etatInitial = &initial;
	etatFinal = &fin;
}

//Destructeur
Transition::~Transition(){

}

//Affiche les infos d'une transition
void Transition::afficheTransition()
{
    cout << "Nom : " << name << endl;
	cout << "Etat Initial : ";
	etatInitial -> afficheNomEtat();
	cout << "Etat Final : ";
	etatFinal -> afficheNomEtat();
	if (read != -1){
		cout << "Lecture en Case : " << read << endl;
		}
	else{
		cout << "Epsilon Transition " << endl;
	}
	cout << endl;
}

//Effectue la transition
int Transition::actionTransition(char input,int indice,int tour)
{
	cout << "Debut de la transition : " << name << endl;
	Token * token = new Token (etatInitial -> tabToken[indice] -> idToken,etatInitial -> tabToken[indice] -> tailleMemoire,etatInitial -> tabToken[indice] -> memoire,etatInitial -> tabToken[indice] -> nbTour);
	if (token->nbTour == tour){
		int etatWrite = etatInitial -> returnWrite();
		char transitionRead = token -> memoire[read];
		if (read == -1){
			return etatFinal -> ajoutTokenEpsilon(token,tour);
		}
		else if (transitionRead == input){
			return etatFinal -> ajoutToken(token);
		}
		else if (read == etatWrite){// modifie les tokens de etat ini et les rajoute a etat final
		///// Modifier modifMemoire //////
			int change = token -> modifMemoire(read,input);
			if (change == 0){
				return etatFinal -> ajoutToken(token);	
			}
			else {
				return 0;
			}
		}
		else {// transition fail
			cout << "transition fail" << endl;
			return 0;
		}
	}
	else {// transition fail
		cout << "transition fail" << endl;
		return 0;
	}
}
