#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <math.h>

using namespace std;

class Fp{
	private:
		int P;

	public:
		// Construim un Fp
		Fp(int p = 1);
		// Returneaza p-ul 
		int getP();
		// Modifica p-ul
		int setP(int p);
		// Afiseaza corpul cu p elemete
		void afisare();
};

class Fpn{
	private:
		Fp F;
		int N;
		std :: vector <int> Pol;
	public:
		// Construim un Fp^n
		Fpn(Fp H, int n);
		Fpn();
		// Returneaza Fp -ul
		Fp getFp();
		// Modifica Fp -ul
		Fp setFp(Fp H);
		// Afiseaza polinomul
		void getP();
		// Afiseaza copul cu p la n elemente
		void afisare();
		// Returneaza n -ul
		int getN();
		// Returneaza Polinomul
		std::vector <int> getPol();
};

// Element al unui grup cu p la n elemente
class E{
	private:
		Fpn Fn;
		int M;
		std :: vector <int> element;
	public:
		// Construim un element
		E(Fpn H, int m);
		E(Fpn H, int m,int x);
		E();
		E(const E &);
		// Returneaza m -ul
		int getM();
		// Returneaza Elementul
		std::vector <int> getElem();
		// Seteaza Elementul
		std::vector <int> setElem(std::vector <int> V);
		// Afisare element
		void afisare();
		// Retuneaza Fn -ul
		Fpn getFn();
		
		// operatori
		friend E operator +(E x, E y); //yes
		friend E operator -(E x, E y); //yes
		friend bool operator ==(E x, E y); // yes
		friend bool operator ==(E x, int y); // yes
		E & operator =(const E &x); // yes
		//E & operator =(const int &x);
		friend E operator *(E x, E y); // yes
		friend E operator *(E x, int y); // yes
		friend E operator *(int y, E x); // yes
		friend E operator /(E x, E y); // yes
		friend E operator ^(E x, int n); // yes
		friend E sqrt(E x);
};

class PUNCT{
	char Nume;
	E X;
	E Y;
	bool Inf;
	
	public:
		//Construim un punct
		PUNCT(char n, E x, E y, bool inf = false); //yes
		PUNCT();
		//Seteaza numele
		int setNume(int n); // yesy
		//Seteaza X-ul
		E setX(E x); //yes
		//Seteaza Y-ul
		E setY(E y); //yes
		//Seteaza infinitatea
		bool setInf(bool inf); // yes 
		//Returneaza numele
		int getNume(); //yes
		//Returneaza X-ul
		E getX(); //yes
		//Returneaza Y-ul
		E getY(); //yes
		//Returneaza infinitatea
		bool getInf(); //yes
		// Afisare
		void afisare(); //yes
		
		// operatori
		PUNCT & operator =(const PUNCT &x); // yes
};

class CURBA{  // E(Fpn): y^2 = x^3 + A*x + B
	Fpn Corp;
	E A;
	E B;
	public:
		// Contruim o curba eliptica
		CURBA(Fpn C, E a, E b); //yes
		// Returneaza corpul peste care definim curba
		Fpn getCorp(); //yes
		// Retuneaza coeficientul lui x 
		E getA(); //yes
		// Returneaza termenul liber
		E getB(); //yes
		// Steaza un alt corp pentru curba
		Fpn setCorp(Fpn c); //yes
		// Seteaza coeficientul lui x 
		E setA(E a); //yes
		// Seteaza termenul liber
		E setB(E b); //yes
		// Afiseaza curba eliptica
		void afisare(); // yes
		// Verifica daca un punct apartine curbei
		bool punctValid(PUNCT Q); //yes
		// Adunare puncte
		PUNCT AdunarePuncte(PUNCT P, PUNCT Q); // yes
		// Cardinalul unei curbe
		int Cardinal();
		// Ordinul unui punct
		int Ordinul(PUNCT P); // yes
		// Calculam n * punct
		PUNCT Multiplicare(PUNCT P, int n); // yes
};

// Contruim un Fp
Fp::Fp(int p){
	int i;

	if(p == 1){
		this->P = p;
		return;
	}
	if(p == 2){
		this->P = p;
		return;
	}else{
		if(p % 2 == 0){
			cout << "P nu este prim !!! (-_-) " << endl;
			this->P = 1;
			return;
		}else{
			for(i = 3; i <= sqrt(p); i = i + 2){
				if(p % i == 0){
					cout << "P nu este prim !!! (-_-) " << endl;
					this->P = 1;
					return;
				}
			}
		}
			this->P = p;
	}
}

// Returneaza p-ul 
int Fp::getP(){
	return this->P;
}

