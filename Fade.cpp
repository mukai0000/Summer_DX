#include "Fade.h"
#include "texture.h"
#include "sprite.h"

#define CIRCLE_FADE_MAX_RADIUS (900)

CircleFade::CircleFade(D3DXVECTOR2* player)
{
	SetTexture("data/TEXTURE/FADE/CircleFade.png", 1, 1, 1);
	m_FState = FADE_NONE;

	m_TargetP = player;
}

void CircleFade::Draw()
{
	if (m_FState != FADE_NONE) {
		//’†‰›‚ÌŠÛ
		DrawSprite(&m_TexData, m_TargetP, &m_Radius);
	}
}
