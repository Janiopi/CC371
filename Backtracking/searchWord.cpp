#include<string>
#include<iostream>

template<size_t rows, size_t cols>
void printArray2D(char (&array)[rows][cols]){
    for(size_t i=0;i<rows;i++){
        for(size_t j=0;j<cols;j++){
                std::cout<<array[i][j]<<" ";
            }
            std::cout<<"\n";
        }
}

template<size_t rows, size_t cols>
bool findWord(char (&array)[rows][cols],char word[],int lenWord, int x, int y, int index){
     std::cout << "Visitando [" << x << "][" << y << "], "
              << "comparando '" << word[index] << "' con '" << array[x][y] << "'" << std::endl;
    if(rows == 1 && cols == 1){
        std::cout<<"Se encontro la palabra"<<std::endl;
        return array[0][0]==word[0];
    }
    if(index == lenWord){
        std::cout<<"Se encontro la palabra"<<std::endl;
        return true;
    } 
    if(x<0 || x>= rows || y<0 || y>= cols || array[x][y]!=word[index] ){
        std::cout << "Retrocede desde [" << x << "][" << y << "]" << std::endl;        
        return false;
    }
    char c = array[x][y];
    array[x][y] = '#'; //Lo marcamos para no visitarlo nuevamente
    bool found = findWord(array, word, lenWord, x+1, y,  index+1)||findWord(array,word,lenWord, x,  y-1,  index+1)||findWord(array,word,lenWord,  x-1,  y,  index+1)||findWord(array,word,lenWord,  x,  y+1, index+1);
    array[x][y] = c;
    if (!found) {
        std::cout << "Retrocede desde [" << x << "][" << y << "]" << std::endl;
    }
    return found;
}
int main(){
    //Tablero
    int rows = 4;
    int cols = 2;
    char t[4][2] = {
        {'A','B'},
        {'C','D'},
        {'A','B'},
        {'C','D'},
        
    };
    std::cout<<"Tablero\n";
    printArray2D(t);
    char word[] = { 'A','B','D'};
    int lenWord = sizeof(word) / sizeof(word[0]);
    bool wordFound = false;
    for(int i=0;i<rows && !wordFound;i++){
        for(int j=0;j<cols && !wordFound;j++){
            std::cout << "Comenzando la busqueda desde [" << i << "][" << j << "]" << std::endl;
            if(findWord(t,word,lenWord,i,j,0)){
                wordFound = true;
            }
        }
    }
    if(!wordFound){
        std::cout<<"Palabra no encontrada. "<<std::endl;
    }
    return 0;
}