// command helpers, move to module
local ccm = import "ccm.jsonnet";
local ch = {

    // round trip to make sure the name is defined.
    CmdName(n) :: ccm.commands.names[ccm.commands.name2id(n)],

    Command(name, payloads=[]) :: {
        id: $.CmdName(name), payloads: payloads },

    Payload(recipient, data) :: {
        recipient:recipient, data:data },

};

[
    ch.Command("init", [
        ch.Payload("foo", {initbar:42})
    ]),

    ch.Command("conf", [
        ch.Payload("foo", {confbar:1234}),
    ]),
]
