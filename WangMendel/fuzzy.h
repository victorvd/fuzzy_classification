#include <vector>
#include <cmath>

struct flowSize
{
	//Vectores con inicio y final de cada conjunto
	vector <double> setsVec = {};
	
	//nombre de la regla
	string name;
	
	double grade;
	
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
		double temp = 0;
		for (int i = 0; i < muVal.size(); ++i) {
			
			if (muVal[i][2] > temp) {
				if (muVal[i][0] == X[0] && muVal[i][1] == X[1]) {
					grade = muVal[i][2];
					name = "very small";
				}
				else if (muVal[i][0] == X[2] && muVal[i][1] == X[3]) {
					grade = muVal[i][2];
					name = "small";
				}
				else if (muVal[i][0] == X[4] && muVal[i][1] == X[5]) {
					grade = muVal[i][2];
					name = "medium";
				}
				else if (muVal[i][0] == X[6] && muVal[i][1] == X[7]) {
					grade = muVal[i][2];
					name = "large";
				}
				else if (muVal[i][0] == X[8] && muVal[i][1] == X[9]) {
					grade = muVal[i][2];
					name = "very large";
				}
			}
			temp = muVal[i][2];
		}
	}
	
	void initialize()
	{
		grade = 0;
	
		name.erase();
	}
};


//Función para cargar archivo CSV

vector<vector<string>> load_csv(string path)
{
	fstream file (path, ios::in);

	vector<vector<string>> lista;		//Variable para almacenar kernel
	vector<string> row;
	string line, word;
	
	if(file.is_open())
	{
		while(getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while(getline(str, word, ','))
			row.push_back(word.c_str());
			
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
