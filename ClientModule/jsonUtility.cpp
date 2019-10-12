//
// Created by giova on 05/10/2019.
//

#include "jsonUtility.h"

void jsonUtility::to_json(json &j, const std::string &op,const std::string &user, const std::string &pass) {
    j = json{
            {"operation", op},
            {"username", user},
            {"password", pass},
    };
}

void jsonUtility::to_json(json &j, const std::string &op, const std::string &reply) {
    j = json{
            {"operation", op},
            {"reply", reply},
    };
}

void jsonUtility::from_json(const json &j, std::string &op, std::string &user, std::string &pass) {
    op = j.at("operation").get<std::string>();
    user = j.at("username").get<std::string>();
    pass = j.at("password").get<std::string>();
}
