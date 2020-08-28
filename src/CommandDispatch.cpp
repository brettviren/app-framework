#include "appfwk/CommandDispatch.hpp"
#include "appfwk/CommandHandler.hpp"
#include "appfwk/AppNljs.hpp"
#include "appfwk/Issues.hpp"

#include <regex>
using namespace dunedaq::appfwk;

CommandDispatch::object_t CommandDispatch::dispatch(object_t cmdobj)
{
    auto cmd = cmdobj.get<CMD_FQNS::Command>();

    if (cmd.id == CMD_FQNS::Id::init) {
        ERS_INFO("Dispatch init construction with:\n" << cmd.data.dump(4));
        auto ads = cmd.data.get<APP_FQNS::Addressed>();
        for (const auto& ad : ads.addrdats) {
            ERS_INFO("construct: " << ad.tn.type << " : " << ad.tn.name);
            auto h = makeCommandHandler(ad.tn.type, ad.tn.name);
            assert(h);              // assume factory throws, o.w. replace this with a throw test
            handlers_.push_back(HInfo{ad.tn, h});
        }
    }
    return forward(cmd);
}


CMD_FQNS::Reply CommandDispatch::forward(const CMD_FQNS::Command& cmd)
{
    auto id = cmd.id;
    
    APP_FQNS::Addressed addr_reply;

    auto ads = cmd.data.get<APP_FQNS::Addressed>();
    for (const auto& ad : ads.addrdats) {
        for (auto& hi : match(ad.tn)) {
            CMD_FQNS::Command hcmd{id, ad.data};
            auto res = hi.handler->handle(hcmd);
            addr_reply.addrdats.push_back(APP_FQNS::AddrDat{ad.tn, res});
        }
    }
    return CMD_FQNS::Reply{id, addr_reply};
}

std::vector<CommandDispatch::HInfo>
CommandDispatch::match(APP_FQNS::TypeName tn)
{
    if (tn.type.empty()) { tn.type = ".*"; }
    if (tn.name.empty()) { tn.name = ".*"; }

    std::vector<CommandDispatch::HInfo> ret;
    for (auto& hi : handlers_) {
        if (! std::regex_match(hi.tn.type.c_str(), std::regex(tn.type.c_str())) ) {
            continue;
        }
        if (! std::regex_match(hi.tn.name.c_str(), std::regex(tn.name.c_str())) ) {
            continue;
        }
        ret.push_back(hi);
    }
    return ret;
}
