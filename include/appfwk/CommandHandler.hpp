#ifndef DUNEDAQ_APPFWK_COMMANDHANDLER_HPP
#define DUNEDAQ_APPFWK_COMMANDHANDLER_HPP

#include "appfwk/AppStructs.hpp"

#include <nlohmann/json.hpp>

namespace dunedaq::appfwk {

    class CommandHandler {
      public:
        using pointer = std::shared_ptr<CommandHandler>;

        using object_t = nlohmann::json;

        // Implement if you want the instance name.
        CommandHandler(std::string /*name*/) {}
        virtual ~CommandHandler() {}

        /// Implement to receive commands.  Return result, if any.
        virtual object_t handle(const APP_FQNS::Command& command) = 0;
    };

    /** @brief Load a CommandHandler plugin and return an instance.
     */
    CommandHandler::pointer
    makeCommandHandler(std::string const& plugin_name, std::string const& inst);

}



#endif
