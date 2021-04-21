//
// Created by Tommy Pujol 4/21/21.
//

#ifndef BANK_SIM_ELAPSED_TIME_H
#define BANK_SIM_ELAPSED_TIME_H

#include "common.h"

struct TimeElapsed {
    int years;
    int months;
    int days;
    int hours;
    int minutes;
    int seconds;
    int microseconds;
};

namespace Time {
    TimeElapsed none() {
        return TimeElapsed{
                0, 0, 0, 0, 0, 0, 0
        };
    }

    std::string human_time(TimeElapsed& t) {
        return boost::str(boost::format("%d/%d/%d-%d:%d:%d%d%d") % t.years % t.months % t.days % t.hours %
                          t.minutes % t.seconds % t.microseconds);
    }
}

#endif //BANK_SIM_ELAPSED_TIME_H