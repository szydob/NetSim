#ifndef LAB6_REPORTS_HPP
#define LAB6_REPORTS_HPP

#include "factory.hpp"

void generate_structure_report(const Factory& f, std::ostream& os);
void generate_simulation_turn_report(const Factory& f, std::ostream& os, Time t);

#endif //LAB6_REPORTS_HPP


