
#include "DataStructure.h"
#include "unity.h"


void setUp(void)
{

}

void tearDown(void)
{
}
/* All of these should pass */

void test_Readfile_CorrectFile(void){
  game=fopen("Game.txt","r");
  Step=10;
  TEST_ASSERT_EQUAL_INT(0,Readfile(game));
  TEST_ASSERT_EQUAL_INT(0,WriteResult(game));
}


void test_stepAnddelay_validinput(void)
{
  Step=123;
  Delay=1000;
  TEST_ASSERT_EQUAL_INT(0, steps());
  TEST_ASSERT_EQUAL_INT(Delay, delay());
}

void test_stepAnddelay_Invalidinput(void)
{
  Step=-1;
  Delay=-1;
  TEST_ASSERT_EQUAL_INT(0, steps());
  TEST_ASSERT_EQUAL_INT(-1, delay());
}


void test_map_validinput(void)
{
  Row=123;
  Column=123;
  TEST_ASSERT_EQUAL_INT(0, map());
}


