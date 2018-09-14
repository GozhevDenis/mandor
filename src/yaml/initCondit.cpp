#include "initCondit.h"
#include "testConstMacros.h"

void setInitCond()
{

    YAML::Node config = YAML::LoadFile( "../config.yaml" );

    for ( unsigned int i = 0 ; i < 3 ; ++i ) {
        min[i]     = config["min"][i].as<int>();
        max[i]     = config["max"][i].as<int>();
        l[i]       = config["L"][i].as<double>();
        cpu_min[i] = config["cpu_min"][i].as<int>();
        cpu_max[i] = config["cpu_max"][i].as<int>();
    }

    dt    = config["dt"].as<double>();
    nStep = config["nStep"].as<int>();

    dx = l[0] / max[0];
    dy = l[1] / max[1];
    dz = l[2] / max[2];

}
