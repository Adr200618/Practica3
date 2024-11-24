#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

string determinarCuadrante(double x, double y) {
    if (x > 0 && y > 0) return "Cuadrante I";
    else if (x < 0 && y > 0) return "Cuadrante II";
    else if (x < 0 && y < 0) return "Cuadrante III";
    else if (x > 0 && y < 0) return "Cuadrante IV";
    else if (x == 0 && y != 0) return "Sobre el eje Y";
    else if (y == 0 && x != 0) return "Sobre el eje X";
    else return "Origen";
}

bool sonColineales(pair<double, double> p1, pair<double, double> p2, pair<double, double> p3) {
    return (p2.second - p1.second) * (p3.first - p2.first) == (p3.second - p2.second) * (p2.first - p1.first);
}

void imprimirEcuacionLinea(pair<double, double> p1, pair<double, double> p2) {
    double A = p2.second - p1.second;
    double B = p1.first - p2.first;
    double C = (p2.first * p1.second) - (p1.first * p2.second);
    cout << "Ecuación de la línea: " << A << "x + " << B << "y + " << C << " = 0" << endl;
}

double distancia(pair<double, double> p1, pair<double, double> p2) {
    return sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2));
}

double distanciaMaxima(vector<pair<double, double>>& puntos, double x_min, double x_max, double y_min, double y_max) {
    double max_distancia = 0;
    for (size_t i = 0; i < puntos.size(); ++i) {
        for (size_t j = i + 1; j < puntos.size(); ++j) {
            if ((puntos[i].first >= x_min && puntos[i].first <= x_max &&
                 puntos[i].second >= y_min && puntos[i].second <= y_max) &&
                (puntos[j].first >= x_min && puntos[j].first <= x_max &&
                 puntos[j].second >= y_min && puntos[j].second <= y_max)) {
                double d = distancia(puntos[i], puntos[j]);
                max_distancia = max(max_distancia, d);
            }
        }
    }
    return max_distancia;
}

void distanciasDesdePunto(pair<double, double> puntoSeleccionado, vector<pair<double, double>>& puntos) {
    cout << "Distancias desde el punto (" << puntoSeleccionado.first << ", " << puntoSeleccionado.second << "):" << endl;
    for (const auto& p : puntos) {
        cout << "Distancia a (" << p.first << ", " << p.second << ") es: " << distancia(puntoSeleccionado, p) << endl;
    }
}

int main() {
    vector<pair<double, double>> puntos;
    double x_min, x_max, y_min, y_max;

    cout << "Ingrese los límites del cuadrante (x_min, x_max, y_min, y_max): ";
    cin >> x_min >> x_max >> y_min >> y_max;

    while (true) {
        cout << "Ingrese las coordenadas x, y (o 'q' para salir): ";
        string entrada;
        cin >> entrada;
        if (entrada == "q") break;

        double x = stod(entrada);
        double y;
        cin >> entrada;
        y = stod(entrada);
        
        puntos.push_back(make_pair(x, y));
        
        string cuadrante = determinarCuadrante(x, y);
        cout << "La coordenada (" << x << ", " << y << ") se encuentra en: " << cuadrante << endl;
    }

    for (size_t i = 0; i < puntos.size(); ++i) {
        for (size_t j = i + 1; j < puntos.size(); ++j) {
                        for (size_t k = j + 1; k < puntos.size(); ++k) {
                if (sonColineales(puntos[i], puntos[j], puntos[k])) {
                    cout << "Los puntos (" << puntos[i].first << ", " << puntos[i].second << "), "
                         << "(" << puntos[j].first << ", " << puntos[j].second << "), "
                         << "(" << puntos[k].first << ", " << puntos[k].second << ") están en la misma línea." << endl;
                    imprimirEcuacionLinea(puntos[i], puntos[j]);
                }
            }
        }
    }

    double max_distancia = distanciaMaxima(puntos, x_min, x_max, y_min, y_max);
    cout << "La distancia máxima encontrada entre dos puntos dentro de los límites es: " << max_distancia << endl;

    if (!puntos.empty()) {
        pair<double, double> punto_seleccionado = puntos[0];
        distanciasDesdePunto(punto_seleccionado, puntos);
    }

    return 0;
}