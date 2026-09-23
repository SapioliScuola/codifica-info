#include <iostream>
#include <limits>
#include <cstdint>
#include <cstring>

float somma(float a, float b) {
    return a + b;
}

void stampaFloatInBinario(float numero)
{
    std::uint32_t bits = 0;

    static_assert(sizeof(float) == sizeof(std::uint32_t),
                  "Questo codice richiede float da 32 bit");

    std::memcpy(&bits, &numero, sizeof(numero));

    for (int i = 31; i >= 0; --i)
    {
        std::cout << ((bits >> i) & 1);

        if (i == 31 || i == 23)
        {
            std::cout << ' ';
        }
    }

    std::cout << '\n';
}


int main() {

    std::cout << "Byte occupati da float: " << sizeof(float) << '\n';

    std::cout << "Valore minimo di float: "
              << std::numeric_limits<float>::min()
              << '\n';

    std::cout << "Valore massimo di float: "
              << std::numeric_limits<float>::max()
              << '\n';

    float primo;
    float secondo;

    std::uint32_t bits_primo = 0;
    std::uint32_t bits_secondo = 0;

    std::cout << "\nInserisci il primo numero: ";
    std::cin >> primo;

    std::cout << "Inserisci il secondo numero: ";
    std::cin >> secondo;

    std::cout << "\nI due numeri sono: "
              << primo << " e " << secondo << '\n';

    std::cout <<"primo in binario:" <<'\n';
    stampaFloatInBinario(primo);

    std::cout <<"secondo in binario: " <<'\n';
    stampaFloatInBinario(secondo);

    std::cout << "La loro somma e': "
              << somma(primo, secondo)
              << '\n';

    return 0;
}
