#include "Debug.h"
#include "Thread.h"

Thread::Thread()
{
	this->task = (long unsigned int) 0;
	this->retval = nullptr;
}

Thread::~Thread()
{
}

// Create a simple thread.
bool Thread::create(function_task_t fn_task_t, void *arg)
{
	int ret;

	if(fn_task_t == nullptr)
	{
		Debug::print(Debug::CL_RED, "%s: callback not defined\n", __FUNCTION__);
		return false;
	}

	ret = pthread_create(&this->task, NULL, fn_task_t, arg);
	if(ret)
	{
		Debug::print(Debug::CL_RED, "%s: pthread_create error\n", __FUNCTION__);
		return false;
	}

	return true;
}

// Waits for thread end.
bool Thread::join()
{
	int ret;

	ret = pthread_join(this->task, &this->retval);
	if(ret)
	{
		Debug::print(Debug::CL_RED, "%s: pthread_join error\n", __FUNCTION__);
		return false;
	}

	return true;
}

// Check if the thread was canceled.
bool Thread::wasCanceled()
{
	return (this->retval == PTHREAD_CANCELED);
}

// Get thread return value.
void *Thread::getRetval()
{
	return this->retval;
}
