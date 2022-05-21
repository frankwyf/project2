#include "Check.h"
#include "DataStructure.h"
#include "NextGenre.h"
#include "unity.h"
#include <stdlib.h>
/* this file tests the check functions for the game during evolution
  the case is the sam as provided in the cpursework specification  
*/

int check[5][5]={{0,0,0,0,0},{0,0,1,0,0},{1,0,1,0,0},{0,1,1,0,0},{0,0,0,0,0}};
int **Game = &check;

void setUp(void)
{
}

void tearDown(void)
{
}

//8 check functions
void test_Checkup(void){
    TEST_ASSERT_EQUAL_INT(1,CheckUp(Game,2,2));
    TEST_ASSERT_EQUAL_INT(0,CheckUp(Game,0,2));
    TEST_ASSERT_EQUAL_INT(0,CheckUp(Game,3,3));
}

void test_Checkdown(void){
    TEST_ASSERT_EQUAL_INT(0,CheckDown(Game,4,2));
    TEST_ASSERT_EQUAL_INT(1,CheckDown(Game,0,2));
    TEST_ASSERT_EQUAL_INT(0,CheckDown(Game,1,3));
}

void test_Checkleft(void){
    TEST_ASSERT_EQUAL_INT(0,CheckLeft(Game,0,2));
    TEST_ASSERT_EQUAL_INT(1,CheckLeft(Game,1,3));
    TEST_ASSERT_EQUAL_INT(0,CheckLeft(Game,1,4));
}

void test_Checkright(void){
    TEST_ASSERT_EQUAL_INT(0,CheckRight(Game,4,3));
    TEST_ASSERT_EQUAL_INT(1,CheckRight(Game,1,2));
    TEST_ASSERT_EQUAL_INT(0,CheckRight(Game,0,1));
}

void test_Checkupleft(void){
    TEST_ASSERT_EQUAL_INT(0,CheckUpLeft(Game,0,0));
    TEST_ASSERT_EQUAL_INT(1,CheckUpLeft(Game,2,3));
    TEST_ASSERT_EQUAL_INT(0,CheckUpLeft(Game,3,4));
}

void test_Checkupright(void){
    TEST_ASSERT_EQUAL_INT(0,CheckUpRight(Game,0,4));
    TEST_ASSERT_EQUAL_INT(1,CheckUpRight(Game,2,1));
    TEST_ASSERT_EQUAL_INT(0,CheckUpRight(Game,1,3));
}

void test_Checkdownleft(void){
    TEST_ASSERT_EQUAL_INT(0,CheckDownLeft(Game,4,0));
    TEST_ASSERT_EQUAL_INT(1,CheckDownLeft(Game,2,3));
    TEST_ASSERT_EQUAL_INT(0,CheckDownLeft(Game,3,4));
}

void test_Checkdownright(void){
    TEST_ASSERT_EQUAL_INT(0,CheckDownRight(Game,4,4));
    TEST_ASSERT_EQUAL_INT(1,CheckDownRight(Game,2,1));
    TEST_ASSERT_EQUAL_INT(0,CheckDownRight(Game,3,3));
}

//next geneartion part
void test_evolution(void){
    TEST_ASSERT_EQUAL_INT(1,Evolution(Game,1,1));
    TEST_ASSERT_EQUAL_INT(0,Evolution(Game,0,0));
}
