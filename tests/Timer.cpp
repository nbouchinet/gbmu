#include "gtest/gtest.h"
#include "src/cpu/Timer.hpp"
#include "src/Gameboy.hpp"

namespace {
	ComponentsContainer container("tools/Tetris.gb");
	Timer t(container);

	TEST(Timer, readwrite) {
		t.write(0xFF04, 0x42);
		t.write(0xFF05, 0x21);
		t.write(0xFF06, 0x42);
		EXPECT_EQ(t.read(0xFF04), 0x0);
		EXPECT_EQ(t.read(0xFF05), 0x21);
		EXPECT_EQ(t.read(0xFF06), 0x42);
	}

	TEST(Timer, EnableTimer) {
		t.EnableTimer();
		EXPECT_EQ(t.TimerEnabled(), 1);
	}

	TEST(Timer, GetFrequence) {
		for (int i = 0; i <= 3; i++) {
			t.write(0xFF07, i);
			EXPECT_EQ(t.read(0xFF07), i);
			EXPECT_EQ(t.GetFrequence() & 0x3, i);
		}
	}

	TEST(Timer, GetCounter) {
		for (int i = 0; i <= 3; i++) {
			t.write(0xFF07, i);
			switch (i) {
				case 0x0:
					EXPECT_EQ(t.GetCounter(), 0x400);
					break ;
				case 0x1:
					EXPECT_EQ(t.GetCounter(), 0x10);
					break ;
				case 0x2:
					EXPECT_EQ(t.GetCounter(), 0x40);
					break ;
				case 0x3:
					EXPECT_EQ(t.GetCounter(), 0x100);
					break ;
			}
		}
	}

	TEST(Timer, Update) {
		t.EnableTimer();
		int cycles = 0;
		for (int i = 0; i <= 42000; i++) {
			t.Update(cycles);
			cycles += 4;
		}
	}
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
