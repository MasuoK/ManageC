//
// ex00.cc - [演習0] プログラムファイル
//	作者: (あなたの名前); 日付: (完成した日付)
// [注意] 以降の演習では，上記を適切に書き換えること
//

#include "rt00.h"
#include <iostream>
using namespace std;

//
// RTHit::intensity() - ピクセルの輝度(0〜255)を返す
//
unsigned char
RTHit::intensity(void)
{
	return 255;	// この場合は常に 255(真白)を返す
}

//
// main() - [演習0] メインルーチン
//
int
main()
{
	RTPoint vp, vrp, cnt;
	double angle, rad;
	int ds;

// ビューの設定 (標準入力からデータ入力)
	cin >> vp.c[0] >> vp.c[1] >> vp.c[2];	// 視点の入力
	cin >> vrp.c[0] >> vrp.c[1] >> vrp.c[2]; // 参照視点の入力
	cin >> angle >> ds;	// 視野角とピクセル数(各半分)の入力
	RTViewMgr view(vp, vrp, angle, ds);
// 物体(球)データの設定 (標準入力からデータ入力)
	cin >> cnt.c[0] >> cnt.c[1] >> cnt.c[2]; // 球の中心の入力
	cin >> rad;				// 球の半径の入力
	RTObject obj(cnt, rad);
// 各ピクセルの輝度の計算と標準出力への出力
	view.prnpgmhdr();	// PGMファイルのヘッダ出力
	RTRay ray;
	RTHit hit;
	for(int y = 2 * ds - 1; y >= 0; y--)
		for(int x = 0; x < 2 * ds; x++) {
			view.getray(x, y, &ray); // ピクセルへの光線を得る
			if(obj.rayhit(ray, &hit))
				cout << hit.intensity();
			else
				cout << static_cast<unsigned char>(0);
		}
}
