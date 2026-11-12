// Tercer corte - Estructura de Datos
// Tema 1: Vectores y Matrices
// Tema 2: Funciones y Registros (struct)

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// ======================================================
//  TEMA 1: VECTORES Y MATRICES
// ======================================================

// Lee n números en un vector
vector<int> leerVector(int n) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cout << "  Elemento [" << i << "]: ";
        cin >> v[i];
    }
    return v;
}

void mostrarVector(const vector<int>& v) {
    cout << "  [ ";
    for (int x : v) cout << x << " ";
    cout << "]\n";
}

int sumaVector(const vector<int>& v) {
    int suma = 0;
    for (int x : v) suma += x;
    return suma;
}

int mayorVector(const vector<int>& v) {
    int mayor = v[0];
    for (int x : v) if (x > mayor) mayor = x;
    return mayor;
}

int menorVector(const vector<int>& v) {
    int menor = v[0];
    for (int x : v) if (x < menor) menor = x;
    return menor;
}

typedef vector<vector<int>> Matriz;

Matriz leerMatriz(int filas, int cols) {
    Matriz m(filas, vector<int>(cols));
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < cols; j++) {
            cout << "  M[" << i << "][" << j << "]: ";
            cin >> m[i][j];
        }
    return m;
}

void mostrarMatriz(const Matriz& m) {
    for (const auto& fila : m) {
        cout << "  ";
        for (int x : fila) cout << setw(5) << x;
        cout << "\n";
    }
}

Matriz transpuesta(const Matriz& m) {
    int f = m.size(), c = m[0].size();
    Matriz t(c, vector<int>(f));
    for (int i = 0; i < f; i++)
        for (int j = 0; j < c; j++)
            t[j][i] = m[i][j];
    return t;
}

Matriz sumarMatrices(const Matriz& a, const Matriz& b) {
    Matriz r(a.size(), vector<int>(a[0].size()));
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = 0; j < a[0].size(); j++)
            r[i][j] = a[i][j] + b[i][j];
    return r;
}

Matriz multiplicarMatrices(const Matriz& a, const Matriz& b) {
    int f = a.size(), c = b[0].size(), k = b.size();
    Matriz r(f, vector<int>(c, 0));
    for (int i = 0; i < f; i++)
        for (int j = 0; j < c; j++)
            for (int x = 0; x < k; x++)
                r[i][j] += a[i][x] * b[x][j];
    return r;
}

void menuVectores() {
    int n;
    cout << "\n--- VECTORES ---\n";
    cout << "Tamano del vector: ";
    cin >> n;
    if (n <= 0) { cout << "Tamano invalido.\n"; return; }

    vector<int> v = leerVector(n);
    cout << "Vector: ";
    mostrarVector(v);
    cout << "  Suma:    " << sumaVector(v) << "\n";
    cout << "  Mayor:   " << mayorVector(v) << "\n";
    cout << "  Menor:   " << menorVector(v) << "\n";
    cout << "  Promedio: " << fixed << setprecision(2)
         << (double)sumaVector(v) / n << "\n";
}

void menuMatrices() {
    int f, c;
    cout << "\n--- MATRICES ---\n";
    cout << "Filas y columnas: ";
    cin >> f >> c;
    if (f <= 0 || c <= 0) { cout << "Dimensiones invalidas.\n"; return; }

    cout << "Matriz A:\n";
    Matriz A = leerMatriz(f, c);
    cout << "Matriz B (mismo tamano):\n";
    Matriz B = leerMatriz(f, c);

    cout << "\nA:\n";  mostrarMatriz(A);
    cout << "B:\n";    mostrarMatriz(B);
    cout << "A + B:\n"; mostrarMatriz(sumarMatrices(A, B));
    cout << "Transpuesta de A:\n"; mostrarMatriz(transpuesta(A));

    // Multiplicacion A x B^T (siempre es valida: f x c por c x f)
    cout << "A x B^T:\n";
    mostrarMatriz(multiplicarMatrices(A, transpuesta(B)));
}

