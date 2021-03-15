#ifndef GAME_JOIN_TREAD_H_
#define GAME_JOIN_TREAD_H_

#include <thread>
#include <utility>

namespace thread_utils {
    class JoinThread {
    public:
        JoinThread() noexcept=default;
        template<typename Callable, typename... Args>
        JoinThread(Callable&& callable, Args&&... args):
            t(std::forward<Callable>(callable), std::forward<Args>(args)...) {}
        explicit JoinThread(std::thread tt) noexcept: t(std::move(tt)) {}

        JoinThread(JoinThread&& other) noexcept: t(std::move(other.t)) {}
        JoinThread& operator=(JoinThread&& other) noexcept {
            if (t.joinable())
                t.join();
            t = std::move(other.t);
            return *this;
        }

        ~JoinThread() noexcept {
            if (t.joinable())
                t.join();
        }

        void swap(JoinThread& other) noexcept {
            t.swap(other.t);
        }

        /* thread functions */
        std::thread::id get_id() const noexcept {
            return t.get_id();
        }
        bool joinable() const noexcept {
            return t.joinable();
        }
        void join() {
            t.join();
        }
        void detach() {
            t.detach();
        }

        /* retrieve thread */
        std::thread& get_thread() noexcept {
            return t;
        }
        const std::thread& get_thread() const noexcept {
            return t;
        }
    private:
        std::thread t;
    };
}

#endif
