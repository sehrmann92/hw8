#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>

using namespace std;

void Euler(double* const p, double* const q, const double dt, double& H, const int dim);
void plot(const double dt);

int main()
{
	//Initialisierung
	int dim=2;
	double e=0.6;
	double p[dim], q[dim];
	p[0]=0.;
	p[1]=sqrt((1.+e)/(1.-e));
	q[0]=1.-e;
	q[1]=0.;
	double H=1./2.*(p[0]*p[0]+p[1]*p[1])-1./sqrt(q[0]*q[0]+q[1]*q[1]);
	double dt=0.0005, TEnde=20*M_PI, TStart=0.;
	int N=(TEnde-TStart)/dt;
	
	//Datei in Abhängigkeit vom Zeitschritt
	stringstream daten;
	daten.str("");	
	daten<<dt<<"_data.txt";									
	ofstream out(daten.str().c_str());	

	out<<TStart<<"\t"<<p[0]<<"\t"<<p[1]<<"\t"<<q[0]<<"\t"<<q[1]<<"\t"<<H<<endl;
	
	//symplectic Euler
	for (int i=0; i<N; i++)
	{
		Euler(p,q,dt,H,dim);
		out<<(i+1)*dt<<"\t"<<p[0]<<"\t"<<p[1]<<"\t"<<q[0]<<"\t"<<q[1]<<"\t"<<H<<endl;		
	}
	
	out.close();
	plot(dt);
	
}

void Euler(double* const p, double* const q, const double dt, double& H, const int dim)
{
	double temp=pow(q[0]*q[0]+q[1]*q[1], 3./2.);
	for (int i=0; i<dim; i++)
	{
		p[i]-=dt/temp*q[i];
		q[i]+=dt*p[i];
	}
	H=1./2.*(p[0]*p[0]+p[1]*p[1])-1./sqrt(q[0]*q[0]+q[1]*q[1]);
}

void plot(const double dt)
{
	stringstream daten,befehle;
	daten.str("");	
	daten<<dt<<"_data.txt";	
	befehle.str("");
	befehle<<dt<<"_befehl.txt";
	
	ofstream out(befehle.str().c_str());
	out<<"set terminal png"<<endl;
	out<<"set output \""<<dt<<"_Energie.png\""<<endl;
	out<<"plot \""<<daten.str()<<"\" u 1:6 w l title \"Energie\""<<endl;
	out<<"unset output"<<endl;
	out<<"set output \""<<dt<<"_Trajektorie.png\""<<endl;
	out<<"plot \""<<daten.str()<<"\" u 4:5 w l"<<endl;
	out<<"unset output"<<endl;
	out.close();
	
	string kommando="gnuplot ";
	kommando.append(befehle.str());
	system(kommando.c_str());
	
}