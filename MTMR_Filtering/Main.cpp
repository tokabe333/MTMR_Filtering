/*==============================================*/
/*		D1���|�[�g�p�T���v���v���O����				*/
/*		�쐬�Ҏ����@��������						*/
/*==============================================*/

#include "Saeki.h"

/// <summary>
/// Initialize��K���Ăڂ��ˁI�I�I�I�I(1�s)
/// </summary>
int main(int argc, char *argv[]) {
	//Filter�̏�������Y�ꂸ���悤�ˁI�I�I�I�I�I�I�I
	Initialize();

	/*****�K�v�ȕϐ�������ΓK�X�錾*****/


	/*****���͉摜�I�[�v��*****/
	printf("���͉摜�t�@�C��������́i�g���q�͂Ȃ��Ă悢�j�F");
	scanf("%s", name);
	if (openImage() != 0)
		return 1;

	//�摜���J���O�ɐ錾����Ƃ��񂿂����ɂȂ�
	const int imageWidthAfterFiltering = width - (FilterSize - 1) / 2;	//�t�B���^�����O��̉摜�T�C�Y(x����)
	const int imageHeightAfterFiltering = height - (FilterSize - 1) / 2;	//�t�B���^�����O��̉摜�T�C�Y(y����)

	/*****�O���[�X�P�[����*****/
	makeGrayImage();

	/*****�G�b�W���o���ʏo�͉摜�p�z��m��*****/
	outputImage = (unsigned char*)malloc(sizeof(unsigned char) * imageWidthAfterFiltering * imageHeightAfterFiltering); //��*�����̃T�C�Y�Ŕz��m�ہ@�P���ɓ��͉摜���̂܂܂̕��A�����ɂ͂Ȃ�Ȃ����Ƃɒ���

	/*****��������t�B���^�����O�����������Ă���******/
	/******grayImage�ɑ΂��ăt�B���^�ɂ���ݍ��݉��Z���s���A���ʂ�outputImage��*****/
	/*****outputImage[y * width + x]�ňʒu(x,y)�̉�f�ɃA�N�Z�X�ł���igrayImage�����l�ɃA�N�Z�X�j*****/
	for (int i = (FilterSize - 1) / 2; i < imageHeightAfterFiltering; ++i) {
		for (int j = (FilterSize - 1) / 2; j < imageWidthAfterFiltering; ++j) {
			outputImage[i * width + j] = MultiplyAdd(j, i, grayImage, Filter);
		} //End_For
	} //End_For




	/*****�摜�o��*****/
	printf("�o�͉摜�t�@�C��������́i�g���q�͂Ȃ��Ă悢�j�F");

	//outputBebebe();
	scanf("%s", name);
	if (outputMTMR() != 0)
		return 1;

	free();

	return 0;
} //End_Function