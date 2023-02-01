#pragma once

#include "output.hpp"

class OutputIpTables6 : public Output {
    using Output::Output;
    void write(std::ostream& os, MachinePtrConst m, const MachineVect& mvect) const override;
};
