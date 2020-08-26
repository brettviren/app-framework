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

    types: [cmd.ulong, cmd.ident, self.queue.kind, self.queue.spec],
}

