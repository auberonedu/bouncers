#include <bn_core.h>
#include <bn_backdrop.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>
#include <bn_random.h>

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


int main() {
    bn::core::init();

    bn::random rng = bn::random();

    bn::fixed starting_x = rng.get_fixed(MIN_X, MAX_X);
    bn::fixed starting_y = rng.get_fixed(MIN_Y, MAX_Y);

    bn::sprite_ptr bouncer = bn::sprite_items::dot.create_sprite(starting_x, starting_y);

    bn::fixed dx = rng.get_fixed(MIN_DX, MAX_DX);
    bn::fixed dy = rng.get_fixed(MIN_DY, MAX_DY);

    while(true) {

        bn::fixed x = bouncer.x();
        bn::fixed y = bouncer.y();

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

        bouncer.set_x(x);
        bouncer.set_y(y);

        bn::core::update();
    }
}