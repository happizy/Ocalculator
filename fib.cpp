#include <iostream>

// Fonction pour générer le n-ième nombre de la suite de Fibonacci
unsigned long long fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    unsigned long long a = 0;
    unsigned long long b = 1;
    unsigned long long c;

    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }

    return b;
}

// Fonction qui utilise la fonction fibonacci k fois
void utiliserFibonacci(int k) {
    for (int i = 0; i < k; ++i) {
        int n;
        std::cout << "Entrez un nombre pour générer le n-ième nombre de Fibonacci : ";
        std::cin >> n;
        std::cout << "Le " << n << "-ième nombre de Fibonacci est : " << fibonacci(n) << std::endl;
    }
}

int main() {
    int k;
    std::cout << "Combien de fois voulez-vous utiliser la fonction Fibonacci ? ";
    std::cin >> k;

    utiliserFibonacci(k);

    return 0;
}
