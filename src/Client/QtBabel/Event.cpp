#include "Event.hpp"

Event::Event(const EventType &type)
    : _eventType(type)
{}

const Event::EventType				&Event::getType() const
{
    return _eventType;
}


void                                            Event::addData(const std::string &id,
                                                               const std::string &data)
{
    this->_data.emplace(id, data);
}

const std::string				&Event::getData(const std::string &id) const
{
    return this->_data.at(id);
}

const std::map<std::string, std::string>	&Event::getAllData() const
{
    return this->_data;
}
