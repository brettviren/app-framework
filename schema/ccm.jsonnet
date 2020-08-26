// Helper schema code for CCM command code generator
local moo = import "moo.jsonnet";
local avro = moo.schema.avro;

// Return a function which looks like a concrete schema but is
// actually many concrete schema.  When returned function is
// itself called an a domain schema, call each concrete schema on
// the domain and return the result as a flat array.
local multischema(ss) = function(schemalist) {
    types: std.flattenArrays([s(schemalist).types for s in ss])
};


{
    // Meta info for codegen.
    metagen(as) :: {
        // name, incdir, basenamespace, ext=".hpp", deps=[]) :: {
        name: as.name,          // short Capitalized name
        ext: ".hpp",            // hard-code for now
        incdir: if std.objectHas(as, "incdir") then as.incdir else "appfwk",
        basens: if std.objectHas(as, "basens") then as.basens else "dunedaq::appfwk",
        deps: if std.objectHas(as, "deps") then [$.metagen(s) for s in as.deps] else [],
        ns: self.basens + "::" + std.asciiLower(self.name),
    },


    // The "any" type is outside Avro type system and the concrete C++
    // type to supply it must be chosen.  In appfwk we use NLJS, but
    // in principle, others can be substituted.
    nljsany: {
        incs: ["nlohmann/json.hpp"],
        type: "nlohmann::json",
    },

    // Return data structure for generating code.
    codegen(schema) :: {
        local as = schema(moo.schema.avro),
        res: {
            any: $.nljsany,
            types: moo.schema.avro.export(as.types),
            meta: $.metagen(as), // .name, incdir, basens, ext, deps),
            [if std.objectHas(as, "fsm") then "fsm"]: as.fsm,
        }
    }.res,


    // This collects all meta info about CCM commands intended for use
    // in other parts of the schema.
    commands: {
        Names: ["Undef","Exec","Init","Conf","Start","Stop","Scrap","Fina","Term"],
        names: [std.asciiLower(n) for n in self.Names],

        name2id(name) :: std.find(name, self.names)[0],

        // Access name as jsonnet variable (avoid typos)
        N: {[N]:N for N in self.Names},
        n: {[std.asciiLower(n)]:n for n in self.Names},
    },

    // fixme: describe an fsm, add template to realize it.  Assume boost::msm.
}

