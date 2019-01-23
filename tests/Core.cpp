#include "src/Core.hpp"

#include "gtest/gtest.h"

class Accesser {
	public:
		Core _core;
		Register& getPc(void){return _core._pc;}
		Register& getSp(void){return _core._sp;}
		Register& getAf(void){return _core._af;}
		Register& getBc(void){return _core._bc;}
		Register& getDe(void){return _core._de;}
		Register& getHl(void){return _core._hl;}
};

class TestCoreFixture : public ::testing::Test {
	public:
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
