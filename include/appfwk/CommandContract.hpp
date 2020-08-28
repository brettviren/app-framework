/** @file CommandContract.hpp Provide a base class for command behavior contract.
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */
#ifndef DUNEDAQ_APPFWK_COMMANDCONTRACT_HPP
#define DUNEDAQ_APPFWK_COMMANDCONTRACT_HPP

#include <nlohmann/json.hpp>
#include <string>
#include <memory>

namespace dunedaq::appfwk {

    /** @brief CommandContract provides abstract base class to enact a contract of commands
     *
     * An subclass shall override validate() in order to provide
     * validation of the contract that the subclass asserts.  It shall
     * throw an exception on violating behavior and otherwise return
     * the command object.
     */
    class CommandContract {
      public:
        using object_t = nlohmann::json;
        using pointer = std::shared_ptr<CommandContract>;

        /// Subclass must override to get an instance name
        CommandContract(std::string /*name*/) {}
        virtual ~CommandContract() {};

        /// Validate the command.
        virtual object_t validate(object_t command) = 0;

    };

    /** @brief Load a CommandContract plugin and return instance for URI.
     */
    
    CommandContract::pointer makeCommandContract(std::string const& kind,
                                                 std::string const& inst="");

    /*
     * Implementations add function like:
     *
     * extern "C" {
     *    std::shared_ptr<dunedaq::appfwk::CommandContract> make(std::string inst) { 
     *        return std::shared_ptr<dunedaq::appfwk::CommandContract>(new MyContract(inst));
     *    }
     * }
     */

} // namespace dunedaq::appfwk

#endif
