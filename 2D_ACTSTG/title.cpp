//=============================================
//
//3DTemplate[title.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "title.h"
#include "title_screen.h"
#include "fade.h"
#include "manager.h"
#include "sound.h"

//=============================================
//�R���X�g���N�^
//=============================================
CTitle::CTitle()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CTitle::~CTitle()
{
}

//=============================================
//������
//=============================================
HRESULT CTitle::Init()
{
    CTitle_Screen*pTitle_Screen = CTitle_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f));
    CSound*pSound = CManager::GetSound();

    pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM_TITLE);
    return S_OK;
}

//=============================================
//�I��
//=============================================
void CTitle::Uninit()
{
    CSound* pSound = CManager::GetSound();
    //�T�E���h�̒�~
    pSound->StopSound();
    CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CTitle::Update()
{
    CObject::UpdateAll();
    CInputKeyboard* pKeyboard = CManager::GetKeyboard();

    //CFade*pFade= CFade::GetFade();
    if (pKeyboard->GetTrigger(DIK_RETURN))
    {
        CManager::SetMode(CScene::MODE::MODE_GAME);
    }
}

//=============================================
//�`��
//=============================================
void CTitle::Draw()
{
}
