/*Si se tienen 5 objetos cuyos pesos son 10, 20, 30, 40 y 50, y sus
valores son 20, 30, 66, 40 y 60, respectivamente. Adem ́as se sabe que
la capacidad de la mochila es de 100 kg. Resuelva usando los criterios
anteriores y comp ́arelos.
*/

#include<iostream>
#include<vector>
int seleccionarMasPrometedor(int* valores,int* pesos, int num,int criterio,std::vector<bool>& seleccionado){
    
    int mayor=-1;
    int prometedor= -1;

    switch (criterio)
    {
    case 1:   //Mayor valor
        for(int i=0;i<num;i++){
            if(!seleccionado[i] && valores[i]>mayor)
            {
                mayor=valores[i];
                prometedor = i;
            }
            }
                
        break;
    case 2:   //Mayor peso
        for(int i=0;i<num;i++){
            if(!seleccionado[i] && pesos[i]>mayor){
        
                mayor=pesos[i];
                prometedor = i;
                }
        }
        break;
    case 3:   //Mayor valor/peso
        for(int i=0;i<num;i++){
            if(!seleccionado[i] && valores[i]/pesos[i]>mayor){
                mayor=valores[i]/pesos[i];
                prometedor = i;
            }
                
        }
        break;

    default:
        break;
    }


    return prometedor;
}



int greedy(int* valores, int* pesos, int num,int criterio,int capacidadMochila){
    int peso = 0,valorTotal=0;
    std::vector<bool> seleccionado(num,false);

    while(peso<capacidadMochila){
        int i = seleccionarMasPrometedor(valores,pesos,num,criterio,seleccionado);
        if(i==-1)
            break; //No hay más prometedores
        
        if(peso+pesos[i]<capacidadMochila){
            peso += pesos[i];
            valorTotal  +=valores[i];
            seleccionado[i]=true;

        }
        else
            break;
   
    }
    return peso;

}




int main(){
    int pesos[5] = {10,20,30,40,50};
    int valores[5] = {20,30,66,40,60};
    int num = 5;
    
    int capacidadMochila = 100;

    std::cout<<"\nUtilizando el criterio de mayor valor: ";
    std::cout<<"\nPeso utilizado : "<<greedy(valores,pesos,num,1,capacidadMochila);

    std::cout<<"\nUtilizando el criterio de mayor peso: ";
    std::cout<<"\nPeso utilizado : "<<greedy(valores,pesos,num,2,capacidadMochila);

    std::cout<<"\nUtilizando el criterio de mayor valor/peso: ";
    std::cout<<"\nPeso utilizado : "<<greedy(valores,pesos,num,3,capacidadMochila);
    std::cout<<"\n";
    return 0;
}