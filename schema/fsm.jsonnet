local ccm = import "ccm.jsonnet";

{
    state(name, doc="") :: {
        name: name, doc:doc
    },

    trans(ini, evt, fin, act="handle") :: {
        ini: ini, fin:fin, act: act,
        evt: ccm.commands.Names[ccm.commands.name2id(std.asciiLower(evt))]},

    states(tt) :: std.set([t.ini for t in tt]+[t.fin for t in tt],
                          function(s) s.name),

    actions(tt) :: std.set([{name:t.act, evt:t.evt} for t in tt],
                           function(a) a.name + a.evt),
    events(tt) :: std.set([t.evt for t in tt]),
}
