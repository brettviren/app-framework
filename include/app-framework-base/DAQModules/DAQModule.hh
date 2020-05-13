/**
 * @file DAQModule Class Interface
 *
 * The DAQModule interface defines the required functionality for all
 * UserModules that use the Application Framework. DAQModules are defined as "a
 * set of code which performs a specific task". They are connected to one
 * another within a DAQ Application by Queues instances, in a graph defined by a
 * ModuleList.
 *
 * This interface is intended to define only absolutely necessary methods to be
 * able to support the many different tasks that UserModules will be asked to
 * perform.
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef APP_FRAMEWORK_BASE_INCLUDE_APP_FRAMEWORK_BASE_DAQMODULES_DAQMODULE_HH_
#define APP_FRAMEWORK_BASE_INCLUDE_APP_FRAMEWORK_BASE_DAQMODULES_DAQMODULE_HH_

#include <vector>
#include <string>

namespace appframework {
/**
 * @brief The DAQModule class is a set of code which performs a specific task.
 *
 * This interface defines the basic methods which all DAQModules should expose.
 * Developers implementing DAQModules should feel free to use whatever Plugins
 * and Services are necessary to accomplish their needed functionality.
 */
class DAQModule {
public:
  /**
   * @brief Execute a command in this UserModule
   * @param cmd The command from CCM
   * @return String with detailed status of the command (future).
   *
   * execute_command is the single entry point for DAQProcess to pass CCM
   * commands to UserModules. The implementation of this function should route
   * accepted commands to the appropriate functions within the UserModule and
   * return their result. Non-accepted commands should return a status
   * indicating this result.
   */
  virtual void execute_command( const std::string & cmd, const std::vector<std::string> & args = {} ) = 0;
};
} // namespace appframework

#endif // APP_FRAMEWORK_BASE_INCLUDE_APP_FRAMEWORK_BASE_DAQMODULES_DAQMODULE_HH_
