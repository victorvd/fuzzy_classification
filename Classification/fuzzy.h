#include <vector>
#include <cmath>

struct flowSize
{
	double vsmall = 0;
	double small = 0;
	double medium = 0;
	double large = 0;
	double vlarge = 0;
	
	//Vectores con inicio y final de cada conjunto
	vector <double> setsVec = {};
	
	//nombre de la regla
	string name;
	
	//Crear conjuntos igualmente espaciados y traslapados
	void newSets(double Xmin, double Xmax, int sets, double pct)
	{	
		for(int i = 0; i < sets * 2; ++i)
		{
			setsVec.emplace_back(0);
		}
		
		double Xp = (Xmax - Xmin) / (sets - sets * pct + pct);
		double Xl = Xp - Xp * pct;
		
		setsVec[0] = Xmin;
		setsVec[1] = Xmin + Xp;
		
		for (int i = 2; i < setsVec.size(); ++i) {
			setsVec[i] = setsVec[i-2] + Xl;
		}
		
		for (int i = 0; i < setsVec.size(); ++i) {
			cout<<setsVec[i]<<" ";
		}
		cout<<endl;
	}
	
	void rulVal(const vector <vector <double>> &muVal, const vector <double> &X)
	{
		for (int i = 0; i < muVal.size(); ++i) {
			if (muVal[i][0] == X[0] && muVal[i][1] == X[1]) {
				vsmall = muVal[i][2];
				name = "very small";
			}
			if (muVal[i][0] == X[2] && muVal[i][1] == X[3]) {
				small = muVal[i][2];
				name = "small";
			}
			if (muVal[i][0] == X[4] && muVal[i][1] == X[5]) {
				medium = muVal[i][2];
				name = "medium";
			}
			if (muVal[i][0] == X[6] && muVal[i][1] == X[7]) {
				large = muVal[i][2];
				name = "large";
			}
			if (muVal[i][0] == X[8] && muVal[i][1] == X[9]) {
				vlarge = muVal[i][2];
				name = "very large";
			}
		}
	}
	
	void initialize()
	{
		vsmall = 0;
		small = 0;
		medium = 0;
		large = 0;
		vlarge = 0;
	
		name.erase();
	}
};

struct flowClass
{
	vector <double> setosa = {};
	vector <double> versicolor = {};
	vector <double> virginica = {};
	
	double resultado = 0;
	vector <double> result_temp = {0, 0, 0};
	string classification;
	
	void winRule()
	{
		if (!setosa.empty())
		{
			for (int i = 0; i < setosa.size(); ++i)
			{
				if (setosa[i] > resultado){
					resultado = setosa[i];
					classification = "Iris-setosa";
				}
			}
		}
		
		if (!versicolor.empty())
		{
			for (int i = 0; i < versicolor.size(); ++i)
			{
				if (versicolor[i] > resultado){
					resultado = versicolor[i];
					classification = "Iris-versicolor";
				}	
			}
			
		}
		
		if (!virginica.empty())
		{
			for (int i = 0; i < virginica.size(); ++i)
			{
				if (virginica[i] > resultado){
					resultado = virginica[i];
					classification = "Iris-virginica";
				}
			}			
		}
	}
	
	void gralRule()
	{
		if (!setosa.empty())
		{
			for (int i = 0; i < setosa.size(); ++i)
			{
				result_temp[0] = result_temp[0] + setosa[i];
			}
			result_temp[0] = result_temp[0] / setosa.size();
			
			if (result_temp[0] > resultado){
				resultado = result_temp[0];
				classification = "Iris-setosa";
			}
		}
		
		if (!versicolor.empty())
		{
			for (int i = 0; i < versicolor.size(); ++i)
			{
				result_temp[1] = result_temp[1] + versicolor[i];
			}
			result_temp[1] = result_temp[1] / versicolor.size();
			
			if (result_temp[1] > resultado){
				resultado = result_temp[1];
				classification = "Iris-versicolor";
			}
		}
		
		if (!virginica.empty())
		{
			for (int i = 0; i < virginica.size(); ++i)
			{
				result_temp[2] = result_temp[2] + virginica[i];
			}
			result_temp[2] = result_temp[2] / virginica.size();
						
			if (result_temp[2] > resultado){
				resultado = result_temp[2];
				classification = "Iris-virginica";
			}
		}
	}
};


//Función para cargar archivo CSV

