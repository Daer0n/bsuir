
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>

#define alhabet "0123456789abcdefghijklmnopqrstuvwxyz"

std::string get_random_password(int length)
{
    
    static const char alphabet_array[] = alhabet;

    std::string password;
    password.reserve(length);

    for (int i = 0; i < length; i++)
        password += alphabet_array[rand() % (sizeof(alphabet_array) - 1)];


    return password;
}

std::string letter_removing(std::string str)
{
    std::string numbers = "abcdefghijklmnopqrstuvwxyz";

    for (char c : numbers)
        str.erase(std::remove(str.begin(), str.end(), c), str.end());

    return str;
}

std::string number_removing(std::string str)
{
    std::string numbers = "0123456789";

    for (char c : numbers)
        str.erase(std::remove(str.begin(), str.end(), c), str.end());

    return str;
}

void symbol_frequency_distribution(std::string str)
{
    int letter_frequencies[26] = {0};
    int number_frequencies[10] = { 0 };
    std::string str_without_letters = letter_removing(str);
    std::string str_without_numbers = number_removing(str);

    for (char c : str_without_numbers)
        letter_frequencies[c - 'a']++;

    for (int i = 0; i < 26; i++) {
        char c = 'a' + i;
        std::cout << c << ": " << letter_frequencies[i] << "\n";
    }

    for (char c : str_without_letters)
        number_frequencies[c - '0']++;

    for (int i = 0; i < 10; i++) {
        char c = '0' + i;
        std::cout << c << ": " << number_frequencies[i] << "\n";
    }

}

std::string form_string(std::vector<int>& symbols_register, const std::string& alphabet) {
    std::string password;

    for (const auto& index : symbols_register) {
        password += alphabet[index];
    }

    return password;
}

void increment(std::vector<int>& symbols_register, int alphabet_length) {
    for (int i = symbols_register.size() - 1; i >= 0; i--) {
        symbols_register[i]++;

        if (symbols_register[i] == alphabet_length) {
            symbols_register[i] = 0;
        }
        else {
            break;
        }
    }
}

void password_selection(std::string& correct_password,const std::string& alphabet) {
    std::vector<int> symbols_register(correct_password.size(), 0);

    double start_time = clock();

    while (true) {
        std::string current_password = form_string(symbols_register, alphabet);

        if (current_password == correct_password) {
            double end_time = clock();
            std::cout << "Пароль подобран: " << current_password << "\nВремя подбора пароля: " << end_time - start_time << "мск" << std::endl;
            break;
        }

        increment(symbols_register, alphabet.length());
    }
}

int main() {
    srand((unsigned)time(NULL));
    setlocale(LC_ALL, "ru");
    int length;
    std::cout << "Введите длину пароля: ";
    std::cin >> length;

    std::string password = get_random_password(length);
    std::cout << "Сгенерированный пароль: " << password << "\n";

    std::cout << "Частотное распределение символов:\n";
    symbol_frequency_distribution(password);

    password_selection(password, alhabet);
}