// Modifica p-ul
int Fp::setP(int p){
	int i;

	if(p == 1){
		i = this->P;
		this->P = p;
		return i;
	}
	if(p == 2){
		this->P = p;
	}else{
		if(p % 2 == 0){
			cout << "P nu este prim !!! (-_-) " << endl;
			return 1;
		}else{
			for(i = 3; i <= sqrt(p); i = i + 2){
				if(p % i == 0){
					cout << "P nu este prim !!! (-_-) " << endl;
					return 1;
				}
			}
		}
		i = this->P;
		this->P = p;
		return i;
	}
	return 0;
}

// Afiseaza corpul cu p elemete
void Fp::afisare(){
	if(this->P == 1){
		cout << " Fp" << endl;
	}else{
		cout << " F" << this->P << endl;
	}
}

// Construim un Fp^n
Fpn::Fpn(Fp H, int n){
	this->F = H;
	this->N = n;
	ifstream f("/home/alb/Documente/Licenta/Test1/iesire1.txt");
	int p = H.getP();
	if(5 > p || p > 181){
		cout << "p nu e bun \n";
		return;
	}
	if(2 > n || n > 8){
		cout << "n nu e bun \n";
		return;
	}
	int nrPr, putPol;
	//identificare nr prim
	f >> nrPr;
	while(nrPr != p){
		f >> putPol;
		int i = 0;
		while(i <= putPol){
			int x;
			f >> x;
			i = i + 1;
		}
		f >> nrPr;
	}
	// identificare putere polinom
	f >> putPol;
	while(putPol != n){
		int i = 0;
		while(i <= putPol){
			int x;
			f >> x;
			i = i + 1;
		}
		f >> i;
		f >> putPol;
	}
	for(int i = 0; i <= n; i++){
		Pol.push_back(0);
	}
	for(int i = n; i >= 0; i--){
		int x;
		f >> x;
		Pol[i] = x;
	}
}

Fpn::Fpn(){
	Fp H;
	this->F = H;
	this->N = 1;
}

// Returneaza Fp -ul
Fp Fpn::getFp(){
	return this->F;
}

// Modifica Fp -ul
Fp Fpn::setFp(Fp H){
	this->F = H;
	for(int i = 0; i <= N; i++){
		Pol[i] = Pol[i] % F.getP(); 
	}
	int suma = 0;
	for(int i = 0; i < F.getP(); i++){
		for(int j = 0; j <= N; j++){
			suma = suma + i*Pol[j];
		}
		if(suma % F.getP() == 0 ){
			cout << "Polinomul nu mai este ireductibil peste Fp -ul nou !!!";
		}
	}
	return H;
}

// Afiseaza polinomul
void Fpn::getP(){
	for(int i = N; i >= 2; i--){
		if(i == N){
			if(Pol[i] != 0){
				cout << Pol[i] << "*X^" << i ;
			}
		}else{
			if(Pol[i] != 0){
				cout << "+" << Pol[i] << "*X^" << i ;
			}
		}
	}
	if(Pol[1] != 0){
		cout << "+" << Pol[1] << "*X";
	}
	if(Pol[0] != 0){
		cout << "+" << Pol[0];
	}
}

// Afiseaza copul cu p la n elemente
void Fpn::afisare(){
	cout << "Lucram peste corpul : \n";
	cout << "F" << F.getP() << "[X] / " ;
	int ok = 0;
	for(int i = N; i >= 2; i--){
		if(i == N){
			if(Pol[i] != 0){
				if(Pol[i] == 1){
					cout << "X^" << i ;
					ok = 1;
				}else{
					cout << Pol[i] << "*X^" << i ;
					ok = 1;
				}
			}
		}else{
			if(Pol[i] != 0){
				if(Pol[i] == 1){
					cout << "+" << "X^" << i ;
					ok = 1;
				}else{
					cout << "+" << Pol[i] << "*X^" << i ;
					ok = 1;
				}
			}
		}
	}
	if(Pol[1] != 0){
		if(ok == 1){
			cout << "+";
		}
		if(Pol[1] == 1){
			cout << "X";
			ok = 1;
		}else{
			cout << Pol[1] << "*X";
			ok = 1;
		}
	}
	if(Pol[0] != 0){
		if(ok == 1){
			cout << "+";
		}
		cout << Pol[0];
	}
	cout << endl;
}

// Returneaza N -ul
int Fpn::getN(){
	return this->N;
}

// Returneaza polinomul
vector <int> Fpn::getPol(){
	return Pol;
}

//Construim un element din Fp^n
E :: E(Fpn H, int m){
	this-> Fn = H;
	if(m >= H.getN()){
		return;
	}
	this->M = m;
	for(int i = 0; i <= m; i++){
		cout << "Dati coeficientul e" << i << " = ";
		int tmp;
		cin >> tmp;
		tmp = tmp % (H.getFp()).getP();
		element.push_back(tmp);
	}
}

E :: E(Fpn H, int m, int x){
	this-> Fn = H;
	if(m >= H.getN()){
		return;
	}else{
		this->M = m;
		for(int i = 0; i <= m; i++){
			element.push_back(0);
		}
	}
}

