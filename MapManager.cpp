#include "MapManager.h"
#include "input.h"
#include "sprite.h"
#include "main.h"

#define BLOCK_SIZE			50
#define HULF_PI				1.5703f

#define DRAW_NUM			12					//�v���C���[����n�����܂ł̐� 4�Ŋ���鐔���ɂ�����
#define HORIZONTAL_NUM		DRAW_NUM*0.75f
#define UNDER_NUM			DRAW_NUM*0.25f
#define DRAW_ANGLE			1.0f/DRAW_NUM		//�{��

#define DRAW_WIDETH			20

Map::Map()
{
	sumple = { 
		BLOCK_SIZE * MAP_SIZE * 0.5f,
		BLOCK_SIZE * MAP_SIZE * 0.5f 
	};

	m_MouseTex = LoadTexture((char*)"data/TEXTURE/MousePoint.png");

}

void Map::InitMapManager(D3DXVECTOR2* playerPos)
{
}

void Map::UninitMapManager()
{
}

void Map::UpdateMapManager()
{
	/*if (GetKeyboardPress(DIK_A)) {
		sumple.x -= 5;
	}
	if (GetKeyboardPress(DIK_D)) {
		sumple.x += 5;
	}*/
	if (GetKeyboardPress(DIK_W)) {
		sumple.y -= 5;
	}
	if (GetKeyboardPress(DIK_S)) {
		sumple.y += 5;
	}
}

void Map::DrawMapManager()
{
	//�v���C���[�̂���Y���W���ȈՕϊ��H
	int sy = sumple.y / 50;									//�v���C���[�̍�����Ȉ�Y���W
	float subY = (float)((int)sumple.y % 50) / 50.0f;		//�v���C���[��Y���W�̍���	�q�̍����̂Ԃ񂾂��}�b�v�̍��W�̕`������炵�Ĉړ����Ă���悤�Ɍ�����@�����
	
	float hrizon = SCREEN_HEIGHT * 0.2f;	//�}�b�v�`��̒n�����@
	float under = SCREEN_HEIGHT * 0.8f;		//�n��������v���C���[���̉�ʊO�܂ł̍���


	//�v���C���[�̂���X���W���ȈՕϊ�
	int sx = sumple.x / 50;
	float subX = (float)((int)sumple.x % 50) / 50.0f;		//�v���C���[��X���W�̍���





	int num = 0;			//�n�������牽�ڂ̂��

	for (int y = sy - HORIZONTAL_NUM; y < sy + UNDER_NUM; y++) {		//�`�悷�鐔�𐧌�
		float subAngle = HULF_PI * DRAW_ANGLE * subY;
		float wideT = 1 - cosf(HULF_PI * DRAW_ANGLE * num + subAngle);	
		num++;															//num�̍X�V�����̓_�����Ǝv�����ǁ@�߂�ǂ���������ꎞ�I��
		float wideB = 1 - cosf(HULF_PI * DRAW_ANGLE * num + subAngle);

		float lineT = hrizon + under * wideT;
		float lineB = hrizon + under * wideB;

		D3DXCOLOR col = { //�΂����񂾂񂱂�
			1.0f - 0.02f * y,
			1.0f - 0.02f * y,
			1.0f - 0.02f * y,
			1.0f 
		};

		//for (int x = 0;x < MAP_SIZE; x++) {								//x�͂܂�������Ȃ�
		float lt = 0;
		float rt = SCREEN_WIDTH;
		float lb = 0;
		float rb = SCREEN_WIDTH;
		DrawBoxColor_TB_FOUR(&lineT, &lineB, &lt, &rt, &lb, &rb, &col);
		//}
	}


	//�v���C���[�̕`��ꏊ�͌Œ�
	D3DXVECTOR2 pos = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.7f };
	D3DXVECTOR2 siz = { 100,100 };
	D3DXCOLOR col = { 1.0f,1.0f,1.0f,1.0f };
	DrawBoxColor(&pos, &siz, col);

	//DrawSpriteLeftTop(m_MouseTex, mouse.x, mouse.y, 30, 30, 0, 0, 1, 1);
	DrawSpriteLeftTop(m_MouseTex, GetMousePosition().x, GetMousePosition().y, 30, 30, 0, 0, 1, 1);
	//ShowCursor(true);
	ShowCursor(false);
	
}
