#include <iostream>
#include <fstream>
#include <vector>
#include "etat.h"

using namespace std;

//constructeur par defaut
Etat::Etat():name("Defaut"), start(false), end(false), write(-1)
{
	
}

//constructeur Name Start End 
Etat::Etat(string nom, bool debut, bool fin): name(nom), start(debut), end(fin), write(-1)
{
	
}

//constructeur Name Start End Write
Etat::Etat(string nom, bool debut, bool fin, int ecrit): name(nom), start(debut), end(fin), write(ecrit)
{

}

//constructeur Name
Etat::Etat(string nom):name(nom), start(false), end(false), write(-1)
{

}

//Affiche les infos d'un etat 
void Etat::afficheEtat()
{
	cout << "Nom : " << name << endl;
	cout << "Start : " << start << endl;
	cout << "End : " << end << endl;
	if (write != -1){
		cout << "Ecrit dans : " << write << endl;
		}
	afficheToken();
	cout << endl;
}

//Affiche le nom d'un etat
void Etat::afficheNomEtat()
{
	cout << "Nom : " << name << endl;
}

//Affiche l'id d'un token
void Etat::afficheIdenToken(Token* jeton)
{
	Token jetonObjet = *jeton;
	jetonObjet.afficheIdToken();
}

//Affiche la liste des Tokens d'un etat
void Etat::afficheToken()
{
	int i = 0;
	int taille = tabToken.size();
	if (taille == 0){
		cout << "Cet etat ne possede pas de token" << endl;
	}
	else{
		cout << "Liste des "<< taille << " Tokens de "<< name <<" : " << endl;
		while (i<taille){
		tabToken[i]->afficheToken();
		i++;
		}
		cout << endl;
	}

}

//Affiche le nombre de token d'un etat
int Etat::tailleToken(){
	int taille = tabToken.size();
	return taille;
}

//return dans quel case un etat permet l'ecriture
int Etat::returnWrite(){
	int ecrit = write;
	return ecrit;
}

//Ajoute un Token initial a un etat
void Etat::ajoutTokenInitial(Token* jeton)
{
	int indiceToken = 0;
	int vu = 0;
	int taille = tabToken.size();
	while (indiceToken<taille){//compare les tokens
		int indiceMemoire = 0;
		int dif = 0;
		while (indiceMemoire < jeton->tailleMemoire){//compare les memoires des tokens
			if (tabToken[indiceToken]->memoire[indiceMemoire] != jeton->memoire[indiceMemoire]){
			dif=1;//Marque la difference
			}
		indiceMemoire++;
		}
		if (dif == 0 and (jeton->nbTour==tabToken[indiceToken]->nbTour)){//si pas de difference de memoire token existe deja
			vu=1;
			}
	indiceToken++;
	}

	if (vu == 0){
		Token token = *jeton;
		Token * jeton2 = new Token(token.idToken,token.tailleMemoire,token.memoire,token.nbTour);
		tabToken.push_back(jeton2);		
		jeton2 -> ~Token();
		cout << "le token a ete ajoute dans la memoire de " << name << endl;
		}
	else {
		cout << "le token existe deja dans la memoire de " << name << endl;
		}
}

//Ajoute un Token a un etat
int Etat::ajoutToken(Token* jeton)
{
	cout << "Ajout "<< tabToken.size() <<endl;
	int vu = 0;
	int indiceToken = 0;
	while(indiceToken<tabToken.size()){//compare les tokens
		int dif = 0;
		int indiceMemoire = 0;
		while(indiceMemoire < jeton->tailleMemoire){//compare les memoires des tokens
			cout << tabToken[indiceToken]->memoire[indiceMemoire] << "XXX"<< jeton->memoire[indiceMemoire]<<endl;
			if (tabToken[indiceToken]->memoire[indiceMemoire] != jeton->memoire[indiceMemoire]){
				dif=1;//Marque la difference
			}
			indiceMemoire++;
		}
		cout << "dif " << dif << "JT" << jeton->nbTour << "TT" << tabToken[indiceToken]->nbTour <<endl;
		if((dif == 0) and (jeton->nbTour == tabToken[indiceToken]->nbTour-1)){
			//si pas de difference de memoire token existe deja
			vu=1;
		}
		indiceToken++;
	}
	cout <<" vu " << vu <<endl;
	if(vu == 0){
		Token token = *jeton;
		Token * jeton2 = new Token(token.idToken,token.tailleMemoire,token.memoire,token.nbTour);
		jeton2 -> nbTour++;
		jeton2->afficheToken();
		tabToken.push_back(jeton2);		
		jeton2 -> ~Token();
		cout << "le token a ete ajoute dans la memoire de " << name << endl;
		return 1;
	}
	else{
		cout << "le token existe deja dans la memoire de " << name << endl;
		return 0;
	}
}

//Ajoute un Token a un etat via Epsilon Transition
int Etat::ajoutTokenEpsilon(Token* jeton, int tour)
{
	int indiceToken = 0;
	int vu = 0;
	int indiceTokenVu;
	while (indiceToken<tabToken.size()){//compare les tokens
		int indiceMemoire = 0;
		int dif = 0;
		while (indiceMemoire < jeton->tailleMemoire){//compare les memoires des tokens
			if (tabToken[indiceToken]->memoire[indiceMemoire] != jeton->memoire[indiceMemoire]){
				dif=1;//Marque la difference
			}
			indiceMemoire++;
		}
		if (dif == 0){
			//si pas de difference de memoire token existe deja
			vu=1;
			indiceTokenVu = indiceToken;
			}
		indiceToken++;
	}

	if (vu == 0){
		Token token = *jeton;
		Token * jeton2 = new Token(token.idToken,token.tailleMemoire,token.memoire,tour);
		tabToken.push_back(jeton2);
		jeton2 -> ~Token();
		cout << "le token a ete ajoute dans la memoire de " << name << endl;
		return 1;
		}
	else {
		cout << "le token a ete remplace dans la memoire de " << name << endl;
		supprToken(indiceTokenVu);		
		Token token = *jeton;
		Token * jeton2 = new Token(token.idToken,token.tailleMemoire,token.memoire,tour);
		tabToken.push_back(jeton2);		
		jeton2 -> ~Token();
		return 0;
		}
}


//Supprime un Token d'un etat
void Etat::supprToken(int indice)
{
	cout << "Suppression dans " << name << endl;
	if (end == true){
		string nameFile = "output.txt";
		ofstream fichier("output.txt", ios::out | ios::app);
		if(fichier){
			fichier << "Etat Final : " << name << endl;
			fichier << "Token " << tabToken[indice]->idToken << ", Tour " << tabToken[indice]->nbTour << " : ";
			int indiceMemoire = 0 ;
			while (indiceMemoire < tabToken[indice]->tailleMemoire){
				fichier << tabToken[indice]->memoire[indiceMemoire];
				indiceMemoire++;
			}
			fichier << endl;
			fichier.close();	
		}
		else{
			cerr << "Impossible d'ouvrir le fichier !" << endl;
		}

	}
	tabToken.erase(tabToken.begin() + indice);
}
