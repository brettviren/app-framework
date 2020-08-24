#ifndef DUNEDAQ_APPFWK_APPLICATION_HPP
#define DUNEDAQ_APPFWK_APPLICATION_HPP

#include "appfwk/CommandHandler.hpp"
#include "appfwk/AppFSM.hpp"
#include <boost/msm/back/state_machine.hpp>

namespace dunedaq::appfwk {

    class Application : public appfsm::FE {
        std::vector<CommandHandler::pointer> pipeline_;

      public:

        using object_t = nlohmann::json;

        object_t outcome;       // may be set by handlers

        // FSM actions
        virtual void handle_exec(const cmd::Exec& evt){}
        virtual void handle_init(const cmd::Init& evt);
        virtual void handle_conf(const cmd::Conf& evt);
        virtual void handle_start(const cmd::Start& evt);
        virtual void handle_stop(const cmd::Stop& evt);
        virtual void handle_scrap(const cmd::Scrap& evt);
        virtual void handle_fina(const cmd::Fina& evt);
        virtual void handle_term(const cmd::Term& evt){}

        /// Add to the pipeline structure.
        void append(CommandHandler::pointer cd);

      private:

    };
    using AppFSM = boost::msm::back::state_machine<Application>;
}



#endif
