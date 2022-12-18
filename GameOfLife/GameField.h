#pragma once
#include "Univerese.h"

#ifndef LABS_GAMEFIELD_H
#define LABS_GAMEFIELD_H

#include <iostream>
#include <vector>
using namespace std;

const bool ALIVE = true;
const bool DEAD = false;

class gamefield : public universe {
public:
    gamefield(std::ifstream &);
    ~gamefield();

    void print_field();

    void set_life(int, int);

    int coord_mod(int, int);

    int neighbors_count(int, int);

    void make_iteration();

    bool is_field_empty();

    void tick (int);





private:
    //int length;
    //int width;

     //
    vector<vector<int>> neighbors;
    vector<vector<bool>> cur_field;

};

#endif
