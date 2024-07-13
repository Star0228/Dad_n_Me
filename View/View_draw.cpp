//
// Created by 16579 on 2024/7/9.
//
#include "Animation.h"
#include "View_draw.h"
void View_draw::Reset_idx_pl_atk(){
    Idx_Player_attack = 0;
}

int* View_draw::Get_Idx_Common_Hit(){
    return Idx_Common_Hit;
}

Animation* View_draw::Get_anim_Common_hit(){
    return anim_Common_hit;
}

void View_draw::draw(Player& player,QPainter& painter, int delta){
    player.AddTimer(delta);
    if (Idx_Player_attack == 19 )
    {
        player.Change_Isattack(false);
        Idx_Player_attack = 0;
    }

    //首先判定是否正在攻击
    if (Idx_Player_attack < 20 && player.GetIsAttack())
    {
        if (player.GetHitTimer() >= anim_Player_attack->GetInterval() - 10) {
            Idx_Player_attack = (Idx_Player_attack + 1) % anim_Player_attack->GetFrameCount();
            player.ResetTimer();
        }
        anim_Player_attack->Display(painter, player.getPosition().x, player.getPosition().y - 70,
                                    Idx_Player_attack, player.GetFacingRight()); // 调整了y方向参数来保证图片显示位置的一致性
    }
    else if(player.getIsMove())
    {
        if (player.GetHitTimer() >= anim_Player_run->GetInterval()) {
            Idx_Player_run = (Idx_Player_run + 1) % anim_Player_run->GetFrameCount();
            player.ResetTimer();
        }
        anim_Player_run->Display(painter, player.getPosition().x, player.getPosition().y,
                                 Idx_Player_run, player.GetFacingRight());
    }
    else{
        if (player.GetHitTimer() >= anim_Player_stand->GetInterval()) {
            Idx_Player_stand = (Idx_Player_stand+ 1) % anim_Player_stand->GetFrameCount();
            player.ResetTimer();
        }
        anim_Player_stand->Display(painter, player.getPosition().x, player.getPosition().y,
                                 Idx_Player_stand, player.GetFacingRight());
    }
}

