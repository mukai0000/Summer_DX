#include "MapManager.h"
#include "input.h"
#include "sprite.h"
#include "main.h"

#include "myString.h"

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
		BLOCK_SIZE * MAP_SIZE * 0.5f,
		BLOCK_SIZE * MAP_SIZE * 0.5f
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

	if (GetKeyboardTrigger(DIK_W) && GetKeyboardPress(DIK_LSHIFT)) {
		sumple.y -= speed;
		move.y += speed;
	}
	else if (GetKeyboardPress(DIK_W) && !GetKeyboardPress(DIK_LSHIFT)) {
		sumple.y -= speed;
		//if (sumple.y > 450)		
		move.y += speed;
	}

	if (GetKeyboardTrigger(DIK_S) && GetKeyboardPress(DIK_LSHIFT)) {
		sumple.y += speed;
		move.y -= speed;
	}
	else if (GetKeyboardPress(DIK_S) && !GetKeyboardPress(DIK_LSHIFT)) {
		sumple.y += speed;
		move.y -= speed;
	}

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
	int sy = (int)sumple.y / 50;							//�v���C���[�̍�����Ȉ�Y���W
	float subY = (float)((int)move.y % 50) / 50.0f;			//�v���C���[��Y���W�̍���	�q�̍����̂Ԃ񂾂��}�b�v�̍��W�̕`������炵�Ĉړ����Ă���悤�Ɍ�����@�����

	float hrizon = SCREEN_HEIGHT * 0.2f;					//�}�b�v�`��̒n�����@
	float under = SCREEN_HEIGHT - hrizon;					//�n��������v���C���[���̉�ʊO�܂ł̍���


	//�n�������r�R�r�R����̂͂����ŏ����_�ȉ��؂�̂Ăɂ��Ă��܂��Ă镔�����E���ĂȂ�����

	//�v���C���[�̂���X���W���ȈՕϊ�
	int sx = (int)sumple.x / 50;
	float subX = (float)((int)sumple.x % 50) / 50.0f;		//�v���C���[��X���W�̍���


	int numY = 0;			//�n�������牽�ڂ̂����Y�o�[�W����
	float hWideT, hWideB, lineT, lineB, subAngle, topAngle, bottomAngle;

	TEXTURE_DATA box = SetTexture("data/TEXTURE/box.png", 1, 1, 1);
	int startY = sy - HORIZON_TO_PLAYER;
	int endY = sy + PLAYER_TO_UNDER;

	for (int y = startY; y < endY; y++) {		//�`�悷�鐔�𐧌�

		subAngle = HULF_PI * DRAW_ANGLE_Y * subY;								//�v���C���[�̈ړ��ɂ���Ĕ��������p�x�̒[���H

		topAngle = HULF_PI * DRAW_ANGLE_Y * numY + subAngle;					//�`��̃`�b�v�̂������W�̊p�x
		bottomAngle = HULF_PI * DRAW_ANGLE_Y * (numY + 1) + subAngle;			//�`��̃`�b�v�̉��̍��W�̊p�x

		hWideT = 1 - cosf(topAngle);
		hWideB = 1 - cosf(bottomAngle);

		lineT = hrizon + under * hWideT;
		lineB = hrizon + under * hWideB;

		int numX = -TOP_LEFT_RIGHT * 0.5f;				//�v���C���[���牽���ꂽ���

		float wideT, wideB;								//���̏�Ɖ��̕ӂ̒���
		float lt, rt, lb, rb;							///����E�㍶���E����X���W

		int startX = sx - TOP_LEFT_RIGHT * 0.5f;
		int endX = sx + TOP_LEFT_RIGHT * 0.5f;

		for (int x = startX; x < endX; x++) {
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

			if (topAngle < 0)topAngle = 0;

			wideT = WIDE_WIDE + WIDE_WIDE * (sinf(topAngle));		//���̐�����������
			wideB = WIDE_WIDE + WIDE_WIDE * (sinf(bottomAngle));

			lt = SCREEN_WIDTH * 0.5f + wideT * numX;
			rt = SCREEN_WIDTH * 0.5f + wideT * (numX + 1);
			lb = SCREEN_WIDTH * 0.5f + wideB * numX;
			rb = SCREEN_WIDTH * 0.5f + wideB * (numX + 1);
			
			if (numY == 0) {
				//DrawBoxColor_TB_FOUR(&hrizon, &lineB, &lt, &rt, &lb, &rb, &col);
				//DrawSprite_TB_FOUR(&box, &hrizon, &lineT, &lb, &rb, &lt, &rt);
				DrawSprite_TB_FOUR(&box, &hrizon, &lineT, &lb, &rb, &lb, &rb);
			}

			//DrawBoxColor_TB_FOUR(&lineT, &lineB, &lt, &rt, &lb, &rb, &col);

			DrawSprite_TB_FOUR(&box, &lineT, &lineB, &lt, &rt, &lb, &rb);
			if (numY == 0) {

				//DrawNumberSumple(D3DXVECTOR2(0, 200), D3DXVECTOR2(50, 50), lt - rt);
				/*DrawNumberSumple(D3DXVECTOR2(300, 200), D3DXVECTOR2(50, 50), lineT);
				DrawNumberSumple(D3DXVECTOR2(500, 200), D3DXVECTOR2(50, 50), hrizon);*/
				//DrawNumberSumple(D3DXVECTOR2(300, 100), D3DXVECTOR2(50, 50), numX);
			}


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



	/*MyString* ms = new MyString("World Wide Pokemon Project");

	D3DXVECTOR2 sp = { 0,0, };
	D3DXVECTOR2 ss = { 50,50, };
	D3DXCOLOR sc = { 1,1,1,1 };

	ms->DrawString(sp,ss,sc);

	delete ms;*/
}
