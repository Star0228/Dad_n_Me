//
// Created by 16579 on 2024/7/9.
//

#include "View_draw.h"
void View_draw::Reset_idx_pl_atk(){
    Idx_Player_attack = 0;
}

int View_draw::Get_Idx_Common_Hit(){
    return Idx_Common_Hit;
}

Animation* View_draw::Get_anim_Common_hit(){
    return anim_Common_hit;
}

void View_draw::draw(Player& player,QPainter& painter, int delta){
//    if(player.GetHitTimer()==0){
//        Idx_Player_attack = 0;
//    }
    player.AddTimer(delta);
    if (Idx_Player_attack == 20)
    {
        player.Change_Isattack(false);
        Idx_Player_attack = 0;
    }

    //首先判定是否正在攻击
    if (Idx_Player_attack < 20 && player.GetIsAttack())
    {
        if (player.GetHitTimer() >= anim_Player_attack->GetInterval()) {
            Idx_Player_attack = (Idx_Player_attack + 1) % anim_Player_attack->GetFrameCount();
            player.ResetTimer();
        }
        anim_Player_attack->Display(painter, player.getPosition().x, player.getPosition().y - 70,
                                    Idx_Player_attack, player.GetFacingRight()); // 调整了y方向参数来保证图片显示位置的一致性
    }
    else
    {
        if (player.GetHitTimer() >= anim_Player_run->GetInterval()) {
            Idx_Player_run = (Idx_Player_run + 1) % anim_Player_run->GetFrameCount();
            player.ResetTimer();
        }
        anim_Player_run->Display(painter, player.getPosition().x, player.getPosition().y,
                                 Idx_Player_run, player.GetFacingRight());
    }
}
void View_draw::draw(Common& common,QPainter& painter, int delta,int playerSignal = 1){
    common.AddTimer(delta);
    if (playerSignal > 0)
    {
        common.Change_IsHit(true);
    }
    if (common.GetIsHit()) {
        if (common.GetTimer()>= anim_Common_hit->GetInterval()) {
            Idx_Common_Hit = (Idx_Common_Hit + 1) % anim_Common_hit->GetFrameCount();
            common.ResetTimer();
        }
        anim_Common_hit->Display(painter, common.getPosition().x, common.getPosition().y - 100, common.GetTimer(),
                                 Idx_Common_Hit);
    } else {
        if (common.GetTimer() >= anim_Common_run->GetInterval()) {
            Idx_Common_Run = (Idx_Common_Run + 1) % anim_Common_run->GetFrameCount();
            common.ResetTimer();
        }
        anim_Common_run->Display(painter, common.getPosition().x, common.getPosition().y, common.GetTimer(),
                                 Idx_Common_Run);
    }
}
void View_draw::draw(Boss& boss,Player& player,QPainter& painter, int delta){
    // 计算boss和player的距离
    Point position = boss.Getposition();
    float dx = position.x - player.getPosition().x;
    float dy = position.y - player.getPosition().y;
    float dist = std::sqrt(dx*dx + dy*dy);

    if (Idx_Boss_Hit == 14)
    {
        boss.Change_IsHit(false);
    }

    // 首先判断boss是否收到攻击
    boss.AddTimer(delta);
    if (boss.GetIsHit() && Idx_Boss_Hit > 0)
    {
        if (boss.GetIsHit() >= anim_Boss_hit->GetInterval()) {
            Idx_Boss_Hit = (Idx_Boss_Hit + 1) % anim_Boss_hit->GetFrameCount();
            boss.ResetTimer();
        }
        anim_Boss_hit->Display(painter, position.x, position.y - 20,
                               Idx_Boss_Hit, boss.GetFacingRight());
    }
    else if (dist < 120)
    {
        if (boss.GetTimer() >= anim_Boss_attack->GetInterval()) {
            Idx_Boss_Attack = (Idx_Boss_Attack + 1) % anim_Boss_attack->GetFrameCount();
            boss.ResetTimer();
        }
        anim_Boss_attack->Display(painter, position.x, position.y,
                                  Idx_Boss_Attack, boss.GetFacingRight());
    }
    else
    {
        if (boss.GetTimer() >= anim_Boss_run->GetInterval()) {
            Idx_Boss_Run = (Idx_Boss_Run + 1) % anim_Boss_run->GetFrameCount();
            boss.ResetTimer();
        }
        anim_Boss_run->Display(painter, position.x, position.y,
                               Idx_Boss_Run, boss.GetFacingRight());
    }
}
