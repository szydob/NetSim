//
// Created by Michał on 06.12.2023.
//

#include "nodes.hpp"

void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    double num_of_receivers_begin = double(preferences_.size());
    if (num_of_receivers_begin == 0) {
        preferences_[r] = 1.0;
    } else {
        for (auto &rec: preferences_) {
            rec.second = 1 / (num_of_receiversbegin + 1);
        }
        preferences[r] = 1 / (num_of_receivers_begin + 1);
    }
}