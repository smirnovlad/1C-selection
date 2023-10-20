#include <vector>
#include "directory_comparator.h"

int main(int argc, char* argv[]) {
    assert(argc == 4);
    char* dir_1_path = argv[1];
    char* dir_2_path = argv[2];
    double percent = std::stod(std::string(argv[3]));
    DirectoryComparator cmp(dir_1_path, dir_2_path);
    cmp.analyze(percent);

    return 0;
}