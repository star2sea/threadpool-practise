#ifndef __THREADPOOL_H
#define __THREADPOOL_H
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>
#include <mutex>
#include "Task.h"


class ThreadPool{
public:
    ThreadPool(int threads_num);
	~ThreadPool();
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool & operator=(const ThreadPool &) = delete;
    void addTask(Task &);
	Task getReadyTask();
    
private:
    std::vector<std::thread> threads_;
	std::condition_variable cond_;
	std::mutex mtx_;
	std::mutex ready_mtx_;
	std::condition_variable ready_cond_;
	std::queue<Task> tasks_;
	std::queue<Task> ready_tasks_;
	bool stop_;
};

#endif

