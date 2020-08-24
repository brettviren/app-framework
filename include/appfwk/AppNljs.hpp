/*
 * This file is 100% generated.  Any manual edits will likely be lost.
 */
#ifndef DUNEDAQ__APPFWK__APP_APP_NLJS_HPP
#define DUNEDAQ__APPFWK__APP_APP_NLJS_HPP

#include "AppStructs.hpp"
#include <nlohmann/json.hpp>


namespace dunedaq::appfwk::app {

    using json = nlohmann::json;


    // Converters for Payload
    // Associate data to a recipient
    inline void to_json(json& j, const Payload& obj) {
        j["recipient"] = obj.recipient;
        j["data"] = obj.data;
    }
    inline void from_json(const json& j, Payload& obj) {
        if (j.contains("recipient")) {
            j.at("recipient").get_to(obj.recipient);
        }
        if (j.contains("data")) {
            j.at("data").get_to(obj.data);
        }
    }
    // Converters for Undef
    // FSM event type for command Undef
    inline void to_json(json& j, const Undef& obj) {
        j["payloads"] = obj.payloads;
    }
    inline void from_json(const json& j, Undef& obj) {
        if (j.contains("payloads")) {
            j.at("payloads").get_to(obj.payloads);
        }
    }
    // Converters for Exec
    // FSM event type for command Exec
    inline void to_json(json& j, const Exec& obj) {
        j["payloads"] = obj.payloads;
    }
    inline void from_json(const json& j, Exec& obj) {
        if (j.contains("payloads")) {
            j.at("payloads").get_to(obj.payloads);
        }
    }
    // Converters for Init
    // FSM event type for command Init
    inline void to_json(json& j, const Init& obj) {
        j["payloads"] = obj.payloads;
    }
    inline void from_json(const json& j, Init& obj) {
        if (j.contains("payloads")) {
            j.at("payloads").get_to(obj.payloads);
        }
    }
    // Converters for Conf
    // FSM event type for command Conf
    inline void to_json(json& j, const Conf& obj) {
        j["payloads"] = obj.payloads;
    }
    inline void from_json(const json& j, Conf& obj) {
        if (j.contains("payloads")) {
            j.at("payloads").get_to(obj.payloads);
        }
    }
    // Converters for Start
    // FSM event type for command Start
    inline void to_json(json& j, const Start& obj) {
        j["payloads"] = obj.payloads;
    }
    inline void from_json(const json& j, Start& obj) {
        if (j.contains("payloads")) {
            j.at("payloads").get_to(obj.payloads);
        }
    }
    // Converters for Stop
    // FSM event type for command Stop
    inline void to_json(json& j, const Stop& obj) {
        j["payloads"] = obj.payloads;
    }
    inline void from_json(const json& j, Stop& obj) {
        if (j.contains("payloads")) {
            j.at("payloads").get_to(obj.payloads);
        }
    }
    // Converters for Scrap
    // FSM event type for command Scrap
    inline void to_json(json& j, const Scrap& obj) {
        j["payloads"] = obj.payloads;
    }
    inline void from_json(const json& j, Scrap& obj) {
        if (j.contains("payloads")) {
            j.at("payloads").get_to(obj.payloads);
        }
    }
    // Converters for Fina
    // FSM event type for command Fina
    inline void to_json(json& j, const Fina& obj) {
        j["payloads"] = obj.payloads;
    }
    inline void from_json(const json& j, Fina& obj) {
        if (j.contains("payloads")) {
            j.at("payloads").get_to(obj.payloads);
        }
    }
    // Converters for Term
    // FSM event type for command Term
    inline void to_json(json& j, const Term& obj) {
        j["payloads"] = obj.payloads;
    }
    inline void from_json(const json& j, Term& obj) {
        if (j.contains("payloads")) {
            j.at("payloads").get_to(obj.payloads);
        }
    }


} // namespace dunedaq::appfwk::app

#endif // DUNEDAQ__APPFWK__APP_APP_NLJS_HPP