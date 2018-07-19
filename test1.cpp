#include <iostream>
#include <math.h>
#include <set>

using namespace std;

class Fp{      // Fp p-prim
	int P;

	public:
		// Contruim un Fp
		Fp(int p = 1){
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
		int getP(){
			return this->P;
		}

		// Modifica p-ul
		int setP(int p){
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
		}

		// Afiseaza corpul cu p elemete
		void afisare(){
			if(this->P == 1){
				cout << " Fp" << endl;
			}else{
				cout << " F" << this->P << endl;
			}
		}
};

class Punct{    // P(x,y)
	char Nume;
	int X;
	int Y;
	bool Inf;

	public:
		// Contruim un punct din R^2
		Punct(char n = ' ', int x = 0, int y = 0, bool inf = false){
			this->Nume = n;
			this->X = x;
			this->Y = y;
			this->Inf = inf;
		}

		// Seteaza numele punctului
		int setNume(int n){
			this->Nume = n;
			return n;
		}

		// Seteaza coordonata X a punctului
		int setX(int x){
			this->X = x;
			return x;
		}

		// Seteaza coordonata Y a punctului
		int setY(int y){
			this->Y = y;
			return y;
		}

		// Seteaza daca punctul este punct de la infinit
		bool setInf(bool inf){
			this->Inf = inf;
			return inf;
		}

		// Returneaza numele punctului
		int getNume(){
			return this->Nume;
		}

		// Returneaza coordonata X a punctului
		int getX(){
			return this->X;
		}

		// Returneaza coordonata Y a punctului
		int getY(){
			return this->Y;
		}

		// Returneaza daca punctul este punct de la infinit
		bool getInf(){
			return this->Inf;
		}

		// Afiseaza punctul din R^2
		void afisare(){
			if(this->Inf == true){
				cout << this->Nume << "(inf,inf)";
			}else{
				cout << this->Nume << "(" << this->X << "," << this->Y << ")";
			}
		}
};

class Curba{    // E(Fp): y^2 = x^3 + A*x + B
	Fp F;
	int A;
	int B;

	public:

		// Contruim o curba eliptica
		Curba(Fp f, int a = 0, int b = 0){
			if(a == 0 && b == 0){
				this->F = f;
				this->A = 0;
				this->B = 0;
			}else{
				if( (4*a*a*a + 27*b*b) % f.getP() == 0 ){
					cout << "A -ul si B -ul nu desciu o curba valida !!!" << endl;
					return;
				}
				this->F = f;
				this->A = a % f.getP();
				this->B = b % f.getP();
			}
		}

		// Returneaza corpul peste care definim curba
		Fp getF(){
			return this->F;
		}

		// Retuneaza coeficientul lui x 
		int getA(){
			return this->A;
		}

		// Returneaza termenul liber
		int getB(){
			return this->B;
		}

		// Steaza un alt corp pentru curba
		Fp setFp(Fp fp){
			Fp temp = this->F;

			if(this->A != 0 && this->B != 0){
				if( (4*this->A*this->A*this->A + 27*this->B*this->B) % fp.getP() == 0 ){
					cout << "A -ul si B -ul nu descriu o curba valida peste noul Fp !!! " << endl;
					this->A = 0;
					this->B = 0;
				}
			}

			this->F = fp;
			this->A = this->A % fp.getP();
			this->B = this->B % fp.getP();
			return temp;
		}

		// Seteaza coeficientul lui x 
		int setA(int a){
			int temp = this->A;

			a = a % this->F.getP();
			this->A = a;
			return temp;
		}

		// Seteaza termenul liber
		int setB(int b){
			int temp = this->B;

			b = b % this->F.getP();
			this->B = b;
			return temp;
		}

		// Afiseaza curba eliptica
		void afisare(){
			if(this->A == 0 && this->B == 0){
				cout << "y^2 = x^3 + A*x + B " << endl;
			}else{
				cout << "y^2 = x^3";
				if(this->A != 0){
					cout << " + " << this->A << "*x"; 
				}
				if (this->B != 0){
					cout << " + "<< this->B;
				}
				cout << ";" << endl;
			}
		}