// ======================================================
//  TEMA 2: FUNCIONES Y REGISTROS (STRUCT)
// ======================================================

struct Estudiante {
    int codigo;
    string nombre;
    double nota1, nota2, nota3;
};

double calcularPromedio(const Estudiante& e) {
    return (e.nota1 + e.nota2 + e.nota3) / 3.0;
}

string estadoEstudiante(const Estudiante& e) {
    return calcularPromedio(e) >= 3.0 ? "Aprobado" : "Reprobado";
}

Estudiante leerEstudiante() {
    Estudiante e;
    cout << "  Codigo: ";
    cin >> e.codigo;
    cin.ignore();
    cout << "  Nombre: ";
    getline(cin, e.nombre);
    cout << "  Nota 1: "; cin >> e.nota1;
    cout << "  Nota 2: "; cin >> e.nota2;
    cout << "  Nota 3: "; cin >> e.nota3;
    return e;
}

void mostrarEstudiante(const Estudiante& e) {
    cout << "  " << setw(6) << e.codigo
         << " | " << left << setw(18) << e.nombre << right
         << " | " << fixed << setprecision(2) << setw(5) << calcularPromedio(e)
         << " | " << estadoEstudiante(e) << "\n";
}

void mostrarRegistro(const vector<Estudiante>& lista) {
    if (lista.empty()) { cout << "  (No hay estudiantes registrados)\n"; return; }
    cout << "  Codigo | Nombre             | Prom. | Estado\n";
    cout << "  -------+--------------------+-------+----------\n";
    for (const auto& e : lista) mostrarEstudiante(e);
}

// Busqueda por codigo: devuelve el indice o -1 si no existe
int buscarEstudiante(const vector<Estudiante>& lista, int codigo) {
    for (size_t i = 0; i < lista.size(); i++)
        if (lista[i].codigo == codigo) return i;
    return -1;
}

int mejorEstudiante(const vector<Estudiante>& lista) {
    int mejor = 0;
    for (size_t i = 1; i < lista.size(); i++)
        if (calcularPromedio(lista[i]) > calcularPromedio(lista[mejor]))
            mejor = i;
    return mejor;
}

void menuRegistros() {
    vector<Estudiante> lista;
    int op;
    do {
        cout << "\n--- REGISTROS (STRUCT) ---\n"
             << "1. Agregar estudiante\n"
             << "2. Mostrar todos\n"
             << "3. Buscar por codigo\n"
             << "4. Mejor promedio\n"
             << "0. Volver\n"
             << "Opcion: ";
        cin >> op;

        switch (op) {
            case 1:
                lista.push_back(leerEstudiante());
                break;
            case 2:
                mostrarRegistro(lista);
                break;
            case 3: {
                int cod;
                cout << "  Codigo a buscar: ";
                cin >> cod;
                int pos = buscarEstudiante(lista, cod);
                if (pos == -1) cout << "  No encontrado.\n";
                else mostrarEstudiante(lista[pos]);
                break;
            }
            case 4:
                if (lista.empty()) cout << "  No hay estudiantes.\n";
                else {
                    cout << "  Mejor promedio:\n";
                    mostrarEstudiante(lista[mejorEstudiante(lista)]);
                }
                break;
            case 0:
                break;
            default:
                cout << "  Opcion invalida.\n";
        }
    } while (op != 0);
}

// ======================================================
//  PROGRAMA PRINCIPAL
// ======================================================

int main() {
    int opcion;
    do {
        cout << "\n===== TERCER CORTE =====\n"
             << "1. Vectores\n"
             << "2. Matrices\n"
             << "3. Funciones y registros (struct)\n"
             << "0. Salir\n"
             << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuVectores();  break;
            case 2: menuMatrices();  break;
            case 3: menuRegistros(); break;
            case 0: cout << "Hasta luego.\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}
