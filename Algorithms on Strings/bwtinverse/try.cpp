#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<char> chars = {'c', 'a', 'b', 'd', 'e'};

    // Create a vector of pointers to characters
    std::vector<char*> charPtrs;
    for (char& c : chars) {
        charPtrs.push_back(&c);
    }

    // Custom comparator function to sort pointers based on the values they point to
    auto comparator = [](char* a, char* b) {
        return *a < *b;
    };

    // Sort the pointers
    std::sort(charPtrs.begin(), charPtrs.end(), comparator);

    // Output the sorted characters and their addresses
    std::cout << "Sorted characters and their addresses:\n";
    for (char* ptr : charPtrs) {
        std::cout << *ptr << " at address " << static_cast<void*>(ptr) << std::endl;
    }

    return 0;
}