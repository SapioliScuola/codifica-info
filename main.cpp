#include <iostream>
#include <limits>

int somma(int a, int b) {
    return a + b;
}

int main() {

    std::cout << "Byte occupati da int: " << sizeof(int) << '\n';

    //complemento a 2


    std::cout << "Valore minimo di int: "
              << std::numeric_limits<int>::min()
              << '\n';

    std::cout << "Valore massimo di int: "
              << std::numeric_limits<int>::max()
              << '\n';

    int primo;
    int secondo;

    std::cout << "\nInserisci il primo numero: ";
    std::cin >> primo;

    std::cout << "Inserisci il secondo numero: ";
    std::cin >> secondo;

    std::cout << "\nI due numeri sono: "
              << primo << " e " << secondo << '\n';

    std::cout <<"primo in binario:   "
        << std::bitset<sizeof(int) * 8>(static_cast<unsigned int>(primo))
        <<'\n';

    std::cout <<"secondo in binario: "
        << std::bitset<sizeof(int) * 8>(static_cast<unsigned int>(secondo))
        <<'\n';

    std::cout << "La loro somma e': "
              << somma(primo, secondo)
              << '\n';

    return 0;
}