		// Verifica daca un punct apartine curbei
		bool punctValid(Punct Q){
			int temp = ((int)pow(Q.getX(),3) + this->A*Q.getX() + this->B) % (this->F).getP();
			
			if(Q.getInf() == true){
				return true;
			}
			
			if((Q.getY()*Q.getY()) % (this->F).getP() == temp){
				return true;
			}
			
			return false;
		}
};

// Capculeaza a/b(mod p)
int ImpartireModP(int a, int b, int p){
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

// Cauta toate punctele unei curbe peste un Fp
int PuncteleCurbei(Curba C){
	Punct P;
	set<int> RS; // Vectorul de resturi patratice
	RS.insert(0);
	for(int i = 1; i < (C.getF()).getP(); i++){
		int it; 
		it = i;
		it = it % (C.getF()).getP();
		for(int j = 2; j <= ( ((C.getF()).getP() - 1) / 2); j++){
			it = it * i;
			it = it % (C.getF()).getP();
		}
		if( it == 1 ){
			RS.insert(i);
		}
	}
	
	int it = 1;
	char n = 'A';

	// Cautam puncte posibile
	for(int i = 0; i < (C.getF()).getP(); i++){
		int yp = (i*i*i + C.getA()*i + C.getB()) % (C.getF()).getP();
		
		if(yp == 0){
			P.setNume(n);
			P.setX(i);
			P.setY(0);
			it = it + 1;
			n = n + 1;
			P.afisare();cout << "; ";
		}else{
			if(RS.count(yp) != 0){   // Cauta yp printre resturile patratice
				P.setNume(n);
				P.setX(i);
				P.setY(RadicalModular(yp, (C.getF()).getP()));
				it = it + 1;
				n = n + 1;
				P.afisare();cout << "; ";
				P.setNume(n);
				P.setX(i);
				P.setY((C.getF()).getP() - RadicalModular(yp, (C.getF()).getP()));
				it = it + 1;
				n = n + 1;
				P.afisare();cout << "; ";
			}
		}
	}
	P.setNume(n);
	P.setX(0);
	P.setY(0);
	P.setInf(true);
	P.afisare();cout << "; ";
	
	return it;
}

// Aduna 2 puncte de pe o curba
Punct AdunarePuncte(Punct P, Punct Q, Curba C){
	// Verific daca vreunul e punct de la infinit
	if(P.getInf() == true){
		Punct R('R',Q.getX(),Q.getY());
		return R;
	}
	if(Q.getInf() == true){
		Punct R('R',P.getX(),P.getY());
		return R;
	}

	// Verific daca punctele sunt valide
	if(C.punctValid(P) == false || C.punctValid(Q) == false){
		cout << "Unul din punte nu verifica ecuatia curbei !!!";
		Punct R(' ',0,0);
		return R;
	}

	char n = 'R';
	int x, y;
	
	if( (P.getX() == Q.getX()) && (P.getY() == Q.getY()) ){
		if( P.getY() == 0 ){
			x = 0; y = 0;
			Punct R(n,x,y,true);
			return R;
		}else{
			int m = ImpartireModP( (3*P.getX()*P.getX() + C.getA()), (2*P.getY()), (C.getF()).getP());

			x = (m*m - 2*P.getX()) % (C.getF()).getP();
			
			y = ((-1)*P.getY() - m*(x - P.getX())) % (C.getF()).getP();
			
			if(y < 0){
				y = (C.getF()).getP() + y;
			}
			if(x < 0){
				x = (C.getF()).getP() + x;
			}
			
			Punct R(n,x,y);
			return R;
		}
	}else{
		if( P.getX() == Q.getX() ){
			x = 0; y = 0;
			Punct R(n,x,y,true);
			return R;
		}else{
			int m = ImpartireModP( (Q.getY() - P.getY()), (Q.getX() - P.getX()), (C.getF()).getP());
			
			x = (m*m - (P.getX() + Q.getX())) % (C.getF()).getP();
			
			y = ((-1)*P.getY() - m*(x - P.getX())) % (C.getF()).getP();
			
			if(y < 0){
				y = (C.getF()).getP() + y;
			}
			if(x < 0){
				x = (C.getF()).getP() + x;
			}
			
			Punct R(n,x,y);
			return R;
		}
	}
}

// Calculeaza cardinalul unei curbe peste un Fp
int Cardinal(Curba C){
	int card = (C.getF()).getP() + 1;
	int p = (C.getF()).getP();
	int sum = 0;

	if( (p % 3 == 2 && C.getA() == 0) || (p % 4 == 3 && C.getB() == 0) ){
		return card;
	}

	for(int i = 0; i < (C.getF()).getP(); i++){
		int y = (i*i*i + i*C.getA() + C.getB()) % (C.getF()).getP();
		int temp = y;
		temp = temp % (C.getF()).getP();
		for(int j = 2 ; j <= ( ((C.getF()).getP() - 1) / 2); j++){
			temp = temp * y;
			temp = temp % (C.getF()).getP();
		}
		if(temp == (C.getF()).getP()-1){
			temp = temp - (C.getF()).getP();
		}
		//cout << i << "are : " << temp << endl;
		sum = sum + temp;
	}
	
	card = card + sum;
	return card;
}

// Ordinul unui punct 
int Ordinul(Punct P, Curba C){
	int ord = 1;
	
	if(C.punctValid(P) == false){
		cout << "Puntul nu verifica ecuatia curbei !!!";
		return -1;
	}

	if(P.getInf() == true){
		cout << "Puntul este punct de la infinit !!!";
		return ord;
	}

	Punct Q = AdunarePuncte(P,P,C);
	ord = 2;
	//Q.afisare();

	while(Q.getInf() != true){
		Q = AdunarePuncte(Q,P,C);
		//Q.afisare();
		ord = ord + 1;
	}
	return ord;
}

Punct PuterePunct(Punct P, Curba C, int n){
	int it;
	if(n == 1){
		return P;
	}else{
		Punct Q = AdunarePuncte(P,P,C);
		if(n == 2){
			return Q;
		}else{
			it = 2;
			while(it < n){
				Q = AdunarePuncte(Q,P,C);
				it = it + 1;
			}
			return Q;
		}
	}
}

int main (){
	Fp F(1);
	Curba C(F,0,0);

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
		cout << "Lucram peste : "; F.afisare();
		cout << "Folosind curba  : "; C.afisare(); 
		for(int i = 0; i < 60; i++){
			cout << '=';
		}
		cout << endl << endl;

		cout << "Menu : \n";
		cout << "1) Setati P-ul corpului cu p elemente; \n";
		cout << "2) Setati A-ul si B-ul pentru curba; \n";
		cout << "3) Listati toate punctele curbei peste Fp -ul curent; \n";
		cout << "4) Verificati daca un punct este pe curba; \n";
		cout << "5) Calculati ordinul unui punct; \n";
		cout << "6) Adunati doua puncte pe curba; \n";
		cout << "7) Afisare cardinalul curbei peste Fp -ul curent; \n";
		cout << "8) Calculati nP; \n";
		cout << "0) EXIT! \n";
		cout << endl;
		cout << "Alegeti operatia dorita : "; cin >> decizie;

		switch(decizie){

			case 1 :{//Setati P-ul corpului cu p elemete
				int temp;
				cout << "Dati P-ul dorit : "; cin >> temp;
				F.setP(temp);
				C.setFp(F);
				break;
			}
			case 2 :{//Setati A-ul si B-ul pentru curba
				int A, B;
				cout << "Dati A -ul : "; cin >> A;
				cout << "Dati B -ul : "; cin >> B;
				if( (4*A*A*A + 27*B*B) % (C.getF()).getP() == 0){
					cout << " A -ul si B-ul nu descriu o curba valida !!!" << endl;
				}else{
					C.setA(A);
					C.setB(B);
				}
				break;
			}
			case 3 :{//Listati toate punctele curbei peste Fp -ul curent
				cout << "Punctele curbei sunt : ";
				int it = PuncteleCurbei(C);
				cout << endl;
				cout << "Curba contine " << it << " puncte peste ";
				F.afisare();
				cout << endl;
				break;
			}
			case 4 :{//Verificati daca un punct este pe curba
				int x, y;
				char c;
				cout << "Dati numele punctului : "; cin >> c;
				cout << "Dati x -ul : "; cin >> x;
				cout << "Dati y -ul : "; cin >> y;
				Punct P(c,x,y);
				if(C.punctValid(P) == true){
					cout << "Punctul "; P.afisare(); cout << " este pe curba. \n";
				}else{
					cout << "Punctul "; P.afisare(); cout << " nu este pe curba. \n";
				}
				break;
			}
			case 5 :{//Calculati ordinul unui punct
				int x, y;
				char c;
				cout << "Dati numele punctului : "; cin >> c;
				cout << "Dati x -ul : "; cin >> x;
				cout << "Dati y -ul : "; cin >> y;
				Punct P(c,x,y);
				if(C.punctValid(P) == false){
					cout << "Punctul "; P.afisare(); cout << " nu este pe curba. \n";
					break;
				}else{
					cout << "Ordinul punctului "; P.afisare();
					cout << " pe curba este : " << Ordinul(P,C);
					cout << endl;
				}
				break;
			}
			case 6 :{//Adunati doua puncte pe curba
				int x1, y1, x2, y2;
				char c, d;
				cout << "Dati numele primului punctul : "; cin >> c;
				cout << "Dati x1 -ul : "; cin >> x1;
				cout << "Dati y1 -ul : "; cin >> y1;
				Punct P(c,x1,y1);
				cout << "Dati numele pentru al 2-lea punct : "; cin >> d;
				cout << "Dati x2 -ul : "; cin >> x2;
				cout << "Dati y2 -ul : "; cin >> y2;
				Punct Q(d,x2,y2);
				if(C.punctValid(P) == false || C.punctValid(Q) == false){
					cout << "Un punct nu se afla pe curba !!! \n";
					break;
				}else{
					P.afisare(); cout << " + ";
					Q.afisare(); cout << " = ";
					(AdunarePuncte(P,Q,C)).afisare();
					cout << endl; 
				}
				break;
			}
			case 7 :{//Afisare cardinalul curbei peste Fp -ul curent
				cout << "Cardinalul curbei peste F" << F.getP();
				cout << " este " << Cardinal(C) << endl;
				break;
			}
			case 8 :{//Calculati nP
				int n, x, y;
				char c;
				cout << "Dati numele punctului : "; cin >> c;
				cout << "Dati x -ul : "; cin >> x;
				cout << "Dati y -ul : "; cin >> y;
				cout << "Dati n -ul : "; cin >> n;
				Punct P(c,x,y);
				cout << n << "*";P.afisare();
				cout << " = ";(PuterePunct(P,C,n)).afisare();
				cout << endl; 
				break;
			}
			case 0 :{//EXIT!
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