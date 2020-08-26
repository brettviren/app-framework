#include "appfwk/CommandHandler.hpp"
#include "appfwk/Issues.hpp"
#include <cetlib/BasicPluginFactory.h>


using namespace dunedaq::appfwk;

CommandHandler::pointer
dunedaq::appfwk::makeCommandHandler(std::string const& short_name, std::string const& inst)
{
    static cet::BasicPluginFactory bpf("duneCommandHandler", "make");
    std::string pname = short_name + "CommandHandler";
    ERS_INFO("Construct CommandHandler: \"" << short_name << "\"::\"" << inst << "\"");

    return bpf.makePlugin<std::shared_ptr<CommandHandler>>(pname, inst);
}

