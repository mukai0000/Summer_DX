#pragma once

#include "main.h"

#define pi (3.15f)
#define RAD(x) x/180*pi

//=================== MEMO =================
/*
����Q�[�������Ƃ��̂��߂̉�����

�Ⴆ�΋��剻����G�������Ƃ��āA���̏ꍇscale�ϐ���������K�v������킯�����ǁA�����Ȃ����ꍇ�ǂ����邩�l���Ă�
���t���[���X�P�[���Ɋ֌W���鏈��������̂͌�������������AEditScale�֐��݂����Ȃ̂�����ď��������ȊO�͂�����o�R���Ȃ���scale�͂�����Ȃ��悤�ɂ���̂�����ȋC������

OldPosition��OldRotation���ǉ����邩�Y�ݒ�

*/

class BoxTransform
{
	//======================
	//�R���X�g���N�^
	//======================
	BoxTransform();
	BoxTransform(D3DXVECTOR2 pos, D3DXVECTOR2 size, float rot);



	//======================
	//		�ϐ�
	//======================
private:
	D3DXVECTOR2 position;		//���_���W
	D3DXVECTOR2 oldPosition;	//1�t���[���O�̌��_���W
	D3DXVECTOR2 scale;			//���ƍ���
	D3DXVECTOR2 velocity;		//�ړ������H ��Ƀm�[�}���C�Y�����l���L�^����悤�ɂ�����	direction�̂ق��������̂��H
	float rotation;				//��]�p
	float radian;				//���W�A���p�@���ׂ����Y��ł�@���x�v�Z������ϐ��Ŋm�ۂ��Ă������ق����������ĕ�����
	float speed;				//�ړ�������ݒ肵�Ă����A�P�ʃx�N�g����velocity�ɏ�Z���Ď��ۂ̈ړ������ɂ���\��

	float range;				//���S�_����l�p�܂ł̋����@�ǂ̃^�C�~���O�ōX�V���邩�Y��

	D3DXVECTOR2 no1Position;	//�|���S���̐����Ɏg���l�p
	D3DXVECTOR2 no2Position;
	D3DXVECTOR2 no3Position;
	D3DXVECTOR2 no4Position;




	//�C�j�V�����C�U�[
	//�R���X�g���N�^�ȂǂŎ󂯎�����f�[�^���g���āA�󂯎���ĂȂ��f�[�^�Ɋi�[����
	void VertexPositionInitialize();


	//======================
	//�Z�b�^�[
	//======================
	void	SetPosition(D3DXVECTOR2 pos) { position = pos; }
	void	SetPosition(float x, float y) { position = D3DXVECTOR2(x, y); }

	void	SetScale(D3DXVECTOR2 size) { scale = size; }
	void	SetScale(float x, float y) { scale = D3DXVECTOR2(x, y); }

	void	SetRotation(float rot) { rotation = rot; radian = RAD(rotation);}		//���̍X�V�������ŉ�]�̏��������Ă�֐�����邩�炠�܂肱��͂���Ȃ�����

	void	SetSpeed(float spd) { speed = spd; }

	//======================
	//�Q�b�^�[
	//======================

	//�����o�ϐ��̃Q�b�^�[
	D3DXVECTOR2		GetPosition() { return position; }								//���_�̎擾
	D3DXVECTOR2		GetScale() { return scale; }									//���A�����̃Q�b�^�[
	float			GetRotation() { return rotation;						 }		//��]�p�x�̃Q�b�^�[
	float			GetRadius() { return (scale.x + scale.y) * 0.5f; }				//�l�p���e�N�X�`���𒣂邱�Ƃ�O��ɂ��Ă邩��BoxTransform�����Ǔ����蔻���BC���Ƃ鎞�ɔ��a���K�v�ɂȂ邩��A�����`�ł͂Ȃ��ꍇ�ɕ��ƍ����̒��Ԃ��擾�ł���悤�ɂ��Ă����A�����ɒ[�ɍג�����̂��Ƃ͍l���ĂȂ�

	float			GetRadian() { return radian; }									//��]�Ɏg�����W�A���p�̎擾


	//�����̃Q�b�^�[
	D3DXVECTOR2		GetFront();														//LT,RT�̒��Ԓn�_�̂���������擾����֐��AUnity�̃p�N��
	D3DXVECTOR2		GetBack();														//LB,RB�̒��Ԓn�_�̂���������擾����֐��AUnity�̃p�N��
	D3DXVECTOR2		GetLeft();														//LT,LB�̒��Ԓn�_�̂���������擾����֐��AUnity�̃p�N��
	D3DXVECTOR2		GetRight();														//RT,RB�̒��Ԓn�_�̂���������擾����֐��AUnity�̃p�N��

