#include <iostream>
#include <string>

int main() {
    std::string surname = "Nazimova";
    std::string name = "Ekaterina";

    // Преобразование в нижний регистр
    for (char& c : surname) c = std::tolower(c);
    for (char& c : name) c = std::tolower(c);

    std::cout << surname << "." << name << std::endl;

    return 0;
}
