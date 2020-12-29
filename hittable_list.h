#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list: public hittable {
public:
    hittable_list(){}
    hittable_list(shared_ptr<hittable> object){add(object);}

    void clear() {objects.clear();}
    void add(shared_ptr<hittable> object){objects.push_back(object);}

    virtual bool hit(
        const ray& r, float t_min, float t_max, hit_record& rec
    )   const;

public:
    std::vector<shared_ptr<hittable>> objects;
};

bool hittable_list::hit(
    const ray& r, float t_min, float t_max, hit_record& rec
)   const {
    hit_record tmp_rec; //  退避用のhit_record構造体
    bool hit_anything = false;  //  初期値はどの物体とも衝突していない
    auto closest_so_far = t_max;

    for (const auto& object : objects){
        if(object->hit(r, t_min, closest_so_far, tmp_rec)){ //  これまでに衝突したものより近い位置で衝突する物体があったら...
            hit_anything = true;    //  少なくとも1回は衝突している
            closest_so_far = tmp_rec.t; //  再近衝突位置を更新
            rec = tmp_rec;  //  衝突履歴も更新
        }
    }
    return hit_anything;
}
#endif //HITTABLE_LIST_H
