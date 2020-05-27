/**
 * @file The FakeDataConsumerDAQModule class implementation
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "app-framework/DAQModules/FakeDataConsumerDAQModule.hh"

#include "TRACE/trace.h"
#define TRACE_NAME "FakeDataConsumer"

#include <chrono>
#include <functional>
#include <thread>

appframework::FakeDataConsumerDAQModule::FakeDataConsumerDAQModule(
  std::string name,
  std::vector<std::shared_ptr<QueueI>> inputs,
  std::vector<std::shared_ptr<QueueI>> outputs)
  : DAQModule(name, inputs, outputs)
  , bufferTimeout_(100)
  , thread_(std::bind(&FakeDataConsumerDAQModule::do_work, this))
{
  if (outputs.size()) {
    throw std::runtime_error(
      "Invalid Configuration for FakeDataConsumerDAQModule: Output buffer "
      "provided!");
  }
  if (inputs.size() > 1) {
    throw std::runtime_error("Invalid Configuration for "
                             "FakeDataConsumerDAQModule: More than one Input "
                             "provided!");
  }

  inputQueue_.reset(dynamic_cast<QueueOutput<std::vector<int>>*>(&*inputs_[0]));
}

std::future<std::string>
appframework::FakeDataConsumerDAQModule::execute_command(std::string cmd)
{
  if (cmd == "configure" || cmd == "Configure") {
    return std::async(std::launch::async, [&] { return do_configure(); });
  }
  if (cmd == "start" || cmd == "Start") {
    return std::async(std::launch::async, [&] { return do_start(); });
  }
  if (cmd == "stop" || cmd == "Stop") {
    return std::async(std::launch::async, [&] { return do_stop(); });
  }

  return std::async(std::launch::async,
                    [] { return std::string("Unrecognized Command"); });
}

std::string
appframework::FakeDataConsumerDAQModule::do_configure()
{
  nIntsPerVector_ = 10;
  starting_int_ = -4;
  ending_int_ = 14;

  return "Success";
}

std::string
appframework::FakeDataConsumerDAQModule::do_start()
{
  thread_.start_working_thread_();
  return "Success";
}

std::string
appframework::FakeDataConsumerDAQModule::do_stop()
{
  thread_.stop_working_thread_();
  return "Success";
}

TraceStreamer&
operator<<(TraceStreamer& t, std::vector<int> ints)
{
  t << "{";
  bool first = true;
  for (auto& i : ints) {
    if (!first)
      t << ", ";
    first = false;
    t << i;
  }
  return t << "}";
}

void
appframework::FakeDataConsumerDAQModule::do_work()
{
  int current_int = starting_int_;
  int counter = 0;
  int fail_count = 0;
  std::vector<int> vec;

  while (thread_.thread_running()) {
    if (!inputQueue_->empty()) {

      TLOG(TLVL_DEBUG) << instance_name_
                       << " Going to receive data from inputQueue";

      try {
        vec = inputQueue_->pop(bufferTimeout_);
      } catch (const std::runtime_error& err) {
        TLOG(TLVL_WARNING) << "Tried but failed to pop a value from an "
                              "inputQueue (exception is \""
                           << err.what() << "\"";
        continue;
      }

      TLOG(TLVL_DEBUG) << instance_name_ << " Received vector of size "
                       << vec.size();

      bool failed = false;

      TLOG(TLVL_DEBUG) << instance_name_ << " Starting processing loop";
      TLOG(TLVL_INFO) << instance_name_ << " Received vector " << counter
                      << ": " << vec;
      size_t ii = 0;
      for (auto& point : vec) {
        if (point != current_int) {
          if (ii != 0) {
            TLOG(TLVL_WARNING)
              << instance_name_ << " Error in received vector " << counter
              << ", position " << ii << ": Expected " << current_int
              << ", received " << point;
            failed = true;
          } else {
            TLOG(TLVL_INFO) << instance_name_ << " Jump detected!";
          }
          current_int = point;
        }
        ++current_int;
        if (current_int > ending_int_)
          current_int = starting_int_;
        ++ii;
      }
      TLOG(TLVL_DEBUG) << instance_name_
                       << " Done with processing loop, failed=" << failed;
      if (failed)
        fail_count++;

      counter++;
    } else {
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }

  TLOG(TLVL_INFO) << instance_name_ << " Processed " << counter
                  << " vectors with " << fail_count << " failures.";
}

DEFINE_DUNE_USER_MODULE(appframework::FakeDataConsumerDAQModule)
