#ifndef GAME_QUEUE_H_
#define GAME_QUEUE_H_

#include <mutex>
#include <list>
#include <deque>
#include <queue>
#include <memory>
#include <future>
#include <condition_variable>

namespace thread_utils {
    template<typename T, typename Container=std::list<T>>
    class ThreadSafeQueue;

    template<typename Func, typename... Args, 
        typename ReturnType=typename std::result_of<
            std::decay_t<Func>(std::decay_t<Args>...)>::type,
        typename ThreadQueue=ThreadSafeQueue<
            std::packaged_task<ReturnType(Args...)>, std::list<Func>>>
    std::future<ReturnType> post_task(
            ThreadQueue& task_queue, Func&& f, Args&&... args) {
        std::packaged_task<ReturnType()> task(
            std::bind(std::forward<Func>(f), std::forward<Args>(args)...));
        std::future res = task.get_future();
        task_queue.push(std::move(task));   // packaged_task is not copyable
        return res;
    }

    template<typename T>
    class ThreadSafeQueue<T, std::list<T>> {
    public:
        // constructors
        ThreadSafeQueue(): head(std::make_unique<Node>()), tail(head.get()) {}
        ThreadSafeQueue(ThreadSafeQueue&&);

        // assignments
        ThreadSafeQueue& operator=(ThreadSafeQueue&&);

        // general purpose operations
        void swap(ThreadSafeQueue&);
        bool empty() const;
        std::size_t size() const;

        // queue operations
        void push(const T&);
        void push(T&&);
        template <typename... Args>
        void emplace(Args&&... args);
        T pop();
        bool try_pop(T&);
        // delete front() and back(), these functions may waste notifications. To enable these function, one should replace notify_one() with notify_all() in push() and emplace()
        T& front() = delete;
        const T& front() const = delete;
        T& back() = delete;
        const T& back() const = delete;
    private:
        struct Node {
            std::unique_ptr<T> data;    // data is a pointer as it may be empty
            std::unique_ptr<Node> next;
        };

        Node* get_tail() {
            std::lock_guard l(tail_mutex);
            return tail;
        }
        Node* get_head() {
            std::lock_guard l(head_mutex);
            return head.get();
        }
        std::unique_lock<std::mutex> get_head_lock() {
            std::unique_lock l(head_mutex);
            data_cond.wait(l, [this] { return head.get() != get_tail(); });
            return l;
        }
        T pop_data() {
            auto data = std::move(*head->data);
            head = std::move(head->next);   // we move head to the next so that the tail is always valid
            return std::move(data);
        }

        std::unique_ptr<Node> head;
        std::mutex head_mutex;
        Node* tail;
        std::mutex tail_mutex;
        std::condition_variable data_cond;
    };

    template<typename T>
    ThreadSafeQueue<T, std::list<T>>::ThreadSafeQueue(
        ThreadSafeQueue<T, std::list<T>>&& other) {
        {
            std::scoped_lock l(head_mutex, other.head_mutex);
            head(std::move(other.data_queue));
        }
        {
            std::lock_guard l(tail_mutex);
            tail = head.get();
        }
        {
            std::lock_guard l(other.tail_mutex);
            other.tail = nullptr;
        }
    }

    template<typename T>
    ThreadSafeQueue<T, std::list<T>>& 
    ThreadSafeQueue<T, std::list<T>>::operator=(
        ThreadSafeQueue<T, std::list<T>>&& rhs) {
        {
            std::scoped_lock l(head_mutex, rhs.head_mutex);
            head(std::move(rhs.data_queue));
        }
        {
            std::lock_guard l(tail_mutex);
            tail = head.get();
        }
        {
            std::lock_guard l(rhs.tail_mutex);
            rhs.tail = nullptr;
        }
    }

    template<typename T>
    void ThreadSafeQueue<T, std::list<T>>::swap(
        ThreadSafeQueue<T, std::list<T>>& other) {
        {
            std::scoped_lock l(head_mutex, other.head_mutex);
            head(std::move(other.data_queue));
        }
        {
            std::lock_guard l(tail_mutex);
            tail = head.get();
        }
        {
            std::lock_guard l(other.tail_mutex);
            other.tail = other.head.get();
        }
    }

    template<typename T>
    inline bool ThreadSafeQueue<T, std::list<T>>::empty() const {
        return get_head() == get_tail();
    }

    template<typename T>
    std::size_t ThreadSafeQueue<T, std::list<T>>::size() const {
        int n = 0;
        std::lock_guard l(tail_mutex);  // do not use get_tail() here to avoid race condition
        for (auto p = get_head(); p != tail; p = p->next.get())
            ++n;
        return n;
    }

    template<typename T>
    void ThreadSafeQueue<T, std::list<T>>::push(const T& data) {
        push(T(data));
    }

    template<typename T>
    void ThreadSafeQueue<T, std::list<T>>::push(T&& data) {
        {
            auto p = std::make_unique<Node>();
            std::lock_guard l(tail_mutex);
            tail->data = std::make_unique<T>(std::move(data));   // we add data to the current tail, this allows us to move head to the next when popping
            tail->next = std::move(p);
            tail = tail->next.get();
        }
        data_cond.notify_one();
    }

    template<typename T>
    template<typename...Args>
    void ThreadSafeQueue<T, std::list<T>>::emplace(Args&&... args) {
        {
            auto p = std::make_unique<Node>();
            std::lock_guard l(tail_mutex);
            tail->data = std::make_unique<T>(std::forward<Args>(args)...);
            tail->next = std::move(p);
            tail = tail->next.get();
        }
        data_cond.notify_one();
    }

    template<typename T>
    T ThreadSafeQueue<T, std::list<T>>::pop() {
        auto l(get_head_lock());
        return pop_data();
    }

    template<typename T>
    bool ThreadSafeQueue<T, std::list<T>>::try_pop(T& data) {
        std::lock_guard l(head_mutex);
        if (head.get() == get_tail())
            return false;
        data = pop_data();
        return true;
    }
}

#endif