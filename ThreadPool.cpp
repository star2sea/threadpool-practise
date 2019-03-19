#include <iostream>
#include "ThreadPool.h"
#include "Task.h"
using namespace std;

ThreadPool::ThreadPool(int threads_num) : stop_(false){
	for (auto i = 0; i < threads_num; ++i) {
		threads_.emplace_back(
			[this] {
				while (1) {
					Task task;
					{
						unique_lock<mutex> lock(this->mtx_);
						this->cond_.wait(lock, [this] {return this->stop_ || !this->tasks_.empty(); });
						if (this->stop_ && this->tasks_.empty())
							return;
						task = move(this->tasks_.front());
						this->tasks_.pop();
					}
					task.execute();
					{
						std::unique_lock<std::mutex> lock(this->ready_mtx_);
						this->ready_tasks_.emplace(move(task));
						ready_cond_.notify_one();
					}
				}
			}
		);
	}
}

ThreadPool::~ThreadPool() {
	{
		unique_lock<mutex> lock(mtx_);
		stop_ = true;
	}
	this->cond_.notify_all();
	for (auto & t : threads_) {
		t.join();
	}
}

void ThreadPool::addTask(Task &task) {
	unique_lock<mutex> lock(this->mtx_);
	tasks_.emplace(move(task));
	cond_.notify_one();
}

Task ThreadPool::getReadyTask() {
	std::unique_lock<std::mutex> lock(ready_mtx_);
	ready_cond_.wait(lock, [this] {return !this->ready_tasks_.empty(); });
	Task t = move(ready_tasks_.front());
	ready_tasks_.pop();
	return t;
}

