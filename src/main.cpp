#include <bn_core.h>
#include <bn_backdrop.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>
#include <bn_random.h>
#include <bn_vector.h>

#include "bn_sprite_items_dot.h"

static constexpr int HALF_SCREEN_WIDTH = bn::display::width() / 2;
static constexpr int HALF_SCREEN_HEIGHT = bn::display::height() / 2; 

static constexpr bn::fixed MIN_X = -HALF_SCREEN_WIDTH;
static constexpr bn::fixed MAX_X = HALF_SCREEN_WIDTH;
static constexpr bn::fixed MIN_Y = -HALF_SCREEN_HEIGHT;
static constexpr bn::fixed MAX_Y = HALF_SCREEN_HEIGHT;

static constexpr bn::fixed MIN_DX = -2;
static constexpr bn::fixed MAX_DX = 2;
static constexpr bn::fixed MIN_DY = -2;
static constexpr bn::fixed MAX_DY = 2;

class Bouncer {
    public:
        bn::sprite_ptr spr = bn::sprite_items::dot.create_sprite();
        bn::fixed dx;
        bn::fixed dy;

        void update() {
            bn::fixed x = spr.x();
            bn::fixed y = spr.y();

            x += dx;
            y += dy;

            if(x > MAX_X) {
                x = MAX_X;
                dx *=-1;
            }
            if(x < MIN_X) {
                x = MIN_X;
                dx *= -1;
            }

            if(y > MAX_Y) {
                y = MAX_Y;
                dy *= -1;
            }
            if(y < MIN_Y) {
                y = MIN_Y;
                dy *= -1;
            }

            spr.set_x(x);
            spr.set_y(y);
        }
};


int main() {
    bn::core::init();

    bn::random rng = bn::random();

    // bn::fixed starting_x = rng.get_fixed(MIN_X, MAX_X);
    // bn::fixed starting_y = rng.get_fixed(MIN_Y, MAX_Y);

    //bn::sprite_ptr bouncer = bn::sprite_items::dot.create_sprite(starting_x, starting_y);

    // bn::fixed dx = rng.get_fixed(MIN_DX, MAX_DX);
    // bn::fixed dy = rng.get_fixed(MIN_DY, MAX_DY);

    // bn::vector<bn::sprite_ptr, 20> bouncers = {};
    // bn::vector<bn::fixed, 20> dxs = {};
    // bn::vector<bn::fixed, 20> dys = {};

    

    bn::vector<Bouncer, 20> bouncers = {};


    while(true) {

        if(bn::keypad::a_pressed()) {
            Bouncer b = Bouncer();
            b.dx = rng.get_fixed(MIN_DX, MAX_DX);
            b.dy = rng.get_fixed(MIN_DY, MAX_DY);
            bouncers.push_back(b);
        }

        for(Bouncer& bouncer : bouncers) {
            bouncer.update();
        }

        

        bn::core::update();
    }
}