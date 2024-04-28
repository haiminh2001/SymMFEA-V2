#ifndef SYMMFEA_MUTEX_UTILS_H
#define SYMMFEA_MUTEX_UTILS_H
#include <mutex>
namespace MutexUtils
{
    template <typename T>
    class MutexObject
    {
    public:
        T data;
        std::mutex *lock;
        MutexObject(T data) : data(data), lock(new std::mutex()){};
        T get_data()
        {
            lock->lock();
            T result = this->data;
            lock->unlock();
            return result;
        }
        void set_data(T value)
        {
            lock->lock();
            this->data = value;
            lock->unlock();
        }

        MutexObject& operator-=(T other)
        {
            lock->lock();
            this->data = this->data - other;
            lock->unlock();
            return *this;
        }
    };

}
#endif // SYMMFEA_MUTEX_UTILS_H
