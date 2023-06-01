#include <fstream>
#include <vector>
#include <cmath>

struct anemiaSets {
	vector <double> severa;
	vector <double> moderada;
	vector <double> leve;
	vector <double> normal;
	vector <double> elevado;
};

//Crear conjuntos igualmente espaciados y traslapados
vector <double> sets(double Xmin, double Xmax, int sets, double pct)
{
	
	vector <double> X(sets * 2);
	double Xp = (Xmax - Xmin) / (sets - sets * pct + pct);
	double Xl = Xp - Xp * pct;
	
	X[0] = Xmin;
	X[1] = Xmin + Xp;
	
	for (int i = 2; i < X.size(); ++i) {
		X[i] = X[i-2] + Xl;
	}
	
	for (int i = 0; i < X.size(); ++i) {
		cout<<X[i]<<" ";
	}
	cout<<endl;
	
	return X;
}

//Encontrar el valor de mu para una entrada dentro del conjunto
double muValue(double x, double a, double b)
{
	double mu;

	if (x>=a && x<=(b+a)/2)
		mu = (2 * x - 2 * a) / (b - a);
	else if (x>=(b+a)/2 && x<=b)
		mu = (2 * x - 2 * b) / (a - b);
	else
		return 0;
		
	return mu;
}

//Encuentra los valores de mu para cada uno de los conjuntos
vector <vector <double>> muSets (vector <double> &X, double Y) {

	vector <double> row(3);
	vector <double> col;
	vector <vector <double>> mu;

	for (int i = 0; i < X.size(); i = i + 2) {
		if(Y >= X[i] && Y < X[i+1]) {
			row[0] = X[i];
			row[1] = X[i+1];
			row[2] = muValue(Y, X[i], X[i+1]);
			col.emplace_back(row[2]);
			mu.emplace_back(row);
		}		
	}
	
	int minElementIndex = min_element(col.begin(),col.end()) - col.begin();
	
	//return mu[minElementIndex];
	return mu;
}

//Valor de X para los conjuntos de salida
vector <double> xoutValue(double mu, double a, double b)
{
	vector <double> X(2);
	
	X[0] = a + mu * (b - a) / 2;
	
	X[1] = b + mu * (a - b) / 2;
	
	return X;
}

//Encontrar el centroide para los trapecios resultantes
double centroid(double x1, double x2, double x3, double x4, double mu)
{
	double a = x3 - x2;
	double b = x4 - x1;
	double c = sqrt(pow(x2 - x1,2) + pow(mu,2));
	double d = sqrt(pow(x4 - x3,2) + pow(mu,2));
	
	double cen = b / 2 + (2 * a + b) * (pow(c,2) - pow(d,2)) / (6 * (pow(b,2) - pow(a,2))) + x1;
	
	return cen;
}

//Valores característicos para cada trapecio resultante
void xoutVector(vector <double> &xout,
		const double ageR,
		const double weightR,
		const double Xmin,
		const double Xmax)
{
	if (xout.size() > 0 && xout[4] > min(ageR,weightR))
		return;
	else {
		xout = xoutValue(min(ageR,weightR), Xmin, Xmax);
		xout.emplace_back(Xmin);
		xout.emplace_back(Xmax);
		xout.emplace_back(min(ageR,weightR));
		xout.emplace_back(centroid(Xmin, xout[0], xout[1], Xmax, xout[4]));
		//xout = [b, c, a, d, mu, cen]
	}	
	return;
}

//Método de centro de sumas
double cosMeth(const anemiaSets &anemiaRul, vector <vector <double>> defVec)
{
	vector <double> A;
	vector <double> cen;
	
	double num = 0;
	double den = 0;
	
	for (int i = 0; i < defVec.size(); ++i) {
	
		A.emplace_back((defVec[i][3] + defVec[i][1] - defVec[i][2] - defVec[i][0]) * defVec[i][4] / 2);
		
		cen.emplace_back(centroid(defVec[i][2], defVec[i][0], defVec[i][1], defVec[i][3], defVec[i][4]));
		
		num += (A[i] * cen[i]);
		den += A[i];
	}
	 	 
	double x_def = num / den;
	 
	return x_def;
}

double cogMeth(const vector <double> &XAn, anemiaSets &anemiaRul, vector <vector <double>> defVec)
{
	int iter = 1000;
	
	double t = (XAn[9] - XAn[0]) / iter;
	double x = XAn[0];
	vector <double> y;
	
	double num = 0;
	double den = 0;
	
	vector <vector <double>> plotear;
	vector <double> row(2);
	
	for (int j = 0; j < iter; ++j) {
		for (int i = 0; i < defVec.size(); ++i) {
			if (x >= defVec[i][2] && x < defVec[i][0]) {
				y.emplace_back(defVec[i][4] * (x - defVec[i][2]) / (defVec[i][0] - defVec[i][2]));
			}
			else if (x >= defVec[i][0] && x <= defVec[i][1]) {
				y.emplace_back(defVec[i][4]);
			}
			else if (x > defVec[i][1] && x <= defVec[i][3]) {
				y.emplace_back(defVec[i][4] * (x - defVec[i][3]) / (defVec[i][1] - defVec[i][3]));
			}
		}
		
		if(y.size() > 0) {
			switch (y.size()) {
				case 1:
					row={x,y[0]};
					num += y[0] * x;
					den += y[0];					
					break;
				case 2:
					row={x,max(y[0], y[1])};
					num += row[1] * x;
					den += row[1];
					break;
			}
			plotear.emplace_back(row);
			y.clear();
		}
		
		x = x + t;
	}
	
	double s = num / den;
	
	fstream file;
	file.open("plotear.csv",ios_base::out);

	for(int i=0;i<plotear.size();++i)
	{
		file<<plotear[i][0]<<","<<plotear[i][1]<<endl;
	}

	file.close();
	
	return s;
}

void printSet(string age, string weight, string HB, const vector <double> &xout)
{
	cout<<"\nEdad: "<<age<<"; Peso: "<<weight<<"; HB: "<<HB<<endl;
	cout<<"mu = "<<xout[4]<<endl;
	cout<<xout[0]<<endl;
	cout<<xout[1]<<endl;
	cout<<xout[5]<<endl;
	
	return;
}