E :: E(){
	element.push_back(0);
}

// Returneaza M -ul
int E::getM(){
	return this->M;
}

// Returneaza Elementul
vector <int> E::getElem(){
	return this->element;
}

// Seteaza Elementul
vector <int> E::setElem(vector <int> V){
	if((int)V.size() - 1 < (int)(this->getFn()).getN()){
		for(int i = 0; i < (this->getFn()).getN() ; i++){
			this->element[i] = V[i];
		}
		this->M = (this->getFn()).getN() - 1;
	}else{
		cout << "Nu e bine !!!!" << endl;
	}
	return V;
}

// Afisare element
void E::afisare(){
	int ok = 0;
	int ok1 = 0;
	for(int i = M; i >= 2; i--){
		if(i == M){
			if(element[i] != 0){
				if(element[i] == 1){
					cout << "E^" << i ;  ok1 = 1;
					ok = 1;
				}else{
					if(element[i] < 0){
						cout << (Fn.getFp()).getP() + element[i]; ok1 = 1;
					}else{
						cout << element[i]; ok1 = 1;
					}
					cout << "*E^" << i ;  ok1 = 1;
					ok = 1;
				}
			}
		}else{
			if(element[i] != 0){
				if(element[i] == 1){
					cout << "+" << "E^" << i ;  ok1 = 1;
					ok = 1;
				}else{
					cout << "+";
					if(element[i] < 0){
						cout << (Fn.getFp()).getP() + element[i]; ok1 = 1;
					}else{
						cout << element[i]; ok1 = 1;
					}
					cout << "*E^" << i ;  ok1 = 1;
					ok = 1;
				}
			}
		}
	}
	if(element.size() != 0){
		if(element[1] != 0){
			if(ok == 1){
				cout << "+";  ok1 = 1;
			}
			if(element[1] == 1){
				cout << "E";  ok1 = 1;
				ok = 1;
			}else{
				if(element[1] < 0){
					cout << (Fn.getFp()).getP() + element[1]; ok1 = 1;
				}else{
					cout << element[1]; ok1 = 1;
				}
				cout << "*E";  ok1 = 1;
				ok = 1;
			}
		}
		if(element[0] != 0){
			if(ok == 1){
				cout << "+";  ok1 = 1;
			}
			if(element[0] < 0){
				cout << (Fn.getFp()).getP() + element[0]; ok1 = 1;
			}else{
				cout << element[0]; ok1 = 1;
			}
		}
		if(ok1 == 0){
			cout << 0;
		}
	}
}

// Retuneaza Fn -ul
Fpn E::getFn(){
	return Fn;
}

// Capculeaza a/b(mod p)
int ImpartireModP(int a, int b, int p){
	if (a == 0 || b == 0){
		return 0;
	}
	a = a % p;
	b = b % p;
	if(a < 0){
		a = p + a;
	}
	if(b < 0){
		b = p + b;
	}
	for(int i = 1; i < p; i++){
		if( (b * i) % p == a){
			return i;
		}
	}
	return 0;
}

// Radical modulo p
int RadicalModular(int a, int p){
	a = a % p;
	if(a < 0){
		a = p + a;
	}
	for(int i = 1; i < p; i++){
		if( (i*i) % p == a ){
			return i;
		}
	}
	return -1;
}

// operatori
E & E::operator =(const E &x){
	this->Fn = x.Fn;
	(this->element).clear();
	
	for(int i = 0 ; i <= x.M; i++){
		(this->element).push_back(x.element[i]);
	}
	this->M = x.M;
	return *this;
}

E::E(const E & x){
	this->Fn = x.Fn;
	(this->element).clear();
	
	for(int i = 0 ; i <= x.M; i++){
		(this->element).push_back(x.element[i]);
	}
	this->M = x.M;
}

E operator +(E x, E y){
	int mi, ma;
	if(x.getM() > y.getM()){
		ma = x.getM();
		mi = y.getM();
	}else{
		ma = y.getM();
		mi = x.getM();
	}
	E t(x.getFn(), ma, 0);
	for(int i = 0; i <= mi; i++){
		t.element[i] = (x.element[i] + y.element[i]) % ((x.getFn()).getFp()).getP();
	}
	if(ma == x.getM()){
		for(int i = mi + 1; i <= ma; i++){
			t.element[i] = x.element[i];
		}
	}else{
		for(int i = mi + 1; i <= ma; i++){
			t.element[i] = y.element[i];
		}
	}
	return t;
}

bool operator ==(E x, E y){
	if(x.getM() != y.getM()){
		return false;
	}else{
		for(int i = 0; i <= x.getM(); i++){
			if(x.element[i] != y.element[i]){
				return false;
			}
		}
	}
	return true;
}

