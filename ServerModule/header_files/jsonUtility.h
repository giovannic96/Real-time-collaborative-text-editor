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
    static json merge(const json &a, const json &b);
    static std::vector<json> fromSymToJson(std::vector<symbol> symbols);
    static std::vector<json> fromFileToJson(const std::vector<File>& files);
    static void to_json(json &j, const std::string &op, const std::string &resp);
    static void to_json_symbol(json &j, const symbol &symbol);
    static void to_json_file(json &j, const File &file);
    static void to_json_newuri(json &j, const std::string &op, const std::string &resp, const std::string &uri);
    static void to_json_usernameLogin(json &j, const std::string &op, const std::string &resp, const std::string &usernameLogin);
    static void to_json_symVector(json &j, const std::string &op, const std::string &resp, const std::vector<json> &symVector);
    static void to_json_fileVector(json &j, const std::string &op, const std::string &resp, const std::vector<json> &vectorFile);
    static void to_json(json& j, const std::string& op, const std::string& user, const std::string& pass);
    static void to_json(json& j, const std::string& op, const std::string& user, const std::string& pass, const std::string& email);
    static void from_json(const json& j, std::string& op);
    static void from_json_symbol(const json& j, symbol& symbol);
    static void from_json_filename(const json &j, std::string &user, std::string &filename);
    static void from_json_uri(const json &j, std::string &user, std::string &uri);
    static void from_json_username(const json &j, std::string &user);
    static void from_json_resp(const json &j, std::string &resp);
    static void from_json(const json& j, std::string& user, std::string& pass);
    static void from_json(const json &j, std::string &user, std::string &pass, std::string &email);


};


#endif //SERVERMODULE_JSONUTILITY_H
