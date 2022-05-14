/*
 * @Author: Limer
 * @Date: 2022-04-16 21:46:35
 * @LastEditors: Limer
 * @LastEditTime: 2022-05-03 13:43:11
 * @Description:
 */
#ifndef __THREADPOLL_H__
#define __THREADPOLL_H__
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

class ThreadPool {
   private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex tasks_mtx;
    std::condition_variable cv;
    bool stop;

   public:
    ThreadPool(int size = std::thread::hardware_concurrency());
    ~ThreadPool();
    template <class F, class... Args>
    auto add(F&&, Args&&...)
        -> std::future<typename std::result_of<F(Args...)>::type>;
};
template <class F, class... Args>
auto ThreadPool::add(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;
    // Use smart Pointers to protect task resources
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(tasks_mtx);
        if (stop) throw std::runtime_error("enqueue on stopped ThreadPool");
        tasks.emplace([task]() { (*task)(); });
    }
    cv.notify_one();
    return res;
}

#endif