bool operator ==(E x, int y){
	if(x.element[0] != y){
		return false;
	}else{
		for(int i = 1; i <= x.getM(); i++){
			if(x.element[i] != 0){
				return false;
			}
		}
	}
	return true;
}

E operator -(E x, E y){
	int mi, ma;
	if(x.getM() > y.getM()){
		ma = x.getM();
		mi = y.getM();
	}else{
		ma = y.getM();
		mi = x.getM();
	}
	E t(x.getFn(), ma, 0);
	for(int i = 0; i <= mi; i++){
		if(x.element[i] - y.element[i] < 0){
			int tmp = ((x.getFn()).getFp()).getP() + (x.element[i] - y.element[i]);
			t.element[i] = tmp % ((x.getFn()).getFp()).getP();
		}else{
			int tmp = (x.element[i] - y.element[i]);
			t.element[i] = tmp % ((x.getFn()).getFp()).getP();
		}
	}
	if(ma == x.getM()){
		for(int i = mi + 1; i <= ma; i++){
			t.element[i] = x.element[i];
		}
	}else{
		for(int i = mi + 1; i <= ma; i++){
			t.element[i] = y.element[i];
		}
	}
	return t;
}

E operator *(E x, E y){
	int m = x.getM() + y.getM();
	E t(x.getFn(), (x.getFn()).getN() - 1, 0);

	if(x == 0 || y == 0){
		return t;
	}

	vector <int> V;
	
	for(int i = 0 ; i <= m; i++){
		V.push_back(0);
	}
	for(int i = 0 ; i <= m; i++){
		for(int j = 0 ; j <= x.getM(); j++){
			for(int k = 0 ; k <= y.getM(); k++){
				if(i == j + k){
					V[i] = V[i] + (x.element[j] * y.element[k]);
				}
			}
		}
	}
	
	for(int i = 0; i < (int)V.size(); i++){
		V[i] = V[i] % ((x.getFn()).getFp()).getP();
	}
	
	bool ok = false;
	for(int i = 0; i < (int)V.size(); i++){
		if(V[i] != 0){
			ok = true;
		}
	}
	if(ok == false){
		for(int j = 0 ; j < (int)V.size(); j++){
			t.element[j] = V[j];
		}
		return t;
	}
	
	vector <int> W;
	vector <int> T;
	T = (x.getFn()).getPol();
	
	int i = m;
	while(V[i] == 0){
		i = i - 1;
	}
	int j = 0;
	while(j <= i){
		W.push_back(V[j]);
		j = j + 1;
	}
	
	if(W.size() < T.size()){
		for(int j = 0 ; j < (int)W.size(); j++){
			t.element[j] = W[j];
		}
		for(int j = (int)W.size(); j <= t.getM(); j++){
			t.element[j] = 0;
		}
		return t;
	}else{
		int itt = W.size() - T.size() + 1;
		for(int i = 0; i < itt; i++){
			int temp = ImpartireModP(W[W.size() - i - 1], T[T.size() - 1], ((x.getFn()).getFp()).getP());
			for(int j = 0; j < (int)T.size(); j++){
				int Ws = (int)W.size() - i - 1;
				int Ts = (int)T.size() - 1;
				int var = (W[Ws - j] - (temp * T[Ts - j])) % ((x.getFn()).getFp()).getP();
				if(var < 0){
					W[Ws - j] = var + ((x.getFn()).getFp()).getP();
				}else{
					W[Ws - j] = var;
				}
			}
		}
		
		for(int i = 0; i <= (int)x.getM(); i++){
			t.element[i] = W[i];
		}
		return t;
	}
}

E operator *(E x, int y){
	E t(x.getFn(), (x.getFn()).getN() - 1, 0);
	for(int i = 0; i <= x.getM(); i++){
		t.element[i] = (y * x.element[i]) % ((x.getFn()).getFp()).getP();
		if( t.element[i] < 0){
			t.element[i] = t.element[i] + ((x.getFn()).getFp()).getP();
		}
	}
	return t;
}

E operator *(int y, E x){
	E t(x.getFn(), (x.getFn()).getN() - 1, 0);
	for(int i = 0; i <= x.getM(); i++){
		t.element[i] = (y * x.element[i]) % ((x.getFn()).getFp()).getP();
		if( t.element[i] < 0){
			t.element[i] = t.element[i] + ((x.getFn()).getFp()).getP();
		}
	}
	return t;
}

vector <int> add(vector<int> V, int p){
	int i = 0;
	while(i < (int)V.size()){
		if(V[i] + 1 != p){
			V[i] = V[i] + 1;
			break;
		}else{
			if(V[i] + 1 == p){
				if(i == (int)V.size() - 1){
					V[i] = p;
					break;
				}
				V[i] = 0;
				i = i + 1;
			}
		}
	}
	return V;
}

