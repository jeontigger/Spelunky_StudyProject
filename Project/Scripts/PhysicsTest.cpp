#include "pch.h"
#include "PhysicsTest.h"

#include <Box2D/box2d.h>

#include <Engine/CGameObject.h>
#include <Engine/CTransform.h>
#include <Engine/CCamera.h>
#include <Engine/CCollider2D.h>
#include <Engine/CCollisionMgr.h>

#include <Scripts/CBackgroundScript.h>
#include <Scripts/CCameraMovement.h>

void PhysicsTest::begin()
{
	CLevel::begin();

	wstring path = CPathMgr::GetContentPath();
	path += L"..\\log";
	path += L"\\log.txt";
	m_file.open(path);

	CCollisionMgr::GetInst()->LayerCheck(CameraLayer, BackgroundLayer);

}

void PhysicsTest::tick()
{
	CLevel::tick();

	//b2Vec2 position = m_body->GetPosition();
	//m_obj->Transform()->SetRelativePos(Vec3(position.x, position.y, m_obj->Transform()->GetRelativePos().z));
	/*if (m_file.is_open()) {
		m_file << position.x << " " << position.y << " " << angle << endl;
	}*/

}

PhysicsTest::PhysicsTest()
{

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.f, -10.f);

	b2Body* groundBody = CCollisionMgr::GetInst()->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.f, 10.f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0.0f, 400.0f);
	//m_body = CCollisionMgr::GetInst()->CreateBody(&bodyDef);

	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(1.0f, 1.0f);

	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &dynamicBox;
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 0.3f;

	//m_body->CreateFixture(&fixtureDef);

	//Main Camera Object 积己
	m_MainCamera = new CGameObject;
	m_MainCamera->SetName(L"MainCamera");
	m_MainCamera->AddComponent(new CTransform);
	m_MainCamera->AddComponent(new CCamera);
	m_MainCamera->AddComponent(new CCollider2D);
	m_MainCamera->AddComponent(new CCameraMovement);


	m_MainCamera->Transform()->SetRelativePos(Vec3(0, 0, 0.f));
	m_MainCamera->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	m_MainCamera->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));

	m_MainCamera->Collider2D()->SetOffsetScale(Vec2(TileBlockScaleX * 1.5, TileBlockScaleY + TileScaleY));

	m_MainCamera->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	m_MainCamera->Camera()->SetCameraPriority(0);
	m_MainCamera->Camera()->LayerCheckAll();
	m_MainCamera->Camera()->LayerCheck(31, false);

	AddObject(m_MainCamera, CameraLayer);

	// Backgruond Object 积己
	m_obj = CAssetMgr::GetInst()->Load<CPrefab>(TitleBackgroundPrefKey, TitleBackgroundPrefKey)->Instantiate();
	m_obj->Animator2D()->Play(AnimTitleBackground);
	m_obj->Transform()->SetRelativePos(Vec3(0, 1000, 0));
	AddObject(m_obj, BackgroundLayer);

	// 傈开 堡盔 眠啊
	CGameObject* pLight = new CGameObject;
	pLight->SetName(L"Directional Light");
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetAmbient(Vec3(1.f, 1.f, 1.f));
	AddObject(pLight, LightLayer);



}

PhysicsTest::~PhysicsTest()
{
}
