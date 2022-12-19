#ifndef LABS_GAMEINTERFACE_H
#define LABS_GAMEINTERFACE_H

#include "GameField.h"

class interface {
public:
    virtual void startGame(std::string) = 0;
};

class online_interface : public interface {
public:
    void startGame(std::string) override;
    void print_help();
    void print_game_field_informaton(gamefield &, int);
};

class offline_interface : public interface {
public:
    void startGame(std::string) override;
};



#endif
