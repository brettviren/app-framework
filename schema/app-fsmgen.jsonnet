local moo = import "moo.jsonnet";
local as = import "app-schema.jsonnet";


{
    fsm: as(moo.schema.avro).fsm,
    name: "App",
    namespace: "dunedaq::appfwk::app",
    structincs: '#include "AppNljs.hpp"',
}

