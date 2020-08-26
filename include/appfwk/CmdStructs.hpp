/*
 * This file is 100% generated.  Any manual edits will likely be lost.
 */
#ifndef DUNEDAQ__APPFWK__CMD_STRUCTS_HPP
#define DUNEDAQ__APPFWK__CMD_STRUCTS_HPP

#include <nlohmann/json.hpp>
#include <map>


// Hand-written code may find it handy to use the codegen namespace
// via CPP macro to insulate any changes in schema.  Short and fully
// qualified versions:
#ifndef CMD_NS 
#define CMD_NS cmd
#endif
#ifndef CMD_FQNS
#define CMD_FQNS dunedaq::appfwk::cmd
#endif

namespace dunedaq::appfwk::cmd {


    /// @brief The set of expected command identifiers
    enum class Id: unsigned {
        undef,
        exec,
        init,
        conf,
        start,
        stop,
        scrap,
        fina,
        term,
    };
    struct IdNames {
        static constexpr char const* undef = "undef";
        static constexpr char const* exec = "exec";
        static constexpr char const* init = "init";
        static constexpr char const* conf = "conf";
        static constexpr char const* start = "start";
        static constexpr char const* stop = "stop";
        static constexpr char const* scrap = "scrap";
        static constexpr char const* fina = "fina";
        static constexpr char const* term = "term";
    };
    /// Convert a Id to a string.
    inline
    std::string str(const Id& id) {
        const std::map<Id, std::string> id2s = {
            { Id::undef, "undef" },
            { Id::exec, "exec" },
            { Id::init, "init" },
            { Id::conf, "conf" },
            { Id::start, "start" },
            { Id::stop, "stop" },
            { Id::scrap, "scrap" },
            { Id::fina, "fina" },
            { Id::term, "term" },
        };
        auto it = id2s.find(id);
        if (it == id2s.end()) {
            // fixme: replace with ERS
            throw std::runtime_error("unknown Id enum");
        }
        return it->second;
    }
    /// Convert a string to a Id
    inline
    Id toId(const std::string& id) {
        const std::map<std::string, Id> s2id = {
            { "undef", Id::undef },
            { "exec", Id::exec },
            { "init", Id::init },
            { "conf", Id::conf },
            { "start", Id::start },
            { "stop", Id::stop },
            { "scrap", Id::scrap },
            { "fina", Id::fina },
            { "term", Id::term },
        };
        auto it = s2id.find(id);
        if (it == s2id.end()) {
            throw std::runtime_error("no Id enum for " + id);
        }
        return it->second;
    }

    // @brief 
    using Data = nlohmann::json;

    /// @brief A command
    struct Command {
        Id id{ Id::undef };
        Data data{  };
    };


    /// @brief A command
    struct Reply {
        Id id{ Id::undef };
        Data data{  };
    };


} // namespace dunedaq::appfwk::cmd

#endif // DUNEDAQ__APPFWK__CMD_STRUCTS_HPP