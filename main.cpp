#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "transition.h"


using namespace std;

vector<Etat> tabEtat;
vector<Transition> tabTransition;
vector<int> etatStartAlgo;
vector<int> etatEndAlgo;
int tailleMemoireMain;
string memoireInitial;
string input;
int tour = 0;

//////////////////////////////////
///////// AFFICHAGE ALGO /////////
//////////////////////////////////
void affichageAlgo(){
	int i = 0;
	while (i<tabEtat.size()){
	tabEtat[i].afficheEtat();
	i++;
	}
	/*int x = 0;
	while (x<tabTransition.size()){
	tabTransition[x].afficheTransition();
	x++;
	}
	*/
}

////////////////////////////////
///////// CREATION DOT /////////
////////////////////////////////
void creationDot(){
	string nameFile = "algo.dot";
	ofstream fichier("algo.dot", ios::out | ios::trunc);
	if(fichier){
		cout << "Ouverture de " << nameFile << endl;
		fichier << "digraph {" << endl;
//creation des etats
		int indiceEtat = 0;
		while (indiceEtat < tabEtat.size()){
			fichier << tabEtat[indiceEtat].name ;
			if (tabEtat[indiceEtat].write != -1){
			fichier << " [label=\"" << tabEtat[indiceEtat].write << "\"]";
			}
			else{
			fichier << " [label=\" \"]";
			}
			if (tabEtat[indiceEtat].start == true and tabEtat[indiceEtat].end == true ){
			fichier << " [color=pink]" << endl;
			}
			else if (tabEtat[indiceEtat].start == true){
			fichier << " [color=blue]" << endl;
			}
			else if (tabEtat[indiceEtat].end == true){
			fichier << " [color=red]" << endl;
			}
			else{
			fichier << endl;
			}
			indiceEtat++;
		}
//creation des Transitions
		int indiceTransition = 0;
		while (indiceTransition < tabTransition.size()){
			fichier << tabTransition[indiceTransition].etatInitial->name << " -> " << tabTransition[indiceTransition].etatFinal->name;
			if (tabTransition[indiceTransition].read != -1){
				fichier << " [label=\"" << tabTransition[indiceTransition].read << "\"]" << endl;
			}
			else {
				fichier << " [label=\"Epsilon\"]" << endl;
			}
			indiceTransition++;
		}
		fichier << "}";
		fichier.close();
		cout << "Fermeture du fichier : " << nameFile << endl;	
	}
	else{
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	}
	cout << endl;
}

