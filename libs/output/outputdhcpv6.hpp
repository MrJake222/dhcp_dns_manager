#pragma once

#include "output.hpp"

class OutputDHCPv6 : public Output {
    using Output::Output;
    void write(std::ostream& os, MachinePtrConst m, const MachineVect& mvect) const override;
};
