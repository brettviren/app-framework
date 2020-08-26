local ccm = import "ccm.jsonnet";
local schema = import "test-schema.jsonnet";
ccm.codegen(schema)
