#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Node {
    int value, peso;
    Node* next;
};

struct Grafo {
    int num_ver;
    Node** num;
};

Node* crear_node(int, int);
Grafo* crear_grafo(int);
void unir_vertices(Grafo*, int, int, int);
void imprimir_grafo(Grafo*);
void prim_mst(Grafo*);

Node* lista = NULL;

int main() {
    string texto, linea;
    int num_vertices, n1, n2, p;

    ifstream archivo("taller2-ejemplo.txt");
    getline(archivo, linea);
    num_vertices = stoi(linea);

    Grafo* grafo = crear_grafo(num_vertices);

    while (getline(archivo, linea)) {
        istringstream iss(linea);
        iss >> n1 >> n2 >> p;
        unir_vertices(grafo, n1, n2, p);
    }
    
    int opcion, inicio, fin;

    do {
        cout << "Menu:\n";
        cout << "1. Mostrar grafo\n";
        cout << "2. Obtener árbol mínimo cobertor con algoritmo de Prim\n";
        cout << "3. Obtener camino mínimo entre dos vértices con Dijkstra\n";
        cout << "4. Ejecutar algoritmo voraz de coloración\n";
        cout << "5. Salir\n";
        cout << "Elija una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                imprimir_grafo(grafo);
                break;
            case 2:
                cout << "Árbol mínimo cobertor (MST) usando Prim:\n";
                prim(grafo);
                break;
            case 3:
                cout << "Ingrese el vértice de inicio: ";
                cin >> inicio;
                dijkstra(grafo, inicio);
                break;
            case 4:
                cout << "Algoritmo voraz de coloración:\n";
                greedy_coloring(grafo);
                break;
            case 5:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida, intente de nuevo.\n";
        }
    } while(opcion != 5);

    return 0;
}



Node* crear_node(int v, int p) {
    Node* new_node = new Node;
    new_node->value = v;
    new_node->peso = p;
    new_node->next = NULL;
    return new_node;
}

Grafo* crear_grafo(int nv) {
    Grafo* new_grafo = new Grafo;
    new_grafo->num_ver = nv;
    new_grafo->num = new Node*[nv];

    for (int i = 0; i < nv; i++) {
        new_grafo->num[i] = NULL;
    }
    return new_grafo;
}

void unir_vertices(Grafo* grafo, int n1, int n2, int p) {
    Node* new_node = crear_node(n2, p);
    new_node->next = grafo->num[n1];
    grafo->num[n1] = new_node;

    new_node = crear_node(n1, p);
    new_node->next = grafo->num[n2];
    grafo->num[n2] = new_node;
}

void imprimir_grafo(Grafo* grafo) {
    for (int i = 0; i < grafo->num_ver; i++) {
        Node* aux1 = grafo->num[i];
        cout << i << ":";
        while (aux1 != nullptr) {
            cout << " -> (" << aux1->value << ", peso: " << aux1->peso << ")";
            aux1 = aux1->next;
        }
        cout << endl;
    }
}

void prim(Grafo* grafo) {
    //anadimos al algoritmo un total para saber el peso total de nuestro recorrido
    int total = 0;
    int V = grafo->num_ver;
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (Node* adj = grafo->num[u]; adj != nullptr; adj = adj->next) {
            int v = adj->value;
            int peso = adj->peso;

            if (!inMST[v] && key[v] > peso) {
                key[v] = peso;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < V; ++i)
        cout << parent[i] << " - " << i << " \tPeso: " << key[i] << "\n";
        total += key[i];
    cout << "Peso total del recorrido: " << total << endl;
}
