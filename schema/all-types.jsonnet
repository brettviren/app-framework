// dump types for reference.

local moo = import "moo.jsonnet";
local as = moo.schema.avro;
local s = {
    cmd: import "cmd-schema.jsonnet",
    app: import "app-schema.jsonnet",
    dqm: import "dqm-schema.jsonnet",
};

{[n]:as.types(s[n]) for n in std.objectFields(s)}
    