bool full(vector<int> v, int n, int p){
	bool ok = true;
	for(int i = 0; i <= n ;i++){
		if(v[i] != p - 1){
			ok = false;
		}
	}
	return ok;
}

E operator /(E x, E y){
	E t(y.getFn(), (y.getFn()).getN() - 1, 0);
	if(y == 0){
		return t;
	}
	if(y == 1){
		return x;
	}
	if(x == y){
		t.element[0] = 1;
		return t;
	}
	
	vector <int> P;
	P.push_back(1);
	for(int i = 1 ; i < (y.getFn()).getN() ; i++){
		P.push_back(0);
	}
	E tmp(y.getFn(),(y.getFn()).getN() - 1,0);
	while( full(P, y.getM(), ((y.getFn()).getFp()).getP() ) != true ){
		
		for(int i = 0 ; i < (y.getFn()).getN(); i++){
			tmp.element[i] = P[i];
		}
		t = y * tmp;
		if(t == 1){
			t = x * tmp;
			return t;
		}
		P = add(P, ((y.getFn()).getFp()).getP());
	}
	for(int i = 0 ; i < (y.getFn()).getN(); i++){
		tmp.element[i] = P[i];
	}
	t = y * tmp;
	if(t == 1){
		t = x * tmp;
		return t;
	}
	return t;
}

E operator ^(E x, int n){
	E t(x.getFn(), (x.getFn()).getN() - 1, 0);
	if(n < 0){
		E tt(x.getFn(), (x.getFn()).getN() - 1, 0);
		tt.element[0] = 1;
		x = tt / x;
		return x;
		n = -n;
		int dec = n;
		
		vector<int> bin;
		while( dec > 0 ) {
			if( dec % 2 == 0 ){
				bin.push_back( 0 );
			}else{
				bin.push_back( 1 );
			}
			dec = dec >> 1;
		}
		
		t.element[0] = 1;
		
		for(int i = 0; i < (int)bin.size(); i++){
			if(bin[i] != 0){
				t = t * x;
			}
			x = x * x;
		}
		return t;
	}
	if(n == 0){
		return t;
	}else{
		int dec = n;
		
		vector<int> bin;
		while( dec > 0 ) {
			if( dec % 2 == 0 ){
				bin.push_back( 0 );
			}else{
				bin.push_back( 1 );
			}
			dec = dec >> 1;
		}
		
		t.element[0] = 1;
		
		for(int i = 0; i < (int)bin.size(); i++){
			if(bin[i] != 0){
				t = t * x;
			}
			x = x * x;
		}
		return t;
	}
}

E sqrt(E x){
	E t(x.getFn(), (x.getFn()).getN() - 1, 0);
	if(x == 0){
		return t;
	}
	
	vector <int> P;
	P.push_back(1);
	for(int i = 1 ; i < (x.getFn()).getN() ; i++){
		P.push_back(0);
	}
	E tmp(x.getFn(),(x.getFn()).getN() - 1,0);
	
	while( full(P, x.getM(), ((x.getFn()).getFp()).getP() ) != true ){
		
		for(int i = 0 ; i < (x.getFn()).getN(); i++){
			tmp.element[i] = P[i];
		}
		t = tmp * tmp;
		if(t == x){
			t = tmp;
			return t;
		}
		P = add(P, ((x.getFn()).getFp()).getP());
	}
	for(int i = 0 ; i < (x.getFn()).getN(); i++){
		tmp.element[i] = P[i];
	}
	t = tmp * tmp;
	if(t == x){
		t = tmp;
		return t;
	}
	return t;
}

PUNCT::PUNCT(char n, E x, E y, bool inf){
	this->Nume = n;
	this->X = x;
	this->Y = y;
	this->Inf = inf;
}

PUNCT::PUNCT(){
	this->Nume = 'a';
	Fp fp(2);
	Fpn F(fp, 2);
	E t(F, 1, 0);
	this->X = t;
	this->Y = t;
	this->Inf = true;
}

// Seteaza numele punctului
int PUNCT::setNume(int n){
	this->Nume = n;
	return n;
}

// Seteaza coordonata X a punctului
E PUNCT::setX(E x){
	this->X = x;
	return x;
}

// Seteaza coordonata Y a punctului
E PUNCT::setY(E y){
	this->Y = y;
	return y;
}

// Seteaza daca punctul este punct de la infinit
bool PUNCT::setInf(bool inf){
	this->Inf = inf;
	return inf;
}

// Returneaza numele punctului
int PUNCT::getNume(){
	return this->Nume;
}

// Returneaza coordonata X a punctului
E PUNCT::getX(){
	return this->X;
}

// Returneaza coordonata Y a punctului
E PUNCT::getY(){
	return this->Y;
}

// Returneaza daca punctul este punct de la infinit
bool PUNCT::getInf(){
	return this->Inf;
}

