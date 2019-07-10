#include "Mutex.h"

pthread_mutex_t Mutex::mutex;

Mutex::Mutex()
{
}

Mutex::~Mutex()
{
}

bool Mutex::init()
{
	return (pthread_mutex_init(&mutex, NULL) == 0);
}

bool Mutex::lock()
{
	return (pthread_mutex_lock(&mutex) == 0);
}

bool Mutex::unlock()
{
	return (pthread_mutex_unlock(&mutex) == 0);
}

bool Mutex::destroy()
{
	return (pthread_mutex_destroy(&mutex) == 0);
}
