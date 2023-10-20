#include <assert.h>
#include <fstream>
#include <filesystem>
#include <vector>
#include <iostream>
#include "fft.h"
#include <algorithm>

namespace fs = std::filesystem;

size_t get_max_common_chars_count(const std::string& text, const std::string& pattern) {
    size_t n = text.size();
    size_t m = pattern.size();
    std::vector<size_t> common_chars_count(text.size() - pattern.size() + 1, 0);
    for (char c{' '}; c <= '~'; ++c) {
        std::vector<int32_t> R(n);
        for (int32_t i = 0; i < n; ++i) {
            R[i] = (text[i] == c);
        }
        std::vector<int32_t> S(m);
        for (int32_t i = 0; i < m; ++i) {
            S[i] = (pattern[m - 1 - i] == c);
        }

        uint32_t deg = 1;
        while (deg <= n + m) {
            deg *= 2;
        }

        R.resize(deg);
        for (uint32_t i = n; i < deg; ++i) {
            R[i] = 0;
        }

        S.resize(deg);
        for (uint32_t i = m; i < deg; ++i) {
            S[i] = 0;
        }

        std::vector<int32_t> res(deg, 0);
        FFT::multiply(R, S, res);

        for (size_t i = 0; i < common_chars_count.size(); ++i) {
            common_chars_count[i] += res[pattern.size() - 1 + i];
        }

    }
    size_t result = 0;
    for (auto count: common_chars_count) {
        result = std::max(result, count);
    }
    return result;
}

void get_files_in_directory(char* dir_path, std::vector<std::basic_string<char>>& file_paths) {
    for (const auto& entry : fs::directory_iterator(dir_path)) {
        if (entry.is_regular_file()) {
            file_paths.push_back(entry.path().string());
        }
    }
}

std::string read_data_from_file(std::basic_string<char>& file_path) {
    std::ifstream fin;
    fin.open(file_path);
    size_t file_size = fs::file_size(file_path);
    std::string file_data(file_size, '\0');
    fin.read(&file_data[0], file_size);
    fin.close();
    return file_data;
}

void solve(char* dir_1_path, char* dir_2_path, size_t percent) {
    assert(fs::is_directory(dir_1_path));
    assert(fs::is_directory(dir_2_path));

    std::vector<std::basic_string<char>> dir_1_file_paths;
    std::vector<std::basic_string<char>> dir_2_file_paths;

    get_files_in_directory(dir_1_path, dir_1_file_paths);
    get_files_in_directory(dir_2_path, dir_2_file_paths);

    for (auto& file_path_1: dir_1_file_paths) {
        std::string data_1 = read_data_from_file(file_path_1);
        for (auto& file_path_2: dir_2_file_paths) {
            std::string data_2 = read_data_from_file(file_path_2);
            size_t max_common_chars_count = data_1.size() >= data_2.size() ?
                    get_max_common_chars_count(data_1, data_2) : get_max_common_chars_count(data_2, data_1);
            std::cout << "File 1: " << file_path_1 << ", file 2: " << file_path_2 << '\n';
            std::cout << "Max common chars: " << max_common_chars_count << '\n';
        }
    }
}

int main(int argc, char* argv[]) {
    assert(argc == 4);
    char* dir_1_path = argv[1];
    char* dir_2_path = argv[2];
    size_t percent = std::stoi(std::string(argv[3]));
    solve(dir_1_path, dir_2_path, percent);

    return 0;
}