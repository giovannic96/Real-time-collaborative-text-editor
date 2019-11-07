//
// Created by giova on 05/10/2019.
//

#ifndef SERVERMODULE_JSONUTILITY_H
#define SERVERMODULE_JSONUTILITY_H

#include "json.hpp"
#include "symbol.h"
#include "File.h"

using nlohmann::json;

//SERIALIZATION (convert json into string) -> it is obtained with method dump() (e.g. json.dump())
//DESERIALIZATION (convert data into json) -> it is obtained with method parse() (e.g. json::parse(data_));

class jsonUtility {

public:
    static void to_json(json &j, const std::string &op, const std::string &resp);
    static void to_json(json& j, const std::string& op, const std::string& user, const std::string& pass);
    static void to_jsonFilename(json& j, const std::string& op, const std::string& user, const std::string& filename);
    static void to_jsonUri(json& j, const std::string& op, const std::string& user, const std::string& uri);
    static void to_json(json& j, const std::string& op, const std::string& user, const std::string& pass, const std::string& email);
    static void to_jsonUser(json &j, const std::string &op, const std::string &user);
    static void from_json(const json& j, std::string& op);
    static void from_json_resp(const json &j, std::string &resp);
    static void from_json_symbols(const json &j, std::vector<json> &jsonSymbols);
    static void from_json_files(const json &j, std::vector<json> &jsonFiles);
    static File* from_json_file(const json &j);
    static symbol* from_json_symbol(const json &j);
    static void from_json_usernameLogin(const json &j, std::string &name);
    static void from_json(const json& j, std::string& user, std::string& pass);
    static void from_json(const json &j, std::string &user, std::string &pass, std::string &email);
};


#endif //SERVERMODULE_JSONUTILITY_H
