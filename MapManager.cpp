#include "MapManager.h"
#include "input.h"
#include "sprite.h"
#include "main.h"

#include <windows.h>

#define BLOCK_SIZE					50
#define HULF_PI						1.5703f

#define HOLIZON_TO_UNDER			12								//�v���C���[����n�����܂ł̐� 4�Ŋ���鐔���ɂ�����
#define HORIZON_TO_PLAYER			(HOLIZON_TO_UNDER*0.75f)		//����������v���C���[�܂ł̕`�搔
#define PLAYER_TO_UNDER				(HOLIZON_TO_UNDER*0.25f)		//�v���C���[�����ʂ����ł̕`�搔
#define DRAW_ANGLE_Y				(1.0f/HOLIZON_TO_UNDER)			//�p�x�{��

#define UNDER_LEFT_TO_RIGHT			16								//�v���C���[�̂��鍂���͍��E��8���`�悷�邩��
#define TOP_LEFT_RIGHT				(UNDER_LEFT_TO_RIGHT*1.5)
#define WIDE_WIDE					SCREEN_WIDTH/TOP_LEFT_RIGHT		//���ꂪ��ɂȂ镝

Map::Map()
{
	sumple = { 
		BLOCK_SIZE * MAP_SIZE * 0.2f,
		BLOCK_SIZE * MAP_SIZE * 0.2f 
	};
	mouse = { 
		SCREEN_WIDTH * 0.2f,
		SCREEN_HEIGHT * 0.2f 
	};
	move = {
		(BLOCK_SIZE * MAP_SIZE) - sumple.x,
		(BLOCK_SIZE * MAP_SIZE) - sumple.y
	};

	m_MouseTex = LoadTexture((char*)"data/TEXTURE/MousePoint.png");
	m_BGTex = LoadTexture((char*)"data/TEXTURE/sky.png");

	isMouse = !true;
}

void Map::InitMapManager(D3DXVECTOR2* playerPos)
{
}

void Map::UninitMapManager()
{
}

void Map::UpdateMapManager()
{
	int speed = 1;
	if (GetKeyboardPress(DIK_A)) {
		sumple.x -= speed;
		move.x += speed;
	}
	if (GetKeyboardPress(DIK_D)) {
		sumple.x += speed;
		move.x -= speed;
	}
	if (GetKeyboardPress(DIK_W)) {
		sumple.y -= speed;
		//if (sumple.y > 450)		
			move.y += speed;
	}
	if (GetKeyboardPress(DIK_S)) {
		sumple.y += speed;
		move.y -= speed;
	}/*
	if (GetKeyboardTrigger(DIK_W)) {
		sumple.y -= speed;
		move.y += speed;
	}
	if (GetKeyboardTrigger(DIK_S)) {
		sumple.y += speed;
		move.y -= speed;
	}*/

	if (GetKeyboardTrigger(DIK_TAB)) {
		isMouse = !isMouse;
	}

	if (isMouse) {
		SetCursorPos(800, 500);
	}
}

