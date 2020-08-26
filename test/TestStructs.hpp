/*
 * This file is 100% generated.  Any manual edits will likely be lost.
 */
#ifndef DUNEDAQ__APPFWK__TEST_STRUCTS_HPP
#define DUNEDAQ__APPFWK__TEST_STRUCTS_HPP

#include <string>


// Hand-written code may find it handy to use the codegen namespace
// via CPP macro to insulate any changes in schema.  Short and fully
// qualified versions:
#ifndef TEST_NS 
#define TEST_NS test
#endif
#ifndef TEST_FQNS
#define TEST_FQNS dunedaq::appfwk::test
#endif

namespace dunedaq::appfwk::test {



    /// @brief Configuration for FakeDataProducerDAQMOdule
    struct FakeDataProducerCfg {
        std::string output{  };
        int32_t starting_int{ -4 };
        int32_t ending_int{ 14 };
        int32_t queue_timeout_ms{ 1000 };
        int32_t wait_between_sends_ms{ 1000 };
        uint64_t nIntsPerVector{ 10 };
    };


    /// @brief Configuration for FakeDataConsumerDAQMOdule
    struct FakeDataConsumerCfg {
        std::string input{  };
        int32_t starting_int{ -4 };
        int32_t ending_int{ 14 };
        int32_t queue_timeout_ms{ 1000 };
    };


} // namespace dunedaq::appfwk::test

#endif // DUNEDAQ__APPFWK__TEST_STRUCTS_HPP