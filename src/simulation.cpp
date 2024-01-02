//
// Created by Michał on 06.12.2023.
//

#include "simulation.hpp"

void simulate(Factory& f, TimeOffset d, std::function<void (Factory&, Time)> rf) {
    Time turn = 1;

    while (turn <= d){
        f.do_deliveries(turn);
        f.do_package_passing();
        f.do_work(turn);
        rf(f,turn);
        turn++;
    }
}

//bool IntervalReportNotifier::should_generate_report(Time t) {
//    if (to_ != 1) {
//        return t % to_ == 1;
//    } else {
//        return true;
//    }
//}