//bondNum 表示map中绑定的下标
void View_draw::draw(int bondNum, Simple& simple, QPainter& painter, int delta, int playerSignal = 0){
    simple.AddTimer(delta);
    if (simple.GetIsHit()) {
        if (simple.GetTimer() >= anim_Common_hit->GetInterval()) {
            Idx_Common_Hit[bondNum] = (Idx_Common_Hit[bondNum] + 1) % anim_Common_hit->GetFrameCount();
            simple.ResetTimer();
        }
        anim_Common_hit->Display(painter, simple.getPosition().x, simple.getPosition().y - 100,
                                 Idx_Common_Hit[bondNum]);
    } else {
        if (simple.GetTimer() >= anim_Common_run->GetInterval()) {
            Idx_Common_Run[bondNum] = (Idx_Common_Run[bondNum] + 1) % anim_Common_run->GetFrameCount();
            simple.ResetTimer();
        }
        anim_Common_run->Display(painter, simple.getPosition().x, simple.getPosition().y,
                                 Idx_Common_Run[bondNum]);
    }
}
void View_draw::draw(Boss& boss,Player& player,Background& background,QPainter& painter, int delta){
    // 计算boss和player的距离
    Point position = boss.Getposition();
    float dx = position.x - player.getPosition().x;
    float dy = position.y - player.getPosition().y;
    float dist = std::sqrt(dx*dx + dy*dy);

    if (Idx_Boss_Hit == 13)
    {
        boss.Change_IsHit(false);
        Idx_Boss_Hit = 0;
    }

    if (Idx_Boss_Attack != 5)
    {
        boss.isAttacking = false;
    }

    if (Idx_Boss_Attack == 5 && dist < 120)
    {
        boss.attack(background);
    }

    // 首先判断boss是否收到攻击
    boss.AddTimer(delta);
    if (boss.GetIsHit())
    {
        boss.isAttacking = false;
        if (boss.GetTimer() >= anim_Boss_hit->GetInterval() - 10) {
            Idx_Boss_Hit = (Idx_Boss_Hit + 1) % anim_Boss_hit->GetFrameCount();
            boss.ResetTimer();
        }
        anim_Boss_hit->Display(painter, position.x, position.y - 20,
                               Idx_Boss_Hit, boss.GetFacingRight());
    }
    else if (dist < 120 )
    {
        if (boss.GetTimer() >= anim_Boss_attack->GetInterval()) {
            Idx_Boss_Attack = (Idx_Boss_Attack + 1) % anim_Boss_attack->GetFrameCount();
            boss.ResetTimer();
        }
        anim_Boss_attack->Display(painter, position.x, position.y,
                                  Idx_Boss_Attack, !boss.GetFacingRight());
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

void View_draw::draw(Background& background,QPainter *painter, const QRectF &rect, int gameState) {
    QVector<QImage> obstacleImages;   // 障碍物图片
    std::vector<QPoint> obPositions;    // 障碍物位置
    QVector<QImage> backgroundImages;
    std::vector<QPoint> bgPositions;    // 障碍物位置
    // 添加障碍物图片和位置
    obstacleImages.append(obstacles);
    obPositions.push_back(QPoint(50, 50));

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    for (int j = 1; j < 3; j++) {
        for (int i = 0; i * (grandPic.width() - 10) < screenGeometry.width(); i++) {
            backgroundImages.append(grandPic);
            bgPositions.push_back(
                    QPoint(i * (grandPic.width() - 10), screenGeometry.height() - j * (grandPic.height() - 20)));
        }
    }


    // 绘制背景颜色
    painter->fillRect(rect, background.getBgcolor());

    for (const auto &pos: bgPositions) {
        int index = &pos - &bgPositions[0]; // 计算当前位置的索引
        painter->drawImage(pos, backgroundImages[index]);
    }

    if(gameState == 1){
        painter->drawImage(600,400,ResourceManager::getInstance().getImage("../resource/background/win.png"));
    }else if(gameState ==2){
        painter->drawImage(600,400,ResourceManager::getInstance().getImage("../resource/background/gameover.png"));
    }

    // 绘制障碍物
    for (const auto &pos: obPositions) {
        int index = &pos - &obPositions[0]; // 计算当前位置的索引
        painter->drawImage(pos, obstacleImages[index]);
    }

    // 绘制血条和精力条
    QPen borderPen(Qt::black); // 设置边框颜色为黑色
    borderPen.setWidth(3);     // 设置边框宽度为3个像素，可以根据需要调整粗细
    borderPen.setStyle(Qt::SolidLine); // 设置边框线条样式为实线
    painter->setPen(borderPen);

    // 绘制血条边框
    QRectF healthRectPlayer = background.getHealthRectPlayer();
    QRectF healthRectBoss = background.getHealthRectBoss();
    QRectF patienceRectPlayer = background.getPatienceRectPlayer();
    QRectF patienceRectBoss = background.getPatienceRectBoss();

    float health_Player = background.getPlayerHealth();
    float patience_Player = background.getPlayerPatience();
    float health_Boss = background.getBossHealth();
    float patience_Boss = background.getBossPatience();

    painter->drawRect(healthRectPlayer);
    painter->drawRect(healthRectBoss);

    // 绘制血条内部（红色部分）
    QRectF innerRect = healthRectPlayer.adjusted(3, 3, -3, -3); // 调整内部矩形，留出边框宽度的空间
    healthRectPlayer = QRectF(innerRect.x(), innerRect.y(),
                                     health_Player > 0 ? innerRect.width() * health_Player : 0, innerRect.height());
    painter->fillRect(healthRectPlayer, Qt::red);

    innerRect = healthRectBoss.adjusted(3, 3, -3, -3); //调整内部矩形，留出边框宽度的空间
    healthRectBoss = QRectF(innerRect.x() + innerRect.width() * (1 - health_Boss), innerRect.y(),
                                   health_Boss > 0 ? innerRect.width() * health_Boss : 0, innerRect.height());
    painter->fillRect(healthRectBoss, Qt::red);

    painter->drawRect(patienceRectPlayer);
    painter->drawRect(patienceRectBoss);
    //绘制绿色精力条
    innerRect = patienceRectPlayer.adjusted(3, 3, -3, -3); //调整内部矩形，留出边框宽度的空间
    patienceRectPlayer = QRectF(innerRect.x(), innerRect.y(), innerRect.width() * patience_Player,
                                       innerRect.height());
    painter->fillRect(patienceRectPlayer, Qt::green);

    innerRect = patienceRectBoss.adjusted(3, 3, -3, -3); //调整内部矩形，留出边框宽度的空间
    patienceRectBoss = QRectF(innerRect.x() + innerRect.width() * (1 - patience_Boss), innerRect.y(),
                                     innerRect.width() * patience_Boss, innerRect.height());
    painter->fillRect(patienceRectBoss, Qt::green);
}