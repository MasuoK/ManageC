//
// viewmgr.cc - RTViewMgr クラスのメンバ関数の実装
//

#include "rtbase.h"
#include <iostream>
using namespace std;

#define sqr(x) ((x) * (x))

//
// RTViewMgr::RTViewMgr() - コンストラクタ. 各種パラメータの設定を伴う.
//
RTViewMgr::RTViewMgr(const RTPoint& vp, const RTPoint& vrp, double alp, int ds)
{
	for(int i = 0; i < 3; i++) {
		viewp.c[i] = vp.c[i];
		vfvec.c[i] = vrp.c[i] - vp.c[i];
	}
	dotsize = ds;
//
	double dvf = 0;
	for(int i = 0; i < 3; i++)
		dvf += sqr(vfvec.c[i]);
	dvf = sqrt(dvf);
	double unitsize = dvf * tan((alp * M_PI / 180)) / dotsize;
	xunit.c[0] = vfvec.c[1];
	xunit.c[1] = -vfvec.c[0];
	xunit.c[2] = 0;
	xunit.resize(unitsize);
	yunit.c[0] = -vfvec.c[0] * vfvec.c[2];
	yunit.c[1] = -vfvec.c[1] * vfvec.c[2];
	yunit.c[2] = sqr(vfvec.c[0]) + sqr(vfvec.c[1]);
	yunit.resize(unitsize);
}

//
// RTViewMgr::getray() - 視点からピクセル(x,y)への光線を得る
//
void
RTViewMgr::getray(int x, int y, RTRay* ray)
{
	ray->pnt = viewp;
	for(int i = 0; i < 3; i++)
		ray->vec.c[i] = vfvec.c[i]
		 + xunit.c[i] * (x - dotsize + 0.5)
		 + yunit.c[i] * (y - dotsize + 0.5);
	ray->vec.resize();
}

//
// RTViewMgr::prnpgmhdr() - PGM ファイルヘッダを cout に出力
//
void
RTViewMgr::prnpgmhdr(void)
{
	cout << "P5 " << 2 * dotsize << " "  << 2 * dotsize << " 255" << endl;
}

//
// RTViewMgr::prnppmhdr() - PPM ファイルヘッダを cout に出力
//
void
RTViewMgr::prnppmhdr(void)
{
	cout << "P6 " << 2 * dotsize << " "  << 2 * dotsize << " 255" << endl;
}
