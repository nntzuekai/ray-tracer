//
// Created by Arche on 2019/11/27.
//

#include "tracer.h"
#include <iostream>


using namespace std;
using namespace nzk;
using namespace glm;


void nzk::tracer::trace(int max_d) {
    this->max_depth=max_d;

    auto dx=img_width/win_width;
    auto dy=img_height/win_height;

    auto x0=-0.5*img_width;
    auto y0=-0.5*img_height;

    vec3 rtv;
    vec3 pix_pos={x0+0.5*dx,y0+0.5*dy,img_plane};

    for(int i=0;i<win_height;++i){
        for(int j=0;j<win_width;++j){
//            if(i==110&&j==300){
//                cerr<<"here"<<endl;
//            }

            auto v=normalize(pix_pos-this->eye);

            rtv=recursive(eye,v,0, nullptr);
            frame[i][j]=rtv;
            pix_pos.x+=dx;
        }
        pix_pos.x=x0;
        pix_pos.y+=dy;
    }
}

vec3 tracer::recursive(vec3 pos, vec3 pv, int depth, const object *from) {
    auto next_obj= object::next_intersection(pos,pv,this->scene,from);

    if(next_obj.first== nullptr){
        return back_color;

//        auto c=dot(normalize(pv),{0,1,0});
//        return {2*c,0,2*sqrt(1-c*c)};
    }

    auto p2=pos+next_obj.second*pv;

    return phong(p2,pv,next_obj.first,depth);
}

vec3 tracer::phong(vec3 pos, vec3 pv, object *obj, int depth) {
    vec3 I=this->Ia*obj->kd(pos);

    vec3 N=normalize(obj->normal_at(pos));
//    vec3 L=normalize(this->light_src-pos);
//    vec3 V=normalize(eye-pos);
    vec3 L=normalize(pos-this->light_src);
    vec3 V=normalize(pos-eye);

    float Si=1;
    if(with_shadow){
        for(const auto &o:scene){
            if(o.get()!=obj&&o->shadowing(pos,this->light_src)){
                Si=0;
                break;
            }
        }
    }

    if(Si!=0){

        auto Id=this->Ii*obj->kd(pos)*std::max(dot(N,-L),0.f);
        I+=Id;

//        vec3 R=2.f*dot(L,N)*N-L;
        vec3 R=reflect(L,N);

        auto Is=this->Ii*(obj->ks()*pow(std::max(dot(R,-V),0.f),obj->q()));
        I+=Is;

    }

    if(this->with_reflect &&depth<max_depth){
//        vec3 V=normalize(pos-eye);
//        auto vr=2.f*dot(V,N)*N-V;
        auto vr=reflect(V,N);
        auto kr=obj->kr();
        if(kr>prec){
            I+=kr*recursive(pos,vr,depth+1,obj);
        }

    }

    if(with_refract&&depth<std::max(max_depth,max_refract)){
        auto r=obj->refracted_ray(pos,pv);
        auto kt=obj->kt();

        if(r.first&&kt>prec){
            I+=kt*recursive(r.second.p0,r.second.pv,depth+1,obj);
        }
    }

    return I;
}

tracer::tracer(vec3 (&frame)[win_height][win_width] , const vector<std::unique_ptr<object>> &scene, const vec3 &backColor,
               const vec3 &defaultColor, const vec3 &eye, const vec3 &lightSrc, const vec3 &ii, const vec3 &ia,
               int maxDepth, bool withShadow, bool withReflect, bool withRefract) : frame(frame), scene(scene),
                                                                                    back_color(backColor),
                                                                                    default_color(defaultColor),
                                                                                    eye(eye), light_src(lightSrc),
                                                                                    Ii(ii), Ia(ia), max_depth(maxDepth),
                                                                                    with_shadow(withShadow),
                                                                                    with_reflect(withReflect),
                                                                                    with_refract(withRefract) {}

