#include "Task.h"


Task::Task(Task && t) noexcept :result_(t.result_), done_(t.done_), func_(move(t.func_)){

}

Task & Task::operator=(Task &&rhs) noexcept {
	if (this != &rhs) {
		result_ = rhs.result_;
		done_ = rhs.done_;
		func_ = move(rhs.func_);
	}
	return *this;
}

void Task::execute() {
	result_ = func_();
	done_ = true;
}