/** @file ddnode.cpp DUNE DAQ Node
 *
 * Usage:
 *
 *     ddnode <URI>
 *
 * This program provides a fully generic, command-driven application.
 *
 * The behavior of this process is fully parameterized by the URI and
 * subsequent command information found at that location.  Independent
 * on the command source or the format of data it provides, behavior
 * is implemented in a common manner.
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "appfwk/Application.hpp"
#include "appfwk/CommandSource.hpp"
#include "appfwk/Issues.hpp"

int main(int argc, char* argv[])
{
    using namespace dunedaq::appfwk;
    using object_t = CommandSource::object_t;

    if (argc != 2) {
        ERS_INFO("No URI provided.\n"
                 << "usage:\n" << "\tddnode <URI>\n"
                 << "Examples:\n"
                 << "\tddnode somefile.jsonstream\n"
                 << "\tddnode file://path/to/somefile.json\n");
	throw BadCliUsage(ERS_HERE, "no URI provided");
    }
    const std::string uri = argv[1];

    using BE = boost::msm::back::state_machine<Application>;
    BE app;

    auto cs = makeCommandSource(uri);
    while (true) {
        object_t command;
        try {
            command = cs->recv();
        }
        catch (const StreamExhausted& e) {
            ERS_INFO("Command stream end");
            break;
        }
        app.outcome = {};
        appfsm::process(app, command);
        cs->send(app.outcome);
    }
    return 0;    
}
