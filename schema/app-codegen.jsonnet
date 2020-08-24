local ccm = import "ccm.jsonnet";
local schemalist = [
    import "app-schema.jsonnet",
];
ccm.codegen("App", "dunedaq::appfwk::app", schemalist)
