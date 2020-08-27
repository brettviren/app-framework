#include "appfwk/CommandHandler.hpp"
#include "appfwk/DAQModule.hpp"
#include "appfwk/Issues.hpp"
#include "appfwk/AppNljs.hpp"
#include "appfwk/DqmNljs.hpp"

using namespace dunedaq::appfwk;

struct ModCH : public CommandHandler {

    std::shared_ptr<DAQModule> dmptr;

    std::string name_;

    ModCH(std::string name) : CommandHandler(name), name_(name) {}
    virtual ~ModCH() {}

    virtual object_t handle(const CMD_FQNS::Command& cmd) {
        ERS_INFO("Module command handler for \"" << name_ << "\" got: "
                 << str(cmd.id) << "\n" << cmd.data.dump(4));

        auto data = cmd.data;

        if(cmd.id == CMD_FQNS::Id::init) {
            auto mi = data.get<DQM_FQNS::ModInit>();
            data = mi.data;
            dmptr = makeModule(mi.plugin, name_);
        }
        if (!dmptr) {
            throw InternalError(ERS_HERE, "no such module: " + name_);
        }
        if (! data.is_null()) { // at least an empty object is needed
            dmptr->execute_command(str(cmd.id), data);
        }

        // Fixme: what to return here?
        return CMD_FQNS::Reply{cmd.id, {}};
    }
};




extern "C" {
    std::shared_ptr<dunedaq::appfwk::CommandHandler> make(std::string inst) { 
        return std::shared_ptr<dunedaq::appfwk::CommandHandler>(new ModCH(inst));
    }
}
