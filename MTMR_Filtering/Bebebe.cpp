/*==============================================*/
/*		D1���|�[�g�p�T���v���v���O����				*/
/*		�쐬�Ҏ����@��������						*/
/*==============================================*/

#include "Saeki.h"

unsigned char *ppmImage;		//���͉摜�p(rgb3�`���l��)
unsigned char *grayImage;		//�O���C�X�P�[���摜�p�i1�`���l���j
unsigned char *outputImage;		//�o�͉摜�p(�G�b�W���o�摜�ۑ��p�@1�`���l��...�O���[�X�P�[��)
int width;						//���͉摜����(pixel)
int height;						//���͉摜�c��(pixel)
char name[256];					//�t�@�C���l�[���p

const int FilterSize = 3;		//�t�B���^�T�C�Y(�t�B���^�͐����`�݂̂������߂ł�)
int** Filter;					//�t�B���^�����O�Ɏg��Filter(��������Initialize)

/// <summary>
/// ������������
/// </summary>
void Initialize() {
	Filter = new int*[FilterSize];
	Filter[0] = new int[FilterSize] {0, 1, 0};
	Filter[1] = new int[FilterSize] {1, -4, 1};
	Filter[2] = new int[FilterSize] {0, 1, 0};
} //End_Function

/// <summary>
/// �摜�̍��W���w�肵�ĐϘa���Z������
/// </summary>
int MultiplyAdd(int x, int y, unsigned char* img, int** filter) {
	int sum = 0;
	//�t�B���^�����O�O�O�O
	for (int i = -(FilterSize - 1) / 2; i < (FilterSize - 1) / 2; ++i) {
		for (int j = -(FilterSize - 1) / 2; j < (FilterSize - 1) / 2; ++j) {
			sum += img[(y + i) * width + (x + j)] * filter[i][j];
		} //End_For
	} //End_For
	return sum;
} //End_Function


int main(int argc, char *argv[]) {
	/*****�K�v�ȕϐ�������ΓK�X�錾*****/
	int imageWidthAfterFiltering = width - (FilterSize - 1) / 2;	//�t�B���^�����O��̉摜�T�C�Y(x����)
	int imageHeightAfterFiltering = height - (FilterSize - 1) / 2;	//�t�B���^�����O��̉摜�T�C�Y(y����)

	/*****���͉摜�I�[�v��*****/
	printf("���͉摜�t�@�C��������́i�g���q�͂Ȃ��Ă悢�j�F");
	scanf("%s", name);
	if (openImage() != 0)
		return 1;

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
	scanf("%s", name);
	if (output() != 0)
		return 1;


	free();

	return 0;
} //End_Function