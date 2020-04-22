#ifndef app_framework_Buffers_DequeBuffer_hh
#define app_framework_Buffers_DequeBuffer_hh

#include "app-framework-base/Buffers/Buffer.hh"

#include <unistd.h>
#include <atomic>
#include <deque>
#include <functional>
#include <mutex>

namespace appframework {

template <class T>
class DequeBuffer : virtual public BufferInput<T>, virtual public BufferOutput<T> {
   public:
    DequeBuffer();

    void Configure();

    size_t size() { return fSize.load(); }
    size_t capacity() { return fCapacity; }

    bool empty() { return size() == 0; }
    bool full() { return size() >= capacity(); }

    int push(T&&);  /// push one on, return new size if successful, -1 if not
    T pop();        /// pop one off, return object

   private:
    std::deque<T> fDeque;
    std::atomic<size_t> fSize = 0;
    size_t fCapacity;

    std::mutex fMutex;
    size_t fRetryTime_ms;
    size_t fPushRetries;
    size_t fPopRetries;
};

}  // namespace appframework

#endif  // app_framework_Buffers_Buffer_hh