	//4�ӂ̍��W���擾
	float			GetTopY();														//��ԏ�����Y
	float			GetBottomY();													//��ԑ傫��Y
	float			GetLeftX();														//��ԏ�����X
	float			GetRightX();													//��ԑ傫��X

	//4���_�̎擾		�}�b�v�`�b�v�̓����蔻����Ƃ�Ƃ��ɕK�{�A
	D3DXVECTOR2		GetLeftTopPosition();											//����̍��W�̃Q�b�^�[	��]���Ă����͍ł�������X�AY��D3DXVECTOR2�ϐ��Ɋi�[���ĕԋp
	D3DXVECTOR2		GetRightTopPosition();											//�E��̍��W�̃Q�b�^�[
	D3DXVECTOR2		GetLeftBottomPosition();										//�����̍��W�̃Q�b�^�[
	D3DXVECTOR2		GetRightBottomPosition();										//�E���̍��W�̃Q�b�^�[

	//�J�����O�ˑ���4���_�̎擾�@Z�̏������ɂȂ�悤�ɒ��g���l����
	//1----2
	//   �^
	// �^ 
	//3----4
	//�|���S���`�掞�ɖ��x���x�v�Z���ďo�͂���̌����������烁���o�ϐ��ɒǉ����邩�Y��ł�
	//�����o�ϐ��ɒǉ������烁������H�����A�ǉ����Ȃ������珈�����x���Ȃ邵
	D3DXVECTOR2		GetNo1Position() { return no1Position; }
	D3DXVECTOR2		GetNo2Position() { return no2Position; }
	D3DXVECTOR2		GetNo3Position() { return no3Position; }
	D3DXVECTOR2		GetNo4Position() { return no4Position; }

	//���_���璸�_�܂ł̋���
	float			GetVertex_CentorRange(){ return sqrtf(pow(scale.x * 0.5,2) + pow(scale.y * 0.5,2)); }

	//���̃g�����X�t�H�[���̌��_�ƈ����i�^�[�Q�b�g�́j��������p�x���擾����֐�
	float			GetTarget_CentorRadian(D3DXVECTOR2 target);

	//======================
	//�X�V����
	//======================

	//���S�����_�ɂ��ĉ�]����ꍇ�ƁA4���_�����_�ɂ��ĉ�]����ꍇ�Ƃŕʂ̊֐���p�ӂ��Ă�������
	//�����Z�b�^�[��Rotation�̃Z�b�^�[�����邩�炻��Ƃ̌��ˍ����͂܂��l���ĂȂ�

	//���S��]�̍X�V����
	//void UPDataRotation_C();							//���݂̊p�x���w�肵���p�x�ɕύX�������ꍇ�A��]�p�̃Z�b�^�[�ƕ��p���Ďg�p����?
	void UPDataRotation_C(float rotate);				//���݂̊p�x�������̒l�ɂ���
	void UPDataAddRotation_C(float rotate);				//���݂̊p�x�ɉ��Z���ĉ�]���������ꍇ�Ăяo��

	void UPDataRotation_LT(float rotate);				//����i1�̍��W�j�����_�ɉ�]������ꍇ�ɌĂ�
	void UPDataRotation_RT(float rotate);				//�E��i2�̍��W�j�����_�ɉ�]������ꍇ�ɌĂ�
	void UPDataRotation_LB(float rotate);				//�����i3�̍��W�j�����_�ɉ�]������ꍇ�ɌĂ�
	void UPDataRotation_RB(float rotate);				//�E���i4�̍��W�j�����_�ɉ�]������ꍇ�ɌĂ�

	//void UPDataAddRotation_LT(float rotate);			//����i1�̍��W�j�����_�ɉ��Z��]������ꍇ�ɌĂ�
	//void UPDataAddRotation_RT(float rotate);			//�E��i2�̍��W�j�����_�ɉ��Z��]������ꍇ�ɌĂ�
	//void UPDataAddRotation_LB(float rotate);			//�����i3�̍��W�j�����_�ɉ��Z��]������ꍇ�ɌĂ�
	//void UPDataAddRotation_RB(float rotate);			//�E���i4�̍��W�j�����_�ɉ��Z��]������ꍇ�ɌĂ�


	void UPDataMovePosition();							//�x���V�e�B�ƃX�s�[�h�����ۂ̈ړ����x�Ƃ��ă|�W�V�����ɔ��f

	void UPDataNumberPosition();						//�|���S���Ɏg���l�p�̍��W�����݂̉�]�p����X�V����֐�

	void UPDataOldData();								//�I�[���h�|�W�V�������X�V����֐��A��]�p���L�����Ȃ��Ƃ����Ȃ��C������

};

