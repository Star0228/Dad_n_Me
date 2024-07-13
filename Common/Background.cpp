//
// Created by 16579 on 2024/7/9.
//

#include "Background.h"
void Background::reset() {
    health_Player = 1.0;
    patience_Player = 1.0;
    health_Boss = 1.0;
    patience_Boss = 1.0;
}

float Background::getPlayerHealth(){
    return health_Player;
}

float Background::getBossHealth(){
    return health_Boss;
}

float Background::getPlayerPatience(){
    return patience_Player;
}

float Background::getBossPatience(){
    return patience_Boss;
}

QColor Background::getBgcolor(){
    return backgroundColor;
}

QRectF Background::getHealthRectPlayer(){
    return healthRectPlayer;
}
QRectF Background::getHealthRectBoss(){
    return healthRectBoss;
}
QRectF Background::getPatienceRectPlayer(){
    return patienceRectPlayer;
}
QRectF Background::getPatienceRectBoss(){
    return patienceRectBoss;
}

void Background::addObstacles(QVector<QRect>* obstacles) {
    obstacles->append(QRect(50,-80, 473,372));
}