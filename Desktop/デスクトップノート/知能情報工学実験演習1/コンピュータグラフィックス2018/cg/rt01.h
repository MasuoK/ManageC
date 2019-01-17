//
// rt01.h - [演習1] 用ヘッダファイル
//	作者: (国益良太); 日付: (完成した日付)
//
//

using namespace std;

#include "rtbase.h"

class RTHit;		// Hit(交点) クラスの(事前の)宣言

//
// 物体(球) クラス
//
class RTObject {
private:
// メンバ変数
	RTPoint cnt;	// 球の中心
	double rad;	// 球の半径
	double kd;      // 拡散反射率
public:
// メンバ関数
	RTObject(	// コンストラクタ
		 const RTPoint& c,	// 中心
		 double r,		// 半径
		double k                // 反射率
			) : cnt(c), rad(r), kd(k) {}
	bool rayhit(	// 光線 r が物体に交差するか判定し，
			// 交差した場合は交点データを h に入れる
		    const RTRay& r,	// 光線データ
		    RTHit* h	// 交点データ(返値)
			);
	double g_kd(void){return kd; }
};
//無限遠点光源のクラス

class RTLSrc {
 private:
  //メンバ変数
  RTVec dir; //光源の方向
  double it; //光源（入射光）の強さ
 public:
  //メンバ関数
  RTLSrc( //コンストラクタ
	 const RTVec& d, // 光源の方向
	 double i  //光源（入射光）の強さ
	  ): dir(d), it(i) {dir.resize(); }
  const RTVec& g_dir(void) const {return dir; }//dirのアクセサ
  double g_it(void) const {return it; } //itのアクセサ
};


//
// Hit(交点) クラス
//
class RTHit {
private:
// メンバ変数
	double t;	// 交点での光線のパラメータ値
	RTObject* obj;	// 光線が交差した物体
	RTVec nor;	// 交点での単位法線ベクトル
	RTRay ref;	// 交点からの反射光線 (交点自身は ref.pnt)
public:
// メンバ関数
	unsigned char intensity(const RTLSrc& ls);	// ピクセルの輝度(0〜255)を返す
// フレンド宣言
	friend bool RTObject::rayhit(const RTRay& r, RTHit* h);
};
