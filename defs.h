//
// Created by Arche on 2019/11/26.
//

#ifndef PROJECT3_DEFS_H
#define PROJECT3_DEFS_H

#include "glm/glm.hpp"


namespace nzk{
    constexpr float prec=1e-7;

    constexpr float plane_kr=0.3;
    constexpr float plane_kt=0;
    constexpr glm::vec3 plane_ks={};
    constexpr float plane_q=35;

    constexpr glm::vec3 plane_grey={0.2,0.2,0.2};
    constexpr glm::vec3 plane_white={0.75, 0.75, 0.75};

    constexpr int win_width=800;
    constexpr int win_height=800;
    constexpr float img_plane=-1.5;
    constexpr float img_width=2;
    constexpr float img_height=2;
    constexpr int max_refract=4;

}

#endif //PROJECT3_DEFS_H
