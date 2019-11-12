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
	Filter[0] = new int[FilterSize] {0, 0, 0};
	Filter[1] = new int[FilterSize] {1, -1, 0};
	Filter[2] = new int[FilterSize] {0, 0, 0};
} //End_Function

/// <summary>
/// �摜�̍��W���w�肵�ĐϘa���Z������
/// </summary>
int MultiplyAdd(int x, int y, unsigned char* grayImg, int** filter) {
	int sum = 0;
	//�t�B���^�����O�O�O�O
	for (int i = -(FilterSize - 1) / 2; i < (FilterSize - 1) / 2; ++i) {
		for (int j = -(FilterSize - 1) / 2; j < (FilterSize - 1) / 2; ++j) {
			sum += grayImg[(y + i) * width + (x + j)] * filter[i + (FilterSize - 1) / 2][j + (FilterSize - 1) / 2];
		} //End_For
	} //End_For
	return sum;
} //End_Function


/// <summary>
/// outputMTMR���悭�킩���̂Ŏ���
/// </summary>
int outputBebebe() {
	//�o�̓p�X�擾
	std::string outPath;
	std::cin >> outPath;
	outPath += ".pgm";
	std::cout << "�o�̓p�X : " << outPath << std::endl;

	//�o�̓X�g���[��
	std::ofstream outStream(outPath, std::ios::out);

	//�w�b�_���o�͏���
	outStream << "P5\n" + std::to_string(width) + " " + std::to_string(height) + "\n255\n";

	//�ۑ��摜��f�l�o��
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			outStream << outputImage[i * width + j] << " ";
		} //End_For
		outStream << "\n";
	} //End_For

	//���������(C#��Using�݂����Ȃ̂ق���)C++
	outStream.close();

	return 0;
} //End_Function