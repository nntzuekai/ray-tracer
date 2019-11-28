//
// Created by Arche on 2019/11/26.
//

#include "primitive.h"
#include <limits>

using namespace std;
using namespace nzk;
using namespace glm;

std::pair<nzk::object *,float>
nzk::object::next_intersection(glm::vec3 pos, glm::vec3 v, const std::vector<std::unique_ptr<object>> &objs, const object *from) {
    object *ptr= nullptr;
    float min_dis=numeric_limits<float>::infinity();
    ray r={pos,v};

    for(const auto &o:objs){
        if(o.get()==from){
            continue;
        }

        auto dis=o->intersection(r,true);
        if(dis>0&&dis<min_dis){
            ptr=o.get();
            min_dis=dis;
        }
    }

    return {ptr,min_dis};

}

bool object::shadowing(vec3 pos, vec3 light_src) {
    return intersection({pos,normalize(light_src-pos)},true)>0;
}

float sphere::intersection(const ray &r,bool near) {
    const auto &p0=r.p0;
    const auto &pv=r.pv;

    auto A=dot(pv,pv);
    auto Q= p0 - this->center;
    auto B=2*dot(pv, Q);
    auto C= dot(Q, Q) - this->radius * this->radius;

    auto delta=B*B-4*A*C;

    if(delta<prec){
        return -1;
    }

    auto x1=(-B+sqrt(delta))/(2*A);
    auto x2=(-B-sqrt(delta))/(2*A);

    if(x1<0){
        return -1;
    }
    else if(x2<0){
        return x1;
    }
    else{
        if(near){
            return x2;
        }
        else{
            return x1;
        }
    }


}

vec3 sphere::normal_at(vec3 p)const {
    return normalize(p-this->center);
}

float sphere::kr() {
    return this->_kr;
}

float sphere::kt() {
    return this->_kt;
}

vec3 sphere::kd(const vec3 &p) {
    return this->_kd;
}

vec3 sphere::ks() {
    return this->_ks;
}

float sphere::q() {
    return this->_q;
}

pair<bool, ray> sphere::refracted_ray(vec3 pos, vec3 v) {
    auto N=normal_at(pos);
    float ri=1.f/this->refr_idx;

//    if(dot(v,N)>0){
//        ri=1.f/this->refr_idx;
//    }
//    else{
//        ri=this->refr_idx;
//        N=-N;
//    }

    auto refra=refract(normalize(v),N,ri);
    if(refra==vec3{0,0,0}){
        return {false,{}};
    }

    auto t2=intersection({pos,refra},false);
    if(t2<prec){
        return {false,{}};
    }

    auto p2=pos+t2*refra;
    auto N2=normal_at(p2);
    auto r2=refract(normalize(refra),-N2,this->refr_idx);

    if(r2==vec3{0,0,0}){
        return {false,{}};
    }

    return {true,{p2,r2}};

}

sphere::sphere(float kr, float kt, const vec3 &kd, const vec3 &ks, float q, const vec3 &center, float radius,
               float refrIdx) : _kr(kr), _kt(kt), _kd(kd), _ks(ks), _q(q), center(center), radius(radius),
                                refr_idx(refrIdx) {}

float plane::intersection(const ray &r, bool near) {
    auto t1=dot(this->normal,r.pv);

    if(t1==0){
        return -1;
    }

    auto t2=dot(this->normal,center-r.p0)/t1;

    if(t2<prec){
        return  -1;
    }

    auto p2=r.p0+t2*r.pv;

    auto d=p2-this->center;
    if(fabs(d.x)>this->length||fabs(d.z)>this->length){
        return -1;
    }

    return t2;
}

float plane::kr() {
    return plane_kr;
}

float plane::kt() {
    return plane_kt;
}

vec3 plane::kd(const vec3 &p) {
//    return {1,1,1};

    int dx=round(p.x-center.x-length);
    int dz=round(p.z-center.z-length);

    if((dx+dz)%2!=0){
        return plane_grey;
    }
    else{
        return plane_white;
    }

}

vec3 plane::ks() {
    return plane_ks;
}

float plane::q() {
    return plane_q;
}

vec3 plane::normal_at(vec3 p) const{
    return this->normal;
}

pair<bool, ray> plane::refracted_ray(vec3 pos, vec3 v) {
    return {false,{}};
}

plane::plane(const vec3 &center, const vec3 &normal, float length) : center(center), normal(normalize(normal)), length(length) {}
