/*==============================================*/
/*		D1レポート用サンプルプログラム				*/
/*		作成者氏名　岡部蒼太						*/
/*==============================================*/

#include "Saeki.h"

unsigned char *ppmImage;		//入力画像用(rgb3チャネル)
unsigned char *grayImage;		//グレイスケール画像用（1チャネル）
unsigned char *outputImage;		//出力画像用(エッジ検出画像保存用　1チャネル...グレースケール)
int width;						//入力画像横幅(pixel)
int height;						//入力画像縦幅(pixel)
char name[256];					//ファイルネーム用

const int FilterSize = 3;		//フィルタサイズ(フィルタは正方形のみしかだめです)
int** Filter;					//フィルタリングに使うFilter(初期化はInitialize)

/// <summary>
/// 初期化したい
/// </summary>
void Initialize() {
	Filter = new int*[FilterSize];
	Filter[0] = new int[FilterSize] {0, 1, 0};
	Filter[1] = new int[FilterSize] {1, -4, 1};
	Filter[2] = new int[FilterSize] {0, 1, 0};
} //End_Function

/// <summary>
/// 画像の座標を指定して積和演算したい
/// </summary>
int MultiplyAdd(int x, int y, unsigned char* img, int** filter) {
	int sum = 0;
	//フィルタリンググググ
	for (int i = -(FilterSize - 1) / 2; i < (FilterSize - 1) / 2; ++i) {
		for (int j = -(FilterSize - 1) / 2; j < (FilterSize - 1) / 2; ++j) {
			sum += img[(y + i) * width + (x + j)] * filter[i][j];
		} //End_For
	} //End_For
	return sum;
} //End_Function


int main(int argc, char *argv[]) {
	/*****必要な変数があれば適宜宣言*****/
	int imageWidthAfterFiltering = width - (FilterSize - 1) / 2;	//フィルタリング後の画像サイズ(x方向)
	int imageHeightAfterFiltering = height - (FilterSize - 1) / 2;	//フィルタリング後の画像サイズ(y方向)

	/*****入力画像オープン*****/
	printf("入力画像ファイル名を入力（拡張子はなくてよい）：");
	scanf("%s", name);
	if (openImage() != 0)
		return 1;

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
	scanf("%s", name);
	if (output() != 0)
		return 1;


	free();

	return 0;
} //End_Function