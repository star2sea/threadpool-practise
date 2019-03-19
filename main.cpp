#include <iostream>
#include "Task.h"
#include "ThreadPool.h"
using namespace std;

int func(int v) {
	return v * v;
}

int main(){
	ThreadPool pool(20);

	for (auto i = 0; i < 20; ++i) {
		Task task(bind(func, i));
		pool.addTask(task);
	}

	for (auto i = 0; i < 20; ++i) {
		Task t = move(pool.getReadyTask());
		cout << t.get_result() << endl;
	}
	return 0;
}
