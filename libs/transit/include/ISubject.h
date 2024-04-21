#ifndef ISUBJECT_H_
#define ISUBJECT_H_

#include <string>
#include <vector>
#include "IObserver.h"

class ISubject {
 public:
    /**
     * @brief Deconstruct the ISubject object
    */
    virtual ~ISubject() {}

    /**
     * @brief Notify all observers of the entity
     * 
     * @param message The message to notify the observers with
    */
    virtual void Attach(IObserver* observer) = 0;

    /**
     * @brief Detach an observer from the entity
     * 
     * @param observer The observer to detach
    */
    virtual void Detach(IObserver* observer) = 0;

    /**
     * @brief Notify all observers of the entity
     * 
     * @param message The message to notify the observers with
    */
    virtual void Notify(const std::string& msg) = 0;
 protected:
    std::vector<IObserver*> observers;
};
#endif
