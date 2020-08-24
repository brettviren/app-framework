#include "appfwk/Application.hpp"
#include "appfwk/CmdStructs.hpp"
#include "ers/ers.h"



using namespace dunedaq::appfwk;


void Application::handle_init(const cmd::Init& evt)
{
    ERS_INFO("\n" << cmd::str(evt.object.id));
    for (const auto& pl : evt.object.payloads) {
        ERS_INFO("\nfor: " << pl.recipient << ":\n" << pl.data.dump(4));
        if (pl.recipient == "app") {
            // construct
        }
        else {
            delegate(recipient, pl.data);
        }
    }
}

void Application::handle_conf(const cmd::Conf& evt)
{
}

void Application::handle_start(const cmd::Start& evt)
{
}

void Application::handle_stop(const cmd::Stop& evt)
{
}

void Application::handle_scrap(const cmd::Scrap& evt)
{
}

void Application::handle_fina(const cmd::Fina& evt)
{
}

