//
// Created by Arche on 2019/11/26.
//

#ifndef PROJECT3_PRIMITIVE_H
#define PROJECT3_PRIMITIVE_H

#include "glm/glm.hpp"
#include <vector>
#include <memory>
#include <utility>
#include <tuple>
#include "defs.h"

namespace nzk{
    using glm::vec3;
//    using RGB=vec3;
    struct ray{
        vec3 p0;
        vec3 pv;
    };

    struct object{
        virtual ~object()= default;
        virtual float intersection(const ray &r, bool near)=0;
        virtual float kr()=0;
        virtual float kt()=0;
        virtual vec3 kd(const vec3 &p)=0;
        virtual vec3 ks()=0;
        virtual float q()=0;
//        virtual vec3 Ir()=0;
//        virtual vec3 It()=0;

        bool shadowing(vec3 pos,vec3 light_src);
        virtual vec3 normal_at(vec3 p)const =0;
        virtual std::pair<bool, ray> refracted_ray(vec3 pos, vec3 v)=0;

        static std::pair<object *,float> next_intersection(vec3 pos, vec3 v, const std::vector<std::unique_ptr<object>> &objs, const object *from);
    };

    struct sphere:public object{
        float _kr;
        float _kt;
        vec3 _kd;
        vec3 _ks;
        float _q;


        vec3 center;
        float radius;
        float refr_idx;

        sphere(float kr, float kt, const vec3 &kd, const vec3 &ks, float q, const vec3 &center, float radius,
               float refrIdx);

        float kr() override;

        float kt() override;

        vec3 kd(const vec3 &p) override;

        vec3 ks() override;

        float q() override;

        ~sphere() override= default;

        std::pair<bool, ray> refracted_ray(vec3 pos, vec3 v) override;

        vec3 normal_at(vec3 p)const override;
        float intersection(const ray &r, bool near) override;
    };

    struct plane:public object{
        vec3 center;
        vec3 normal;
        float length;

        plane(const vec3 &center, const vec3 &normal, float length);

        ~plane() override = default;

        float intersection(const ray &r, bool near) override;

        float kr() override;

        float kt() override;

        vec3 kd(const vec3 &p) override;

        vec3 ks() override;

        float q() override;

        vec3 normal_at(vec3 p)const override;

        std::pair<bool, ray> refracted_ray(vec3 pos, vec3 v) override;

    };

}

#endif //PROJECT3_PRIMITIVE_H
