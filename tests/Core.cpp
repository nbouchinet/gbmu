#include "src/Core.hpp"

#include "gtest/gtest.h"
#define test_flags(...) test_flags_base((TestCoreFixture::s_flags){__VA_ARGS__})

class Accesser {
	public:
		Core _core;
		Register& getPc(void){return _core._pc;}
		Register& getSp(void){return _core._sp;}
		Register& getAf(void){return _core._af;}
		Register& getBc(void){return _core._bc;}
		Register& getDe(void){return _core._de;}
		Register& getHl(void){return _core._hl;}

		void test_flags_base(struct s_flags f)
		{
			EXPECT_EQ(_accesser._core.get_flag(Core::Flags::C), f.c);
			EXPECT_EQ(_accesser._core.get_flag(Core::Flags::Z), f.z);
			EXPECT_EQ(_accesser._core.get_flag(Core::Flags::N), f.n);
			EXPECT_EQ(_accesser._core.get_flag(Core::Flags::H), f.h);
		}
};

class TestCoreFixture : public ::testing::Test {
	public:
		struct s_flags { bool c, z, n, h; };
		Accesser _accesser;
};

TEST_F(TestCoreFixture, basic_test)
{
	//std::vector<Byte> opcode{0xC3, 0x4};
	//auto a = opcode.begin();
	_accesser._core.instr_jp(Core::JumpCondition::None, 0x4);
	EXPECT_EQ(_accesser.getPc().word, 0x4);
}

int main(int ac, char *av[]) {
  ::testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
