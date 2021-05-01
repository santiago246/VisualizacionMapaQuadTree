#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;
ofstream file("map.js");

template<class T>
struct Punto {
    T x;
    T y;
    Punto() {
        x = 0;
        y = 0;
    }
    Punto(T x, T y) {
        this->x = x;
        this->y = y;
    }
};

template<class T >
struct Nodo {
    Punto<T> arribaIz, abajoDer;
    vector<Punto<T>> puntos;
    Nodo() {
        arribaIz = NULL;
        abajoDer = NULL;
    }
    Nodo(Punto<T> arribaIz, Punto<T> abajoDer) {
        this->arribaIz = arribaIz;
        this->abajoDer = abajoDer;
    }
};

template<class T>
class QuadTree {
    int profundidad;
    int n;
    vector<Punto<T>> puntos;
    Punto<T> limSupIzquierdo;
    Punto<T> limInfDerecho;
    QuadTree* divSupIzquierda;
    QuadTree* divSupDerecha;
    QuadTree* divInfIzquierda;
    QuadTree* divInfDerecha;

public:
    void insertar(Punto<T>,int);
    void buscar(Punto<T>,int);
    bool verifica(Punto<T>);
    void dibujar(int);
    QuadTree() {
        n = 0;
        limSupIzquierdo = Punto<T>(0, 0);
        limInfDerecho = Punto<T>(0, 0);
        puntos = NULL;
        divSupIzquierda = NULL;
        divSupDerecha = NULL;
        divInfIzquierda = NULL;
        divInfDerecha = NULL;
        profundidad = 0;
    }
    QuadTree(Punto<T> limSupIzquierdo, Punto<T>  limInfDerecho, int profundidad) {
        
        n = 0;
        divSupIzquierda = NULL;
        divSupDerecha = NULL;
        divInfIzquierda = NULL;
        divInfDerecha = NULL;
        this->limSupIzquierdo = limSupIzquierdo;
        this->limInfDerecho = limInfDerecho;
        this->profundidad = profundidad;
        
        if (profundidad <= 0) {
            return;
        }
        divSupIzquierda = new QuadTree(limSupIzquierdo,Punto<T>((limSupIzquierdo.x + limInfDerecho.x) / 2.0,(limSupIzquierdo.y + limInfDerecho.y) / 2.0), profundidad-1);
        divSupDerecha = new QuadTree(Punto<T>((limSupIzquierdo.x + limInfDerecho.x) / 2.0, limSupIzquierdo.y), Punto<T>(limInfDerecho.x, (limSupIzquierdo.y + limInfDerecho.y) / 2.0), profundidad - 1);
        divInfIzquierda = new QuadTree(Punto<T>(limSupIzquierdo.x , (limSupIzquierdo.y + limInfDerecho.y) / 2.0), Punto<T>((limSupIzquierdo.x + limInfDerecho.x) / 2.0,  limInfDerecho.y), profundidad - 1);
        divInfDerecha = new QuadTree(Punto<T>((limSupIzquierdo.x + limInfDerecho.x) / 2.0, (limSupIzquierdo.y + limInfDerecho.y) / 2.0), limInfDerecho, profundidad - 1);
        //cout << "profundidad: " << profundidad << endl;
    }
};


template<class T>
void QuadTree<T>::dibujar(int prof) {
    if (prof <= 0) {
        if (n>0) {
            //cout << "Lim Sup Izquierdo: " << limSupIzquierdo.x << ", " << limSupIzquierdo.y << endl;
            //cout << "Lim Inf Derecho: " << limInfDerecho.x << ", " << limInfDerecho.y << endl;
            //cout << "cantidad de puntos en el cuadrante: " << n << endl;

            file << "var latlngs = [\n";
            file << "[\n";
            file<< "[[" << limInfDerecho.y << "," << limSupIzquierdo.x << "],[" << limSupIzquierdo.y << "," << limSupIzquierdo.x << "],[" << limSupIzquierdo.y << "," << limInfDerecho.x <<  "],[" << limInfDerecho.y << "," << limInfDerecho.x << "]]," << endl;
            file << "],\n";
            file << "];\n";
            

           
            if (n < 7)
                file << "var polygon = L.polygon(latlngs, {color: '#ffff52', fill:true}).addTo(mymap);\n";
            else if (n < 14)
                file << "var polygon = L.polygon(latlngs, {color: '#ffff00', fill:true }).addTo(mymap);\n";
            else if (n < 22)
                file << "var polygon = L.polygon(latlngs, {color: '#f5d033', fill:true }).addTo(mymap);\n";
            else if (n < 30)
                file << "var polygon = L.polygon(latlngs, {color: '#fad201', fill:true }).addTo(mymap);\n";
            else  if (n < 38)
                file << "var polygon = L.polygon(latlngs, {color: '#efc300', fill:true}).addTo(mymap);\n";
            else if (n < 48)
                file << "var polygon = L.polygon(latlngs, {color: '#e0b600',fill:true }).addTo(mymap);\n";
            else if (n < 58)
                file << "var polygon = L.polygon(latlngs, {color: '#dc4340', fill:true }).addTo(mymap);\n";
            else if (n < 68)
                file << "var polygon = L.polygon(latlngs, {color: '#d33a3a', fill:true }).addTo(mymap);\n";
            else if (n < 78)
                file << "var polygon = L.polygon(latlngs, {color: '#cb3234', fill:true}).addTo(mymap);\n";
            else if (n < 88)
                file << "var polygon = L.polygon(latlngs, {color: '#c3292e', fill:true }).addTo(mymap);\n";
            else if (n < 98)
                file << "var polygon = L.polygon(latlngs, {color: '#ba1f28', fill:true }).addTo(mymap);\n";
            else if (n < 110)
                file << "var polygon = L.polygon(latlngs, {color: '#b21322', fill:true }).addTo(mymap);\n";
            else
                file << "var polygon = L.polygon(latlngs, {color: '#842725', fill: true }).addTo(mymap);\n";            
        }
        return;
    }
            divSupDerecha->dibujar( prof - 1);
            divInfDerecha->dibujar(prof - 1);
            divSupIzquierda->dibujar(prof - 1);
            divInfIzquierda->dibujar(prof - 1);
    
}

