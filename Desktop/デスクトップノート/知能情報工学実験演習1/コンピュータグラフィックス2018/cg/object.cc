//
// object.cc - RTObject クラスのメンバ関数の実装
//

#include "rtcurrent.h"

#define sqr(x) ((x) * (x))

//
// RTObject::rayhit() - 光線 r が物体に交差するか判定し，
//                      交差した場合は交点データを h に入れる
//
bool
RTObject::rayhit(const RTRay& r, RTHit* h)
{
	RTVec v;

	for(int i = 0; i < 3; i++)
		v.c[i] = cnt.c[i] - r.pnt.c[i];
	double b = v.dotprod(r.vec);
	double c = v.dotprod(v) - sqr(rad);
//
// solve t^2 - 2 * b * t  + c = 0
//
	double d;

	if((d = sqr(b) - c) >= 0 && (h->t = b - sqrt(d)) > 0) {
		for(int i = 0; i < 3; i++) {
			h->ref.pnt.c[i] = r.pnt.c[i] + h->t * r.vec.c[i];
			h->nor.c[i] = (h->t * r.vec.c[i] - v.c[i]) / rad;
		}
		double k = 2 * h->nor.dotprod(r.vec);
		for(int i = 0; i < 3; i++)
			h->ref.vec.c[i] = r.vec.c[i] - k * h->nor.c[i];
		h->obj = this;
		return true;
	}
	else
		return false;
}
