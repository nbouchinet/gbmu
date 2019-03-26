#include <gb/console.h>
#include <gb/drawing.h>
#include <gb/gb.h>

int main() {
    gprint("Alaric's sound tests");

    NR52_REG = 0x80u;
    NR50_REG = 0x77u;
    NR51_REG = 0xffu;

    NR50_REG = 0x77;
    delay(0x10);
    NR50_REG = 0x77;
    NR51_REG = 0xbb;
    delay(0xf);
    NR50_REG = 0x77;
    delay(0x11);
    NR50_REG = 0x77;
    delay(0x10);
    NR50_REG = 0x77;
    delay(0x10);
    NR50_REG = 0x77;
    NR12_REG = 0xb1;
    NR11_REG = 0xc9;
    NR51_REG = 0xbb;
    NR13_REG = 0xad;
    NR14_REG = 0x85;
    NR22_REG = 0xc2;
    NR21_REG = 0xc9;
    NR51_REG = 0xbb;
    NR23_REG = 0x41;
    NR24_REG = 0x86;
    NR32_REG = 0x20;
    NR31_REG = 0x5;
    NR51_REG = 0xff;
    NR30_REG = 0x0;
    NR30_REG = 0x80;
    NR33_REG = 0x20;
    NR34_REG = 0x87;
    delay(0x1);
    NR41_REG = 0x1;
    NR42_REG = 0x91;
    NR41_REG = 0x1;
    NR51_REG = 0xff;
    NR43_REG = 0x22;
    NR44_REG = 0x80;
    NR10_REG = 0x8;
    delay(0xb);
    NR50_REG = 0x77;
    NR10_REG = 0x26;
    NR11_REG = 0x8d;
    NR12_REG = 0xc2;
    NR11_REG = 0x8d;
    NR51_REG = 0xff;
    NR13_REG = 0x40;
    NR14_REG = 0x87;
    delay(0xf);
    NR50_REG = 0x77;
    delay(0x10);
    NR50_REG = 0x77;
    delay(0xf);
    NR50_REG = 0x77;
    delay(0x11);
    NR50_REG = 0x77;
    NR51_REG = 0xbb;
    delay(0xf);
    NR50_REG = 0x77;
    delay(0x11);
    NR50_REG = 0x77;
    delay(0x10);
    NR50_REG = 0x77;
    delay(0x11);
    NR50_REG = 0x77;
    delay(0x1);
    NR22_REG = 0xc5;
    NR21_REG = 0xd3;
    NR51_REG = 0xbb;
    NR23_REG = 0xe6;
    NR24_REG = 0x86;
    NR32_REG = 0x20;
    NR31_REG = 0x13;
    NR51_REG = 0xff;
    NR30_REG = 0x0;
    NR30_REG = 0x80;
    NR33_REG = 0x6b;
    NR34_REG = 0x87;
    delay(0x1);
    NR41_REG = 0x1;
    NR42_REG = 0x91;
    NR41_REG = 0x1;
    NR51_REG = 0xff;
    NR43_REG = 0x22;
    NR44_REG = 0x80;
    delay(0x2c);
    NR50_REG = 0x77;
    delay(0x10);
    NR50_REG = 0x77;
    delay(0x10);
    NR50_REG = 0x77;
    NR10_REG = 0x8;
    delay(0x30);
    NR50_REG = 0x77;
    delay(0x11);
    NR50_REG = 0x77;
    delay(0x32);
    NR50_REG = 0x77;
    delay(0xf);
    NR50_REG = 0x77;
    NR23_REG = 0xe7;
    delay(0x41);
    NR50_REG = 0x77;
    NR10_REG = 0x26;
    NR11_REG = 0x8d;
    NR12_REG = 0xc2;
    NR11_REG = 0x8d;
    NR51_REG = 0xff;
    NR13_REG = 0x80;
    NR14_REG = 0x86;
    delay(0x10);
    NR50_REG = 0x77;
    delay(0x31);
    NR50_REG = 0x77;
    delay(0xf);
    NR50_REG = 0x77;
    delay(0x11);
    NR50_REG = 0x77;
    NR51_REG = 0xbb;
    delay(0x31);
    NR50_REG = 0x77;
    delay(0x11);
    NR50_REG = 0x77;
    delay(0x31);
    NR50_REG = 0x77;
    NR10_REG = 0x8;
    delay(0x10);
    NR50_REG = 0x77;
    delay(0x11);
    NR50_REG = 0x77;
    delay(0x31);
    NR50_REG = 0x77;
    delay(0x11);
    NR50_REG = 0x77;
    delay(0x32);
    NR50_REG = 0x77;
    delay(0x10);
    NR50_REG = 0x77;

    NR50_REG = 0x77u;
    return 0;
}
/*
APU write: ff14 -> 87 | delay: 0
APU write: ff24 -> 77 | delay: e
APU write: ff11 -> bf | delay: 0
APU write: ff24 -> 77 | delay: 43
APU write: ff11 -> c9 | delay: 0
APU write: ff12 -> a0 | delay: 0
APU write: ff11 -> c9 | delay: 0
APU write: ff25 -> 11 | delay: 0
APU write: ff13 -> e0 | delay: 0
APU write: ff14 -> 87 | delay: 0
APU write: ff24 -> 77 | delay: 12
APU write: ff11 -> bf | delay: 0
APU write: ff24 -> 77 | delay: e
APU write: ff11 -> 7f | delay: 0
APU write: ff24 -> 77 | delay: 21
APU write: ff11 -> ff | delay: 0
APU write: ff24 -> 77 | delay: e
APU write: ff11 -> bf | delay: 0
APU write: ff24 -> 77 | delay: 45
APU write: ff11 -> c9 | delay: 0
APU write: ff12 -> a0 | delay: 0
APU write: ff11 -> c9 | delay: 0
APU write: ff25 -> 11 | delay: 0
APU write: ff13 -> e0 | delay: 0
APU write: ff14 -> 87 | delay: 0
APU write: ff24 -> 77 | delay: 11
APU write: ff11 -> bf | delay: 0
APU write: ff24 -> 77 | delay: 30
APU write: ff11 -> ff | delay: 0
APU write: ff24 -> 77 | delay: e
APU write: ff11 -> bf | delay: 0
APU write: ff24 -> 77 | delay: 44
APU write: ff11 -> c9 | delay: 0
APU write: ff12 -> 80 | delay: 0
APU write: ff11 -> c9 | delay: 0
APU write: ff25 -> 11 | delay: 0
APU write: ff13 -> e0 | delay: 0
APU write: ff14 -> 87 | delay: 0
APU write: ff24 -> 77 | delay: 12
APU write: ff11 -> bf | delay: 0
APU write: ff24 -> 77 | delay: 30
APU write: ff11 -> ff | delay: 0
APU write: ff24 -> 77 | delay: d
APU write: ff11 -> bf | delay: 0
APU write: ff11 -> c9 | delay: 45
APU write: ff12 -> 60 | delay: 0
APU write: ff11 -> c9 | delay: 0
APU write: ff25 -> 11 | delay: 0
APU write: ff13 -> e0 | delay: 0
APU write: ff14 -> 87 | delay: 0
APU write: ff24 -> 77 | delay: 12
APU write: ff11 -> bf | delay: 0
 */
