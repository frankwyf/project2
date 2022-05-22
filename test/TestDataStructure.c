
#include "DataStructure.h"
#include "unity.h"


void setUp(void)
{
  Row=-1;
  Column=-1;
  Step=-1;
  Delay=-1;
}

void tearDown(void)
{
}
/* All of these should pass */
void test_Readfile_emptyFile(void){
  game=fopen("empty.txt","r");
  TEST_ASSERT_EQUAL_INT(-1,Readfile(game));
  remove("Game.txt");
}

void test_Readfile_badFile(void){
  game=fopen("Bad.txt","r");
  TEST_ASSERT_EQUAL_INT(-1,Readfile(game));
  remove("Game.txt");
}

void test_Readfile_NoFile(void){
  game=NULL;
  TEST_ASSERT_EQUAL_INT(-1,Readfile(game));
  remove("Game.txt");
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
  TEST_ASSERT_EQUAL_INT(0, steps());
  TEST_ASSERT_EQUAL_INT(-1, delay());
}

void test_map_invalidinput(void)
{
  TEST_ASSERT_EQUAL_INT(1, map());
}

void test_map_invalidinput_toolarge(void)
{
  Row=201;
  Column=201;
  TEST_ASSERT_EQUAL_INT(1, map());
}

void test_map_validinput(void)
{
  Row=123;
  Column=123;
  TEST_ASSERT_EQUAL_INT(1, map());
}