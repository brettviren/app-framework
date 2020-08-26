#include "appfwk/CommandHandler.hpp"
#include <cetlib/BasicPluginFactory.h>

using namespace dunedaq::appfwk;

CommandHandler::pointer
dunedaq::appfwk::makeCommandHandler(std::string const& plugin_name, std::string const& inst)
{
    static cet::BasicPluginFactory bpf("duneCommandHandler", "make");
    return bpf.makePlugin<std::shared_ptr<CommandHandler>>(plugin_name, inst);
}

