#include<iostream>

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
        //-grafo(); 
        void insertarVertice(int);
        void insertarArista(int,int,int);
        void imprimirGrafo();
        int sumaPesos();
};
typedef grafo *pGrafo;

grafo::grafo(){
    pGrafo=NULL;
}

/*
grafo ::-grafo(){
    pvertice p,rp;
    parista r,ra;
    p=pGrafo;
    while(p!=NULL){
        r=p->adyacente;
        while(r!=NULL){
            ra=r;
            r=r->sgteArista;
            delete ra;
        }
        rp=p;
        p=p->sgteVertice;
        delete rp;
    }
}
*/

void grafo::insertarVertice(int x){
    pvertice p;
    p = new vertice ;
    p->datoOrigen=x;
    p->adyacente=NULL;
    p->sgteVertice=pGrafo;
    pGrafo=p;
}


//Al método insertarArista se le agrego un tercer parámetro, el peso de la arista
void grafo::insertarArista(int x,int y,int peso){
    pvertice p;
    parista a;
    p=pGrafo;
    if(p!=NULL){
        while(p->datoOrigen!=x && p!=NULL)
            p=p->sgteVertice;
        if(p!=NULL){
            a=new arista;
            a->datoDestino=y;
            a->peso=peso;
            a->sgteArista=p->adyacente;
            p->adyacente=a;
        }
    }
}

void grafo::imprimirGrafo(){
    pvertice p;
    parista a;
    p=pGrafo;
    if(p==NULL) std::cout<<"Grafo vacio"<<std::endl;
    else
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










int main(){
    grafo g;
    int x,y;
    g.insertarVertice(4);
    g.insertarVertice(6);
    g.insertarVertice(3);
    g.insertarVertice(2);
    g.insertarArista(4,6,10); 
    
    g.insertarArista(4,3,2);
    g.insertarArista(4,2,3);
    std::cout<<"Vert||Aristas"<<std::endl;
    g.imprimirGrafo();
    std::cout<<"Peso de todas las aristas: "<<g.sumaPesos()<<std::endl;
}
