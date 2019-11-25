//
// Created by giova on 26/10/2019.
//

#ifndef SERVERMODULE_FILEUTILITY_H
#define SERVERMODULE_FILEUTILITY_H


#include <string>
#include <vector>
#include "symbol.h"

class fileUtility {

public:
    static std::vector<symbol> readFile(const std::string& filename);
    static void writeFile(const std::string& filename, const std::vector<symbol>& symbols);
    static bool is_empty(std::ifstream& pFile);
};

#endif //SERVERMODULE_FILEUTILITY_H
