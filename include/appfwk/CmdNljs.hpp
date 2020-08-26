/*
 * This file is 100% generated.  Any manual edits will likely be lost.
 */
#ifndef DUNEDAQ__APPFWK__CMD_NLJS_HPP
#define DUNEDAQ__APPFWK__CMD_NLJS_HPP

#include "appfwk/CmdStructs.hpp"

#include <nlohmann/json.hpp>


namespace dunedaq::appfwk::cmd {

    using json = nlohmann::json;

    NLOHMANN_JSON_SERIALIZE_ENUM( Id, {
            { dunedaq::appfwk::cmd::Id::undef, "undef" },
            { dunedaq::appfwk::cmd::Id::exec, "exec" },
            { dunedaq::appfwk::cmd::Id::init, "init" },
            { dunedaq::appfwk::cmd::Id::conf, "conf" },
            { dunedaq::appfwk::cmd::Id::start, "start" },
            { dunedaq::appfwk::cmd::Id::stop, "stop" },
            { dunedaq::appfwk::cmd::Id::scrap, "scrap" },
            { dunedaq::appfwk::cmd::Id::fina, "fina" },
            { dunedaq::appfwk::cmd::Id::term, "term" },
        })

    // Converters for Command
    // A command
    inline void to_json(json& j, const Command& obj) {
        j["id"] = obj.id;
        j["data"] = obj.data;
    }
    inline void from_json(const json& j, Command& obj) {
        if (j.contains("id")) {
            j.at("id").get_to(obj.id);
        }
        if (j.contains("data")) {
            obj.data = j.at("data");
        }
    }
    // Converters for Reply
    // A command
    inline void to_json(json& j, const Reply& obj) {
        j["id"] = obj.id;
        j["data"] = obj.data;
    }
    inline void from_json(const json& j, Reply& obj) {
        if (j.contains("id")) {
            j.at("id").get_to(obj.id);
        }
        if (j.contains("data")) {
            obj.data = j.at("data");
        }
    }


} // namespace dunedaq::appfwk::cmd

#endif // DUNEDAQ__APPFWK__CMD_NLJS_HPP