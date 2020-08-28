/*
 * This file is 100% generated.  Any manual edits will likely be lost.
 *
 * This provides a full implementation of a command contract validator
 * plugin for App.
 *
 * It validates a stream of commands to have expected order as
 * determined by a finite state machine.
 */

#include "appfwk/CommandContract.hpp"
#include "appfwk/Issues.hpp"
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/back/state_machine.hpp>
#include <nlohmann/json.hpp>

#include "appfwk/AppNljs.hpp"

#include <nlohmann/json.hpp>

using namespace dunedaq::appfwk::cmd;
using namespace dunedaq::appfwk::app;

struct AppCommandContract : public dunedaq::appfwk::CommandContract {
private:
    struct FE: public boost::msm::front::state_machine_def<FE> {


        /// FSM States:
        /// The process is configured
        struct Configured : public boost::msm::front::state<> {};
        /// The process structure is constructed
        struct Initialized : public boost::msm::front::state<> {};
        /// The process is a blank slate
        struct Ready : public boost::msm::front::state<> {};
        /// The process is operating
        struct Running : public boost::msm::front::state<> {};

        using initial_state = Ready;

        /// The contract on order
        // clang-format off
        struct transition_table: boost::mpl::vector<
            _row<       Ready,         Init,  Initialized>,
            _row< Initialized,         Conf,   Configured>,
            _row<  Configured,        Start,      Running>,
            _row<     Running,         Stop,   Configured>,
            _row<  Configured,        Scrap,  Initialized>,
            _row< Initialized,         Fina,        Ready>
        > {};
        // clang-format on

        /// MSM catches so we must rethrow
        template <class FSM,class Event>
        void exception_caught (Event const& evt, FSM&, std::exception& e)
        {
            throw dunedaq::appfwk::CommandContractViolation(
                ERS_HERE, "exception caught in FSM",
                CMD_FQNS::str(evt.command.id), "App", e);
        }
    };
    using BE = boost::msm::back::state_machine<FE>;
    BE fsm;

public:
    using object_t = nlohmann::json;

    std::string name_;
    AppCommandContract(std::string name) : dunedaq::appfwk::CommandContract(name), name_(name) {}
    virtual ~AppCommandContract() {}

    virtual object_t validate(object_t cmdobj) {
        auto o = cmdobj.get<CMD_FQNS::Command>();
        std::string msg = "\n" + name_ + " validating: " + str(o.id) + "\n" + o.data.dump(4);
        ERS_INFO(msg);
        switch (o.id) {
        case Id::conf    : fsm.process_event(Conf{o}); break;
        case Id::fina    : fsm.process_event(Fina{o}); break;
        case Id::init    : fsm.process_event(Init{o}); break;
        case Id::scrap   : fsm.process_event(Scrap{o}); break;
        case Id::start   : fsm.process_event(Start{o}); break;
        case Id::stop    : fsm.process_event(Stop{o}); break;
        default:
            throw dunedaq::appfwk::CommandContractViolation(
                ERS_HERE, "unknown command",
                CMD_FQNS::str(o.id), "App");
            break;
        }
        // If we get here, the command is good.
        return cmdobj;
    }

};


extern "C" {
    std::shared_ptr<dunedaq::appfwk::CommandContract> make(std::string inst) { 
        return std::shared_ptr<dunedaq::appfwk::CommandContract>(new AppCommandContract(inst));
    }
}