//
// Created by Arche on 2019/11/27.
//

#ifndef PROJECT3_TRACER_H
#define PROJECT3_TRACER_H

#include "primitive.h"

namespace nzk{
    struct tracer{
        vec3 (&frame)[win_height][win_width];
        const std::vector<std::unique_ptr<object>> &scene;

        vec3 back_color;
        vec3 default_color;
        vec3 eye;

        vec3 light_src;
        vec3 Ii;
        vec3 Ia;

        int max_depth;
        bool with_shadow;
        bool with_reflect;
        bool with_refract;

        tracer(vec3 (&frame)[win_height][win_width] , const std::vector<std::unique_ptr<object>> &scene, const vec3 &backColor,
               const vec3 &defaultColor, const vec3 &eye, const vec3 &lightSrc, const vec3 &ii, const vec3 &ia,
               int maxDepth, bool withShadow, bool withReflect, bool withRefract);

        vec3 recursive(vec3 pos, vec3 pv,int depth, const object *from);
        vec3 phong(vec3 pos, vec3 pv, object *obj, int depth);

        void trace(int max_d);
    };

}

#endif //PROJECT3_TRACER_H
