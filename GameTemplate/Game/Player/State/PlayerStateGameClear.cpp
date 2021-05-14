#include "pch.h"
#include "PlayerStateGameClear.h"
#include "Player/HuntedSprite.h"

void PlayerStateGameClear::Update() {
	if (m_HuntedSprite == nullptr) {
		m_HuntedSprite = NewGO<HuntedSprite>(0);
	}
}