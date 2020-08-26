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
};

local ah = {
    TypeName(t,n="") :: {type:t, name:n},

    AddrDat(tn, data) :: {tn:tn, data:data },

    // The command.data type for app
    Addressed(addrdats) :: { addrdats: addrdats },
};

local noisy = {
    tn: ah.TypeName("noisy"),
    init(greeting="hi") :: { greeting:greeting },
    conf(verbosity=0) :: { verbosity: verbosity },
};

[
    ch.Command("init", 
               ah.Addressed([ah.AddrDat(noisy.tn, noisy.init())])),

    ch.Command("conf",
               ah.Addressed([ah.AddrDat(noisy.tn, noisy.conf())])),
]
