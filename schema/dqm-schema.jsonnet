// Schema for handling of queues/modules
local cmdschema = import "cmd-schema.jsonnet";
function(schema) {
    local cmd = cmdschema(schema),
    name: "Dqm",
    deps: [cmd],

    queue: {

        kinds: ["Unknown", "StdDeQueue", "FollySPSCQueue", "FollyMPMCQueue"],
        kind: schema.enum("Kind", self.kinds, default="Unknown",
                          doc="The kinds of queues"),
        // The "configuration" expected in 'init' command's data
        spec: schema.record("QueueInit", fields = [
            schema.field("kind", $.queue.kind, doc="The kind of queue"),
            schema.field("capacity", cmd.ulong, doc="The queue capacity"),
        ], doc="Queue 'init' data structure"),
    },

    mod: {
        spec: schema.record("ModInit", fields = [
            schema.field("plugin", cmd.ident, doc="Module plugin name"),
            schema.field("data", cmd.data, doc="Any init information to the module"),
        ], doc="Module 'init' data structure"),
    },

    types: [cmd.ulong, cmd.ident, cmd.data,
            self.queue.kind, self.queue.spec,
            self.mod.spec],
}

