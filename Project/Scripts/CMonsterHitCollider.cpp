#include "pch.h"
#include "CMonsterHitCollider.h"

CMonsterHitCollider::CMonsterHitCollider()
	: CDetectCollider((UINT)SCRIPT_TYPE::MONSTERSCRIPT)
{
	
}

CMonsterHitCollider::~CMonsterHitCollider()
{
}

#include "CPlayerScript.h"
#include "CGroundCollider.h"

void CMonsterHitCollider::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CDetectCollider::BeginOverlap(_Collider, _OtherObj, _OtherCollider);

	CGroundCollider* groundScript = _OtherObj->GetScript<CGroundCollider>();
	if (groundScript) {
		CPlayerScript* playerScript = groundScript->GetParent()->GetScript<CPlayerScript>();
		if (playerScript) {
			///////
			auto objmat = groundScript->Collider2D()->GetColliderWorldMat();
			auto tilemat = _Collider->GetColliderWorldMat();

			Vec3 ObjColPos = objmat.Pos();
			Vec3 ObjColScale = objmat.Scale();
			Vec3 TileColPos = tilemat.Pos();
			Vec3 TileColScale = tilemat.Scale();

			float objUnderY = ObjColPos.y - ObjColScale.y / 2.f;
			float velY = playerScript->GetVelocity().y;
			float prevObjUnderY = objUnderY - velY * DT;
			float TileTopY = TileColPos.y + TileColScale.y / 2.f;
			float tileJudgeY = TileColPos.y + TileColScale.y / 2.f * 0.7f;

			if (velY < 0 && prevObjUnderY - tileJudgeY > 0) {
				playerScript->SetGround(true);
				playerScript->Jump();
				GetParent()->GetScript<CCharacterScript>()->Hit(playerScript->GetDamage());
			}
		}
	}
}
