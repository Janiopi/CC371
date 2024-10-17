#include<iostream>
#include<queue>
#include<vector>

struct arista{
    int datoDestino;
    int peso;
    arista *sgteArista;
};

typedef arista *parista;

struct vertice{
    int datoOrigen;
    arista *adyacente;
    vertice *sgteVertice;  
};


typedef vertice *pvertice;

class grafo{
    private:
        pvertice pGrafo;
    public:
        grafo();
        ~grafo();
        void insertarVertice(int);
        void insertarArista(int,int,int);
        void imprimirGrafo();
        int sumaPesos();
        int numVertices();
        pvertice buscarVertice(int);
        std::vector<parista> seleccionarAristasPorVertice(int);
        std::vector<pvertice> seleccionarVerticesAdyacentes(int);
};

typedef grafo *pGrafo;

grafo::grafo(){
    pGrafo=NULL;
}

grafo::~grafo() {  
    pvertice p, rp;
    parista r, ra;
    p = pGrafo;
    while (p != NULL) {
        r = p->adyacente;
        while (r != NULL) {
            ra = r;
            r = r->sgteArista;
            delete ra;
        }
        rp = p;
        p = p->sgteVertice;
        delete rp;
    }
    pGrafo = nullptr;
}

pvertice grafo::buscarVertice(int origen){
    pvertice p = pGrafo;
    while(p != NULL){
        if(p->datoOrigen == origen)
            return p;
        p = p->sgteVertice;
    }
    return NULL;
}


void grafo::insertarVertice(int x){
    pvertice p;
    p = new vertice;
    p->datoOrigen=x;
    p->adyacente=NULL;
    p->sgteVertice=pGrafo;
    pGrafo=p;
}

void grafo::insertarArista(int origen,int destino,int peso){
    pvertice p = buscarVertice(origen);

       
    if(p!=NULL){
       parista nuevaArista = new arista;
       nuevaArista->datoDestino=destino;
       nuevaArista->peso=peso;
       nuevaArista->sgteArista=p->adyacente;
       p->adyacente=nuevaArista;

    }

}

std::vector<parista>  grafo::seleccionarAristasPorVertice(int origen){
    std::vector<parista> aristasEncontradas;
    pvertice p = buscarVertice(origen);


    if(p!=NULL){
        parista a = p->adyacente;
        while(a!=NULL){
            aristasEncontradas.push_back(a);
            a=a->sgteArista;
        }
    }
    return aristasEncontradas;

}

std::vector<pvertice>  grafo::seleccionarVerticesAdyacentes(int origen){
    std::vector<pvertice> verticesEncontrados;
    pvertice p = buscarVertice(origen);

    if(p != NULL){
        parista a = p->adyacente;

        while(a != NULL){
            pvertice adj = buscarVertice(a->datoDestino);
            if(adj != NULL){
                verticesEncontrados.push_back(adj);
            }
            a=a->sgteArista;
        }


    }
    return verticesEncontrados;
  
}

void grafo::imprimirGrafo(){
    pvertice p;
    parista a;
    p=pGrafo;
    if(p==NULL) std::cout<<"Grafo vacio"<<std::endl;
    else   
        std::cout<<"Vertices||Aristas\n";
        while(p!=NULL){
            std::cout<<p->datoOrigen<<" ";
            a=p->adyacente;
            while(a!=NULL){
                std::cout<<a->datoDestino;
                a=a->sgteArista;
            }
            std::cout<<std::endl;
            p=p->sgteVertice;
        }
}


int grafo::sumaPesos(){
    int suma=0;
    pvertice p;
    parista a;
    p=pGrafo;
    if(p==NULL) std::cout<<"Grafo vacio"<<std::endl;
    else
        while(p!=NULL){
            a=p->adyacente;
            while(a!=NULL){
                suma+=a->peso;
                a=a->sgteArista;
            }
            p=p->sgteVertice;
        }


    return suma;
}

int grafo::numVertices(){
    int n=0;
    pvertice temp = pGrafo;

    while(temp!=NULL){
        n++;
        temp = temp->sgteVertice;
        
    }
    return n;
}
bool bfsColor(grafo& G, int v , int color,std::vector<int> &colores){
    pvertice ve = G.buscarVertice(v);
    std::queue<pvertice> cola;
    cola.push(ve);
    colores[ve->datoOrigen]=color;
    while(!cola.empty()){
        pvertice u = cola.front();

        std::vector<pvertice> vecinos;
        vecinos = G.seleccionarVerticesAdyacentes(u->datoOrigen);
        for(pvertice ve:vecinos){
            if(colores[ve->datoOrigen]==-1){
                colores[ve->datoOrigen]=1-colores[u->datoOrigen];
                cola.push(ve);
            }else if(colores[ve->datoOrigen]==colores[u->datoOrigen]){
                return false;
            }
        }
            


    }
    return true;
}








bool bicoloreable(grafo&G){
    std::vector<int> colores(G.numVertices(), -1);
    for(int i=0;i<G.numVertices();i++){
        if(colores[i]==-1){
            if(!bfsColor(G,i,0,colores))
                return false;
        }
    }
    return true;
}





std::vector<int> BFS(grafo& G, int origen){
    
    pvertice r = G.buscarVertice(origen);
    
    
    int cont=0;
    std::queue<pvertice> cola;
    std::vector<int> ord(G.numVertices(), -1);

    if(r == NULL || G.numVertices()==0){
        std::cout<<"Vertice no encontrado\n";
        return ord;

    }

    cola.push(r);
    std::cout<<"BFS: \n";
    while(!cola.empty()){
        pvertice v = cola.front();
        
        cola.pop();
        
        
        int v_acual = v->datoOrigen;

        if(ord[v_acual]==-1){
            ord[v_acual] = cont++;  
            std::cout<<v_acual<<" ";

            std::vector<pvertice> vecinos;
            vecinos = G.seleccionarVerticesAdyacentes(v->datoOrigen);

            for(pvertice ve:vecinos){
                if(ord[ve->datoOrigen]==-1){
                    cola.push(ve);
                }
            }
        
        }
        
    }
    std::cout<<"\n";
    return ord;
}

int main(){
    grafo G;

    G.insertarVertice(0);
    G.insertarVertice(1);
    G.insertarVertice(2);
    G.insertarVertice(3);
    G.insertarVertice(4);
    G.insertarVertice(5);
    G.insertarVertice(6);
    G.insertarVertice(7);

    G.insertarArista(0,2,0);
    G.insertarArista(0,7,0);
    G.insertarArista(0,5,0);
    G.insertarArista(2,6,0);
    G.insertarArista(7,1,0);
    G.insertarArista(5,3,0);
    G.insertarArista(5,4,0);
    G.insertarArista(3,4,0);


    G.imprimirGrafo();

    std::vector<pvertice> vecinos = G.seleccionarVerticesAdyacentes(0);
    std::cout << "Vecinos del vertice  " << 0 << ": ";
    for (pvertice ve : vecinos) {
        std::cout << ve->datoOrigen << " ";
    }
    std::cout << "\n";




    BFS(G,0);


    if(bicoloreable(G)){
        std::cout<<"\nEl grafo es bicoloreable";
    }else{
        std::cout<<"El grafo no es bicoloreable";
    }



    
    return 0;


}


