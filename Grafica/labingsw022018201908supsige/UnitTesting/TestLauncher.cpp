#include <gtest/gtest.h>

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
#ifdef _WINDOWS
	//system("pause");
#endif
	return 0;
}