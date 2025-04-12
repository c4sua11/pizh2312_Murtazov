#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <sys/stat.h> // Для stat() (Unix-системы)
#include <cstring>    // Для strerror()

// Вместо std::filesystem используем stat() для получения размера файла
uintmax_t get_file_size(const std::string& filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) != 0) {
        char buffer[256];
        strerror_s(buffer, sizeof(buffer), errno);
        std::cerr << "Error getting file size for " << filename << ": " << buffer << '\n';
        return 1;
    }
    return st.st_size;
}

// Вместо string::starts_with используем compare()
bool starts_with(const std::string& str, const std::string& prefix) {
    return str.compare(0, prefix.length(), prefix) == 0;
}

int main(int argc, char** argv) {
    bool count_lines = false;
    bool count_bytes = false;
    bool count_words = false;
    bool count_chars = false;
    std::vector<std::string> files;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg[0] == '-') {
            if (arg.size() > 1 && arg[1] == '-') {
                // Длинные опции (--lines, --bytes и т. д.)
                if (arg == "--lines") {
                    count_lines = true;
                }
                else if (arg == "--bytes") {
                    count_bytes = true;
                }
                else if (arg == "--words") {
                    count_words = true;
                }
                else if (arg == "--chars") {
                    count_chars = true;
                }
                else {
                    std::cerr << "Unknown option: " << arg << '\n';
                    return 1;
                }
            }
            else {
                // Короткие опции (-l, -c, -w, -m)
                for (size_t j = 1; j < arg.size(); ++j) {
                    char c = arg[j];
                    switch (c) {
                    case 'l': count_lines = true; break;
                    case 'c': count_bytes = true; break;
                    case 'w': count_words = true; break;
                    case 'm': count_chars = true; break;
                    default:
                        std::cerr << "Unknown option: -" << c << '\n';
                        return 1;
                    }
                }
            }
        }
        else {
            files.push_back(arg);
        }
    }

    // Если опции не указаны, выводим строки, слова и байты
    bool options_given = count_lines || count_bytes || count_words || count_chars;
    if (!options_given) {
        count_lines = true;
        count_words = true;
        count_bytes = true;
    }

    // Определяем порядок вывода
    std::vector<std::string> output_order;
    if (!options_given) {
        output_order = { "lines", "words", "bytes" };
    }
    else {
        if (count_lines) output_order.push_back("lines");
        if (count_bytes) output_order.push_back("bytes");
        if (count_words) output_order.push_back("words");
        if (count_chars) output_order.push_back("chars");
    }

    // Проверяем, что файлы указаны
    if (files.empty()) {
        std::cerr << "No files specified.\n";
        return 1;
    }

    // Обрабатываем каждый файл
    for (const auto& filename : files) {
        // Проверяем существование файла (просто попробуем открыть)
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "File not found or cannot be opened: " << filename << '\n';
            continue;
        }

        // Получаем размер файла
        uintmax_t bytes = get_file_size(filename);

        // Считаем строки, слова и символы
        int lines = 0;
        int words = 0;
        int chars = 0;
        bool in_word = false;
        char c;

        while (file.get(c)) {
            chars++;
            if (c == '\n') {
                lines++;
            }
            if (std::isspace(c)) {
                in_word = false;
            }
            else {
                if (!in_word) {
                    words++;
                    in_word = true;
                }
            }
        }

        file.close();

        // Формируем вывод
        std::vector<std::string> parts;
        for (const auto& field : output_order) {
            if (field == "lines") {
                parts.push_back(std::to_string(lines));
            }
            else if (field == "words") {
                parts.push_back(std::to_string(words));
            }
            else if (field == "bytes") {
                parts.push_back(std::to_string(bytes));
            }
            else if (field == "chars") {
                parts.push_back(std::to_string(chars));
            }
        }
        parts.push_back(filename);

        // Выводим результат
        for (size_t i = 0; i < parts.size(); ++i) {
            if (i > 0) std::cout << ' ';
            std::cout << parts[i];
        }
        std::cout << '\n';
    }

    return 0;
}