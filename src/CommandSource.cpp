#include "appfwk/CommandSource.hpp"
#include <cetlib/BasicPluginFactory.h>

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
