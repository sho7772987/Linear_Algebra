#include<stdio.h>
#include<math.h>

#define MAX 100
#define EPS 1e-9

// 行列積の関数
void Matrix_cal(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int rowA, int colA, int colB){
    for(int i = 0; i < rowA; i++){
        for(int j = 0; j < colB; j++){
            C[i][j] = 0;
            for(int k = 0; k < colA; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// 行列表示関数
void matrix(int mat[MAX][MAX], int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%6d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// スカラー倍
void scalarFun(int mat[MAX][MAX], int rows, int cols, int scalar){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            mat[i][j] *= scalar;
        }
    }
}

// 簡約階段行列（RREF）
void rref(int mat[MAX][MAX], int rows, int cols){
    int lead = 0;
    for(int r = 0; r < rows; r++){
        if(lead >= cols) return;

        int i = r;
        while(mat[i][lead] == 0){
            i++;
            if(i == rows){
                i = r;
                lead++;
                if(lead == cols) return;
            }
        }

        // 行の入れ替え
        if(i != r){
            for(int k = 0; k < cols; k++){
                int temp = mat[r][k];
                mat[r][k] = mat[i][k];
                mat[i][k] = temp;
            }
        }

        int pivot = mat[r][lead];
        if(pivot != 0){
            for(int k = 0; k < cols; k++){
                // 整数除算できる場合のみ割る
                if(mat[r][k] % pivot == 0){
                    mat[r][k] /= pivot;
                }
            }
        }

        for(int i = 0; i < rows; i++){
            if(i != r){
                int factor = mat[i][lead];
                for(int k = 0; k < cols; k++){
                    mat[i][k] -= factor * mat[r][k];
                }
            }
        }
        lead++;
    }
}

int main(void){
    int choice;
    printf("【1】行列の積\n【2】スカラー倍\n【3】簡約階段行列（RREF）\n");
    printf("選択してください：");
    scanf("%d", &choice);

    if(choice == 1){
        int rowA, colA, rowB, colB;
        int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

        printf("行列Aの行数："); 
        scanf("%d", &rowA);
        printf("行列Aの列数：");
         scanf("%d", &colA);
        printf("行列Aを入力：\n");
        for(int i = 0; i < rowA; i++)
            for(int j = 0; j < colA; j++)
                scanf("%d", &A[i][j]);

        printf("行列Bの行数："); 
        scanf("%d", &rowB);
        printf("行列Bの列数："); 
        scanf("%d", &colB);
        printf("行列Bを入力：\n");
        for(int i = 0; i < rowB; i++)
            for(int j = 0; j < colB; j++)
                scanf("%d", &B[i][j]);

        Matrix_cal(A, B, C, rowA, colA, colB);

        printf("≪行列の積≫\n");
        matrix(C, rowA, colB);

    }else if(choice == 2){
        int rows, cols, scalar;
        int mat[MAX][MAX];

        printf("行列の行数："); 
        scanf("%d", &rows);
        printf("行列の列数："); 
        scanf("%d", &cols);
        printf("行列を入力：\n");
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                scanf("%d", &mat[i][j]);

        printf("かけるスカラーを入力：");
        scanf("%d", &scalar);

        scalarFun(mat, rows, cols, scalar);
        printf("≪  スカラー倍された行列≫\n");
        matrix(mat, rows, cols);

    }else if(choice == 3){
        int rows, cols;
        int mat[MAX][MAX];

        printf("行列の行数："); 
        scanf("%d", &rows);
        printf("行列の列数："); 
        scanf("%d", &cols);
        printf("行列を入力：\n");
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                scanf("%d", &mat[i][j]);

        rref(mat, rows, cols);
        printf("≪  簡約階段行列（RREF）≫\n");
        matrix(mat, rows, cols);

    return 0;
    }
}
