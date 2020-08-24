// This provides application-level schema to apply to command-level
// data for programs based on appfwk::Application (eg ddnode).
//
// The command data in interpreted as an array of "payload" objects.
// Each payload has a named recipient and a second element which is
// treated as unstructured data ("any") at this level.  The payloads
// are specified by recipient-specific schema elsewhere.
//
// The appfwk::Application protects itself with an FSM.  CCM command
// types are mapped to FSM event types.  These types are also
// described here.

local moo = import "moo.jsonnet";
local re = moo.schema.re;
local ccm = import "ccm.jsonnet";
local cmdschema = import "cmd-schema.jsonnet";

local fsm = {
    state(name, doc="") :: {
        name: name, doc:doc
    },

    trans(ini, evt, fin, act) :: {
        ini: ini, fin:fin, act: act,
        evt: ccm.commands.Names[ccm.commands.name2id(std.asciiLower(evt))]},

    states(tt) :: std.set([t.ini for t in tt]+[t.fin for t in tt],
                          function(s) s.name),

    actions(tt) :: std.set([{name:t.act, evt:t.evt} for t in tt],
                           function(a) a.name + a.evt),
    events(tt) :: std.set([t.evt for t in tt]),
};

function(schema) {
    local cmd = cmdschema(schema),

    // The command recipient may be a DAQModule instance name or the
    // special names: ":all:" to indicate all DAQModule instances
    // should receive the payload (simple space optimization) or
    // ":app:" to indicate the appfwk::Application itself should
    // consume the payload.
    recipient: schema.string("Recipient",
                             pattern='^:all:$|^:app:$|%s' % self.ident),

    // The command payload recipient plus data.
    payload: schema.record("Payload", fields = [
        schema.field("recipient", $.recipient, "",
                      doc="Recipient of command data"),
        schema.field("data", cmd.data,
                     doc="Command data")
    ], doc="Associate data to a recipient"),

    // The command data is a sequence of payloads.
    payloads: schema.sequence("Payloads", $.payload),

    // The appfwk::Application FSM event types.
    events: [schema.record(N, fields = [
        schema.field("payloads", $.payloads, doc="Command payloads"),
    ], doc="FSM event type for command "+N) for N in ccm.commands.Names],

    fsm: {
        
        local rdy = fsm.state("Ready", "The process is a blank slate"),
        local ini = fsm.state("Initialized", "The process structure is constructed"),
        local cfg = fsm.state("Configured", "The process is configured"),
        local run = fsm.state("Running", "The process is operating"),


        tt: [
            fsm.trans(rdy, "Init", ini, "handle_init"),
            fsm.trans(ini, "Conf", cfg, "handle_conf"),
            fsm.trans(cfg, "Start",run, "handle_forward"),
            fsm.trans(run, "Stop", cfg, "handle_forward"),
            fsm.trans(cfg, "Scrap",ini, "handle_scrap"),
            fsm.trans(ini, "Fina", rdy, "handle_fina"),
        ],

        initial: self.tt[0].ini.name,

        states: fsm.states(self.tt),
        actions: fsm.actions(self.tt),

        events: fsm.events(self.tt),

    },

    types: [$.recipient, $.payload, $.payloads] + self.events,

}
