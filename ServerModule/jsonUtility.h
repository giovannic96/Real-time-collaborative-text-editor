//
// Created by giova on 05/10/2019.
//

#ifndef SERVERMODULE_JSONUTILITY_H
#define SERVERMODULE_JSONUTILITY_H

#include "json.hpp"

using nlohmann::json;

class jsonUtility {

public:
    static void to_json(json& j, const std::string& op, const std::string& user, const std::string& pass);
    static void to_json(json& j, const std::string& op, const std::string& reply);
    static void from_json(const json& j, std::string& op, std::string& user, std::string& pass);
};


#endif //SERVERMODULE_JSONUTILITY_H
