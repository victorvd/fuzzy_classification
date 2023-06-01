//#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#include "fuzzy.h"

struct ageSets {
	double ninez = 0;
	double adoles = 0;
	double juven = 0;
	double adult = 0;
	double vejez = 0;
};

struct weightSets {
	double bajo = 0;
	double medio = 0;
	double alto = 0;
};

int main(int argc, char** argv)
{	
	/*clock_t start, end;
	start = clock();*/
	
	if (argc != 3) {
		printf("Formato: ./Fuzzy <Age value> <Weight value>\n");
		return -1;
	}
	
	double age = atof(argv [1]);
	double weight = atof(argv [2]);
	
	vector <double> XA(10);
	vector <double> XW(6);
	vector <double> XAn(10);
	
	double XAmin = 0;
	double XAmax = 75;
	double XWmin = 0;
	double XWmax = 120;
	double XAnmin = 0;
	double XAnmax = 17.5;
	
	//Imprimir datos de entrada
	cout<<"\nConjunto Edad: ";
	XA = sets(XAmin, XAmax, 5, 0.25);
	cout<<"Conjunto Peso: ";
	XW = sets(XWmin, XWmax, 3, 0.25);
	cout<<"Conjunto Anemia: ";
	XAn = sets(XAnmin, XAnmax, 5, 0.25);
	cout<<endl;
	
	cout<<"Variable de entrada Edad: "<<age<<endl;
	cout<<"Variable de entrada Peso: "<<weight<<"\n"<<endl;
	
	vector <vector <double>> muAge = muSets (XA, age);
	vector <vector <double>> muWeight = muSets (XW, weight);
	
	ageSets ageRul;
	weightSets weightRul;
	anemiaSets anemiaRul;
	
	for (int i = 0; i < muAge.size(); ++i) {
		if (muAge[i][0] == XA[0] && muAge[i][1] == XA[1]) {
			ageRul.ninez = muAge[i][2];
			cout<<"Edad: Niñez"<<endl;
		}
		if (muAge[i][0] == XA[2] && muAge[i][1] == XA[3]) {
			ageRul.adoles = muAge[i][2];
			cout<<"Edad: Adolescencia"<<endl;
		}
		if (muAge[i][0] == XA[4] && muAge[i][1] == XA[5]) {
			ageRul.juven = muAge[i][2];
			cout<<"Edad: Juventud"<<endl;
		}
		if (muAge[i][0] == XA[6] && muAge[i][1] == XA[7]) {
			ageRul.adult = muAge[i][2];
			cout<<"Edad: Adultez"<<endl;
		}
		if (muAge[i][0] == XA[8] && muAge[i][1] == XA[9]) {
			ageRul.vejez = muAge[i][2];
			cout<<"Edad: Vejez"<<endl;
		}
		
		cout<<" Amin: "<<muAge[i][0]<<endl;
		cout<<" Amax: "<<muAge[i][1]<<endl;
		cout<<" mu_age: "<<muAge[i][2]<<endl;
	}
	
	for (int i = 0; i < muWeight.size(); ++i) {
		if (muWeight[i][0] == XW[0] && muWeight[i][1] == XW[1]) {
			weightRul.bajo = muWeight[i][2];
			cout<<"Peso: Bajo"<<endl;
		}
		if (muWeight[i][0] == XW[2] && muWeight[i][1] == XW[3]) {
			weightRul.medio = muWeight[i][2];
			cout<<"Peso: Medio"<<endl;
		}
		if (muWeight[i][0] == XW[4] && muWeight[i][1] == XW[5]) {
			weightRul.alto = muWeight[i][2];
			cout<<"Peso: Alto"<<endl;
		}
		cout<<" Wmin: "<<muWeight[i][0]<<endl;
		cout<<" Wmax: "<<muWeight[i][1]<<endl;
		cout<<" mu_weigh: "<<muWeight[i][2]<<endl;
	}
	
	// Fuzzy Rules
	if (ageRul.ninez && weightRul.bajo) {
		xoutVector(anemiaRul.normal, ageRul.ninez, weightRul.bajo, XAn[6], XAn[7]);
		printSet("Niñez", "Bajo", "Normal", anemiaRul.normal);
	}
	if (ageRul.adoles && weightRul.bajo) {
		xoutVector(anemiaRul.leve, ageRul.adoles, weightRul.bajo, XAn[4], XAn[5]);
		printSet("Adolescencia", "Bajo", "Anemia leve", anemiaRul.leve);
	}
	if (ageRul.juven && weightRul.bajo) {
		xoutVector(anemiaRul.moderada, ageRul.juven, weightRul.bajo, XAn[2], XAn[3]);
		printSet("Juventud", "Bajo", "Anemia moderada", anemiaRul.moderada);
	}
	if (ageRul.adult && weightRul.bajo) {
		xoutVector(anemiaRul.severa, ageRul.adult, weightRul.bajo, XAn[0], XAn[1]);
		printSet("Adultez", "Bajo", "Anemia severa", anemiaRul.severa);
	}
	if (ageRul.vejez && weightRul.bajo) {
		xoutVector(anemiaRul.moderada, ageRul.vejez, weightRul.bajo, XAn[2], XAn[3]);
		printSet("Vejez", "Bajo", "Anemia moderada", anemiaRul.moderada);
	}
	if (ageRul.ninez && weightRul.medio) {
		xoutVector(anemiaRul.elevado, ageRul.ninez, weightRul.medio, XAn[8], XAn[9]);
		printSet("Niñez", "Medio", "HB elevado", anemiaRul.elevado);
	}
	if (ageRul.adoles && weightRul.medio) {
		xoutVector(anemiaRul.normal, ageRul.adoles, weightRul.medio, XAn[6], XAn[7]);
		printSet("Adolescencia", "Medio", "Normal", anemiaRul.normal);
	}
	if (ageRul.juven && weightRul.medio) {
		xoutVector(anemiaRul.leve, ageRul.juven, weightRul.medio, XAn[4], XAn[5]);
		printSet("Juventud", "Medio", "Anemia leve", anemiaRul.leve);
	}
	if (ageRul.adult && weightRul.medio) {
		xoutVector(anemiaRul.leve, ageRul.adult, weightRul.medio, XAn[4], XAn[5]);
		printSet("Adultez", "Medio", "Anemia leve", anemiaRul.leve);
	}
	if (ageRul.vejez && weightRul.medio) {
		xoutVector(anemiaRul.normal, ageRul.vejez, weightRul.medio, XAn[6], XAn[7]);
		printSet("Vejez", "Medio", "Normal", anemiaRul.normal);
	}
	if (ageRul.ninez && weightRul.alto) {
		xoutVector(anemiaRul.elevado, ageRul.ninez, weightRul.alto, XAn[8], XAn[9]);
		printSet("Niñez", "Alto", "HB elevado", anemiaRul.elevado);
	}
	if (ageRul.adoles && weightRul.alto) {
		xoutVector(anemiaRul.elevado, ageRul.adoles, weightRul.alto, XAn[8], XAn[9]);
		printSet("Adolescencia", "Alto", "HB elevado", anemiaRul.elevado);
	}
	if (ageRul.juven && weightRul.alto) {
		xoutVector(anemiaRul.elevado, ageRul.juven, weightRul.alto, XAn[8], XAn[9]);
		printSet("Juventud", "Alto", "HB elevado", anemiaRul.elevado);
	}
	if (ageRul.adult && weightRul.alto) {
		xoutVector(anemiaRul.normal, ageRul.adult, weightRul.alto, XAn[6], XAn[7]);
		printSet("Adultez", "Alto", "Normal", anemiaRul.normal);
	}
	if (ageRul.vejez && weightRul.alto) {
		xoutVector(anemiaRul.elevado, ageRul.vejez, weightRul.alto, XAn[8], XAn[9]);
		printSet("Vejez", "Alto", "HB elevado", anemiaRul.elevado);
	}
	
	//Defuzzification
	
	vector <vector <double>> defVec;
	
	if (anemiaRul.severa.size() > 0) {
		defVec.emplace_back(anemiaRul.severa);
	}
	if (anemiaRul.moderada.size() > 0) {
		defVec.emplace_back(anemiaRul.moderada);
	}
	if (anemiaRul.leve.size() > 0) {
		defVec.emplace_back(anemiaRul.leve);
	}
	if (anemiaRul.normal.size() > 0) {
		defVec.emplace_back(anemiaRul.normal);
	}
	if (anemiaRul.elevado.size() > 0) {
		defVec.emplace_back(anemiaRul.elevado);
	}
	
	double defuzz1 = cosMeth(anemiaRul, defVec);
	cout<<"\nHB (COS) = "<<defuzz1<<endl;
	
	double defuzz2 = cogMeth(XAn, anemiaRul, defVec);	
	cout<<"\nHB (COG) = "<<defuzz2<<endl;
	
	/*end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "\nTime taken by program is : " << fixed 
	<< time_taken << setprecision(5);
	cout << " sec " << endl;*/
	
	return 0;
}
