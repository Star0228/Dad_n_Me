//
// Created by 16579 on 2024/7/3.
//

#ifndef DAD_N_ME_PLAYER_H
#define DAD_N_ME_PLAYER_H


enum enum_state{
    walk_r = 0
};
class Player{
private:
    int pos_x = 0;
    int pos_y = 0;
    enum_state state = walk_r;
public:
    const int player_walk_r_sum = 11;
    void show (int& frame);
};



#endif //DAD_N_ME_PLAYER_H
