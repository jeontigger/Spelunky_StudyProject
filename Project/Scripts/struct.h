#pragma once

#include <Engine/CKeyMgr.h>
struct PlayerKey {
public:
	KEY Jump;
	KEY MoveLeft;
	KEY MoveRight;
	KEY LookUp;
	KEY LookDown;
	KEY Attack;
	KEY Bomb;
	KEY Rope;

public:
	PlayerKey() {
		Jump = Z; MoveLeft = LEFT; MoveRight = RIGHT;
		LookUp = UP; LookDown = DOWN; Attack = X; Bomb = C; Rope = D;
	}
};

struct CharacterInfo {

	int Health;
	int Damage;
	float Speed;
	bool Dead;

public:
	CharacterInfo(): Health(3), Damage(1), Speed(2), Dead(false) {	}
};