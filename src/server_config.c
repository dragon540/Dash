//
// Created by shobhit on 21/4/24.
//

#include "server_config.h"
#include "page_map.h"

void URLMappingConfig() {
    /**temporary config*/
    mapNewURL("/", "../DashServer/resource/index.html");
    mapNewURL("/ex1", "../DashServer/resource/index.html");
    mapNewURL("/new", "../DashServer/resource/example1.html");
    mapNewURL("/dragon", "../DashServer/resource/example1.html");
    mapNewURL("/strawberry", "../DashServer/resource/example1.html");

    // find some way of using xml file to map url and filepath during runtime, so re-compilation
    // is not needed
}