vector<vector<double>> load_csv(string path)
{
	fstream file (path, ios::in);

	vector<vector<double>> lista;		//Variable para almacenar kernel
	vector<double> row;
	string line, word;
	
	if(file.is_open())
	{
		while(getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while(getline(str, word, ','))
			row.push_back(stof(word.c_str()));
			
			lista.push_back(row);
		}
		printf("\nArchivo de lista cargado: ");
		cout<<lista.size()<<"x"<<lista[0].size()<<endl;
	}
	else{
		printf("No se puede abrir el archivo de lista\n");
		return {};
	}
	
	return lista;
}

//Encontrar el valor de mu para una entrada dentro del conjunto
double muValue(double x, double a, double b)
{
	double mu;

	if (x>=a && x<=(b+a)/2)
		mu = (2 * x - 2 * a) / (b - a);
	else if (x>(b+a)/2 && x<=b)
		mu = (2 * x - 2 * b) / (a - b);
	else
		return 0;
		
	return mu;
}

//Encuentra los valores de mu para cada uno de los conjuntos
vector <vector <double>> muSets (vector <double> &X, double Y) {

	vector <double> row={0,0,0};
	vector <vector <double>> mu;

	for (int i = 0; i < X.size(); i = i + 2) {
		if(Y >= X[i] && Y < X[i+1]) {
			row[0] = X[i];
			row[1] = X[i+1];
			row[2] = muValue(Y, X[i], X[i+1]);
			mu.push_back(row);
		}
	}
	
	//return mu[minElementIndex];
	return mu;
}

void rulVal(const vector <vector <double>> &muVal, flowSize &rule, const vector <double> &X)
{
	for (int i = 0; i < muVal.size(); ++i) {
		if (muVal[i][0] == X[0] && muVal[i][1] == X[1]) {
			rule.vsmall = muVal[i][2];
		}
		if (muVal[i][0] == X[2] && muVal[i][1] == X[3]) {
			rule.small = muVal[i][2];
		}
		if (muVal[i][0] == X[4] && muVal[i][1] == X[5]) {
			rule.medium = muVal[i][2];
		}
		if (muVal[i][0] == X[6] && muVal[i][1] == X[7]) {
			rule.large = muVal[i][2];
		}
		if (muVal[i][0] == X[8] && muVal[i][1] == X[9]) {
			rule.vlarge = muVal[i][2];
		}
	}
}

double tNorm(string st_norm, double rule_A, double rule_B, double rule_C, double rule_D)
{
	double tipFlor;
	
	if(st_norm == "min"){
		tipFlor = min(rule_A, min(rule_B, min(rule_C, rule_D)));
	}
	else if(st_norm == "prod_a"){
		tipFlor = rule_A * rule_B * rule_C * rule_D;
	}
	else if(st_norm == "prod_f"){
		tipFlor = rule_C + rule_D - 1;
		tipFlor = max(0.0, tipFlor);
		tipFlor = tipFlor + rule_B - 1;
		tipFlor = max(0.0, tipFlor);
		tipFlor = tipFlor + rule_A - 1;
		tipFlor = max(0.0, tipFlor);
		//tipFlor = max(0.0f, rule_A + max(0.0f, rule_B + max(0.0f, rule_C + rule_D - 1) - 1) - 1);
	}
	else if(st_norm == "prod_d"){
		if (rule_A == 1 && rule_B == 1 && rule_C == 1)
			tipFlor = rule_D;
		else if (rule_A == 1 && rule_B == 1 && rule_D == 1)
			tipFlor = rule_C;
		else if (rule_A == 1 && rule_C == 1 && rule_D == 1)
			tipFlor = rule_B;
		else if (rule_B == 1 && rule_C == 1 && rule_D == 1)
			tipFlor = rule_A;
		else
			tipFlor = 0;
	}
	else
		return -1;
		
	return tipFlor;
}

void ruleApply	(double ruleV_A, double ruleV_B, double ruleV_C, double ruleV_D, 
		flowClass &tipFlor, string setName, string st_norm, int count)
{
	if (ruleV_A && ruleV_B && ruleV_C && ruleV_D) {
		if (setName == "Iris-setosa") {
			tipFlor.setosa.emplace_back(tNorm(st_norm, ruleV_A,ruleV_B, ruleV_C, ruleV_D));
		}
		else if (setName == "Iris-versicolor") {
			tipFlor.versicolor.emplace_back(tNorm(st_norm, ruleV_A,ruleV_B, ruleV_C, ruleV_D));
		}
		else if (setName == "Iris-virginica") {
			tipFlor.virginica.emplace_back(tNorm(st_norm, ruleV_A,ruleV_B, ruleV_C, ruleV_D));
		}
		else
			return;

		//cout<<count<<" - "<<ruleV_A<<" / "<<ruleV_B<<" / "<<ruleV_C<<" / "<<ruleV_D<<":  "<<setName<<endl;
	}
	
	return;
}