// Afiseaza punctul din R^2
void PUNCT::afisare(){
	if(this->Inf == true){
		cout << this->Nume << "(inf,inf)";
	}else{
		cout << this->Nume << "(";
		(this->X).afisare(); 
		cout << ",";
		(this->Y).afisare();
		cout << ")";
	}
}

//operatori

PUNCT & PUNCT::operator =(const PUNCT &x){
	this->Nume = x.Nume;
	this->X = x.X;
	this->Y = x.Y;
	this->Inf = x.Inf;
	
	return *this;
}

// Contruim o curba eliptica
CURBA::CURBA(Fpn C, E a, E b){
	if(a == 0 && b == 0){
		this->Corp = C;
		this->A = a;
		this->B = b;
	}else{
		if( (a*a*a*4 + b*b*27) == 0 ){
			cout << "A -ul si B -ul nu desciu o curba valida !!!" << endl;
			return;
		}
		this->Corp = C;
		this->A = a;
		this->B = b;
	}
}

// Returneaza corpul peste care definim curba
Fpn CURBA::getCorp(){
	return this->Corp;
}

// Retuneaza coeficientul lui x 
E CURBA::getA(){
	return this->A;
}

// Returneaza termenul liber
E CURBA::getB(){
	return this->B;
}

// Seteaza coeficientul lui x 
E CURBA::setA(E a){
	E temp = this->A;
	
	this->A = a;
	return temp;
}

// Seteaza termenul liber
E CURBA::setB(E b){
	E temp = this->B;
	
	this->B = b;
	return temp;
}

// Afiseaza curba eliptica
void CURBA::afisare(){
	if(this->A == 0 && this->B == 0){
		cout << "y^2 = x^3 + A*x + B " << endl;
	}else{
		cout << "y^2 = x^3";
		if(!(this->A == 0)){
			cout << " + (";
			(this->A).afisare();
			cout << ")*x"; 
		}
		if (!(this->B == 0)){
			cout << " + (";
			(this->B).afisare();
			cout << ")";
		}
		cout << ";" << endl;
	}
}

// Verifica daca un punct apartine curbei
bool CURBA::punctValid(PUNCT Q){
	if(Q.getInf() == true){
		return true;
	}
	
	E temp = (Q.getX()^3) + this->A*Q.getX() + this->B;
			
	if(Q.getY()*Q.getY() == temp){
		return true;
	}
	return false;
}

// Adunare puncte
PUNCT CURBA::AdunarePuncte(PUNCT P, PUNCT Q){
	// Verificare daca vreunul e punct de la infinit
	if(P.getInf() == true){
		PUNCT R('R', Q.getX(), Q.getY());
		return R;
	}
	if(Q.getInf() == true){
		PUNCT R('R', P.getX(), P.getY());
		return R;
	}
	if(this->punctValid(P) == false || this->punctValid(Q) == false){
		cout << "Unul din punte nu verifica ecuatia curbei !!!";
		E t( (P.getX()).getFn(), ((P.getX()).getFn()).getN() - 1, 0);
		PUNCT R('R', t, t);
		return R;
	}
	
	char n = 'R';
	if( (P.getX() == Q.getX()) && (P.getY() == Q.getY()) ){
		if( P.getY() == 0 ){
			
			E t( (P.getX()).getFn(), ((P.getX()).getFn()).getN() - 1, 0);
			PUNCT R(n, t, t, true);
			return R;
		}else{
			
			E x( (P.getX()).getFn(), ((P.getX()).getFn()).getN() - 1, 0);
			E y( (P.getX()).getFn(), ((P.getX()).getFn()).getN() - 1, 0);
			
			E m( (P.getX()).getFn(), ((P.getX()).getFn()).getN() - 1, 0);
			m = (P.getX() * P.getX() * 3 + this->getA())/( P.getY() * 2 );

			x = (m * m + P.getX() * (-2));
			
			y = ((-1) * P.getY() - m * (x - P.getX()));
			
			PUNCT R(n, x, y);
			return R;
		}
	}else{
		if( P.getX() == Q.getX() ){
			
			E t( (P.getX()).getFn(), ((P.getX()).getFn()).getN() - 1, 0);
			PUNCT R('R', t, t, true);
			return R;
		}else{
			
			E x( (P.getX()).getFn(), ((P.getX()).getFn()).getN() - 1, 0);
			E y( (P.getX()).getFn(), ((P.getX()).getFn()).getN() - 1, 0);
			
			E m( (P.getX()).getFn(), ((P.getX()).getFn()).getN() - 1, 0);
			
			m = ( Q.getY() - P.getY() ) / ( Q.getX() - P.getX() );
			
			x = (m * m - (P.getX() + Q.getX()));
			
			y = ((-1) * P.getY() - m * (x - P.getX()));
			
			PUNCT R(n, x, y);
			return R;
		}
	}
}

