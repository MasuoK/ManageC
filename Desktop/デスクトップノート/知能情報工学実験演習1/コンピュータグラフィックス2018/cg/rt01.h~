//
// rt00.h - [演習0] 用ヘッダファイル
//	作者: (あなたの名前); 日付: (完成した日付)
// [注意] 以降の演習では，上記を適切に書き換えること
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
public:
// メンバ関数
	RTObject(	// コンストラクタ
		const RTPoint& c,	// 中心
		double r		// 半径
	) : cnt(c), rad(r) {}
	bool rayhit(	// 光線 r が物体に交差するか判定し，
			// 交差した場合は交点データを h に入れる
		const RTRay& r,	// 光線データ
		RTHit* h	// 交点データ(返値)
	);
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
	unsigned char intensity(void);	// ピクセルの輝度(0〜255)を返す
// フレンド宣言
	friend bool RTObject::rayhit(const RTRay& r, RTHit* h);
};
