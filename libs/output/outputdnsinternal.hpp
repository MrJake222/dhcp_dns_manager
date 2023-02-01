#pragma once

#include "output.hpp"
#include "../machine.hpp"

class OutputDNSInternal : public Output {
    using Output::Output;
    void write(std::ostream& os, MachinePtrConst m, const MachineVect& mvect) const override;
};
