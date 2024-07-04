/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "JobSystem.h"

JobHandle::JobHandle(std::vector<std::future<void>>&& futures)
    : m_futures(std::move(futures)), m_progress(0) {}

bool JobHandle::isDone() const {
    for (const auto& future : m_futures) {
        if (future.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
            return false;
        }
    }
    return true;
}

void JobHandle::wait() {
    for (auto& future : m_futures) {
        future.wait();
    }
}

void JobHandle::setProgress(float progress) {
    m_progress = progress;
}

float JobHandle::getProgress() const {
    return m_progress;
}

JobSystem::JobSystem(size_t numThreads) : m_stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        m_workers.emplace_back([this] {
            while (true) {
                std::function<void()> job;
                {
                    std::unique_lock<std::mutex> lock(m_queueMutex);
                    m_condition.wait(lock, [this] { return m_stop || !m_jobs.empty(); });
                    if (m_stop && m_jobs.empty()) return;
                    job = std::move(m_jobs.front());
                    m_jobs.pop();
                }
                job();
            }
            });
    }
}

JobSystem::~JobSystem() {
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_stop = true;
    }
    m_condition.notify_all();
    for (std::thread& worker : m_workers) {
        worker.join();
    }
}

JobHandle JobSystem::createJob(std::function<Generator<float>(JobHandle&)> job) {
    std::packaged_task<void()> task([job = std::move(job), this] {
        JobHandle handle({});
        auto gen = job(handle);
        while (gen.move_next()) {
            handle.setProgress(gen.current_value());
        }
        });
    std::future<void> future = task.get_future();
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_jobs.emplace([task = std::move(task)]() mutable { task(); });
    }
    m_condition.notify_one();
    return JobHandle({ std::move(future) });
}

JobHandle JobSystem::createLoopJob(std::function<Generator<float>(int, JobHandle&)> job, int start, int end) {
    int numThreads = m_workers.size();
    int range = end - start;
    int chunkSize = (range + numThreads - 1) / numThreads;

    std::vector<std::future<void>> futures;
    for (int i = 0; i < numThreads; ++i) {
        int chunkStart = start + i * chunkSize;
        int chunkEnd = std::min(chunkStart + chunkSize, end);
        if (chunkStart >= chunkEnd) break;

        std::packaged_task<void()> task([=, this] {
            JobHandle handle({});
            for (int j = chunkStart; j < chunkEnd; ++j) {
                auto gen = job(j, handle);
                while (gen.move_next()) {
                    handle.setProgress(gen.current_value());
                }
            }
            });
        futures.push_back(task.get_future());
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_jobs.emplace([task = std::move(task)]() mutable { task(); });
        }
        m_condition.notify_one();
    }
    return JobHandle(std::move(futures));
}
