// Schema for handling of queues/modules
local cmdschema = import "cmd-schema.jsonnet";
function(schema) {
    local cmd = cmdschema(schema),
    name: "Dqm",

    // Note, appfwk queue "kind" is mapped from tn.type.
    queue: schema.record("Queue", fields = [
        schema.field("capacity", cmd.ulong, doc="Queue capcity"),
    ], doc="Queue 'init' data structure"),


    types: [cmd.ulong, cmd.ident, $.queue],
}

