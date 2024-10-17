#include<iostream>
#include<string>
#include<vector>
#include<chrono>
#include<fstream>
#include<random>




std::string longestBetweenTwo(const std::string& s1, const std::string& s2) {
    return (s1.length() >= s2.length()) ? s1 : s2;
}

std::string generateRandomString(int length) {
    static const std::string charset = "abcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dist(0, charset.size() - 1);

    std::string random_string;
    for (int i = 0; i < length; ++i) {
        random_string += charset[dist(generator)];
    }
    return random_string;
}


std::string LCS(const std::string& p, const std::string& q, int length_p, int length_q) {
    if (length_p == 0 || length_q == 0)
        return ""; // Base case
    else if (p[length_p - 1] == q[length_q - 1])
        return LCS(p, q, length_p - 1, length_q - 1) + p[length_p - 1];
    else {
        std::string temp1 = LCS(p, q, length_p - 1, length_q);
        std::string temp2 = LCS(p, q, length_p, length_q - 1);
        return longestBetweenTwo(temp1, temp2);
    }
}

std::string LCS_dynamic(const std::string& p, const std::string& q, int length_p, int length_q, std::vector<std::vector<std::string>>& memory) {
    if (memory[length_p][length_q] != "")
        return memory[length_p][length_q];

    if (length_p == 0 || length_q == 0)
        return "";
    else if (p[length_p - 1] == q[length_q - 1])
        return memory[length_p][length_q] = LCS_dynamic(p, q, length_p - 1, length_q - 1, memory) + p[length_p - 1];
    else {
        std::string temp1 = LCS_dynamic(p, q, length_p - 1, length_q, memory);
        std::string temp2 = LCS_dynamic(p, q, length_p, length_q - 1, memory);
        return memory[length_p][length_q] = longestBetweenTwo(temp1, temp2);
    }
}

void runTestAndSaveResults() {
    std::vector<int> lengths = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};// Ajustado a tamaños razonables

    std::ofstream resultFile("lcs_comparison_results.txt");
    if (!resultFile.is_open()) {
        std::cerr << "Error al abrir el archivo de resultados. \n";
        return;
    }

    resultFile << "Length\tRecursiveTime\tDynamicTime\n";

    for (int len : lengths) {
        std::string s1 = generateRandomString(len);
        std::string s2 = generateRandomString(len);


        // Medir tiempo recursivo
        auto start = std::chrono::steady_clock::now();
        std::string lcs_recursive = LCS(s1, s2, len, len);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> recursive_time = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

        // Medir tiempo dinámico
        std::vector<std::vector<std::string>> memory(len + 1, std::vector<std::string>(len + 1, ""));
        start = std::chrono::steady_clock::now();
        std::string lcs_dynamic = LCS_dynamic(s1, s2, len, len, memory);
        end = std::chrono::steady_clock::now();
        std::chrono::duration<double> dynamic_time = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

        resultFile << len << "\t" << recursive_time.count() << "\t" << dynamic_time.count() << "\n";
        std::cout << "Processed length: " << len << "\n";
    }

    resultFile.close();
}

void IngresarCadenas() {
    std::cin.ignore();  // Limpiar el buffer de entrada
    std::string s1 = "", s2 = "";
    std::cout << "Inserte la primera cadena: " << "\n";
    std::getline(std::cin, s1);
    std::cout << "Inserte la segunda cadena: " << "\n";
    std::getline(std::cin, s2);
    int l1 = s1.length();
    int l2 = s2.length();

    // Medir tiempo recursivo
    auto start = std::chrono::steady_clock::now();
    std::string lcs_recursive = LCS(s1, s2, l1, l2);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "LCS(recursivo): " << lcs_recursive << "\n";
    std::cout << "Tiempo de ejecución(recursivo): " << elapsed_time.count() << " segundos\n";

    // Medir tiempo dinámico
    std::vector<std::vector<std::string>> memory(l1 + 1, std::vector<std::string>(l2 + 1, ""));
    start = std::chrono::steady_clock::now();
    std::string lcs_dynamic = LCS_dynamic(s1, s2, l1, l2, memory);
    end = std::chrono::steady_clock::now();
    elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "LCS(dinámico): " << lcs_dynamic << "\n";
    std::cout << "Tiempo de ejecución(dinámico): " << elapsed_time.count() << " segundos\n";
}

int main() {
    std::cout << "Digite una opción: \n";
    std::cout << "1. Ingresar cadenas. \n ";
    std::cout << "2. Generar cadenas \n";

    int opcion;
    std::cin >> opcion;

    switch (opcion) {
        case 1:
            IngresarCadenas();
            break;
        case 2:
            runTestAndSaveResults();
            break;
        default:
            std::cout << "Opción no válida.\n";
            break;
    }

    return 0;
}

