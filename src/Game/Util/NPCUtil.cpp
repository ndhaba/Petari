#include "Game/Util.hpp"
#include "Game/NPC/NPCActor.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/LodCtrl.hpp"
#include "JSystem/JGeometry/TVec.hpp"
#include <cstdio>

// lbl_805E1B60
// /ObjectData/%s.arc SwimWait WatchTurnSwim Watch WatchTurn 

namespace MR {
    void followRailPose(NPCActor*, f32, f32) NO_INLINE {}
    void followRailPoseOnGround(NPCActor*, const LiveActor*, f32) NO_INLINE {}

    void initDefaultPose(NPCActor* actor, const JMapInfoIter& info){
        MR::initDefaultPos(actor, info);
        MR::makeQuatRotateDegree((JGeometry::TQuat4<f32>*) &actor->_A0, actor->mRotation);
        actor->setInitPose();
        actor->setInitPose();
    }

    void invalidateLodCtrl(const NPCActor* actor){
        actor->mLodCtrl->invalidate();
    }

    bool isActionContinuous(const LiveActor* actor){
        return !MR::getBckCtrl(actor)->mLoopMode && !MR::isBckStopped(actor);
    }

    bool isActionLoopedOrStopped(const LiveActor* actor){
        return !MR::getBckCtrl(actor)->mLoopMode ? MR::isBckStopped(actor) : MR::isBckLooped(actor);
    }
    
    bool isNPCItemFileExist(const char * npcFile){
        char buffer[256];
        snprintf(buffer, 256, "/ObjectData/%s.arc", npcFile);
        return MR::isFileExist(buffer, false);
    }

    void setNPCActorPos(NPCActor* actor, const JGeometry::TVec3<f32>& vector){
        actor->mPosition.set<f32>(vector);
        MR::resetPosition(actor);
        MR::onCalcShadowOneTimeAll(actor);
    }

    void setDefaultPose(NPCActor* actor){
        actor->setToDefault();
    }

    void startMoveAction(NPCActor* actor){
        if(!MR::isExistRail(actor)){
            return;
        }
        MR::adjustmentRailCoordSpeed(actor, actor->_10C, actor->_110);
        MR::moveRailRider(actor);
        if(actor->_124){
            MR::followRailPoseOnGround(actor, actor, actor->_114);
        } else {
            MR::followRailPose(actor, actor->_114, actor->_114);
        }
        if(MR::isRailReachedGoal(actor)){
            MR::reverseRailDirection(actor);
        }
    }
}
