/*
 * This file is 100% generated.  Any manual edits will likely be lost.
 */
#ifndef DUNEDAQ__APPFWK__APP_APP_FSM_HPP
#define DUNEDAQ__APPFWK__APP_APP_FSM_HPP

#include "appfwk/Issues.hpp"
#include <boost/msm/front/state_machine_def.hpp>
#include <nlohmann/json.hpp>

#include "AppNljs.hpp"
#include "CmdNljs.hpp"

namespace dunedaq::appfwk::app {

    /** @brief Abstract MSM front end for App
     *
     * Inherit from this class:
     *
     *     class MyFE : public dunedaq::appfwk::app::FE;
     *
     * Implement the action methods.
     *
     * Then to use do:
     * 
     * #include <boost/msm/back/state_machine.hpp>
     * using MyFSM = boost::msm::back::state_machine<MyFE>;
     *
     *     MyFSM sm;
     *     auto met = obj.get<MyEventType>();
     *     sm.process_event(met);
     *
     * Or, to automatically handle the re-typing:
     *
     *     dunedaq::appfwk::app::process(sm, obj);
     *
     */
    struct FE : public boost::msm::front::state_machine_def<FE> {

        using object_t = nlohmann::json;

        /// FSM States:
        /// The process is configured
        struct Configured : public boost::msm::front::state<> {};
        /// The process structure is constructed
        struct Initialized : public boost::msm::front::state<> {};
        /// The process is a blank slate
        struct Ready : public boost::msm::front::state<> {};
        /// The process is operating
        struct Running : public boost::msm::front::state<> {};

        /// FSM Actions:
        virtual void handle_conf(const Conf& evt) = 0;
        virtual void handle_fina(const Fina& evt) = 0;
        virtual void handle_forward(const Start& evt) = 0;
        virtual void handle_forward(const Stop& evt) = 0;
        virtual void handle_init(const Init& evt) = 0;
        virtual void handle_scrap(const Scrap& evt) = 0;

        // clang-format off
        struct transition_table: boost::mpl::vector<
            a_row<       Ready,         Init,  Initialized, &FE::handle_init>,
            a_row< Initialized,         Conf,   Configured, &FE::handle_conf>,
            a_row<  Configured,        Start,      Running, &FE::handle_forward>,
            a_row<     Running,         Stop,   Configured, &FE::handle_forward>,
            a_row<  Configured,        Scrap,  Initialized, &FE::handle_scrap>,
            a_row< Initialized,         Fina,        Ready, &FE::handle_fina>
            > {};
        // clang-format on
    };

    /// Inject an typed event derived from the object.
    template<class BE>
    void process(BE& be, nlohmann::json obj) {
        auto o = obj.get<dunedaq::appfsk::cmd::Command>();
        switch (o.id) {
            case Id::conf: be.process_event(o.data.get<Conf>()); break;
            case Id::fina: be.process_event(o.data.get<Fina>()); break;
            case Id::init: be.process_event(o.data.get<Init>()); break;
            case Id::scrap: be.process_event(o.data.get<Scrap>()); break;
            case Id::start: be.process_event(o.data.get<Start>()); break;
            case Id::stop: be.process_event(o.data.get<Stop>()); break;
            default:
                throw SchemaError(ERS_HERE, "unknown command type");
                break;
        }
    };

} // namespace dunedaq::appfwk::app

#endif // DUNEDAQ__APPFWK__APP_APP_FSM_HPP