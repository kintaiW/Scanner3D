#include "KKLock.h"

using namespace csc;
Mutex::Mutex()
{
  pthread_mutex_init(&this->t_mutex,NULL);
}

Mutex::~Mutex()
{
  pthread_mutex_destroy(&this->t_mutex);
}

void Mutex::lock()
{
  pthread_mutex_lock(&this->t_mutex);
}

void Mutex::unlock()
{
  pthread_mutex_unlock(&this->t_mutex);
}

Lock::Lock(Mutex &mutex): m_mutex(mutex), m_locked(true)
{
  m_mutex.lock();

}

Lock::~Lock()
{
  m_mutex.unlock();
}

void Lock::setUnlock()
{
  m_locked = false;
}

Lock::operator bool() const
{
  return m_locked;
}
