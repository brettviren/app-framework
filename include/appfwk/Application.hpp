#ifndef DUNEDAQ_APPFWK_APPLICATION_HPP
#define DUNEDAQ_APPFWK_APPLICATION_HPP

#include "appfwk/CommandHandler.hpp"
#include "appfwk/AppFSM.hpp"
#include <boost/msm/back/state_machine.hpp>

namespace dunedaq::appfwk {

    // FE to FSM.  Don't use directly.  Instead use AppFSM.
    class Application : public APP_FQNS::FE {

      public:

        using object_t = nlohmann::json;

        // FSM actions
        virtual void handle(const APP_FQNS::Init& evt);
        virtual void handle(const APP_FQNS::Conf& evt);
        virtual void handle(const APP_FQNS::Start& evt);
        virtual void handle(const APP_FQNS::Stop& evt);
        virtual void handle(const APP_FQNS::Scrap& evt);
        virtual void handle(const APP_FQNS::Fina& evt);

        // Forward comand to all addressed handlers.  Called by FSM
        // handle methods.  The final result is available as outcome.
        void forward(const CMD_FQNS::Command& cmd);

        // Return outcome of last command processing as a reply.
        CMD_FQNS::Reply outcome() const { return outcome_; }

      private:

        // Collect command handler output as a reply
        CMD_FQNS::Reply outcome_;

        struct HInfo {
            APP_FQNS::TypeName tn;
            CommandHandler::pointer handler;
        };
        std::vector<HInfo> handlers_;
        std::vector<HInfo> match(APP_FQNS::TypeName tn);
    };

    // This is what you actually use 
    using AppFSM = boost::msm::back::state_machine<Application>;

    // AppFSM app;
    // APP_FQNS::process(app, cmdobj);
    // auto rep = app->outcome();
    
}



#endif
