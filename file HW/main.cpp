// Задача №1. Реализовать чтение ID3v1 MP3-файла. Будьте внимательны, не все MP3-файлы
// содержат заполненный ID3-тег. Год

#include <iostream>
#include <fstream>
#include <cstring>

struct ID3v1Tag {
    char header[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    char genre;
};

int main() {
   std:: ifstream file("1.mp3", ios::binary);

    if (!file.is_open()) {
        std::cout << "Failed to open file." << endl;
        return 1;
    }

    file.seekg(-128, ios::end);
    ID3v1Tag tag;
    file.read((char*)&tag, sizeof(tag));

    if (strncmp(tag.header, "TAG", 3) == 0) { // strncmp - ф-ция сравнения первый символ каждой строки. 
        std::cout << "Year: " << tag.year << endl;
    } else {
        std::cout << "ID3v1 tag not found." << endl;
    }

    file.close();
    return 0;
}

// Задача №2. Протабулировать функцию. Начальную и финальную точки, шаг, параметр Ч
// считывать из файла in.txt. Результат записывать в текстовый файл out.txt
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

void read_variables(std::ifstream &file, short &ch, short &step, short &start_point, short &final_point){
    file >> ch >> step >> start_point >> final_point;
}

void write_variables(std::ofstream &file, std::vector<float> &y_variables){
    for(int i = 0; i < y_variables.size(); i++){
        file << "X" << i << " " << y_variables[i] << "\\n";
    }
}

long int factorial(short number){
    long int factorial = 1;
    for (int i = 1; i <= number; i++){
        factorial *= i;
    }
    return factorial;
}

void tabulate_function(std::vector<float> &y_variables, short ch, short step, short start_point, short final_point){
    bool is_negative = true;
    float x = 0;
    for(short i = start_point; i < final_point; i += step){
        long int ch_factorial = factorial(ch);
        x = pow(i, ch)/ch_factorial;
        y_variables.push_back(x);
    }
    for(short i = 0; i < y_variables.size(); i++){
        if(is_negative){
            y_variables[i] -= y_variables[i+1];
            is_negative = false;
        } else {
            y_variables[i] += y_variables[i+1];
            is_negative = true;
        }
    }
}

int main() {
    short ch = 0;
    short step = 0;
    short start_point = 0;
    short final_point = 0;
    std::vector<float> y_variables;
    std::ifstream input("in.txt");
    std::ofstream out("out.txt");
    if(input.is_open()){
        read_variables(input, ch, step, start_point, final_point);
        tabulate_function(y_variables, ch, step, start_point, final_point);
        write_variables(out, y_variables);
    }
    input.close();
    out.close();
    return 0;
}

// Задача №7. Разработать программу для ввода с клавиатуры и записи в файл полётных данных о
// квадрокоптерах. Одна строка содержит: Х,У,Команда, где ХУ – координаты, а
// Команда – это набор чисел, характеризующих действие коптера: 10 – взлёт, 20 –
// посадка, 50 – полёт, 60 – набрать высоту, 70 снизить высоту. Пользователь вводит
// данные с клавиатуры. Каждая новая строка содержит новый набор координат и
// команд. Организовать переменные для хранения информации.

#include <iostream>
#include <fstream>

int main() {
    double x, y;
    int command;
    std::ofstream file("flight_data.txt");
    if (!file.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }
    std::cout << "Enter flight data in the format X Y Command (10 - takeoff, 20 - landing, 50 - flight, 60 - ascend, 70 - descend):" << std::endl;
    while (std::cin >> x >> y >> command) {
        file << x << " " << y << " " << command << std::endl;
    }
    file.close();
    return 0;
}