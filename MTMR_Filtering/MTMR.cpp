/*==============================================*/
/*		D1レポート用サンプルプログラム				*/
/*		作成者氏名　岡部蒼太						*/
/*==============================================*/

#include "Saeki.h"

/*****注意　上記のようにグローバル変数を多用するのはやめましょう（これは楽をするためです）*****/

//入力画像読み込み用関数
int openImage()
{
	FILE *fp;
	char buff[N]; //ヘッダ読み捨て用
	char *tp;
	char temp[256];

	/*****ファイルオープン*****/
	sprintf(temp, "%s.ppm", name);
	if ((fp = fopen(temp, "rb")) == NULL)
	{
		printf("画像が開けません\n");
		return -1;
	}

	/*****画像ヘッダ部読み込み処理*****/
	fgets(buff, N, fp); //マジックナンバー読み捨て（1行読み込み）

	while (1) { //コメント読み捨てループ
		fgets(buff, N, fp); //1行読み込み
		if (buff[0] != '#')
			break; //もしコメント行ではなかったら抜け出す
	}

	// コメント行部分の次は画像サイズ、チャンネル数が一行で記述
	tp = strtok(buff, " "); //文字列分割
	width = atoi(buff); //最初にwidthが記述
	tp = strtok(NULL, " "); //文字列分割
	height = atoi(tp); //次にheightが記述

	fgets(buff, N, fp); //最大輝度値の読み捨て
	/*****ここまで画像ヘッダ読み込み*****/

	/*****入力画像用配列確保*****/
	ppmImage = (unsigned char*)malloc(sizeof(unsigned char) * height * width * CHANNEL);

	/*****入力画像画素値読み込み*****/
	fread(ppmImage, sizeof(unsigned char), width * height * CHANNEL, fp);

	fclose(fp);

	return 0;
}

//グレースケール化
void makeGrayImage()
{
	/*****入力画像用配列確保*****/
	grayImage = (unsigned char*)malloc(sizeof(unsigned char) * height * width);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			double intensity = 0.298839*(unsigned char)ppmImage[i * width * CHANNEL + j * CHANNEL] + 0.586811*(unsigned char)ppmImage[i * width * CHANNEL + j * CHANNEL + 1] + 0.114350*(unsigned char)ppmImage[i * width * CHANNEL + j * CHANNEL];
			grayImage[i * width + j] = (unsigned char)intensity;
		}
	}
}

//画像保存用関数
int output()
{
	FILE *fp;
	char temp[256];

	/*****ファイルオープン*****/
	sprintf(temp, "%s.pgm", name);
	if ((fp = fopen(temp, "wb")) == NULL)
	{
		printf("画像が保存できません\n");
		return -1;
	}

	/*****画像ヘッダ部出力処理*****/
	fprintf(fp, "P5\n%d %d\n255\n", width, height);

	/*****保存画像画素値出力*****/
	fwrite(outputImage, sizeof(unsigned char), width * height, fp);

	fclose(fp);

	return 0;
}

//よくわからんやつ
void free()
{
	free(ppmImage);
	free(grayImage);
	free(outputImage);
}
