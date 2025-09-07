#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include <algorithm>

int main()
{
    setlocale(LC_ALL, "ru");
    std::cout << "Введите текст: ";
    std::string s;
    std::getline(std::cin, s);
    std::cout << "Сообщение: " << s << std::endl;
    int n = s.size();
    std::cout << "Длина сообщения: " << n << std::endl;

    std::map<std::string, std::vector<double>> m;
    for (int i = 0; i < n; i++) {
        std::string reserv = "";
        reserv += s[i];
        if (m.find(reserv) == m.end()) {
            m[reserv] = std::vector<double>(3, 0.0);
        }
        m[reserv][0]++;
    }

    for (auto& pair : m) {
        pair.second[1] = pair.second[0] / n;
        pair.second[2] = -pair.second[1] * std::log2(pair.second[1]);
    }

    std::cout << "Анализ одиночных символов:\n";
    for (const auto& pair : m) {
        std::cout << "'" << pair.first << "': " << pair.second[0] << " раз, "
            << "вероятность: " << pair.second[1] << ", энтропия: " << pair.second[2] << std::endl;
    }

    double sum = 0;
    for (const auto& pair : m) {
        sum += pair.second[2];
    }

    std::cout << "Энтропия на символ: " << sum << std::endl;
    std::cout << "Длина кода при равномерном кодировании: " << std::ceil(std::log2(m.size())) << std::endl;
    std::cout << "Избыточность источника: " << (1 - sum / std::log2(m.size())) * 100 << "%" << std::endl;

    std::map<std::string, std::vector<double>> m1;
    for (int i = 0; i < n - 1; i++) {
        std::string reserv = "";
        reserv += s[i];
        reserv += s[i + 1];
        if (m1.find(reserv) == m1.end()) {
            m1[reserv] = std::vector<double>(3, 0.0);
        }
        m1[reserv][0]++;
    }

    for (auto& pair : m1) {
        pair.second[1] = pair.second[0] / (n - 1);
        pair.second[2] = -pair.second[1] * std::log2(pair.second[1]);
    }

    std::cout << "\nАнализ пар символов:\n";
    for (const auto& pair : m1) {
        std::cout << "'" << pair.first << "': " << pair.second[0] << " раз, "
            << "вероятность: " << pair.second[1] << ", энтропия: " << pair.second[2] << std::endl;
    }

    double sum1 = 0;
    for (const auto& pair : m1) {
        sum1 += pair.second[2];
    }

    std::cout << "Энтропия на символ для пар: " << sum1 << std::endl;
    std::cout << "Средняя энтропия на символ при учете пар: " << sum1 / 2 << std::endl;

    int twenty_perc = std::round(m.size() * 0.2);
    std::vector<std::pair<std::string, std::vector<double>>> vec1(m.begin(), m.end());

    std::sort(vec1.begin(), vec1.end(),
        [](const auto& a, const auto& b) {
            return a.second[0] > b.second[0]; 
        });

    double total_after_remove_frequent = n;
    for (int i = 0; i < twenty_perc && i < vec1.size(); ++i) {
        total_after_remove_frequent -= vec1[i].second[0];
    }

    if (twenty_perc > 0 && twenty_perc < vec1.size()) {
        vec1.erase(vec1.begin(), vec1.begin() + twenty_perc);
    }

    std::map<std::string, std::vector<double>> new_map;
    for (const auto& pair : vec1) {
        new_map[pair.first] = std::vector<double>(3, 0.0);
        new_map[pair.first][0] = pair.second[0];
        new_map[pair.first][1] = pair.second[0] / total_after_remove_frequent;
        new_map[pair.first][2] = -new_map[pair.first][1] * std::log2(new_map[pair.first][1]);
    }

    std::cout << "\nПосле удаления " << twenty_perc << " самых частых символов:\n";
    std::cout << "Общее количество символов после удаления: " << total_after_remove_frequent << std::endl;
    for (const auto& pair : new_map) {
        std::cout << "'" << pair.first << "': " << pair.second[0] << " раз, "
            << "вероятность: " << pair.second[1] << ", энтропия: " << pair.second[2] << std::endl;
    }

    double sum2 = 0;
    for (const auto& pair : new_map) {
        sum2 += pair.second[2];
    }

    std::cout << "Энтропия на символ после удаления частых: " << sum2 << std::endl;


    int twenty_perc1 = std::round(m.size() * 0.2);
    std::vector<std::pair<std::string, std::vector<double>>> vec2(m.begin(), m.end());

    std::sort(vec2.begin(), vec2.end(),
        [](const auto& a, const auto& b) {
            return a.second[0] < b.second[0]; 
        });


    double total_after_remove_rare = n;
    for (int i = 0; i < twenty_perc1 && i < vec2.size(); ++i) {
        total_after_remove_rare -= vec2[i].second[0];
    }

    if (twenty_perc1 > 0 && twenty_perc1 < vec2.size()) {
        vec2.erase(vec2.begin(), vec2.begin() + twenty_perc1);
    }

    std::map<std::string, std::vector<double>> new_map1;
    for (const auto& pair : vec2) {
        new_map1[pair.first] = std::vector<double>(3, 0.0);
        new_map1[pair.first][0] = pair.second[0];
        new_map1[pair.first][1] = pair.second[0] / total_after_remove_rare;
        new_map1[pair.first][2] = -new_map1[pair.first][1] * std::log2(new_map1[pair.first][1]);
    }

    std::cout << "\nПосле удаления " << twenty_perc1 << " самых редких символов:\n";
    std::cout << "Общее количество символов после удаления: " << total_after_remove_rare << std::endl;
    for (const auto& pair : new_map1) {
        std::cout << "'" << pair.first << "': " << pair.second[0] << " раз, "
            << "вероятность: " << pair.second[1] << ", энтропия: " << pair.second[2] << std::endl;
    }

    double sum3 = 0;
    for (const auto& pair : new_map1) {
        sum3 += pair.second[2];
    }

    std::cout << "Энтропия на символ после удаления редких: " << sum3 << std::endl;

    return 0;
}