void Map::DrawMapManager()
{
	//�\��
	DrawSpriteLeftTop(m_BGTex, 0, -500, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1, 1);


	//�v���C���[�̂���Y���W���ȈՕϊ��H
	int sy = sumple.y / 50;									//�v���C���[�̍�����Ȉ�Y���W
	float subY = (float)((int)move.y % 50) / 50.0f;			//�v���C���[��Y���W�̍���	�q�̍����̂Ԃ񂾂��}�b�v�̍��W�̕`������炵�Ĉړ����Ă���悤�Ɍ�����@�����
	
	float hrizon = SCREEN_HEIGHT * 0.2f;					//�}�b�v�`��̒n�����@
	float under = SCREEN_HEIGHT - hrizon;					//�n��������v���C���[���̉�ʊO�܂ł̍���


	//�v���C���[�̂���X���W���ȈՕϊ�
	int sx = sumple.x / 50;
	float subX = (float)((int)sumple.x % 50) / 50.0f;		//�v���C���[��X���W�̍���



	int numY = 0;			//�n�������牽�ڂ̂����Y�o�[�W����
	float hWideT, hWideB, lineT, lineB, subAngle;



	for (int y = sy - HORIZON_TO_PLAYER; y < sy + PLAYER_TO_UNDER; y++) {		//�`�悷�鐔�𐧌�
		
		subAngle = HULF_PI * DRAW_ANGLE_Y * subY;
		hWideT = 1 - cosf(HULF_PI * DRAW_ANGLE_Y * numY + subAngle);
		hWideB = 1 - cosf(HULF_PI * DRAW_ANGLE_Y * (numY + 1) + subAngle);

		lineT = hrizon + under * hWideT;
		lineB = hrizon + under * hWideB;

		int numX = -TOP_LEFT_RIGHT *0.5f;				//�v���C���[���牽���ꂽ���

		float wideT, wideB;								//���̏�Ɖ��̕ӂ̒���
		float lt, rt, lb, rb;							///����E�㍶���E����X���W

		for (int x = sx - TOP_LEFT_RIGHT * 0.5f; x < sx + TOP_LEFT_RIGHT * 0.5f; x++) {
			//���������Q�@�v���C���[�̂Ƃ���艺���R�ɂ���\��

			D3DXCOLOR col = { //�΂����񂾂񂱂�
				1.0f - 0.05f * x,
				1.0f - 0.05f * x,
				1.0f - 0.05f * x,
				/*1.0f - 0.05f * y,
				1.0f - 0.05f * y,
				1.0f - 0.05f * y,*/
				1.0f
			};

			
			wideT = WIDE_WIDE+ WIDE_WIDE*(sinf(HULF_PI * DRAW_ANGLE_Y * numY + subAngle));		//���̐�����������
			wideB = WIDE_WIDE+ WIDE_WIDE*(sinf( HULF_PI * DRAW_ANGLE_Y * (numY+1) + subAngle));
			

			/*lt = 0;
			rt = SCREEN_WIDTH;
			lb = 0;
			rb = SCREEN_WIDTH;*/

			lt = SCREEN_WIDTH * 0.5f + wideT * numX;
			rt = SCREEN_WIDTH * 0.5f + wideT * (numX + 1);
			lb = SCREEN_WIDTH * 0.5f + wideB * numX;
			rb = SCREEN_WIDTH * 0.5f + wideB * (numX + 1);

			//�n�������r�R�r�R�Ȃ�̂��C�� ����Ȃ�������
			if (numY == 0) {
				DrawBoxColor_TB_FOUR(&hrizon, &lineB, &lt, &rt, &lb, &rb, &col);
			}

			DrawBoxColor_TB_FOUR(&lineT, &lineB, &lt, &rt, &lb, &rb, &col);

			numX++;
		}
		if (numY <= y)numY++;
	}


	//�v���C���[�̕`��ꏊ�͊�{�Œ�
	D3DXVECTOR2 pos = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.7f };
	D3DXVECTOR2 siz = { 100,100 };
	D3DXCOLOR col = { 1.0f,1.0f,1.0f,1.0f };
	DrawBoxColor(&pos, &siz, col);

	mouse.x += GetMouseX();
	mouse.y += GetMouseY();

	//DrawSpriteLeftTop(m_MouseTex, mouse.x, mouse.y, 30, 30, 0, 0, 1, 1);
	DrawSpriteLeftTop(m_MouseTex, GetMousePosition().x, GetMousePosition().y, 30, 30, 0, 0, 1, 1);
	//ShowCursor(true);
	ShowCursor(false);

	HCURSOR hcu;
	
	
	DrawNumberSumple(D3DXVECTOR2(100, 100), D3DXVECTOR2(50, 50), sumple.y);
}
