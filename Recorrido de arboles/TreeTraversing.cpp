#include <iostream>
#include<queue>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <chrono>

struct TreeNode{
    int data;
    TreeNode* right;
    TreeNode* left;

    TreeNode(int val){
        data = val;
        right = nullptr;
        left = nullptr;
    };
};


//Depth First
void inorder(TreeNode* root){
    if(root == nullptr)
        return;

    inorder(root->left);
    std::cout<<root->data<<" ";
    inorder(root->right);
}

void preorder(TreeNode* root){
    if(root == nullptr)
        return;

    std::cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(TreeNode* root){
    if(root == nullptr)
        return;

    postorder(root->left);
    postorder(root->right);
    std::cout<<root->data<<" ";

}

void breadthFirst(TreeNode* root, const std::string& filename){
    if(root==nullptr)
        return;
    
    std::ofstream outFile(filename);
    if(!outFile){
        std::cerr<<"Error, no se pudo abrir el archivo."<<std::endl;
        return;
    }

    
    std::queue<TreeNode*> q;
    int ord[]
    q.push(root);
    while(!q.empty()){
        TreeNode* curr = q.front();
        q.pop();
        std::cout<<curr->data<<" ";
        outFile<<curr->data<<" ";
        if(curr->left)
            q.push(curr->left);
        if(curr->right)
            q.push(curr->right);
    }

    std::cout<<std::endl;
    outFile.close();
}

template<typename Func>
double timeExecution(Func funcion){
    auto inicio = std::chrono::high_resolution_clock::now();
    funcion();
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;
    return duracion.count();

}

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

TreeNode* generateBinaryTree(int n) {
    if (n <= 0) return nullptr;

    TreeNode* root = new TreeNode(1);
    std::queue<TreeNode*> q;
    q.push(root);

    int currentNumber = 2;
    while (currentNumber <= n) {
        TreeNode* node = q.front();
        q.pop();

        if (currentNumber <= n) {
            node->left = new TreeNode(currentNumber++);
            q.push(node->left);
        }
        if (currentNumber <= n) {
            node->right = new TreeNode(currentNumber++);
            q.push(node->right);
        }
    }

    return root;
}




void printTree(TreeNode* root) {
    if (root == nullptr)
        return;
    printTree(root->left);
    std::cout << root->data << " ";
    printTree(root->right);
}


void exampleTree(){
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(5);
    root->right = new TreeNode(7);
    root->left->left= new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(8);
    std::cout << "Recorrido In-order :\n";
    inorder(root);
    std::cout << "\nRecorrido Pre-order :\n";
    preorder(root);
    std::cout << "\nRecorrido Post-order: \n";
    postorder(root);
    std::cout << "\nRecorrido Breadth-first :\n";
    breadthFirst(root,"example_tree.txt");
    std::cout << "\n\n";
    deleteTree(root);
}



void generateTree(int n, std::ofstream& outFile){
    TreeNode* root2 = generateBinaryTree(n);
    std::cout << "Recorrido In-order :\n";
    double inOrderTime = timeExecution([&]() { inorder(root2); });
    
    std::cout<<"\n";
    std::cout << "\nRecorrido Post-order :\n";
    double postOrderTime = timeExecution([&]() { postorder(root2); });
    
    std::cout<<"\n";
    std::cout << "\nRecorrido Pre-order :\n";
    double preOrderTime = timeExecution([&]() { preorder(root2); });
    
    std::cout << "\nRecorrido Breadth-first :\n";
    double breadthFirstTime = timeExecution([&]() { breadthFirst(root2,"generated_tree.txt"); });
    

    std::cout<<"\nTiempo de ejecución InOrder: "<<inOrderTime<<" segundos\n";
    std::cout<<"\nTiempo de ejecución PostOrder: "<<postOrderTime<<" segundos\n";
    std::cout<<"\nTiempo de ejecución PreOrder: "<<preOrderTime<<" segundos\n";
    std::cout<<"\nTiempo de ejecución BreadthFirst: "<<breadthFirstTime<<" segundos\n";
    
    outFile << "Nodes: " << n << "\n";
    outFile << "InOrder Time: " << inOrderTime << " seconds\n";
    outFile << "PostOrder Time: " << postOrderTime << " seconds\n";
    outFile << "PreOrder Time: " << preOrderTime << " seconds\n";
    outFile << "BreadthFirst Time: " << breadthFirstTime << " seconds\n";
    outFile << "----------------------------------------\n";
    
    
    
    
    
    deleteTree(root2);
}


int main(){
    std::ofstream outFile("execution_times.txt");
    if (!outFile) {
        std::cerr << "Error: Could not open file for writing.\n";
        return 1;
    }

    std::vector<int> values = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
 
    int n;
    

    std::cout<<"1. Árbol de ejemplo\n ";
    std::cout<<"2. Generar un árbol\n ";
    std::cout<<"3. Generar árboles n=10,100,1000... \n";
    std::cout<<"\nInserte un número: ";
    std::cin>>n;




    switch (n)
    {
    case 1:
        exampleTree();
        break;
    case 2:
        std::cout<<"\nInserte el número de nodos: ";
        std::cin>>n;
        if (n <= 0) {
            std::cerr << "\nNúmero de nodos debe ser mayor que 0." << std::endl;
            break;
        }
        generateTree(n,outFile);
        break;
    case 3:
        for (int n : values) {
        std::cout << "Generating tree with " << n << " nodes...\n";
        generateTree(n, outFile);
    }

        break;

    default:
        break;
    }

    


    outFile.close();
    
    return 0;

}
