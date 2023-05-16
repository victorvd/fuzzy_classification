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

	if (argc != 3) {
		printf("Formato: ./Classif <List_Path> <T_norm>\n");
		return -1;
	}
	
	//Cargar lista de valores y pasar a vector 2D------------------------------------------------------------
	vector <vector <double>> lista;		//Variable para almacenar kernel
	lista = load_csv(argv[1]);
	
	string st_norm = argv[2];
	
	//Valores iniciales y finales
	double XSLmin = 4.3;
	double XSLmax = 7.91;
	double XSWmin = 2.0;
	double XSWmax = 4.41;
	double XPLmin = 1.0;
	double XPLmax = 6.91;
	double XPWmin = 0.1;
	double XPWmax = 2.51;
	
	double sepLen;
	double sepWid;
	double petLen;
	double petWid;
	
	flowSize sepLenRul, sepWidRul, petLenRul, petWidRul;
	
	//Crear e imprimir datos de entrada
	cout<<"\nConjunto largo de sépalo: ";
	sepLenRul.newSets(XSLmin, XSLmax, 5, 0.25);
	cout<<"Conjunto ancho de sépalo: ";
	sepWidRul.newSets(XSWmin, XSWmax, 5, 0.25);
	cout<<"Conjunto largo de pétalo: ";
	petLenRul.newSets(XPLmin, XPLmax, 5, 0.25);
	cout<<"Conjunto ancho de pétalo: ";
	petWidRul.newSets(XPWmin, XPWmax, 5, 0.25);
	cout<<endl;
		
	for (int j = 0; j < lista.size(); j++)
	{		
		flowClass tipFlor;
		
		sepLenRul.initialize();
		sepWidRul.initialize();
		petLenRul.initialize();
		petWidRul.initialize();
	
		sepLen = lista[j][0];
		sepWid = lista[j][1];
		petLen = lista[j][2];
		petWid = lista[j][3];
		
		/*cout<<sepLen<<endl;
		cout<<sepWid<<endl;
		cout<<petLen<<endl;
		cout<<petWid<<endl;*/
		
		//Encontrar los valores de mu para cada uno de los conjuntos
		vector <vector <double>> muSepLen = muSets (sepLenRul.setsVec, sepLen);
		vector <vector <double>> muSepWid = muSets (sepWidRul.setsVec, sepWid);
		vector <vector <double>> muPetLen = muSets (petLenRul.setsVec, petLen);
		vector <vector <double>> muPetWid = muSets (petWidRul.setsVec, petWid);
		
		sepLenRul.rulVal(muSepLen, sepLenRul.setsVec);
		
		sepWidRul.rulVal(muSepWid, sepWidRul.setsVec);
		
		petLenRul.rulVal(muPetLen, petLenRul.setsVec);
	
		petWidRul.rulVal(muPetWid, petWidRul.setsVec);
		
		// Fuzzy Rules
		ruleApply (sepLenRul.vsmall, sepWidRul.small, petLenRul.vsmall, petWidRul.vsmall,
				tipFlor, "Iris-setosa", st_norm, j);

		ruleApply (sepLenRul.vsmall, sepWidRul.medium, petLenRul.vsmall, petWidRul.vsmall,
				tipFlor, "Iris-setosa", st_norm, j);

		ruleApply (sepLenRul.vsmall, sepWidRul.vsmall, petLenRul.vsmall, petWidRul.vsmall,
				tipFlor, "Iris-setosa", st_norm, j);

		ruleApply (sepLenRul.vsmall, sepWidRul.large, petLenRul.vsmall, petWidRul.vsmall,
				tipFlor, "Iris-setosa", st_norm, j);

		ruleApply (sepLenRul.small, sepWidRul.large, petLenRul.vsmall, petWidRul.vsmall,
				tipFlor, "Iris-setosa", st_norm, j);

		ruleApply (sepLenRul.small, sepWidRul.medium, petLenRul.vsmall, petWidRul.vsmall,
				tipFlor, "Iris-setosa", st_norm, j);

		ruleApply (sepLenRul.small, sepWidRul.vlarge, petLenRul.vsmall, petWidRul.vsmall,
				tipFlor, "Iris-setosa", st_norm, j);

		ruleApply (sepLenRul.vsmall, sepWidRul.vsmall, petLenRul.small, petWidRul.small,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.small, sepWidRul.small, petLenRul.medium, petWidRul.medium,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.small, sepWidRul.vsmall, petLenRul.medium, petWidRul.medium,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.small, sepWidRul.vsmall, petLenRul.medium, petWidRul.small,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.small, sepWidRul.small, petLenRul.small, petWidRul.small,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.small, sepWidRul.small, petLenRul.medium, petWidRul.small,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.medium, sepWidRul.small, petLenRul.medium, petWidRul.medium,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.medium, sepWidRul.medium, petLenRul.large, petWidRul.large,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.medium, sepWidRul.vsmall, petLenRul.medium, petWidRul.small,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.medium, sepWidRul.medium, petLenRul.medium, petWidRul.large,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.medium, sepWidRul.small, petLenRul.large, petWidRul.medium,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.medium, sepWidRul.vsmall, petLenRul.medium, petWidRul.medium,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.medium, sepWidRul.medium, petLenRul.medium, petWidRul.medium,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.large, sepWidRul.small, petLenRul.medium, petWidRul.medium,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.large, sepWidRul.medium, petLenRul.medium, petWidRul.medium,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.large, sepWidRul.small, petLenRul.large, petWidRul.large,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.large, sepWidRul.medium, petLenRul.large, petWidRul.medium,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.large, sepWidRul.small, petLenRul.large, petWidRul.medium,
				tipFlor, "Iris-versicolor", st_norm, j);

		ruleApply (sepLenRul.vsmall, sepWidRul.vsmall, petLenRul.medium, petWidRul.large,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.small, sepWidRul.small, petLenRul.large, petWidRul.large,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.small, sepWidRul.vsmall, petLenRul.large, petWidRul.large,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.small, sepWidRul.small, petLenRul.large, petWidRul.vlarge,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.medium, sepWidRul.small, petLenRul.large, petWidRul.large,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.medium, sepWidRul.vsmall, petLenRul.large, petWidRul.medium,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.medium, sepWidRul.medium, petLenRul.large, petWidRul.vlarge,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.medium, sepWidRul.medium, petLenRul.vlarge, petWidRul.vlarge,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.medium, sepWidRul.vsmall, petLenRul.large, petWidRul.large,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.medium, sepWidRul.small, petLenRul.large, petWidRul.vlarge,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.medium, sepWidRul.small, petLenRul.vlarge, petWidRul.vlarge,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.large, sepWidRul.vsmall, petLenRul.vlarge, petWidRul.large,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.large, sepWidRul.medium, petLenRul.large, petWidRul.vlarge,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.large, sepWidRul.small, petLenRul.large, petWidRul.vlarge,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.large, sepWidRul.medium, petLenRul.vlarge, petWidRul.vlarge,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.large, sepWidRul.small, petLenRul.vlarge, petWidRul.vlarge,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.large, sepWidRul.large, petLenRul.vlarge, petWidRul.vlarge,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.large, sepWidRul.medium, petLenRul.vlarge, petWidRul.large,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.large, sepWidRul.small, petLenRul.vlarge, petWidRul.large,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.vlarge, sepWidRul.small, petLenRul.vlarge, petWidRul.large,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.vlarge, sepWidRul.small, petLenRul.vlarge, petWidRul.vlarge,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.vlarge, sepWidRul.large, petLenRul.vlarge, petWidRul.vlarge,
				tipFlor, "Iris-virginica", st_norm, j);

		ruleApply (sepLenRul.vlarge, sepWidRul.large, petLenRul.vlarge, petWidRul.large,
				tipFlor, "Iris-virginica", st_norm, j);
		/*else
			cout<<"No es posible clasificar."<<endl;*/
			
		tipFlor.gralRule();
		
		cout<<j<<":  "<<tipFlor.resultado<<"  "<<tipFlor.classification<<endl;

	}
		
	return 0;
}
