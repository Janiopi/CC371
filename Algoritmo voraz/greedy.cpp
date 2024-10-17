#include<iostream>

int greedy(int monto,int num,int* denominaciones,int* numBilletes)
{
    
    int j=0;

    while(j<num && denominaciones[j]>monto ){
        j++;
    }
    return j;
}

void cambio(int monto,int num,int* denominaciones,int* numBilletes){
    int suma = 0;
    int iDen = 0;

    while(suma<monto){
        iDen = greedy(monto - suma,num,denominaciones,numBilletes);
        if (iDen >= num)
            std::cout<<"\nNo se encontró solución";
        numBilletes[iDen]++;
        suma=suma+denominaciones[iDen];

    }    

}

void Imprimir(int* denominaciones,int* numBilletes,int num)
{
    for(int i=0;i<num;i++){
        std::cout<<"\nBilletes de "<<denominaciones[i]<<": "<<numBilletes[i]<<"\n";
    }
}



int main(){


    int denominaciones[4] = {70,30,10,5};
    int numBilletes[4] = {0,0,0,0};
    int monto = 353;
    int num = 4;




    cambio(monto,num,denominaciones,numBilletes);


    Imprimir(denominaciones,numBilletes,num);

    return 0;
}