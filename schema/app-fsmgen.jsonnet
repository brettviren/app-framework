local ccm = import "ccm.jsonnet";
local as = import "app-schema.jsonnet";
ccm.fsmgen("App", as)

// {
//     local s = as(moo.schema.avro),

//     fsm: s.fsm,
//     name: "App",
//     namespace: s.namespace,
//     structincs: '#include "AppNljs.hpp"',
// }

