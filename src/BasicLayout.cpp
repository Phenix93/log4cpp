/*
 * BasicLayout.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the LICENSE file for the terms of usage and distribution.
 */

#include <strstream>
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

namespace log4cpp {

    BasicLayout::BasicLayout() {
    }
    
    BasicLayout::~BasicLayout() {
    }

    char* BasicLayout::format(const LoggingEvent& event) {
        ostrstream message;

        const string& priorityName = Priority::getPriorityName(event.priority);
        message << event.timeStamp << " " << priorityName << " " 
                << event.categoryName << " " << event.ndc << ": " 
                << event.message << endl << '\0';

        return message.str();
    }
}
