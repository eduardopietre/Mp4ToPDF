#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>


template <typename T> class TQueue {
public:
	void push(const T& item);
	void push(T&& item);
	void pop(T& item);
	T pop();
    void setSize(long size);
    long getSize();


private:
	std::queue<T> _queue;
	std::mutex _mutexQueue;
	std::condition_variable _conditionQueue;

    bool _definedSize = false;
    long _size;
    std::mutex _mutexSize;
    std::condition_variable _conditionSize;
};

template<typename T> inline void TQueue<T>::setSize(long size) {
    std::unique_lock<std::mutex> lock(_mutexSize);
    _size = size;
    _definedSize = true;
    _conditionSize.notify_all();
}

template<typename T> inline long TQueue<T>::getSize() {
    std::unique_lock<std::mutex> lock(_mutexSize);
    while (!_definedSize) {
        _conditionSize.wait(lock);
    }
    return _size;
}

template<typename T> inline void TQueue<T>::push(const T& item) {
    std::unique_lock<std::mutex> lock(_mutexQueue);
    _queue.push(item);
    lock.unlock();
    _conditionQueue.notify_one();
}

template<typename T> inline void TQueue<T>::push(T&& item) {
    std::unique_lock<std::mutex> lock(_mutexQueue);
    _queue.push(std::move(item));
    lock.unlock();
    _conditionQueue.notify_one();
}

template<typename T> inline void TQueue<T>::pop(T& item) {
    std::unique_lock<std::mutex> lock(_mutexQueue);
    while (_queue.empty()) {
        _conditionQueue.wait(lock);
    }
    item = _queue.front();
    _queue.pop();
}

template<typename T> inline T TQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(_mutexQueue);
    while (_queue.empty())
    {
        _conditionQueue.wait(lock);
    }
    T item = _queue.front();
    _queue.pop();
    return item;
}
