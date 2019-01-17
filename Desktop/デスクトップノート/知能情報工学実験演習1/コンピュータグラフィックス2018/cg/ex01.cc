//
// ex01.cc - [演習1] プログラムファイル
//	作者: 国益良太; 日付: 1/17
// 
//

#include "rt01.h"
#include <iostream>
using namespace std;

//
// RTHit::intensity() - ピクセルの輝度(0〜255)を返す
//
unsigned char
RTHit::intensity(const RTLSrc& ls)
{
  //kd: 0.0~1,0 i:0~255  cos: 0.0~1.0
  double kd,i,cos;
  kd = obj->g_kd();
  i = ls.g_it();
  cos = nor.dotprod(ls.g_dir());
  
  if (kd > 1.0) kd = 1.0;
  if (kd < 0.0) kd = 0.0;
  if (i > 255) i = 255;
  if (i < 0) i = 0;
  if (cos < 0.0) cos = 0.0;

  return kd * i * cos;
}

//
// main() - [演習1] メインルーチン
//
int
main()
{
	RTPoint vp, vrp, cnt;
	double angle, rad,kd;
	int ds;
	RTVec dir; double it;  //光源の方向と強さ
// ビューの設定 (標準入力からデータ入力)
	cin >> vp.c[0] >> vp.c[1] >> vp.c[2];	// 視点の入力
	cin >> vrp.c[0] >> vrp.c[1] >> vrp.c[2]; // 参照視点の入力
	cin >> angle >> ds;	// 視野角とピクセル数(各半分)の入力
	RTViewMgr view(vp, vrp, angle, ds);
// 物体(球)データの設定 (標準入力からデータ入力)
	cin >> cnt.c[0] >> cnt.c[1] >> cnt.c[2]; // 球の中心の入力
	cin >> rad;				// 球の半径の入力
	cin >> kd;                              //球の拡散反射率の入力
	RTObject obj(cnt, rad, kd);
// 光源の設定（標準入力からデータ入力）
	cin >> dir.c[0] >> dir.c[1] >> dir.c[2]; //光源の方向の入力
	cin >> it;                               //光源の強さの入力
	RTLSrc lsrc(dir,it);
// 各ピクセルの輝度の計算と標準出力への出力
	view.prnpgmhdr();	// PGMファイルのヘッダ出力
	RTRay ray;
	RTHit hit;
	for(int y = 2 * ds - 1; y >= 0; y--)
		for(int x = 0; x < 2 * ds; x++) {
			view.getray(x, y, &ray); // ピクセルへの光線を得る
			if(obj.rayhit(ray, &hit))
				cout << hit.intensity(lsrc);
			else
				cout << static_cast<unsigned char>(0);
		}
}
