/** CCM command level schema
* 
* The CCM command schema covers a high-level part of an overall schema
* which is general across application implementations.
* 
* A CCM command consists merely of a command identifier (name/ID/enum)
* and unstructured command data.
*
* Additional "application-level" schema is likely applied to the command data.
*/


local moo = import "moo.jsonnet";
local re = moo.schema.re;
local ccm = import "ccm.jsonnet";

function(schema) {

    // An "ident" is a string with a limited "spelling".  It should be
    // used for instance names or implementation names registered with
    // a factory.
    ident: schema.string("Ident", pattern=re.ident),

    // A string consiting of a single letter
    letter: schema.string("Letter", pattern='^[a-zA-Z]$'),

    // A string that is a legal file path
    filepath: schema.string("FilePath", pattern=re.hierpath),

    // A Boolean value 
    bool: schema.boolean("Bool"),

    // A double precision floating piont number
    double: schema.number("Double", dtype="f8"),

    // A single precision floating piont number
    float: schema.number("Float", dtype="f4"),

    // A two byte int
    short: schema.number("Short", dtype="i2"),

    // A four byte int
    int: schema.number("Int", dtype="i4"),

    // An eight byte int
    long: schema.number("Long", dtype="i8"),
    ulong: schema.number("ULong", dtype="u8"),

    // The CCM command ID/name.  It is represented as a literal string
    // from an enumerated set.
    id: schema.enum(
        "Id",
        ccm.commands.names,
        default="undef",
        doc="The set of expected command identifiers"),

    // Command data schema is left open at this level.  Resolving it
    // is left to the application-level schema.
    data: schema.any("Data"),

    // Wrap everything up into a single command.
    command: schema.record("Command", fields = [
        schema.field("id", $.id, "Id::undef", doc="The command identifier"),
        schema.field("data", $.data, doc="The command data")
    ], doc="A command"),

    types: [$.ident, $.letter, $.filepath, $.bool, $.short, $.int, $.long, $.float, $.double,
            $.id, $.data, $.command],

}
