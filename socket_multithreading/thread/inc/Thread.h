#ifndef THREAD_H_
#define THREAD_H_

#include <stdio.h>
#include <pthread.h>

typedef void *(function_task_t)(void *arg);

class Thread
{
private:
	pthread_t task;
	void *retval;

public:
	Thread();
	~Thread();

	bool create(function_task_t fn_task_t, void *arg);
	bool join();
	bool wasCanceled();
	void *getRetval();
};

#endif
