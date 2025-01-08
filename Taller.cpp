#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node{
    int value,peso;
    Node *next;
};

struct Grafo{
    int num_ver;
    Node **num;
};

Node *crear_node(int, int);
Grafo* crear_grafo(int);
void unir_vertices(Grafo *, int, int, int);
void imprimir_grafo(Grafo*); 

Node *lista = NULL;

int main(){
    string texto,linea,num_vertices_,n_1,n_2,p_;
    int num_vertices,n1,n2,p;

    ifstream archivo("taller2.txt");
    getline(archivo,num_vertices_);
    num_vertices = stoi(num_vertices_);
    
    Grafo *grafo = crear_grafo(num_vertices);

    while(getline(archivo,num_vertices_)){
        n_1 = num_vertices_[0];
        n1 = stoi(n_1);
        n_2 = num_vertices_[2];
        n2 = stoi(n_2);
        p_ = num_vertices_[4];
        p = stoi(p_);

        unir_vertices(grafo,n1,n2,p);
    }
    imprimir_grafo(grafo);
    cout<<"\n";
    
}

Node *crear_node(int v, int p){
    Node *new_node = new Node;
    new_node->value = v;
    new_node->peso = p;
    new_node->next = NULL;
    return new_node;
}

Grafo *crear_grafo(int nv){
    Grafo *new_grafo = new Grafo;
    new_grafo->num_ver = nv;
    new_grafo->num = new Node *[nv];

    for (int i=0; i<nv; i++) {
        new_grafo->num[i] = NULL;
    }
    return new_grafo;
}

void unir_vertices(Grafo *grafo, int n1, int n2, int p){
    Node *new_node = crear_node(n1,p);
    new_node->next = grafo->num[n2];
    grafo->num[n2] = new_node;

    new_node = crear_node(n2,p);
    new_node->next = grafo->num[n1];
    grafo->num[n1] = new_node;
}

void imprimir_grafo(Grafo* grafo){
    for (int i = 0; i < grafo->num_ver; i++) {
        Node *aux1 = grafo->num[i];
        cout<<i<<":";
        while (aux1 != nullptr) {
            cout<<" -> ("<<aux1->value<<", peso: "<<aux1->peso<<")";
            aux1 = aux1->next;
        }
        cout<<endl;
    }
}
