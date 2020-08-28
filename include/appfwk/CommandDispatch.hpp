#ifndef DUNEDAQ_APPFWK_APPLICATION_HPP
#define DUNEDAQ_APPFWK_APPLICATION_HPP

#include "appfwk/CommandHandler.hpp"
#include <boost/msm/back/state_machine.hpp>

namespace dunedaq::appfwk {

    // Accept and dispatch commands, interpret "init" to hold command
    // handlers to construct, o.w. forward commands to constructed
    // handlers.
    class CommandDispatch {

      public:

        using object_t = nlohmann::json;

        /// Dispatch a command and return a reply.
        ///
        /// Note, a command contract is assumed to vet all commands
        /// and there is no checking for command behavior here.
        object_t dispatch(object_t command);


      private:

        // Used to collect results from individual handlers during a
        // dispatch.  Returned by dispatch().
        object_t outcome_;

        // Bookkeep the handers we make in "init".
        struct HInfo {
            APP_FQNS::TypeName tn;
            CommandHandler::pointer handler;
        };
        std::vector<HInfo> handlers_;

        // Forward a comand to all existing handlers based on
        // addressed command data.
        CMD_FQNS::Reply forward(const CMD_FQNS::Command& cmd);

        // Used to apply matching for any generically addressed
        // command data.
        std::vector<HInfo> match(APP_FQNS::TypeName tn);
    };
}

#endif
