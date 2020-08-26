// command helpers, move to module
local ccm = import "ccm.jsonnet";
local cmd_schema = import "cmd-schema.jsonnet";
local app_schema = import "app-schema.jsonnet";

local ch = {

    // round trip to make sure the name is defined.
    CmdName(n) :: ccm.commands.names[ccm.commands.name2id(n)],

    // Note: this is manually defined and may not match schema.
    Command(name, data=null) :: {
        id: $.CmdName(name), data: data },

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
