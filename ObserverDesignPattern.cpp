/*
 * Observer Design Pattern (Implemented In C++)
 * Author: Sandeep Singh [github.com/sandeepsinghmails]
 * 2018
 *
 * Source code is licensed under GNU GPLv3
 * (for more details see LICENSE)
 *
 */
 
#include <iostream>
#include <vector>

class AbstractObserver;

class AbstractSubject
{
public:
    void addObserver (AbstractObserver* newObserver)
    {
        observerList.push_back(newObserver);
    }

    void removeObserver (int index)
    {
        observerList.erase(observerList.begin() + index);
    }

    void notifyObservers ();

    // Interface
    virtual std::string  getSubjectState () = 0;
    virtual void setSubjectState (std::string state) = 0;

private:
  std::vector <AbstractObserver*> observerList;
};

class ConcreteSubject : public AbstractSubject
{
public:
    std::string getSubjectState()
    {
        return subject_state;
    }

    void setSubjectState(std::string s)
    {
        subject_state = s;
    }

private:
    std::string subject_state;
};



class AbstractObserver
{
public:
    // Interface
    virtual std::string getObserverState() = 0;
    virtual void updateObserverState (AbstractSubject* subject) = 0;
};

class ConcreteObserver : public AbstractObserver
{
public:
    ConcreteObserver(std::string state) : observer_state(state) {}

    std::string getObserverState()
    {
        return observer_state;
    }

    void updateObserverState (AbstractSubject* subject)
    {
        observer_state = subject->getSubjectState();
        std::cout << "UPDATED OBSERVER'S STATE" << std::endl;
    }

private:
  std::string observer_state;
};

void AbstractSubject::notifyObservers()
{
    for (unsigned int i = 0; i < observerList.size(); i++)
    {
      // Pass On Subject's State To Observers
      observerList[i]->updateObserverState(this);
    }
}

// A Test Drive Application which loves frequent updates :)
void turbulent ()
{
    ConcreteObserver observer1("INITIALIZE-1");
    ConcreteObserver observer2("INITIALIZE-2");

    std::cout << "STATE OF OBSERVER1: " << observer1.getObserverState() << std::endl;
    std::cout << "STATE OF OBSERVER2: " << observer2.getObserverState() << std::endl;

    AbstractSubject* subject = new ConcreteSubject;
    subject->addObserver(&observer1);
    subject->addObserver(&observer2);

    subject->setSubjectState("HAPPY");
    subject->notifyObservers();

    std::cout << "STATE OF OBSERVER1: " << observer1.getObserverState() << std::endl;
    std::cout << "STATE OF OBSERVER2: " << observer2.getObserverState() << std::endl;
    std::cout << std::endl;

    subject->removeObserver(1);
    subject->setSubjectState("SURPRISED");
    subject->notifyObservers();

    std::cout << "STATE OF OBSERVER1: " << observer1.getObserverState() << std::endl;
    std::cout << "STATE OF OBSERVER2: " << observer2.getObserverState() << std::endl;
}



int main()
{
  // Driver Function
  turbulent ();

  return 0;
}
