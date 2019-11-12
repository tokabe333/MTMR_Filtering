/*==============================================*/
/*		D1レポート用サンプルプログラム				*/
/*		作成者氏名　岡部蒼太						*/
/*==============================================*/

#include "Saeki.h"

/// <summary>
/// Initializeを必ず呼ぼうね！！！！！(1敗)
/// </summary>
int main(int argc, char *argv[]) {
	//Filterの初期化を忘れずしようね！！！！！！！！
	Initialize();

	/*****必要な変数があれば適宜宣言*****/


	/*****入力画像オープン*****/
	printf("入力画像ファイル名を入力（拡張子はなくてよい）：");
	scanf("%s", name);
	if (openImage() != 0)
		return 1;

	//画像を開く前に宣言するとうんちっちになる
	const int imageWidthAfterFiltering = width - (FilterSize - 1) / 2;	//フィルタリング後の画像サイズ(x方向)
	const int imageHeightAfterFiltering = height - (FilterSize - 1) / 2;	//フィルタリング後の画像サイズ(y方向)

	/*****グレースケール化*****/
	makeGrayImage();

	/*****エッジ検出結果出力画像用配列確保*****/
	outputImage = (unsigned char*)malloc(sizeof(unsigned char) * imageWidthAfterFiltering * imageHeightAfterFiltering); //幅*高さのサイズで配列確保　単純に入力画像そのままの幅、高さにはならないことに注意

	/*****ここからフィルタリング処理を書いていく******/
	/******grayImageに対してフィルタによる畳み込み演算を行い、結果をoutputImageへ*****/
	/*****outputImage[y * width + x]で位置(x,y)の画素にアクセスできる（grayImageも同様にアクセス）*****/
	for (int i = (FilterSize - 1) / 2; i < imageHeightAfterFiltering; ++i) {
		for (int j = (FilterSize - 1) / 2; j < imageWidthAfterFiltering; ++j) {
			outputImage[i * width + j] = MultiplyAdd(j, i, grayImage, Filter);
		} //End_For
	} //End_For




	/*****画像出力*****/
	printf("出力画像ファイル名を入力（拡張子はなくてよい）：");

	//outputBebebe();
	scanf("%s", name);
	if (outputMTMR() != 0)
		return 1;

	free();

	return 0;
} //End_Function