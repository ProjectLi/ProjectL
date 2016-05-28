#include <stdlib.h>
#include "ctest.h"
#include "main.cpp"

CTEST(testLife, TestClear) {
	int A[3][3] = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
	int B[3][3] = { {3, 3, 3}, {3, 3, 3}, {3, 3, 3} };
	
	clear(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}
}

CTEST(testLife, TestClearScope) {
	int A[3][3] = { { 1, 1, 1 },{ 1, 1, 1 },{ 1, 1, 1 } };
	int B[3][3] = { { 3, 3, 3 },{ 3, 1, 3 },{ 3, 3, 3 } };
	
	clear_Scope(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}

}

CTEST(testLife, TestRandomFirstGen) {
	int A[3][3] = { { 3, 3, 3 },{ 3, 3, 3 },{ 3, 3, 3 } };
	int B[3][3] = { { 3, 3, 3 },{ 3, 3, 3 },{ 3, 3, 3 } };

	random_FirstGen(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}

}

CTEST(testLife, TestRename) {
	int A[3][3] = { { 0, 0, 2 },{ 2, 3, 0 },{ 2, 0, 3 } };
	int B[3][3] = { { 3, 3, 1 },{ 1, 3, 3 },{ 1, 3, 3 } };

	rename(A, 3, 3);	
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}

}

CTEST(testLife, TestDeathGen) {
	int A[3][3] = { { 3, 3, 3 },{ 1, 1, 1 },{ 3, 3, 3 } };
	int B[3][3] = { { 3, 3, 3 },{ 3, 0, 3 },{ 3, 3, 3 } };
	
	deathGen(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}

}

CTEST(testLife, TestSecondGen) {
	int A[3][3] = { { 3, 3, 3 },{ 1, 3, 1 },{ 3, 1, 3 } };
	int B[3][3] = { { 3, 3, 3 },{ 3, 2, 3 },{ 3, 3, 3 } };
	
	secondGen(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}

}

CTEST(testLife, TestCustomRename) {
	int A[3][3] = { { 0, 3, 0 },{ 0, 3, 3 },{ 0, 3, 0 } };
	int B[3][3] = { { 3, 3, 3 },{ 3, 3, 3 },{ 3, 3, 3 } };
	
	custom_Rename(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}

}

CTEST(testLife, TestCustomSecondGen) {
	int A[3][3] = { { 3, 3, 3 },{ 6, 3, 3 },{ 3, 3, 3 } };
	int B[3][3] = { { 3, 3, 3 },{ 6, 2, 3 },{ 3, 3, 3 } };
	
	custom_SecondGen(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}


}

CTEST(testLife, TestCustomDeathGen) {
	int A[3][3] = { { 3, 3, 3 },{ 3, 6, 3 },{ 3, 3, 3 } };
	int B[3][3] = { { 3, 3, 3 },{ 3, 0, 3 },{ 3, 3, 3 } };
	
	custom_DeathGen(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}

}
