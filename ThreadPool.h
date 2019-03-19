#ifndef __THREADPOOL_H
#define __THREADPOOL_H
#include <thread>
#include <vector>

class Task;

class ThreadPool{
public:
    ThreadPool(int n);
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool & operator=(const ThreadPool &) = delete;
    void addTask(Task &);
    void start();
    void stop();
    
private:
    std::vector<std::thread> threads_;
    
    
    
};

#endif

