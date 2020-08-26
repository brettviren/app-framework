#include "appfwk/CommandHandler.hpp"
#include "appfwk/Issues.hpp"

using namespace dunedaq::appfwk;

struct Noisy : public CommandHandler {
    std::string name_;
    Noisy(std::string name) : CommandHandler(name), name_(name) {}
    virtual ~Noisy() {}
    virtual object_t handle(const APP_FQNS::Command& cmd) {
        ERS_INFO("Handle command: " << str(cmd.id) << "\n" << cmd.data.dump(4));
        return {};
    }
    
};

extern "C" {
    std::shared_ptr<dunedaq::appfwk::CommandHandler> make(std::string inst) { 
        return std::shared_ptr<dunedaq::appfwk::CommandHandler>(new Noisy(inst));
    }
}
