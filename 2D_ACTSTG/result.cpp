//=============================================
//
//3DTemplate[result.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "result.h"
#include "result_screen.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CResult::CResult()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CResult::~CResult()
{
}

//=============================================
//������
//=============================================
HRESULT CResult::Init()
{
    CResult_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f, 0.0f));
    CSound* pSound = CManager::GetSound();

    pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM_RESULT);
    return S_OK;
}

//=============================================
//�I��
//=============================================
void CResult::Uninit()
{
    CSound* pSound = CManager::GetSound();
    //�T�E���h�̒�~
    pSound->StopSound();
    CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CResult::Update()
{
    CObject::UpdateAll();
    CInputKeyboard* pKeyboard = CManager::GetKeyboard();
    if (pKeyboard->GetTrigger(DIK_RETURN))
    {
        CManager::SetMode(CScene::MODE::MODE_TITLE);
    }
}

//=============================================
//�`��
//=============================================
void CResult::Draw()
{
}
