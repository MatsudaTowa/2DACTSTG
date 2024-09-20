//=============================================
//
//3DTemplate[result.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "result.h"
#include "result_screen.h"
#include "manager.h"
#include "evaluation.h"

//�X�R�A�ݒ�
CScore* CResult::m_pScore = nullptr;

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

    //�X�R�A������
    if (m_pScore == nullptr)
    {
        m_pScore = new CScore;

        m_pScore->Init();
    }
    int nScore = m_pScore->GetScore();
    m_pScore->AddScore(nScore);

    //�X�R�A�ɂ���ĕς���
    {
        CEvaluation::Create(D3DXVECTOR3(200.0f,480.0f,0.0f),D3DXVECTOR2(200.0f,200.0f),CEvaluation::EVALUATION::EVALUATION_C);
    }
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
    if (m_pScore != nullptr)
    {
        m_pScore->Uninit();
        m_pScore = nullptr;
    }
    CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CResult::Update()
{
    CObject::UpdateAll();
    if (m_pScore != nullptr)
    {
        m_pScore->Update();
    }
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
