#include "appfwk/CommandHandler.hpp"
#include "appfwk/QueueRegistry.hpp"
#include "appfwk/Issues.hpp"
#include "appfwk/AppNljs.hpp"
#include "appfwk/DqmNljs.hpp"

using namespace dunedaq::appfwk;

struct QueueCH : public CommandHandler {

    QueueCH(std::string name) : CommandHandler(name) {}
    virtual ~QueueCH() {}
    virtual object_t handle(const CMD_FQNS::Command& cmd) {
        ERS_INFO("Queue command handler got: " << str(cmd.id) << "\n" << cmd.data.dump(4));

        if(cmd.id == CMD_FQNS::Id::init) {
            auto ads = cmd.data.get<APP_FQNS::Addressed>();
            do_init(ads);
            // fixme: sending back our cmd as ack, probably need some
            // other protocol.
            return CMD_FQNS::Reply{cmd.id, ads};
        }

        throw UnexpectedCommand(ERS_HERE, "queue command handler", CMD_FQNS::str(cmd.id));
    }
    
    void do_init(APP_FQNS::Addressed ads) {
        std::map<std::string, QueueConfig> qrcfg;
        for (auto& ad : ads.addrdats) {
            auto qi = ad.data.get<DQM_FQNS::QueueInit>();
            // N.B.: here we mimic the behavior of daq_application and
            // ignore the tn.type.  This requires user configuration
            // to assure unique queue names across all queue types.
            const std::string qname = ad.tn.name;
            // fixme: maybe one day replace QueueConfig with codgen.
            // Until then, wheeee....
            QueueConfig qc;
            switch(qi.kind) {
            case DQM_FQNS::Kind::StdDeQueue:
                qc.kind = QueueConfig::queue_kind::kStdDeQueue;
                break;
            case DQM_FQNS::Kind::FollySPSCQueue:
                qc.kind = QueueConfig::queue_kind::kFollySPSCQueue;
                break;
            case DQM_FQNS::Kind::FollyMPMCQueue:
                qc.kind = QueueConfig::queue_kind::kFollyMPMCQueue;
                break;
            default:
                throw MissingComponent(ERS_HERE, "unknown queue type");
                break;
            }
            qc.capacity = qi.capacity;
            qrcfg[qname] = qc;
        }
        ERS_INFO("Queue command handler initialize queue registry");
        QueueRegistry::get().configure(qrcfg);
    }

};

extern "C" {
    std::shared_ptr<dunedaq::appfwk::CommandHandler> make(std::string inst) { 
        return std::shared_ptr<dunedaq::appfwk::CommandHandler>(new QueueCH(inst));
    }
}
