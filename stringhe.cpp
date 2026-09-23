#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// Stampa un byte in formato binario
void stampaByteBinario(unsigned char byte)
{
    for (int bit = 7; bit >= 0; --bit)
    {
        std::cout << ((byte >> bit) & 1);
    }
}

// Stampa i byte di una stringa in esadecimale
void stampaByteEsadecimale(const std::string& testo)
{
    for (unsigned char byte : testo)
    {
        std::cout << std::hex
                  << std::uppercase
                  << std::setw(2)
                  << std::setfill('0')
                  << static_cast<int>(byte)
                  << ' ';
    }

    std::cout << std::dec << std::setfill(' ') << '\n';
}

// Stampa i byte UTF-8 in binario
void stampaByteInBinario(const std::string& testo)
{
    for (unsigned char byte : testo)
    {
        stampaByteBinario(byte);
        std::cout << ' ';
    }

    std::cout << '\n';
}

// Decodifica una stringa UTF-8 e stampa i relativi code point Unicode
void stampaUnicode(const std::string& testo)
{
    std::cout << "Code point Unicode: ";

    for (std::size_t i = 0; i < testo.size();)
    {
        unsigned char primoByte =
            static_cast<unsigned char>(testo[i]);

        std::uint32_t codePoint = 0;
        int numeroByte = 0;

        if ((primoByte & 0b10000000) == 0)
        {
            // Carattere ASCII: 0xxxxxxx
            codePoint = primoByte;
            numeroByte = 1;
        }
        else if ((primoByte & 0b11100000) == 0b11000000)
        {
            // Sequenza UTF-8 a 2 byte
            codePoint = primoByte & 0b00011111;
            numeroByte = 2;
        }
        else if ((primoByte & 0b11110000) == 0b11100000)
        {
            // Sequenza UTF-8 a 3 byte
            codePoint = primoByte & 0b00001111;
            numeroByte = 3;
        }
        else if ((primoByte & 0b11111000) == 0b11110000)
        {
            // Sequenza UTF-8 a 4 byte
            codePoint = primoByte & 0b00000111;
            numeroByte = 4;
        }
        else
        {
            std::cout << "[sequenza non valida] ";
            ++i;
            continue;
        }

        // Aggiunge i byte successivi della sequenza UTF-8
        bool sequenzaValida = true;

        for (int j = 1; j < numeroByte; ++j)
        {
            if (i + j >= testo.size())
            {
                sequenzaValida = false;
                break;
            }

            unsigned char byteSuccessivo =
                static_cast<unsigned char>(testo[i + j]);

            if ((byteSuccessivo & 0b11000000) != 0b10000000)
            {
                sequenzaValida = false;
                break;
            }

            codePoint = (codePoint << 6) |
                        (byteSuccessivo & 0b00111111);
        }

        if (!sequenzaValida)
        {
            std::cout << "[sequenza non valida] ";
            ++i;
            continue;
        }

        std::cout << "U+"
                  << std::hex
                  << std::uppercase
                  << std::setw(4)
                  << std::setfill('0')
                  << codePoint
                  << std::dec
                  << std::setfill(' ')
                  << ' ';

        i += numeroByte;
    }

    std::cout << '\n';
}

// Stampa la versione ASCII della stringa
void stampaASCII(const std::string& testo)
{
    std::cout << "ASCII: ";

    bool soloASCII = true;

    for (unsigned char byte : testo)
    {
        if (byte < 128)
        {
            std::cout << static_cast<char>(byte);
        }
        else
        {
            // Un carattere UTF-8 non è rappresentabile direttamente in ASCII
            std::cout << '?';
            soloASCII = false;
        }
    }

    std::cout << '\n';

    if (!soloASCII)
    {
        std::cout
            << "(I caratteri non ASCII sono stati sostituiti con '?')\n";
    }
}

// Mostra tutte le rappresentazioni della stringa
void analizzaStringa(const std::string& testo)
{
    std::cout << "\n===== ANALISI DELLA STRINGA =====\n";

    std::cout << "Stringa inserita: " << testo << '\n';

    std::cout << "Numero di byte: "
              << testo.size()
              << '\n';

    std::cout << "\nUnicode:\n";
    stampaUnicode(testo);

    std::cout << "\nUTF-8 in esadecimale:\n";
    stampaByteEsadecimale(testo);

    std::cout << "\nASCII:\n";
    stampaASCII(testo);

    std::cout << "\nUTF-8 in binario:\n";
    stampaByteInBinario(testo);

    std::cout << "=================================\n";
}

int main()
{
    // -------------------------------------------------
    // ESEMPIO 1: stringa C-style
    // -------------------------------------------------

    char stringaC[] = "Ciao";

    std::cout << "Stringa C-style: "
              << stringaC
              << '\n';

    std::cout << "Primo carattere: "
              << stringaC[0]
              << '\n';

    std::cout << "Secondo carattere: "
              << stringaC[1]
              << '\n';

    std::cout << "Dimensione totale dell'array: "
              << sizeof(stringaC)
              << " byte\n";

    // -------------------------------------------------
    // ESEMPIO 2: std::string
    // -------------------------------------------------

    std::string testo = "Ciao";

    std::cout << "\nstd::string: "
              << testo
              << '\n';

    std::cout << "Numero di byte: "
              << testo.size()
              << '\n';

    testo += " mondo";

    std::cout << "Dopo la concatenazione: "
              << testo
              << '\n';

    // -------------------------------------------------
    // ESEMPIO 3: caratteri ASCII e UTF-8
    // -------------------------------------------------

    std::string ascii = "Citta";
    std::string utf8 = "Città";
    std::string euro = "€";

    std::cout << "\nStringa ASCII: "
              << ascii
              << '\n';

    std::cout << "Numero di byte: "
              << ascii.size()
              << '\n';

    std::cout << "\nStringa UTF-8: "
              << utf8
              << '\n';

    std::cout << "Numero di byte: "
              << utf8.size()
              << '\n';

    std::cout << "\nSimbolo dell'euro: "
              << euro
              << '\n';

    std::cout << "Numero di byte UTF-8: "
              << euro.size()
              << '\n';

    std::cout << "Byte dell'euro in esadecimale: ";
    stampaByteEsadecimale(euro);

    // -------------------------------------------------
    // ESEMPIO 4: input dell'utente
    // -------------------------------------------------

    std::string input;

    std::cout << "\nInserisci una stringa UTF-8: ";
    std::getline(std::cin, input);

    analizzaStringa(input);

    return 0;
}
