/*
 * This file is 100% generated.  Any manual edits will likely be lost.
 */
#ifndef DUNEDAQ__APPFWK__DQM_NLJS_HPP
#define DUNEDAQ__APPFWK__DQM_NLJS_HPP

#include "appfwk/DqmStructs.hpp"

#include <nlohmann/json.hpp>


namespace dunedaq::appfwk::dqm {

    using json = nlohmann::json;


    // Converters for Queue
    // Queue 'init' data structure
    inline void to_json(json& j, const Queue& obj) {
        j["capacity"] = obj.capacity;
    }
    inline void from_json(const json& j, Queue& obj) {
        if (j.contains("capacity")) {
            j.at("capacity").get_to(obj.capacity);
        }
    }


} // namespace dunedaq::appfwk::dqm

#endif // DUNEDAQ__APPFWK__DQM_NLJS_HPP