/////////////////////////////////
///////// CREATION ALGO /////////
/////////////////////////////////
void creationAlgo(){
	char caractere;
	string mot;
	int etatLecture = -1;
	int commentaire = 0;
	int motEnd = 0;
	int objetEnd = 0;
	string name;
	bool start = false;
	bool end = false;
	int var=0;
	int write;
	string etatInitial;
	string etatFinal;
	int read;

	string nameFile = "automate.txt";
	ifstream fichier(nameFile.c_str(), ios::in);

	if(fichier){
		cout << "Ouverture de " << nameFile << endl;

		while (fichier.get(caractere)){
//determine le paragraphe
			if (caractere == '/'){
				commentaire = (commentaire + 1)%2;
			}
			else if (caractere == ':'){
				etatLecture++;
				commentaire = 0;
				mot = "";
			}
			else if (caractere == ','){
				motEnd = 1;
			}
			else if (caractere == ';'){
				objetEnd = 1;
			}
			else if (isalnum(caractere) or caractere == '#' or caractere == '-'){
				if (commentaire == 0){
					mot += caractere;
				}
			}
			
//attribution de la taille de la memoire des tokens
			if (etatLecture == 0 and objetEnd == 1){
				tailleMemoireMain = atoi(mot.c_str());
				objetEnd = 0;
				mot = "";
			}
//memoire initial des tokens
			else if (etatLecture == 1 and objetEnd == 1){
				memoireInitial = mot;
				objetEnd = 0;
				mot = "";
			}
//creation des etats de l'algo
			else if (etatLecture == 2 and (motEnd == 1 or objetEnd == 1)){
				switch (var){
					case 0:
					name = mot;
					motEnd = 0;
					mot = "";
					var++;
					break;

					case 1:
					if(mot[0]== 't' or mot[0]== 'T'){
						start = true;
					}
					motEnd = 0;
					mot = "";
					var++;
					break;
	
					case 2:
					if(mot[0]== 't' or mot[0]== 'T'){
						end = true;
					}
					motEnd = 0;
					mot = "";
					var++;
					break;

					case 3:
					write = atoi(mot.c_str());
					Etat * pEtat = new Etat(name,start,end,write);
					Etat etat = *pEtat;
					tabEtat.push_back(etat);
					objetEnd = 0;
					mot = "";
					var = 0;
					start = false;
					end = false;
					break;
				}						
			}

// creation des transition de l'algo
			else if (etatLecture == 3 and (motEnd == 1 or objetEnd == 1)){
				switch (var){
					case 0:
					name = mot;
					motEnd = 0;
					mot = "";
					var++;
					break;

					case 1:
					etatInitial = mot;
					motEnd = 0;
					mot = "";
					var++;
					break;

					case 2:
					etatFinal = mot;
					motEnd = 0;
					mot = "";
					var++;
					break;

					case 3:
					read = atoi(mot.c_str());
					int indiceEtat=0;
					int indiceEtatInitial,indiceEtatFinal;
					while (indiceEtat<tabEtat.size()){
						if (tabEtat[indiceEtat].name == etatInitial){
							indiceEtatInitial=indiceEtat;
						}
						if (tabEtat[indiceEtat].name == etatFinal){
							indiceEtatFinal=indiceEtat;
						}
							indiceEtat++;
					}
					Transition * pTransition = new Transition(name,tabEtat[indiceEtatInitial],tabEtat[indiceEtatFinal],read);
					Transition transition = *pTransition;
					tabTransition.push_back(transition);
					objetEnd = 0;
					mot = "";
					var = 0;
					break;
				}
			}

		}

//fermeture du fichier
		fichier.close();
		cout << "Fermeture du fichier : " << nameFile << endl;	
	}
	else{
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	}
cout << endl;

//ouverture de input.txt
	string nameFile2 = "input.txt";
	ifstream fichier2(nameFile2.c_str(), ios::in);

	if (fichier2){
	cout << "Ouverture de " << nameFile2 << endl;
	while (fichier2.get(caractere)){
		if (caractere == '/'){
			commentaire = (commentaire + 1)%2;
		}

		else if (caractere == ';'){
			input = mot;
			cout << "Input = " << input << endl;
			break;
		}

		else if (isalnum(caractere)){
			if (commentaire == 0){
				mot += caractere;
			}
		}
	}
//fermeture du fichier
	fichier2.close();
		cout << "Fermeture du fichier : " << nameFile2 << endl;	
	}
	else{
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	}
cout << endl;
}

/////////////////////////////////////
///////// VERIFICATION ALGO /////////
/////////////////////////////////////
void verificationAlgo(){
//identification des etats entrants et finaux
	int i = 0;
	while (i<tabEtat.size()){
		if (tabEtat[i].start == true){
			etatStartAlgo.push_back(i);
			//initialisation des tokens dans les etats initiaux
			Token * token = new Token(i,tailleMemoireMain, memoireInitial);
			tabEtat[i].ajoutTokenInitial(token);
		}
		if (tabEtat[i].end == true){
			etatEndAlgo.push_back(i);		
		}
	i++;
	}
//suppression des transitions doublons
	int indiceTransition=0;
	while (indiceTransition<(tabTransition.size()-1)){
		int y = indiceTransition+1;
		while (y<tabTransition.size()){
			if (tabTransition[indiceTransition].etatInitial == tabTransition[y].etatInitial and tabTransition[indiceTransition].etatFinal == tabTransition[y].etatFinal and tabTransition[indiceTransition].read == tabTransition[y].read ){
			tabTransition[y].~Transition();
			}
		y++;
		}
	indiceTransition++;
	}
	cout << endl;
}

