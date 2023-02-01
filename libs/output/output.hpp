#pragma once

#include "../machine.hpp"
#include "../machinevect.hpp"
#include <ostream>

class Output {

    const MachineVect& mvect;

public:
    explicit Output(const MachineVect& mvect_) : mvect(mvect_) { }
    virtual ~Output() = default;

    virtual void write(std::ostream& os, MachinePtrConst m, const MachineVect& mvect) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Output& out);
};
