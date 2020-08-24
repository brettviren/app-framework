/*
 * This file is 100% generated.  Any manual edits will likely be lost.
 */#ifndef DUNEDAQ__APPFWK__APP_APP_STRUCTS_HPP
#define DUNEDAQ__APPFWK__APP_APP_STRUCTS_HPP

#include <string>
#include <vector>

namespace dunedaq::appfwk::app {


    /// @brief Associate data to a recipient
    struct Payload {
        std::string recipient{  };
        Data data{  };
    };


    /// @brief FSM event type for command Undef
    struct Undef {
        std::vector<Payload> payloads{  };
    };


    /// @brief FSM event type for command Exec
    struct Exec {
        std::vector<Payload> payloads{  };
    };


    /// @brief FSM event type for command Init
    struct Init {
        std::vector<Payload> payloads{  };
    };


    /// @brief FSM event type for command Conf
    struct Conf {
        std::vector<Payload> payloads{  };
    };


    /// @brief FSM event type for command Start
    struct Start {
        std::vector<Payload> payloads{  };
    };


    /// @brief FSM event type for command Stop
    struct Stop {
        std::vector<Payload> payloads{  };
    };


    /// @brief FSM event type for command Scrap
    struct Scrap {
        std::vector<Payload> payloads{  };
    };


    /// @brief FSM event type for command Fina
    struct Fina {
        std::vector<Payload> payloads{  };
    };


    /// @brief FSM event type for command Term
    struct Term {
        std::vector<Payload> payloads{  };
    };


} // namespace dunedaq::appfwk::app

#endif // DUNEDAQ__APPFWK__APP_APP_STRUCTS_HPP