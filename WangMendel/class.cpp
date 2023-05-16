#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

#include "fuzzy.h"

int main(int argc, char** argv)
{

	if (argc != 2) {
		printf("Formato: ./Classif <Rule_Path> \n");
		return -1;
	}
	
	//Cargar reglas de valores y pasar a vector 2D------------------------------------------------------------
	vector <vector <string>> reglas;		//Variable para almacenar kernel

	reglas = load_csv(argv[1]);
	
	//Valores iniciales y finales
	double XSLmin = 4.3;
	double XSLmax = 7.91;
	double XSWmin = 2.0;
	double XSWmax = 4.41;
	double XPLmin = 1.0;
	double XPLmax = 6.91;
	double XPWmin = 0.1;
	double XPWmax = 2.51;
	
	string sepLen;
	string sepWid;
	string petLen;
	string petWid;
	string clase;
	
	flowSize sepLenRul, sepWidRul, petLenRul, petWidRul;
	
	vector <string> row;
	
	vector <vector <string>> fuz_Rules;
	
	double grado;
	
	//Crear conjuntos e imprimir datos
	cout<<"\nConjunto largo de sépalo: ";
	sepLenRul.newSets(XSLmin, XSLmax, 5, 0.25);
	cout<<"Conjunto ancho de sépalo: ";
	sepWidRul.newSets(XSWmin, XSWmax, 5, 0.25);
	cout<<"Conjunto largo de pétalo: ";
	petLenRul.newSets(XPLmin, XPLmax, 5, 0.25);
	cout<<"Conjunto ancho de pétalo: ";
	petWidRul.newSets(XPWmin, XPWmax, 5, 0.25);
	cout<<endl;
		
	for (int i = 0; i < reglas.size(); ++i)
	{		
		
		//Regresar a 0 los valores de pertenencia a cada conjunto
		sepLenRul.initialize();
		sepWidRul.initialize();
		petLenRul.initialize();
		petWidRul.initialize();
	
		sepLen = reglas[i][0];
		sepWid = reglas[i][1];
		petLen = reglas[i][2];
		petWid = reglas[i][3];
		clase = reglas[i][4];
		
		/*cout<<sepLen<<endl;
		cout<<sepWid<<endl;
		cout<<petLen<<endl;
		cout<<petWid<<endl;*/
		
		//Encontrar los valores de mu para cada uno de los conjuntos
		vector <vector <double>> muSepLen = muSets (sepLenRul.setsVec, stof(sepLen));
		vector <vector <double>> muSepWid = muSets (sepWidRul.setsVec, stof(sepWid));
		vector <vector <double>> muPetLen = muSets (petLenRul.setsVec, stof(petLen));
		vector <vector <double>> muPetWid = muSets (petWidRul.setsVec, stof(petWid));
		
		//El método rulVal brinda nombre y grado a las reglas
		sepLenRul.rulVal(muSepLen, sepLenRul.setsVec);
		sepWidRul.rulVal(muSepWid, sepWidRul.setsVec);
		petLenRul.rulVal(muPetLen, petLenRul.setsVec);
		petWidRul.rulVal(muPetWid, petWidRul.setsVec);
		
		//Grado de pertenencia para cada regla
		grado = sepLenRul.grade * sepWidRul.grade * petLenRul.grade * petWidRul.grade;
		
		row.emplace_back(sepLenRul.name);
		row.emplace_back(sepWidRul.name);
		row.emplace_back(petLenRul.name);
		row.emplace_back(petWidRul.name);
		
		row.emplace_back(to_string(grado));
		
		row.emplace_back(clase);
		
		fuz_Rules.emplace_back(row);
		
		if (fuz_Rules.size() > 1){
		
			for (int j = 0; j < fuz_Rules.size() - 1; ++j) {
				 
				 if (row[0] == fuz_Rules[j][0] && row[1] == fuz_Rules[j][1] &&
				 	row[2] == fuz_Rules[j][2] && row[3] == fuz_Rules[j][3]) {
				 	
				 	if (row[4] > fuz_Rules[j][4]){
						vector <vector <string>>::iterator it = fuz_Rules.begin();
						fuz_Rules.erase(it + j);
				 	}			 	
				 	
				 	if (row[4] <= fuz_Rules[j][4]){
						vector <vector <string>>::iterator it = fuz_Rules.end();
						fuz_Rules.erase(it);
				 	}	
				 }
			}
		}
		
		row.clear();

	}
	
	fstream file;
	file.open("fuz_Rules.csv",ios_base::out);

	for(int i = 0; i < fuz_Rules.size(); ++i)
	{
		file << fuz_Rules[i][0] << "," << fuz_Rules[i][1] << "," << fuz_Rules[i][2] << "," << fuz_Rules[i][3] << "," 
			<< fuz_Rules[i][4] << "," << fuz_Rules[i][5] << endl;
	}

	file.close();
		
	return 0;
}