///////////////////////////////////////
///////// TRANSITION RECURSIF /////////
///////////////////////////////////////
void recursif(string etatName){
	int indiceEtat=0;
	int indice;
	while (indiceEtat < tabEtat.size()){
		if (tabEtat[indiceEtat].name == etatName){
			indice = indiceEtat;
		}
		indiceEtat++;
	}
	int indiceTransition = 0;
	while (indiceTransition < tabTransition.size()){
		if (etatName == tabTransition[indiceTransition].etatInitial->name){
			int indiceToken = 0;
			while (indiceToken < tabEtat[indice].tabToken.size()){
				int realise = 0;
				realise = tabTransition[indiceTransition].actionTransition(input[tour],indiceToken,tour);
				if (realise != 0){
					recursif(tabTransition[indiceTransition].etatFinal->name);
				}
				indiceToken++;
			}
		}
		indiceTransition++;
	}
}

///////////////////////////////////
///////// RESOLUTION ALGO /////////
///////////////////////////////////
void resolutionAlgo(){
	int algoEnd = 0;
	while (tour < input.size()){
		vector<string> etatAtteint;
		cout << "Tour " << tour << endl;
		int indiceInitial=0;
		while (indiceInitial < etatStartAlgo.size()){
			recursif(tabEtat[etatStartAlgo[indiceInitial]].name);
			indiceInitial++;
		}	
		//fin du tour
		tour++;		
		// suppression des tokens qui n'ont pas bouge
		int indiceEtat = 0;
		while (indiceEtat<tabEtat.size()){
			int indiceToken = 0;
			while (indiceToken < tabEtat[indiceEtat].tabToken.size()){
				if (tabEtat[indiceEtat].tabToken[indiceToken]->nbTour < tour){
					tabEtat[indiceEtat].supprToken(indiceToken);
				}
				indiceToken++;
			}
			indiceEtat++;
		}
		// initialisation des Tokens
		int i = 0;
		while (i<etatStartAlgo.size()){
			Token * token = new Token(i,tailleMemoireMain, memoireInitial,tour);
			tabEtat[etatStartAlgo[i]].ajoutTokenInitial(token);
			i++;
		}
		cout << endl;
		cout << "/////Affichage/////" << endl;
		affichageAlgo();
		cout << endl;
	}
	int indiceEtat=0;
	while (indiceEtat < tabEtat.size()){
		if (tabEtat[indiceEtat].end == true){
			string nameFile = "output.txt";
			ofstream fichier("output.txt", ios::out | ios::app);
			if(fichier){
				int indiceToken=0;
				while (indiceToken < tabEtat[indiceEtat].tabToken.size()){
					fichier << "Etat Final : " << tabEtat[indiceEtat].name << endl;
					fichier << "Token " << tabEtat[indiceEtat].tabToken[indiceToken]->idToken << ", Tour " << tabEtat[indiceEtat].tabToken[indiceToken]->nbTour << " : ";
					int indiceMemoire = 0 ;
					while (indiceMemoire < tabEtat[indiceEtat].tabToken[indiceToken]->tailleMemoire){
						fichier << tabEtat[indiceEtat].tabToken[indiceToken]->memoire[indiceMemoire];
						indiceMemoire++;
					}
					fichier << endl;
					fichier.close();
					indiceToken++;
				}	
			}
			else{
				cerr << "Impossible d'ouvrir le fichier !" << endl;
			}
		}
		indiceEtat++;
	}
}


int main(){

cout << "/////Creation Algo/////" << endl;
creationAlgo();
cout << "/////Creation Dot/////" << endl;
creationDot();
cout << "///// Verif/////" << endl;
verificationAlgo();
cout << "/////Affichage/////" << endl;
affichageAlgo();
cout << "/////Resolution/////" << endl;
resolutionAlgo();
cout << "/////Affichage/////" << endl;
affichageAlgo();

return 0;

}
