//
//  StratumResponse.hpp
//  stratum client
//
//  Created by landan on 7/13/17.
//  Copyright © 2017 landsv. All rights reserved.
//

#include <json/json.h>

struct StratumRequestObject {
};

struct StratumResponseObject {
    int id;
    Json::Value params;
};