// Cardinalul unei curbe
int CURBA::Cardinal(){
	int decizie = 0;
	cout << " \n Doriti sa afisasi si punctele curbei ? 0-Nu 1-Da \n";
	cin >> decizie;
	int p = ((this->Corp).getFp()).getP();
	int n = (this->Corp).getN();
	int card = pow(p, n);
	int cardinal = card + 1;
	card = (card - 1)/2;
	
	vector <int> P;
	for(int i = 0 ; i < n ; i++){
		P.push_back(0);
	}
	E tmp(this->Corp, n - 1,0);
	E tmp1(this->Corp, n - 1,0);
	E tmp2(this->Corp, n - 1,0);
	E tmp3(this->Corp, n - 1,0);
	
	while( full(P, n - 1, p ) != true ){
		
		tmp.setElem(P);
		tmp2 = tmp;
		tmp1 = (tmp ^ 3) + tmp*this->getA() + this->getB();
		tmp3 = tmp1;
		tmp1 = tmp1 ^ card;
		if(tmp1 == p - 1){
			cardinal = cardinal - 1;
		}else{
			if(tmp1 == 1){
				cardinal = cardinal + 1;
				if(decizie == 1){
					cout << "("; tmp2.afisare();
					cout << ", "; (sqrt(tmp3)).afisare();
					cout << " );" << "\n";
					cout << "("; tmp2.afisare();
					cout << ", "; ((-1)*sqrt(tmp3)).afisare();
					cout << " ); \n";
				}

			}
			if(tmp1 == 0){
				if(decizie == 1){
					cout << "("; tmp2.afisare();
					cout << ", "; (sqrt(tmp3)).afisare();
					cout << " ); \n";
				}
			}
		}
		P = add(P, p);
	}
	
	tmp.setElem(P);
	tmp2 = tmp;
	tmp1 = (tmp ^ 3) + tmp*this->getA() + this->getB();
	tmp3 = tmp1;
	tmp1 = tmp1 ^ card;
	if(tmp1 == p - 1){
		cardinal = cardinal - 1;
	}else{
		if(tmp1 == 1){
			cardinal = cardinal + 1;
			if(decizie == 1){
				cout << "("; tmp2.afisare();
				cout << ", "; (sqrt(tmp3)).afisare();
				cout << " ); \n";
				cout << "("; tmp2.afisare();
				cout << ", "; ((-1)*sqrt(tmp3)).afisare();
				cout << " ); \n";
			}
		}
		if(tmp1 == 0){
			if(decizie == 1){
				cout << "("; tmp2.afisare();
				cout << ", "; (sqrt(tmp3)).afisare();
				cout << " ); \n";
			}
		}
	}
	
	return cardinal;
}

// Ordinul unui punct
int CURBA::Ordinul(PUNCT P){
	int ord = 1;
	
	if(this->punctValid(P) == false){
		cout << "Puntul nu verifica ecuatia curbei !!!";
		return -1;
	}
	
	if(P.getInf() == true){
		cout << "Puntul este punct de la infinit !!!";
		return ord;
	}
	
	PUNCT Q = this->AdunarePuncte(P, P);
	ord = 2;
	
	while(Q.getInf() == false){
		Q = this->AdunarePuncte(Q, P);
		ord = ord + 1;
	}
	return ord;
}

PUNCT CURBA::Multiplicare(PUNCT P, int n){
	PUNCT Q;
	
	if(this->punctValid(P) == false){
		cout << "Puntul nu verifica ecuatia curbei !!!";
		return P;
	}
	
	if(P.getInf() == true){
		cout << "Puntul este punct de la infinit !!!";
		return P;
	}

	n = n % Ordinul(P);

	int dec = n;
		
	vector<int> bin;
	while( dec > 0 ) {
		if( dec % 2 == 0 ){
			bin.push_back( 0 );
		}else{
			bin.push_back( 1 );
		}
		dec = dec >> 1;
	}

	for(int i = 0; i < (int)bin.size(); i++){
		if(bin[i] != 0){
			Q = AdunarePuncte(Q, P);
		}
		P = AdunarePuncte(P, P);
	}
	return Q;
}

bool isPrim(int p){
	if(p == 1){
		cout << "P nu este prim !!! (-_-) " << endl;
		return false;
	}
	if(p == 2){
		return true;
	}else{
		if(p % 2 == 0){
			cout << "P nu este prim !!! (-_-) " << endl;
			return false;
		}else{
			for(int i = 3; i <= sqrt(p); i = i + 2){
				if(p % i == 0){
					cout << "P nu este prim !!! (-_-) " << endl;
					return false;
				}
			}
		}
	}
	return true;
}

