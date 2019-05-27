//
// vector.cc - RTVec クラスのメンバ関数の実装
//

#include "rtbase.h"

#define sqr(x) ((x) * (x))

//
// RTVec::resize() - 大きさを size に(あるいは単位ベクトルに)する
//
void
RTVec::resize(double size)
{
	double d = 0;
	for(int i = 0; i < 3; i++)
		d += sqr(c[i]);
	d = sqrt(d);
	for(int i = 0; i < 3; i++)
		c[i] = c[i] / d * size;
}

//
// RTVec::dotprod() - this と vec の内積を返す
//
double
RTVec::dotprod(const RTVec& vec)
{
	return (c[0] * vec.c[0] + c[1] * vec.c[1] + c[2] * vec.c[2]);
}
