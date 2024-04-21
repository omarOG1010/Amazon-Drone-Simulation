#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include <string>

/**
 * @brief Observer interface for the observer pattern.
*/
class IObserver {
 public:
    /**
     * @brief Deconstruct the IObserver object
    */
    virtual ~IObserver(){};
    /**
     * @brief Update the observer with a message
     * 
     * @param message The message to update the observer with
    */
    virtual void updateMsg(const std::string &message) = 0;
};
#endif