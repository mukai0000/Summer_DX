#include "BoxTransform.h"
#include <math.h>

BoxTransform::BoxTransform()
{
	position = D3DXVECTOR2(0.0f, 0.0f);
	scale = D3DXVECTOR2(100.0f, 100.0f);
	rotation = 0.0f;
	VertexPositionInitialize();
};

BoxTransform::BoxTransform(D3DXVECTOR2 pos, D3DXVECTOR2 size, float rot) :position(pos), scale(size), rotation(rot)
{
	VertexPositionInitialize();
}

void BoxTransform::VertexPositionInitialize()
{
	//����
	float hulfWide = scale.x * 0.5f;
	float hulfHight = scale.y * 0.5f;

	//����̃|�W�V����
	no1Position.x = (-hulfWide) * cosf(GetRadian()) - (-hulfHight) * sinf(GetRadian());
	no1Position.y = (-hulfWide) * sinf(GetRadian()) + (-hulfHight) * cosf(GetRadian());

	//�E��̃|�W�V����
	no2Position.x = hulfWide * cosf(GetRadian()) - (-hulfHight) * sinf(GetRadian());
	no2Position.y = hulfWide * sinf(GetRadian()) + (-hulfHight) * cosf(GetRadian());

	//�����̃|�W�V����
	no3Position.x = (-hulfWide) * cosf(GetRadian()) - hulfHight * sinf(GetRadian());
	no3Position.y = (-hulfWide) * sinf(GetRadian()) + hulfHight * cosf(GetRadian());

	//�E���̃|�W�V����
	no4Position.x = hulfWide * cosf(GetRadian()) - hulfHight * sinf(GetRadian());
	no4Position.y = hulfWide * sinf(GetRadian()) + hulfHight * cosf(GetRadian());

}

D3DXVECTOR2 BoxTransform::GetFront()
{
	return D3DXVECTOR2(cosf(radian - pi * 0.5f), sinf(radian - pi * 0.5f));
}

D3DXVECTOR2 BoxTransform::GetBack()
{
	return D3DXVECTOR2(cosf(radian + pi * 0.5f), sinf(radian + pi * 0.5f));
}

D3DXVECTOR2 BoxTransform::GetLeft()
{
	return D3DXVECTOR2(cosf(radian + pi), sinf(radian + pi));
}

D3DXVECTOR2 BoxTransform::GetRight()
{
	return D3DXVECTOR2(cosf(radian), sinf(radian));
}

float BoxTransform::GetTopY()
{
	float y = no1Position.y;
	if (y > no2Position.y)y = no2Position.y;
	if (y > no3Position.y)y = no3Position.y;
	if (y > no4Position.y)y = no4Position.y;
	return y;
}

float BoxTransform::GetBottomY()
{
	float y = no1Position.y;
	if (y < no2Position.y)y = no2Position.y;
	if (y < no3Position.y)y = no3Position.y;
	if (y < no4Position.y)y = no4Position.y;
	return y;
}

float BoxTransform::GetLeftX()
{
	float x = no1Position.x;
	if (x > no2Position.x)x = no2Position.x;
	if (x > no3Position.x)x = no3Position.x;
	if (x > no4Position.x)x = no4Position.x;
	return x;
}

float BoxTransform::GetRightX()
{
	float x = no1Position.x;
	if (x < no2Position.x)x = no2Position.x;
	if (x < no3Position.x)x = no3Position.x;
	if (x < no4Position.x)x = no4Position.x;
	return x;
}

D3DXVECTOR2 BoxTransform::GetLeftTopPosition()
{
	return D3DXVECTOR2(GetLeftX(), GetTopY());
}

D3DXVECTOR2 BoxTransform::GetRightTopPosition()
{
	return D3DXVECTOR2(GetRightX(), GetTopY());
}

D3DXVECTOR2 BoxTransform::GetLeftBottomPosition()
{
	return D3DXVECTOR2(GetLeftX(), GetBottomY());
}

D3DXVECTOR2 BoxTransform::GetRightBottomPosition()
{
	return D3DXVECTOR2(GetRightX(), GetBottomY());
}

float BoxTransform::GetTarget_CentorRadian(D3DXVECTOR2 target)
{
	return  atan2(position.y - target.y, position.x - target.x);
}

void BoxTransform::UPDataRotation_C(float rotate)
{
	rotation = rotate;

	UPDataNumberPosition();
}

void BoxTransform::UPDataAddRotation_C(float rotate)
{
	rotation += rotate;

	UPDataNumberPosition();
}

void BoxTransform::UPDataRotation_LT(float rotate)
{
	//���_�̉�]�p���X�V
	rotation += rotate;

	//����̍��W�ƒ��S�̍��W�̍�������p�x���擾���āA���̊p�x�Ɏ󂯎�����p�x�𑫂����l
	//�����`���ג����Ȃ�����ǂ�ǂ�p�x���ς�邩�炻�̕ς��p�x���擾����
	float rot = GetTarget_CentorRadian(no1Position) + RAD(rotate);
	
	//rot��
	SetPosition(
		cos(rot)* GetVertex_CentorRange(),
		sin(rot)* GetVertex_CentorRange()
	);

	UPDataNumberPosition();
}

void BoxTransform::UPDataRotation_RT(float rotate)
{
	rotation += rotate;
	float rot = GetTarget_CentorRadian(no2Position) + RAD(rotate);

	//rot��
	SetPosition(
		cos(rot) * GetVertex_CentorRange(),
		sin(rot) * GetVertex_CentorRange()
	);

	UPDataNumberPosition();
}

void BoxTransform::UPDataRotation_LB(float rotate)
{
	rotation += rotate;
	float rot = GetTarget_CentorRadian(no3Position) + RAD(rotate);

	//rot��
	SetPosition(
		cos(rot) * GetVertex_CentorRange(),
		sin(rot) * GetVertex_CentorRange()
	);

	UPDataNumberPosition();
}

void BoxTransform::UPDataRotation_RB(float rotate)
{
	rotation += rotate;
	float rot = GetTarget_CentorRadian(no4Position) + RAD(rotate);

	//rot��
	SetPosition(
		cos(rot) * GetVertex_CentorRange(),
		sin(rot) * GetVertex_CentorRange()
	);

	UPDataNumberPosition();
}

void BoxTransform::UPDataMovePosition()
{
	D3DXVECTOR2 move = velocity * speed;

	position += move;			//���_���ړ�
	no1Position += move;		//������ړ�
	no2Position += move;		//�E����ړ�
	no3Position += move;		//�������ړ�
	no4Position += move;		//�E�����ړ�
}

void BoxTransform::UPDataNumberPosition()
{
	float hw = scale.x * 0.5;
	float hh = scale.y * 0.5;

	no1Position = D3DXVECTOR2(
		(-hw) * cosf(radian) - (-hh) * sinf(radian) + position.x,
		(-hw) * sinf(radian) + (-hh) * cosf(radian) + position.y
	);
	no2Position = D3DXVECTOR2(
		(hw) * cosf(radian) - (-hh) * sinf(radian) + position.x,
		(hw) * sinf(radian) + (-hh) * cosf(radian) + position.y
	);
	no3Position = D3DXVECTOR2(
		(-hw) * cosf(radian) - (hh) * sinf(radian) + position.x,
		(-hw) * sinf(radian) + (hh) * cosf(radian) + position.y
	);
	no4Position = D3DXVECTOR2(
		(hw) * cosf(radian) - (hh) * sinf(radian) + position.x,
		(hw) * sinf(radian) + (hh) * cosf(radian) + position.y
	);
}
