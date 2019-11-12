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
	Filter[0] = new int[FilterSize] {0, 0, 0};
	Filter[1] = new int[FilterSize] {1, -1, 0};
	Filter[2] = new int[FilterSize] {0, 0, 0};
} //End_Function

/// <summary>
/// 画像の座標を指定して積和演算したい
/// </summary>
int MultiplyAdd(int x, int y, unsigned char* grayImg, int** filter) {
	int sum = 0;
	//フィルタリンググググ
	for (int i = -(FilterSize - 1) / 2; i < (FilterSize - 1) / 2; ++i) {
		for (int j = -(FilterSize - 1) / 2; j < (FilterSize - 1) / 2; ++j) {
			sum += grayImg[(y + i) * width + (x + j)] * filter[i + (FilterSize - 1) / 2][j + (FilterSize - 1) / 2];
		} //End_For
	} //End_For
	return sum;
} //End_Function


/// <summary>
/// outputMTMRがよくわからんので自作
/// </summary>
int outputBebebe() {
	//出力パス取得
	std::string outPath;
	std::cin >> outPath;
	outPath += ".pgm";
	std::cout << "出力パス : " << outPath << std::endl;

	//出力ストリーム
	std::ofstream outStream(outPath, std::ios::out);

	//ヘッダ部出力処理
	outStream << "P5\n" + std::to_string(width) + " " + std::to_string(height) + "\n255\n";

	//保存画像画素値出力
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			outStream << outputImage[i * width + j] << " ";
		} //End_For
		outStream << "\n";
	} //End_For

	//メモリ解放(C#のUsingみたいなのほしい)C++
	outStream.close();

	return 0;
} //End_Function