#pragma once

#include "collide.h"
#include "dx9render.h"
#include "model.h"

#define SR_MOVE 1
#define SR_STOPROTATE 2
#define SR_YROTATE 4

class MAST : public Entity
{
    struct MountData
    {
        NODE *pNode;
        entid_t shipEI;
        entid_t modelEI;
    } m_mount_param;
    bool bUse;
    bool bFallUnderWater;
    int wMoveCounter;
    VDX9RENDER *RenderService;
    COLLIDE *pCollide;
    bool bModel;
    entid_t model_id, oldmodel_id;
    entid_t ship_id;
    FILETIME ft_old;
    NODE *m_pMastNode;

  public:
    MAST();
    ~MAST();
    void SetDevice();
    bool Init();
    void Move();
    void Execute(uint32_t Delta_Time);
    void Realize(uint32_t Delta_Time);
    void ProcessStage(Stage stage, uint32_t delta) override
    {
        switch (stage)
        {
        case Stage::execute:
            Execute(delta);
            break;
        case Stage::realize:
            Realize(delta);
            break;
            /*case Stage::lost_render:
                LostRender(delta); break;
            case Stage::restore_render:
                RestoreRender(delta); break;*/
        }
    }

    bool CreateState(ENTITY_STATE_GEN *state_gen);
    bool LoadState(ENTITY_STATE *state);
    uint64_t ProcessMessage(MESSAGE &message);

  protected:
    void AllRelease();
    void Mount(entid_t modelEI, entid_t shipEI, NODE *mastNodePointer);
    void LoadIni();
    void doMove(uint32_t DeltaTime);
    int GetSlide(entid_t mod, CVECTOR &pbeg, CVECTOR &pend, CVECTOR &dp, CVECTOR &lrey, CVECTOR &rrey, float &angl);
    struct MASTMOVE
    {
        CVECTOR bp, ep;     // mast coordinates
        CVECTOR brey, erey; // rhea coordinates

        CVECTOR ang, dang, sdang;
        CVECTOR mov, dmov, sdmov;
    };
    MASTMOVE mm;
};

