/*
 * This file is 100% generated.  Any manual edits will likely be lost.
 */
#ifndef DUNEDAQ__APPFWK__APP_STRUCTS_HPP
#define DUNEDAQ__APPFWK__APP_STRUCTS_HPP

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "appfwk/CmdStructs.hpp"

// Hand-written code may find it handy to use the codegen namespace
// via CPP macro to insulate any changes in schema.  Short and fully
// qualified versions:
#ifndef APP_NS 
#define APP_NS app
#endif
#ifndef APP_FQNS
#define APP_FQNS dunedaq::appfwk::app
#endif

namespace dunedaq::appfwk::app {

    using namespace dunedaq::appfwk::cmd;

    // @brief 
    using Data = nlohmann::json;

    /// @brief Type/instance name pair for factory construction
    struct TypeName {
        std::string type{  };
        std::string name{  };
    };


    /// @brief Data addressed to a particular instance
    struct AddrDat {
        TypeName tn{  };
        Data data{  };
    };


    /// @brief Addressed command data
    struct Addressed {
        std::vector<AddrDat> addrdats{  };
    };


    /// @brief App FSM event 'Conf'
    struct Conf {
        Command command{  };
    };


    /// @brief App FSM event 'Fina'
    struct Fina {
        Command command{  };
    };


    /// @brief App FSM event 'Init'
    struct Init {
        Command command{  };
    };


    /// @brief App FSM event 'Scrap'
    struct Scrap {
        Command command{  };
    };


    /// @brief App FSM event 'Start'
    struct Start {
        Command command{  };
    };


    /// @brief App FSM event 'Stop'
    struct Stop {
        Command command{  };
    };


} // namespace dunedaq::appfwk::app

#endif // DUNEDAQ__APPFWK__APP_STRUCTS_HPP