#ifndef LABS_GAMECONSOLE_H
#define LABS_GAMECONSOLE_H

#include "GameInterface.h"
namespace game {
    enum modes {
        OFFLINE = 0,
        ONLINE = 1
    };

    class console {
    public:
        void choose_mod();

        void launch_programm(interface &);
    };
}

#endif
