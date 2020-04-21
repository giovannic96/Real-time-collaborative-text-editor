//
// Created by giova on 05/10/2019.
//

#ifndef SERVERMODULE_JSONUTILITY_H
#define SERVERMODULE_JSONUTILITY_H
#include <iostream>
#include "json.hpp"
#include "symbol.h"
#include "symbolInfo.h"
#include "File.h"

using nlohmann::json;

//SERIALIZATION (convert json into string) -> it is obtained with method dump() (e.g. json.dump())
//DESERIALIZATION (convert data into json) -> it is obtained with method parse() (e.g. json::parse(data_));

typedef std::map<std::string, std::pair<std::string,bool>> myCollabColorsMap;

class jsonUtility {

public:
    static void to_json(json &j, const std::string &op, const std::string &resp);
    static void to_json(json& j, const std::string& op, const std::string& user, const std::string& pass);
    static void to_jsonRenamefile(json& j, const std::string& op, const std::string& nameFile, const std::string& uri, const std::string& username);
    static void to_jsonFilename(json& j, const std::string& op, const std::string& user, const std::string& filename);
    static void to_jsonUri(json& j, const std::string& op, const std::string& user, const std::string& uri);
    static void to_json_inviteURI(json& j, const std::string& op, const std::string& invited, const std::string& applicant, const std::string& uri);
    static void to_json(json& j, const std::string& op, const std::string& user, const std::string& pass, const std::string& email);
    static void to_json_insertion(json &j, const std::string &op, const symbol &symbol, const int &indexInEditor);
    static void to_json_cursor_change_req(json &j, const std::string &op, const int &index);
    static void to_json_removal_range(json &j, const std::string &op, const int &startIndex, const int &endIndex);
    static void to_json_format_range(json &j, const std::string &op, const int &startIndex, const int &endIndex, const int &format);
    static void to_json_fontsize_change(json &j, const std::string &op, const int &startIndex, const int &endIndex, const int &fontSize);
    static void to_json_alignment_change(json &j, const std::string &op, const int &startBlock, const int &endBlock, const int &alignment);
    static void to_json_fontfamily_change(json &j, const std::string &op, const int &startIndex, const int &endIndex, const std::string &fontFamily);
    static void to_json_insertion_range(json &j, const std::string &op, const std::vector<json> &symVector,  const int &startIndex);
    static void to_json_FormattingSymbol(json &j, const symbol &symbol);
    static void to_jsonUser(json &j, const std::string &op, const std::string &user);
    static void to_json_collab_colors(json &j, const std::string &op, const std::string &uri);
    static void from_json_insertion(const json& j, symbol& s, int &indexInEditor);
    static void from_json(const json& j, std::string& op);
    static void from_json_inviteURI(const json& j, std::string& op);
    static void from_json_rename_file(const json &j, std::string &resp, std::string& filename);
    static void from_json_resp(const json &j, std::string &resp);
    static void from_json_symbols(const json &j, std::vector<symbol> &symbols);
    static void from_json_formatting_symbols(const json &j, std::vector<json>& jsonSymbols);
    static void from_json_symbolsAndFilename(const json &j, std::vector<symbol> &symbols, std::string& filename);
    static void from_json_filename(const json &j, std::string& filename);
    static void from_json_files(const json &j, std::vector<json> &jsonFiles);
    static File* from_json_file(const json &j);
    static symbol* from_json_symbol(const json &j);
    static symbolInfo* from_json_formatting_symbol(const json &j);
    static void from_json_collab_colors_map(const json &j, std::string &op);
    static void from_json_usernameLogin(const json &j, std::string &name, std::string &color, std::string &mail, int &siteId);
    static void from_jsonUri(const json& j, std::string& uri);
    static void from_json(const json& j, std::string& user, std::string& pass);
    static void from_json(const json &j, std::string &user, std::string &pass, std::string &email);
    static void from_json_insertion_range(const json &j, int& firstIndex, std::vector<json>& jsonSymbols);
    static void from_json_cursor_change(const json &j, std::string& username, std::string& color, int& pos);
    static void from_json_collab_colors_resp(const json &j, myCollabColorsMap& collabColorsMap);
    static void from_json_user_offline(const json &j, std::string &username, myCollabColorsMap& collabColorsMap);
    static void from_json_removal(const json &j, int& index);
    static void from_json_removal_range(const json &j, int& startIndex, int& endIndex);
    static void from_json_format_range(const json &j, int& startIndex, int& endIndex, int& format);
    static void from_json_fontsize_change(const json &j, int& startIndex, int& endIndex, int& fontSize);
    static void from_json_alignment_change(const json &j, int& startBlock, int& endBlock, int& alignment);
    static void from_json_fontfamily_change(const json &j, int& startIndex, int& endIndex, std::string& fontFamily);
    static std::vector<json> fromFormattingSymToJson(const std::vector<symbol>& symbols);
};


#endif //SERVERMODULE_JSONUTILITY_H
