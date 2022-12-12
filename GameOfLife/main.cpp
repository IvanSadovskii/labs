#include "GameField.h"

int main() {
    gamefield f(5,10);
    f.set_life(2,0);
    f.set_life(2,1);
    f.set_life(2,2);
    f.set_life(1,2);
    f.set_life(0,1);


    do {
        f.print_field();
        std::cout<<"\n";
        f.make_iteration();
    } while(!f.is_field_empty());

    return 0;
}
