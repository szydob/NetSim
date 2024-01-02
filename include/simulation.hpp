//
// Created by Michał on 06.12.2023.
//

#ifndef LAB6_SIMULATION_HPP
#define LAB6_SIMULATION_HPP

#include "factory.hpp"

void simulate(Factory& f, TimeOffset d, std::function<void (Factory&, Time)> rf);

class IntervalReportNotifier {
public:
    IntervalReportNotifier(TimeOffset to) : to_(to) {}
    bool should_generate_report(Time t) { return  to_ != 1 ? t % to_ == 1 : true; }
private:
    TimeOffset to_;
};

class SpecificTurnsReportNotifier {
public:
    SpecificTurnsReportNotifier(std::set<Time> turns) : turns_(turns) {}
    bool should_generate_report(Time t) { return turns_.find(t) != turns_.end(); }
private:
    std::set<Time> turns_;
};
#endif //LAB6_SIMULATION_HPP
