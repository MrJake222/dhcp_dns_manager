#pragma once

#include "output.hpp"

class OutputNftables : public Output {
    using Output::Output;
    void write(std::ostream& os, MachinePtrConst m, const MachineVect& mvect) const override;
};
