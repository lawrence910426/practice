#include <iostream>
#include <cstring>
#include <iomanip>
#include <memory.h>
const int MAX_N = 102;
const int MOD = 10007;

class Matrix {
	public:
		Matrix() {
			row = col = 0;
			memset(mat, 0, sizeof(mat));
		}
		Matrix(int r, int c): row(r), col(c) { memset(mat, 0, sizeof(mat)); }
		const int &getrow() {
			return row;
		}
		const int &getcol() {
			return col;
		}
		int *operator[] (const int &x) ;
		const int *operator[] (const int &x) const {
			return mat[x];
		}
		Matrix operator+ (const Matrix &x) const; 
		friend Matrix operator* (const Matrix &x, const Matrix &y) ;
		void print() {
			for(int i=0;i<row;i++) {
				if(i==0) std::cout << "/";
				else if(i==row-1) std::cout << "\\";
				else std::cout << "|";
				for(int j=0;j<col;j++) {
					std::cout << std::right << std::setw(8) << mat[i][j];
				}
				if(i==0) std::cout << " \\\n";
				else if(i==row-1) std::cout << " /\n";
				else std::cout << " |\n";
			}
		}
	private:
		int mat[MAX_N][MAX_N];
		int row, col;
        void Consolindate() { for(int i = 0;i < row;i++) for(int j = 0;j < col;j++) mat[i][j] = (mat[i][j] % MOD + MOD) % MOD; }
};

int* Matrix::operator[] (const int &x) { return mat[x]; }

Matrix Matrix::operator+ (const Matrix &x) const {
    Matrix ans(row, col);
    for(int i = 0;i < row;i++) for(int j = 0;j < col;j++) ans[i][j] = (mat[i][j] + x[i][j]) % MOD;
    ans.Consolindate();
    return ans;
}
Matrix operator* (const Matrix &x, const Matrix &y) {
    Matrix ans(x.row, y.col);
    for(int i = 0;i < x.row;i++) for(int k = 0;k < x.col;k++) for(int j = 0;j < y.col;j++) ans[i][j] = (ans[i][j] + x[i][k] * y[k][j]) % MOD;
    ans.Consolindate();
    return ans;
}
