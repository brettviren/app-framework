#include "appfwk/Application.hpp"
#include "appfwk/CommandHandler.hpp"
#include "appfwk/AppNljs.hpp"
#include "appfwk/Issues.hpp"

#include <regex>
using namespace dunedaq::appfwk;


std::vector<Application::HInfo>
Application::match(APP_FQNS::TypeName tn)
{
    if (tn.type.empty()) { tn.type = ".*"; }
    if (tn.name.empty()) { tn.name = ".*"; }

    std::vector<Application::HInfo> ret;
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


void Application::forward(const APP_FQNS::Command& cmd)
{
    auto id = cmd.id;
    
    APP_FQNS::Addressed res;

    auto ads = cmd.data.get<APP_FQNS::Addressed>();
    for (const auto& ad : ads.addrdats) {
        for (auto& hi : match(ad.tn)) {
            CMD_FQNS::Command hcmd{id, ad.data};
            auto res = hi.handler->handle(hcmd);
            res.push_back(APP_FQNS::AddrDat{ad.tn, res});
        }
    }
    outcome_ = CMD_FQNS::Reply{id, res};
}


void Application::handle(const APP_FQNS::Init& evt)
{
    ERS_INFO("Appliation init construction with:\n" << evt.command.data.dump(4));
    auto ads = evt.command.data.get<APP_FQNS::Addressed>();
    for (const auto& ad : ads.addrdats) {
        ERS_INFO("construct: " << ad.tn.type << " : " << ad.tn.name);
        auto h = makeCommandHandler(ad.tn.type, ad.tn.name);
        assert(h);              // assume factory throws, o.w. replace this with a throw test
        handlers_.push_back(HInfo{ad.tn, h});
    }
    forward(evt.command);
}

void Application::handle(const APP_FQNS::Conf& evt)
{
    forward(evt.command);
}

void Application::handle(const APP_FQNS::Start& evt)
{
    forward(evt.command);
}

void Application::handle(const APP_FQNS::Stop& evt)
{
    forward(evt.command);
}

void Application::handle(const APP_FQNS::Scrap& evt)
{
    forward(evt.command);
}

void Application::handle(const APP_FQNS::Fina& evt)
{
    forward(evt.command);
    handlers_.clear();
}

