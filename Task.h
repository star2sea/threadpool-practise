#ifndef __TASK_H
#define __TASK_H
#include <functional>

class Task {
public:
	typedef std::function<int()> FUNC;
	Task() = default;
	Task(FUNC func) :done_(false), func_(move(func)) {}
	Task(Task &&) noexcept;
	Task & operator=(Task &&rhs) noexcept;
	void execute();
	int get_result() { return result_; }
private:
	int result_;
	bool done_;
	FUNC func_;
};


#endif