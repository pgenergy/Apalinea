//
// Created by SlepiK on 06.06.24.
//

#ifndef STREAM_V1_CORE_EXECUTOR_BOOSTEXECUTOR_HPP
#define STREAM_V1_CORE_EXECUTOR_BOOSTEXECUTOR_HPP

#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>

#include "IExecutor.hpp"
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace Energyleaf::Stream::V1::Core::Executor {
    class BoostExecutor : public IExecutor {
    public:
        explicit BoostExecutor(std::size_t numThreads) : excPool(numThreads), numTasksInProgress(0) {
        }

        ~BoostExecutor() override {
            this->excPool.join();
        }

        void addTask(std::function<void()> task) override {
            std::unique_lock<std::mutex> lock(this->mutex);
            ++this->numTasksInProgress;
            boost::asio::post(this->excPool,[this, task = std::move(task)]() {
                task();
                this->completeTask();
            });
        }

        void joinTasks() override {
            std::unique_lock<std::mutex> lock(this->mutex);
            this->cv.wait(lock, [this]() { return this->numTasksInProgress == 0; });
        }

        void shutdown() override {
            this->excPool.join();
        }
    private:
        boost::asio::thread_pool excPool;
        std::atomic<int> numTasksInProgress;
        std::mutex mutex;
        std::condition_variable cv;

        void completeTask() {
            std::unique_lock<std::mutex> lock(this->mutex);
            if(--this->numTasksInProgress == 0) this->cv.notify_all();
        }

    };
}

#endif //STREAM_V1_CORE_EXECUTOR_BOOSTEXECUTOR_HPP
