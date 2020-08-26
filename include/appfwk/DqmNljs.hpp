/*
 * This file is 100% generated.  Any manual edits will likely be lost.
 */
#ifndef DUNEDAQ__APPFWK__DQM_NLJS_HPP
#define DUNEDAQ__APPFWK__DQM_NLJS_HPP

#include "appfwk/DqmStructs.hpp"
#include "appfwk/CmdNljs.hpp"

#include <nlohmann/json.hpp>


namespace dunedaq::appfwk::dqm {

    using json = nlohmann::json;

    NLOHMANN_JSON_SERIALIZE_ENUM( Kind, {
            { dunedaq::appfwk::dqm::Kind::Unknown, "Unknown" },
            { dunedaq::appfwk::dqm::Kind::StdDeQueue, "StdDeQueue" },
            { dunedaq::appfwk::dqm::Kind::FollySPSCQueue, "FollySPSCQueue" },
            { dunedaq::appfwk::dqm::Kind::FollyMPMCQueue, "FollyMPMCQueue" },
        })

    // Converters for QueueInit
    // Queue 'init' data structure
    inline void to_json(json& j, const QueueInit& obj) {
        j["kind"] = obj.kind;
        j["capacity"] = obj.capacity;
    }
    inline void from_json(const json& j, QueueInit& obj) {
        if (j.contains("kind")) {
            j.at("kind").get_to(obj.kind);
        }
        if (j.contains("capacity")) {
            j.at("capacity").get_to(obj.capacity);
        }
    }


} // namespace dunedaq::appfwk::dqm

#endif // DUNEDAQ__APPFWK__DQM_NLJS_HPP