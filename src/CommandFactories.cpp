#include "appfwk/CommandContract.hpp"
#include "appfwk/CommandHandler.hpp"
#include "appfwk/CommandSource.hpp"
#include "appfwk/Issues.hpp"
#include <cetlib/BasicPluginFactory.h>


using namespace dunedaq::appfwk;

std::shared_ptr<dunedaq::appfwk::CommandSource>
dunedaq::appfwk::makeCommandSource(std::string const& uri)
{
    auto sep = uri.find("://");
    std::string scheme;
    if (sep == std::string::npos) { // simple path
        scheme = "file";
    }
    else {                  // with scheme
        scheme = uri.substr(0, sep);
    }
    std::string plugin_name = scheme + "CommandSource";
    static cet::BasicPluginFactory bpf("duneCommandSource", "make");
    return bpf.makePlugin<std::shared_ptr<dunedaq::appfwk::CommandSource>>(plugin_name, uri);
}


CommandHandler::pointer
dunedaq::appfwk::makeCommandHandler(std::string const& short_name, std::string const& inst)
{
    static cet::BasicPluginFactory bpf("duneCommandHandler", "make");
    std::string pname = short_name + "CommandHandler";
    ERS_INFO("Construct CommandHandler: \"" << short_name << "\"::\"" << inst << "\"");

    return bpf.makePlugin<std::shared_ptr<CommandHandler>>(pname, inst);
}


CommandContract::pointer
dunedaq::appfwk::makeCommandContract(std::string const& kind, 
                                     std::string const& inst)
{
    static cet::BasicPluginFactory bpf("duneCommandContract", "make");
    std::string pname = kind + "CommandContract";
    ERS_INFO("Construct CommandContract: \"" << kind << "\"::\"" << inst << "\"");

    return bpf.makePlugin<std::shared_ptr<CommandContract>>(pname, inst);
}
