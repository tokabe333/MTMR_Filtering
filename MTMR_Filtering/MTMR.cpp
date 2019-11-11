/*==============================================*/
/*		D1���|�[�g�p�T���v���v���O����				*/
/*		�쐬�Ҏ����@��������						*/
/*==============================================*/

#include "Saeki.h"

/*****���Ӂ@��L�̂悤�ɃO���[�o���ϐ��𑽗p����̂͂�߂܂��傤�i����͊y�����邽�߂ł��j*****/

//���͉摜�ǂݍ��ݗp�֐�
int openImage()
{
	FILE *fp;
	char buff[N]; //�w�b�_�ǂݎ̂ėp
	char *tp;
	char temp[256];

	/*****�t�@�C���I�[�v��*****/
	sprintf(temp, "%s.ppm", name);
	if ((fp = fopen(temp, "rb")) == NULL)
	{
		printf("�摜���J���܂���\n");
		return -1;
	}

	/*****�摜�w�b�_���ǂݍ��ݏ���*****/
	fgets(buff, N, fp); //�}�W�b�N�i���o�[�ǂݎ̂āi1�s�ǂݍ��݁j

	while (1) { //�R�����g�ǂݎ̂ă��[�v
		fgets(buff, N, fp); //1�s�ǂݍ���
		if (buff[0] != '#')
			break; //�����R�����g�s�ł͂Ȃ������甲���o��
	}

	// �R�����g�s�����̎��͉摜�T�C�Y�A�`�����l��������s�ŋL�q
	tp = strtok(buff, " "); //�����񕪊�
	width = atoi(buff); //�ŏ���width���L�q
	tp = strtok(NULL, " "); //�����񕪊�
	height = atoi(tp); //����height���L�q

	fgets(buff, N, fp); //�ő�P�x�l�̓ǂݎ̂�
	/*****�����܂ŉ摜�w�b�_�ǂݍ���*****/

	/*****���͉摜�p�z��m��*****/
	ppmImage = (unsigned char*)malloc(sizeof(unsigned char) * height * width * CHANNEL);

	/*****���͉摜��f�l�ǂݍ���*****/
	fread(ppmImage, sizeof(unsigned char), width * height * CHANNEL, fp);

	fclose(fp);

	return 0;
}

//�O���[�X�P�[����
void makeGrayImage()
{
	/*****���͉摜�p�z��m��*****/
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

//�摜�ۑ��p�֐�
int output()
{
	FILE *fp;
	char temp[256];

	/*****�t�@�C���I�[�v��*****/
	sprintf(temp, "%s.pgm", name);
	if ((fp = fopen(temp, "wb")) == NULL)
	{
		printf("�摜���ۑ��ł��܂���\n");
		return -1;
	}

	/*****�摜�w�b�_���o�͏���*****/
	fprintf(fp, "P5\n%d %d\n255\n", width, height);

	/*****�ۑ��摜��f�l�o��*****/
	fwrite(outputImage, sizeof(unsigned char), width * height, fp);

	fclose(fp);

	return 0;
}

//�悭�킩�����
void free()
{
	free(ppmImage);
	free(grayImage);
	free(outputImage);
}
