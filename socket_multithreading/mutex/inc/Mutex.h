#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

class Mutex
{
private:
	static pthread_mutex_t mutex;

	Mutex();
	~Mutex();

public:
	static bool init();
	static bool lock();
	static bool unlock();
	static bool destroy();
};

#endif
