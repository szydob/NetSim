#pragma once

#include <set>
#include "types.hpp"

class Package {
public:
    Package();

    explicit Package(ElementID ID) : ID_(ID) {assigned_IDs.insert(ID_);}

    Package(Package &&pack)  noexcept : ID_(pack.ID_) {}

    Package &operator=(Package &&pack) noexcept;

    ElementID get_id() const {return ID_;}

    ~Package();

private:
    ElementID ID_;
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
};