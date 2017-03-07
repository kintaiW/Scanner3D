#ifndef _KKLOCK_H
#define _KKLOCK_H

#include <pthread.h>

#define synchronized(M) for(csc::Lock M##_lock = M; M##_lock; M##_lock.setUnlock())

namespace csc
{
class Mutex
{
public:
  Mutex();
  ~Mutex();

  void lock();
  void unlock();
private:
  pthread_mutex_t t_mutex;
};

class Lock
{
public:
  Lock(Mutex &mutex);
  ~Lock();
  void setUnlock();
  operator bool () const;
private:
  Mutex &m_mutex;
  bool m_locked;
};
}
#endif
