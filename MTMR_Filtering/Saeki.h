#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <string.h>
#include <iostream> //����
#include <string>	//���񂿂���2
#include <fstream>	//���񂿂���3

#define N 256
#define CHANNEL 3

extern unsigned char *ppmImage;		//���͉摜�p(rgb3�`���l��)
extern unsigned char *grayImage;	//�O���C�X�P�[���摜�p�i1�`���l���j
extern unsigned char *outputImage;	//�o�͉摜�p(�G�b�W���o�摜�ۑ��p�@1�`���l��...�O���[�X�P�[��)
extern int width;					//���͉摜����(pixel)
extern int height;					//���͉摜�c��(pixel)
extern char name[256];				//�t�@�C���l�[���p

extern const int FilterSize;		//�t�B���^�T�C�Y(�t�B���^�͐����`�̂�)
extern int** Filter;				//Filtering�Ɏg���t�B���^�[(��������Initialize)


//���͉摜�ǂݍ��ݗp�֐�
int openImage();

//�O���[�X�P�[����
void makeGrayImage();

//�摜�ۑ��p�֐�
int outputMTMR();

//outputMTMR���悭�킩���̂Ŏ���
int outputBebebe();

//�悭�킩�����
void free();

//������������
void Initialize();

//�摜�̍��W���w�肵�ĐϘa���Z������
int MultiplyAdd(int x, int y, unsigned char* img, int** filter);