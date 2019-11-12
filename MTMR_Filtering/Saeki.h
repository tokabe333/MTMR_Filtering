#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <string.h>
#include <iostream> //うんち
#include <string>	//うんちその2
#include <fstream>	//うんちその3

#define N 256
#define CHANNEL 3

extern unsigned char *ppmImage;		//入力画像用(rgb3チャネル)
extern unsigned char *grayImage;	//グレイスケール画像用（1チャネル）
extern unsigned char *outputImage;	//出力画像用(エッジ検出画像保存用　1チャネル...グレースケール)
extern int width;					//入力画像横幅(pixel)
extern int height;					//入力画像縦幅(pixel)
extern char name[256];				//ファイルネーム用

extern const int FilterSize;		//フィルタサイズ(フィルタは正方形のみ)
extern int** Filter;				//Filteringに使うフィルター(初期化はInitialize)


//入力画像読み込み用関数
int openImage();

//グレースケール化
void makeGrayImage();

//画像保存用関数
int outputMTMR();

//outputMTMRがよくわからんので自作
int outputBebebe();

//よくわからんやつ
void free();

//初期化したい
void Initialize();

//画像の座標を指定して積和演算したい
int MultiplyAdd(int x, int y, unsigned char* img, int** filter);