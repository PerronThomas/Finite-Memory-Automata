#include <iostream>
#include "token.h"


using namespace std;

// constructeur par defaut
Token::Token():idToken(0)
{
	int i = 0;
	while (i<2){
	memoire[i]= '#';
	i++;
	}
	nbTour=0;
}

//constructeur Id
Token::Token(int id):idToken(id)
{
	int i = 0;
	while (i<2){
	memoire[i]= '#';
	i++;
	}
	nbTour=0;
}

//constructeur Id Taille de la memoire et Memoire initial
Token::Token(int id,int taille,string memoireInitial):idToken(id),tailleMemoire(taille), memoire(new char[taille])
{
	int i = 0;
	while (i<tailleMemoire){
	memoire[i]= memoireInitial[i];
	i++;
	}
	nbTour=0;
}

//constructeur Id Taille de la memoire , Memoire initial et tour
Token::Token(int id,int taille,string memoireInitial,int tour):idToken(id),tailleMemoire(taille), memoire(new char[taille]),nbTour(tour)
{
	int i = 0;
	while (i<tailleMemoire){
	memoire[i]= memoireInitial[i];
	i++;
	}
}


//Destructeur
Token::~Token()
{

}

//Affiche les infos d'un token
void Token::afficheToken()
{
	cout << "Id : " << idToken << endl;
	cout << "Tour : " << nbTour << endl;
	int i = 0;
	cout << "Memoire : ";
	while (i<tailleMemoire){
	cout << memoire[i];
	i++;
	}
	cout << endl;

}

//Affiche Id 
void Token::afficheIdToken()
{
	cout << "Id : " << idToken << endl;

}

//Modifi la memoire d'un token
int Token::modifMemoire(int idMemoire,char lettre)
{
	int i = 0;
	int vu = 0;
	while (i<tailleMemoire){
		if (memoire[i] == lettre){
		vu = 1;
		}
	i++;
	}
	if (vu == 0){
		memoire[idMemoire] = lettre;
		return 0;
		}
	else {
		cout << "la valeur existe deja dans la memoire" << endl;
		return 1;
		}
}
