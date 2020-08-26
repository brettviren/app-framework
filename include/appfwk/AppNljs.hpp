/*
 * This file is 100% generated.  Any manual edits will likely be lost.
 */
#ifndef DUNEDAQ__APPFWK__APP_NLJS_HPP
#define DUNEDAQ__APPFWK__APP_NLJS_HPP

#include "appfwk/AppStructs.hpp"
#include "appfwk/CmdNljs.hpp"

#include <nlohmann/json.hpp>


namespace dunedaq::appfwk::app {

    using json = nlohmann::json;


    // Converters for TypeName
    // Type/instance name pair for factory construction
    inline void to_json(json& j, const TypeName& obj) {
        j["type"] = obj.type;
        j["name"] = obj.name;
    }
    inline void from_json(const json& j, TypeName& obj) {
        if (j.contains("type")) {
            j.at("type").get_to(obj.type);
        }
        if (j.contains("name")) {
            j.at("name").get_to(obj.name);
        }
    }
    // Converters for AddrDat
    // Data addressed to a particular instance
    inline void to_json(json& j, const AddrDat& obj) {
        j["tn"] = obj.tn;
        j["data"] = obj.data;
    }
    inline void from_json(const json& j, AddrDat& obj) {
        if (j.contains("tn")) {
            j.at("tn").get_to(obj.tn);
        }
        if (j.contains("data")) {
            obj.data = j.at("data");
        }
    }
    // Converters for Addressed
    // Addressed command data
    inline void to_json(json& j, const Addressed& obj) {
        j["addrdats"] = obj.addrdats;
    }
    inline void from_json(const json& j, Addressed& obj) {
        if (j.contains("addrdats")) {
            j.at("addrdats").get_to(obj.addrdats);
        }
    }
    // Converters for Conf
    // App FSM event 'Conf'
    inline void to_json(json& j, const Conf& obj) {
        j["command"] = obj.command;
    }
    inline void from_json(const json& j, Conf& obj) {
        if (j.contains("command")) {
            j.at("command").get_to(obj.command);
        }
    }
    // Converters for Fina
    // App FSM event 'Fina'
    inline void to_json(json& j, const Fina& obj) {
        j["command"] = obj.command;
    }
    inline void from_json(const json& j, Fina& obj) {
        if (j.contains("command")) {
            j.at("command").get_to(obj.command);
        }
    }
    // Converters for Init
    // App FSM event 'Init'
    inline void to_json(json& j, const Init& obj) {
        j["command"] = obj.command;
    }
    inline void from_json(const json& j, Init& obj) {
        if (j.contains("command")) {
            j.at("command").get_to(obj.command);
        }
    }
    // Converters for Scrap
    // App FSM event 'Scrap'
    inline void to_json(json& j, const Scrap& obj) {
        j["command"] = obj.command;
    }
    inline void from_json(const json& j, Scrap& obj) {
        if (j.contains("command")) {
            j.at("command").get_to(obj.command);
        }
    }
    // Converters for Start
    // App FSM event 'Start'
    inline void to_json(json& j, const Start& obj) {
        j["command"] = obj.command;
    }
    inline void from_json(const json& j, Start& obj) {
        if (j.contains("command")) {
            j.at("command").get_to(obj.command);
        }
    }
    // Converters for Stop
    // App FSM event 'Stop'
    inline void to_json(json& j, const Stop& obj) {
        j["command"] = obj.command;
    }
    inline void from_json(const json& j, Stop& obj) {
        if (j.contains("command")) {
            j.at("command").get_to(obj.command);
        }
    }


} // namespace dunedaq::appfwk::app

#endif // DUNEDAQ__APPFWK__APP_NLJS_HPP