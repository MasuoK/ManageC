//
// rtbase.h - 実験演習I(CG)用ヘッダファイル(すべての演習に共通な部分)
//

#include <stdio.h>
#include <math.h>

//
// Point/Vector クラス
//
typedef class RTVec {
public:
// メンバ変数
	double c[3];	// 座標値
// メンバ関数
	void resize(	// 大きさを size (省略時は 1)にする
		double size = 1.0	// ベクトルの大きさ
	);
	double dotprod(	// this と vec の内積を返す
		const RTVec& vec	// 相手のベクトル
	);
} RTPoint;

//
// Ray クラス
//
class RTRay {
public:
// メンバ変数
	RTPoint pnt;	// 起点
	RTVec vec;	// 単位方向ベクトル
};

//
// ViewMgr(ビュー管理) クラス
//
class RTViewMgr {
private:
// メンバ変数
	RTPoint viewp;	// 視点
	RTVec vfvec;	// 視点から参照視点へのベクトル
			// [注意] vf = (0,0,k) は許されない
	double dotsize;	// 縦横のピクセル数の半分 (画像は正方形)
	RTVec xunit;	// 視平面上で x 軸方向 1 ピクセル分のベクトル
	RTVec yunit;	// 視平面上で y 軸方向 1 ピクセル分のベクトル
public:
// メンバ関数
	RTViewMgr(		// コンストラクタ
		const RTPoint& vp,	// 視点
		const RTPoint& vrp,	// 参照視点
		double alp,	// 縦横方向の視野角の半分(単位は度)
		int ds		// 縦横ピクセル数の半分(画面は正方形)
	);
	void getray(	// 視点からピクセル(x,y)への光線を得る
		int x, int y,	// ピクセルの(x,y)座標
		RTRay* ray	// 視点からピクセルへの光線(返値)
	);
	void prnpgmhdr(void);	// PGM ファイルヘッダを cout に出力
	void prnppmhdr(void);	// PPM ファイルヘッダを cout に出力
};
