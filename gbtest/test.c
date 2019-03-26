#include <gb/console.h>
#include <gb/drawing.h>
#include <gb/gb.h>

int main() {
    gprint("Alaric's sound tests");

    NR52_REG = 0x80u;
    NR50_REG = 0x77u;
    NR51_REG = 0xffu;

    NR41_REG = 0x3b;
    NR42_REG = 0xf0;
    NR43_REG = 0x20;
    NR44_REG = 0xc0;

    delay(9 + 0xe);

    NR50_REG = 0x77u;

    delay(9);

    NR50_REG = 0x77u;
    return 0;
}
