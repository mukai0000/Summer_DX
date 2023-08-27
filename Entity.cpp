//================================
// Entity.cpp	Entity(�v���C���[��G�A�������U��
// �����@�C�l	2023/08/08
//================================

#include "Entity.h"


//===========================================
//			�}�N����`
//===========================================
#define POTENTIAL_MAX			(255)
#define UP_STATUS_POINT			(2)
#define INITIAL_STATUS_POINT	(5)
#define INITIAL_HP				(100)
#define INITIAL_MP				(50)
#define INITIAL_AMD				(0)

#define UP_HP					(10)
#define UP_MP					(5)
#define UP_ATK					(3)
#define UP_MAT					(2)
#define UP_DEF					(1)

Status::Status()
{
	m_BathStatus = { 1,1,1,1 };
	m_StatusPoint = INITIAL_STATUS_POINT + UP_STATUS_POINT * m_BathStatus.lv;
	UpdateStandardStatus();
}

void Status::AddLevel()
{
	m_BathStatus.lv++;						//lv�𑝂₷
	m_StatusPoint += UP_STATUS_POINT;		//�X�e�[�^�X�|�C���g�𑝂₷
}

void Status::AddPow()
{
	if (m_BathStatus.pow < POTENTIAL_MAX && m_StatusPoint > 0) {
		m_StatusPoint--;
		m_BathStatus.pow++;		//�ő�l��菬���������瑝�₷
	}
}

void Status::AddVit()
{
	if (m_BathStatus.vit < POTENTIAL_MAX && m_StatusPoint > 0)
	{
		m_StatusPoint--;
		m_BathStatus.vit++;		//�ő�l��菬���������瑝�₷
	}
}

void Status::AddMgc()
{
	if (m_BathStatus.mgc < POTENTIAL_MAX && m_StatusPoint > 0)
	{
		m_StatusPoint--;
		m_BathStatus.mgc++;		//�ő�l��菬���������瑝�₷
	}
}

void Status::AddHp(int add)
{
	if (m_NowStatus.hp + add > m_StandardStatus.hp)m_NowStatus.hp = m_StandardStatus.hp;
	else m_NowStatus.hp += add;
}

void Status::AddMp(int add)
{
	if (m_NowStatus.mp + add > m_StandardStatus.mp)m_NowStatus.mp = m_StandardStatus.mp;
	else m_NowStatus.mp += add;
}

void Status::AddAtk(int add)
{
	m_NowStatus.atk += add;
}

void Status::AddMat(int add)
{
	m_NowStatus.mat += add;
}

void Status::AddDef(int add)
{
	m_NowStatus.def += add;
}

void Status::UpdateStandardStatus()
{
	m_StandardStatus = {
		INITIAL_HP + UP_HP * m_BathStatus.vit,
		INITIAL_MP + UP_MP * m_BathStatus.mgc,
		INITIAL_AMD + UP_ATK * m_BathStatus.pow,
		INITIAL_AMD + UP_MAT * m_BathStatus.mgc,
		INITIAL_AMD + UP_DEF * m_BathStatus.vit
	};
}

void Status::UpdateStandardStatus(ENTITY_STATUS* addStatus)
{
	UpdateStandardStatus();		//��b�n�̒l�ɏ�����
	m_StandardStatus.hp = addStatus->hp;
	m_StandardStatus.mp = addStatus->mp;
	m_StandardStatus.atk = addStatus->atk;
	m_StandardStatus.mat = addStatus->mat;
	m_StandardStatus.def = addStatus->def;
}

Entity::Entity()
{
	m_Buff[BUFF_REGENE] = new Regene;
	m_Buff[BUFF_POISON] = new Poison;
	m_Buff[BUFF_STUN] = new Stun;		//�Ђт�@�V��
	m_Buff[BUFF_SLEEP] = new SLEEP;

	//�ǉ�
	m_CollisionSize = 0;
	m_Transform = { D3DXVECTOR2(0,0), D3DXVECTOR2(0,0), D3DXVECTOR2(0,0)};	

	m_Status =new Status;	
}

bool Entity::GetHitTrigger(Entity* target, COLLIDER_MODE mode)
{
	return false;
}

int Entity::GetDamage(int index)
{
	return 0;
}

void Entity::SetDamage(int damage)
{
}
