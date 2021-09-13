//
// Created by z on 9/13/21.
//

#ifndef INN_REQ_PARSE_SERVICE_H
#define INN_REQ_PARSE_SERVICE_H

#include <string>
#include "server/model/define.h"

namespace Inn{
    class ReqParseService {
    public:
        static int Core(std::string &str);
    };
}



#endif //INN_REQ_PARSE_SERVICE_H
