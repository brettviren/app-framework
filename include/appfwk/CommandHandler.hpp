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
    makeCommandHandler(std::string const& short_plugin_name, std::string const& inst);

    /** Implmentation add like:
        extern "C" {
          std::shared_ptr<dunedaq::appfwk::CommandHandler> make(std::string inst) { 
          return std::shared_ptr<dunedaq::appfwk::CommandHandler>(new xxxCommandHandler(uri));
        }
      }

      And in CMakeLists.txt like:

      add_library(appfwk_xxxCommandHandler_duneCommandHandler src/xxxCommandHandler.cpp)
      target_link_libraries(appfwk_xxxCommandHandler_duneCommandHandler appfwk)

      replace "xxx" with the short plugin name
    */

}



#endif
