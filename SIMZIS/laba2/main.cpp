
#include <iostream>

#define alhabet "abcdefghijklmnopqrstuvwxyz"

std::string encryption(std::string message, int key)
{
    std::string encrypted_message;

    for (size_t i = 0; i < message.size(); i++)
    {
        if (isalpha(message[i]))
        {
            char base = islower(message[i]) ? 'a' : 'A';
            char encrypted = ((message[i] - base + key) % 26) + base;
            encrypted_message += encrypted;
        }
        else
        {
            encrypted_message += message[i];
        }
    }
    return encrypted_message;
}

std::string decrypt(std::string message, int key)
{
    return encryption(message, 26 - key);
}

void brute_force_attack(std::string message, std::string encrypted_message)
{
    double start_time = clock();

    for (int i = 0; i < 26; i++)
    {
        std::string decrypted_message = encryption(encrypted_message, i);

        if (decrypted_message == message)
        {
            double end_time = clock();

            std::cout << "The key is picked up!\n"
                      << "Decryption key: " << i << "\n"
                      << "Key selection time: " << start_time - end_time << " mls\n";

            break;
        }
    }
}

int main()
{
    srand(time(NULL));

    int key = rand() % 26 + 1;
    std::string message, encrypted_message;

    std::cout << "Enter the message: \n";
    std::getline(std::cin, message);

    std::cout << "Message: " << message << "\n"
              << "Encryption key: " << key << "\n";

    encrypted_message = encryption(message, key);
    std::cout << "Decrypted message: " << encrypted_message << "\n\n";

    brute_force_attack(message, encrypted_message);
}