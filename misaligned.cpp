#include "helpers.h"
#include <vector>
#include <string>

int printColorMap() {
    std::vector<std::string> majorColor = {"White", "Red", "Black", "Yellow", "Violet"};
    std::vector<std::string> minorColor = {"Blue", "Orange", "Green", "Brown", "Slate"};
    return printTable(majorColor, minorColor);
}