template<class T>
bool QuadTree<T>::verifica(Punto<T> p){
    for (int i = 0; i < n; i++) {
        if (puntos[i].x == p.x && puntos[i].y == p.y) return 1;
     }
    return 0;
}

template<class T>
void QuadTree<T>::insertar(Punto<T> p, int prof) {
    if (prof <= 0) {
        puntos.push_back(p);
        n++;
        //cout << "inserto en el cuadrante: " << limSupIzquierdo.x << ", " << limSupIzquierdo.y << " y " << limInfDerecho.x << ", " << limInfDerecho.y << endl;
        return;
        }
    
    if ((limSupIzquierdo.x + limInfDerecho.x) / 2 <= p.x) {
        if ((limSupIzquierdo.y + limInfDerecho.y) / 2 <= p.y) {
            return divSupDerecha->insertar(p, prof - 1);
        }

        else {
            return divInfDerecha->insertar(p, prof - 1);
        }
    }
    else {
        if ((limSupIzquierdo.y + limInfDerecho.y) / 2 <= p.y) {
            return divSupIzquierda->insertar(p, prof - 1);
        }

        else {
            return divInfIzquierda->insertar(p, prof - 1);
        }
    }
}


template<class T>
void QuadTree<T>::buscar(Punto<T> p,int prof) {
    if (prof <= 0) {
        if (verifica(p)) {
            cout << "El punto: " << p.x <<","<< p.y << " si esta" << endl;
            cout << "Lim Sup Izquierdo: " << limSupIzquierdo.x << ", " << limSupIzquierdo.y << endl;
            cout << "Lim Inf Derecho: " << limInfDerecho.x << ", " << limInfDerecho.y << endl;
        }
        else cout << "El punto: "<< p.x << p.y <<" NO esta" << endl;
        return;
    }
    if ((limSupIzquierdo.x + limInfDerecho.x) / 2 <= p.x) {
        if ((limSupIzquierdo.y + limInfDerecho.y) / 2 <= p.y) {
            return divSupDerecha->buscar(p, prof - 1);
        }

        else {
            return divInfDerecha->buscar(p, prof - 1);
        }
    }
    else {
        if ((limSupIzquierdo.y + limInfDerecho.y) / 2 <= p.y) {
            return divSupIzquierda->buscar(p, prof - 1);
        }

        else {
            return divInfIzquierda->buscar(p, prof - 1);
        }
    }
};



int main() {
    int profundidad = 2;
    Punto<double> limiteSupIzquierdo(-200.0, 100.0);
    Punto<double> limiteInfDerecho(200.0, -100.0);
    
    QuadTree<double> quad(limiteSupIzquierdo, limiteInfDerecho, profundidad);
   
    //quad.insertar(Punto<double>(2.0, 2.0), profundidad);
    
    ifstream ifile("puntos.tsv", ios::in);
   
    if (!ifile.is_open()) {
        exit(1);
    }

    double num = 0.0;
    double x, y;
    //quad.buscar(Punto<int>(1, 1), 1);

 
    while (ifile >> num) {
        y = num;
        ifile >> num;
        x = num; 
        //cout << num << endl;
        quad.insertar(Punto<double>(x, y), profundidad);   
    }


    
   
    file << "const tilesProvider= 'https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png'"<<endl;
    file << "var mymap = L.map('mapid').setView([0, 0], 3);\n";
    file << "L.tileLayer(tilesProvider, {\n";
    file << "maxZoom:18,\n";
    file << "}).addTo(mymap);\n";
    

    quad.dibujar(profundidad);
    
    file.close();

   

    return 0;
}