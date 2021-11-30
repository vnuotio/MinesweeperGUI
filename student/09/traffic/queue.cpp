#include "queue.hh"
#include <iostream>

using namespace std;
// Implement the member functions of Queue here
Queue::Queue(unsigned int cycle): cycle_(cycle)
{

}

Queue::~Queue()
{

}

void Queue::enqueue(const string &reg)
{
    Vehicle* new_vehicle = new Vehicle{reg, nullptr};
    if (first_ == nullptr and last_ == nullptr)
    {
        first_ = new_vehicle;
        last_ = new_vehicle;
    }
    else
    {
        last_->next = new_vehicle;
        last_ = new_vehicle;
    }

    if (is_green_)
    {
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
    }
}

void Queue::switch_light()
{
    is_green_ = not is_green_;

    print();
    if (is_green_ and first_ != nullptr)
    {
        unsigned int p = 0;
        bool succ = true;
        while (succ and p  < cycle_)
        {
            succ = dequeue();
            p++;
        }
        is_green_ = false;
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print() const
{
    string light = (is_green_)? "GREEN: " : "RED: ";
    cout << light;
    if (first_ == nullptr)
    {
        cout << "No vehicles waiting in traffic lights" << endl;
        return;
    }

    cout << "Vehicle(s) ";

    Vehicle* veh = first_;

    if (not is_green_)
    {
        while (veh != nullptr)
        {
            cout << veh->reg_num << " ";
            veh = veh->next;
        }
        cout << "waiting in traffic lights" << endl;
    }
    else
    {
        unsigned int p = 0;
        while (veh != nullptr and p < cycle_)
        {
            cout << veh->reg_num << " ";
            veh = veh->next;
            p++;
        }
        cout << "can go on" << endl;
    }
}

bool Queue::dequeue()
{
    Vehicle* veh = first_;
    if (veh == nullptr)
    {
        return false;
    }
    else
    {
        first_ = veh->next;
        delete veh;
        return true;
    }
}
