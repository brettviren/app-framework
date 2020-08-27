// command helpers, move to module
local ccm = import "ccm.jsonnet";
// local cmd_schema = import "cmd-schema.jsonnet";
// local app_schema = import "app-schema.jsonnet";
// local dqm_schema = import "dqm-schema.jsonnet";

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

// Group together the tn and the commands to each *instance*

local noisy = {
    tn: ah.TypeName("noisy", "noisy1"),
    init: { greeting:"hi" },
    conf: { verbosity: 0 },
};

local queue(name, kind="StdDeQueue", capacity=10) =
    ah.AddrDat(ah.TypeName(kind, name), { kind:kind, capacity:capacity});

local queues = {
    tn: ah.TypeName("queue"),
    init: ah.Addressed([queue("queue1")]),        
};


local module = {
    tn(inst) :: ah.TypeName("module", inst),
    init(plugin, data=null) :: { plugin:plugin, data:data },
};

local fdph = {
    tn: module.tn("source1"),
    init: module.init("FakeDataProducerDAQModule"),
    conf: {output:"queue1"},
    start: {run:42},
    stop: {},
};

local fdch = {
    tn: module.tn("sink1"),
    init: module.init("FakeDataConsumerDAQModule"),
    conf: {input:"queue1"},
    start: {run:42},
    stop: {},
};

local handlers = [ noisy, queues, fdph, fdch ];

local cn = ccm.commands.n;
local commands = [cn.init, cn.conf, cn.start, cn.stop, cn.scrap, cn.fina];

[ ch.Command(cname,
             ah.Addressed([ah.AddrDat(h.tn, h[cname])
                           for h in handlers if std.objectHas(h, cname)]))
  for cname in commands ]

