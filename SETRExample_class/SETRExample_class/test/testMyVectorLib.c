#include <unity.h>
#include "MyVectorLib.h"

void setUp(void)
{
	return;
}
void tearDown(void)
{
	return;
}

void test_MyVectorLib_Find_NotThere(void)
{
	TEST_ASSERT_EQUAL_INT(0, MyVectorLib_Find(-14));
	TEST_ASSERT_EQUAL_INT(0, MyVectorLib_Find(0));   /* This test is wrong as 0 is part of the array! */
	TEST_ASSERT_EQUAL_INT(0, MyVectorLib_Find(29));
	TEST_ASSERT_EQUAL_INT(0, MyVectorLib_Find(999999));
}

void test_MyVectorLib_Find_AreThere(void)
{
	TEST_ASSERT_EQUAL_INT(1, MyVectorLib_Find(0));
	TEST_ASSERT_EQUAL_INT(2, MyVectorLib_Find(27));
	TEST_ASSERT_EQUAL_INT(5, MyVectorLib_Find(900));
	TEST_ASSERT_EQUAL_INT(8, MyVectorLib_Find(999));
	
}
void test_MyVectorLib_Len_RightSize(void)
{
	TEST_ASSERT_EQUAL_INT(8, MyVectorLib_Len());
}

int main(void)
{
	UNITY_BEGIN();
	
	RUN_TEST(test_MyVectorLib_Find_NotThere);
	RUN_TEST(test_MyVectorLib_Find_AreThere);
	RUN_TEST(test_MyVectorLib_Len_RightSize);
		
	return UNITY_END();
}
