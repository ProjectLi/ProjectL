#include <stdlib.h>
#include "ctest.h"
#include "FUNC.h"

CTEST(testLife, TestClear) {
	int A[3][3] = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
	int B[3][3] = { {3, 3, 3}, {3, 3, 3}, {3, 3, 3} };
	
	Clear(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}
}

CTEST(testLife, TestClearScope) {
	int A[3][3] = { { 1, 1, 1 },{ 1, 1, 1 },{ 1, 1, 1 } };
	int B[3][3] = { { 3, 3, 3 },{ 3, 1, 3 },{ 3, 3, 3 } };
	
	ClearScope(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}

}

CTEST(testLife, TestCh) {
	int A = Ch(A, 3, 3);;
	int B = 9;
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B, A ); 
		}
	}

}

CTEST(testLife, TestRandomFirstGen) {
	int A[3][3] = { { 3, 3, 3 },{ 3, 3, 3 },{ 3, 3, 3 } };
	int B[3][3] = { { 3, 3, 3 },{ 3, 3, 3 },{ 3, 3, 3 } };

	RandomFirstGen(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}

}

CTEST(testLife, TestRename) {
	int A[3][3] = { { 0, 0, 2 },{ 2, 3, 0 },{ 2, 0, 3 } };
	int B[3][3] = { { 3, 3, 1 },{ 1, 3, 3 },{ 1, 3, 3 } };

	Rename(A, 3, 3);	
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}

}

CTEST(testLife, TestDeathGen) {
	int A[3][3] = { { 3, 3, 3 },{ 1, 1, 1 },{ 3, 3, 3 } };
	int B[3][3] = { { 3, 3, 3 },{ 3, 0, 3 },{ 3, 3, 3 } };
	
	DeathGen(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}

}

CTEST(testLife, TestSecondGen) {
	int A[3][3] = { { 3, 3, 3 },{ 1, 3, 1 },{ 3, 1, 3 } };
	int B[3][3] = { { 3, 3, 3 },{ 3, 2, 3 },{ 3, 3, 3 } };
	
	SecondGen(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}

}

CTEST(testLife, TestCustomRename) {
	int A[3][3] = { { 0, 3, 0 },{ 0, 3, 3 },{ 0, 3, 0 } };
	int B[3][3] = { { 3, 3, 3 },{ 3, 3, 3 },{ 3, 3, 3 } };
	
	CustomRename(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}

}

CTEST(testLife, TestCustomSecondGen) {
	int A[3][3] = { { 3, 3, 3 },{ 6, 3, 3 },{ 3, 3, 3 } };
	int B[3][3] = { { 3, 3, 3 },{ 6, 2, 3 },{ 3, 3, 3 } };
	
	CustomSecondGen(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}


}

CTEST(testLife, TestCustomDeathGen) {
	int A[3][3] = { { 3, 3, 3 },{ 3, 6, 3 },{ 3, 3, 3 } };
	int B[3][3] = { { 3, 3, 3 },{ 3, 0, 3 },{ 3, 3, 3 } };
	
	CustomDeathGen(A, 3, 3);
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			ASSERT_EQUAL( B[i][j], A[i][j] ); 
		}
	}

}
