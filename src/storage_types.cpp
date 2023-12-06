#include "storage_types.hpp"

Package PackageQueue::pop()  {
    Package pack;
    if(package_queue_type_ == PackageQueueType::FIFO){
        pack = std::move(queue_.front());
        queue_.pop_front();
    }
    else if(package_queue_type_ == PackageQueueType::LIFO){
        pack = std::move(queue_.back());
        queue_.pop_back();
    }
    return pack;
}