int main() {
	cout << "Momentan 5 <= p <= 181 & 2 <= n <= 8" << endl;
	int N, P;
	cout << "Contruim corpul : \n";
	cout << "Dati P = "; cin >> P;
	if(isPrim(P) == false){
		return 0;
	}
	cout << "Dati N = "; cin >> N;

	if(2 > N || N > 8){
		cout << "N nu e bun !!! \n";
		return 0;
	}
	
	Fp F(P);

	Fpn H(F, N);
	H.afisare();

	cout << "Contruim curba : \n";
	cout << "Dati A : \n";
	E A(H, N-1);
	A.afisare();
	cout << endl;
	
	cout << "Dati B : \n";
	E B(H, N-1);
	B.afisare();
	cout << endl;
	
	CURBA Curb(H, A, B);

	int decizie = 0;

	while(decizie != -1){
		for(int i = 0; i < 60; i++){
			cout << '=';
		}
		cout << endl;
		for(int i = 0; i < 60; i++){
			cout << '=';
		}
		cout << endl;
		cout << "Lucram peste : "; H.afisare();

		cout << "Folosind curba  : "; Curb.afisare(); 
		cout << endl;

		cout << "Menu : \n";
		cout << "1) Adunati doua puncte pe curba; \n";
		cout << "2) Multiplicarea unui punct; \n";
		cout << "3) Calculati ordinul unui punct; \n";
		cout << "4) Afisare cardinalul curbei peste Fp^n ; \n";
		cout << "5) Verificati daca un punct este pe curba; \n";
		cout << "0) EXIT! \n";
		cout << endl;
		cout << "Alegeti operatia dorita : "; cin >> decizie;

		switch(decizie){
			case 1 : { // Adunati doua puncte pe curba
				cout << "Dati C1 : \n";
				E C1(H, N-1);
				C1.afisare();
				cout << endl;
				cout << "Dati D1 : \n";
				E D1(H, N-1);
				D1.afisare();
				cout << endl;

				cout << "Dati C2 : \n";
				E C2(H, N-1);
				C2.afisare();
				cout << endl;
				cout << "Dati D2 : \n";
				E D2(H, N-1);
				D2.afisare();
				cout << endl;

				PUNCT Pct1('P', C1, D1);
				cout << "Pct1 : ";
				Pct1.afisare();
				cout << endl;

				PUNCT Pct2('Q', C2, D2);
				cout << "Pct2 : ";
				Pct2.afisare();
				cout << endl;

				cout << "Retultat : "; Pct1.afisare(); cout << "+";
				Pct2.afisare(); cout << " = "; 
				(Curb.AdunarePuncte(Pct1, Pct2)).afisare();

				cout << endl;

				break;
			}

			case 2 : { // Multiplicarea unui punct
				cout << "Dati C1 : \n";
				E C(H, N-1);
				C.afisare();
				cout << endl;
				cout << "Dati D1 : \n";
				E D(H, N-1);
				D.afisare();
				cout << endl;

				PUNCT Pct1('P', C, D);
				cout << "Pct1 : ";
				Pct1.afisare();
				cout << endl;

				cout << "n = ";
				int n;
				cin >> n;

				cout << n << "*"; Pct1.afisare();
				cout << " = ";
				(Curb.Multiplicare(Pct1, n)).afisare();

				cout << endl;

				break;
			}

			case 3 : { // Calculati ordinul unui punct
				cout << "Dati C1 : \n";
				E C(H, N-1);
				C.afisare();
				cout << endl;
				cout << "Dati D1 : \n";
				E D(H, N-1);
				D.afisare();
				cout << endl;

				PUNCT Pct1('P', C, D);
				cout << "Pct1 : ";
				Pct1.afisare();
				cout << endl;

				cout << "Ordinul lui "; Pct1.afisare();
				cout << "peste curba data este : ";
				cout << Curb.Ordinul(Pct1);

				cout << endl;

				break;
			}

			case 4 : { // Afisare cardinalul curbei peste Fp^n
				cout << "Cardinalul curbei este : ";
				cout << Curb.Cardinal();

				cout << endl;

				break;
			}

			case 5 : { // Verificati daca un punct este pe curba
				cout << "Dati C1 : \n";
				E C(H, N-1);
				C.afisare();
				cout << endl;
				cout << "Dati D1 : \n";
				E D(H, N-1);
				D.afisare();
				cout << endl;

				PUNCT Pct1('P', C, D);
				cout << "Pct1 : ";
				Pct1.afisare();
				cout << endl;

				if(Curb.punctValid(Pct1) == true){
					cout << "Puntul se afla pe curba. ";
					cout << endl;
				}else{
					cout << "Puntul nu se afla pe curba. ";
					cout << endl;
				}

				break;
			}

			case 0 : {//EXIT!
				decizie = -1;
				break;
			}

			default : {
				cout << "Nu exista aceasta comanda !!! " << endl;
			}
		}
	}
	
	cout << endl << "Holla world !!! " << endl;
	return 0;
}