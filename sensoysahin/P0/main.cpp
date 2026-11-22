#include <iostream>
#include <new>

void freeMatrix(int**& matrix, int rows) {
    if (matrix == nullptr) {
        return;
    }

    for (int i = 0; i < rows; ++i) {
        if (matrix[i] != nullptr) {
            delete[] matrix[i];
            matrix[i] = nullptr;
        }
    }

    delete[] matrix;
    matrix = nullptr;
}

int** allocateMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return nullptr;
    }

    int** matrix = new (std::nothrow) int*[rows];
    if (matrix == nullptr) {
        return nullptr;
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = nullptr;
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = new (std::nothrow) int[cols];
        if (matrix[i] == nullptr) {
            freeMatrix(matrix, i);
            return nullptr;
        }
    }

    return matrix;
}

int main() {
    const int rows = 3;
    const int cols = 4;
  
    int** matrix = nullptr;
    matrix = allocateMatrix(rows, cols);
    if (matrix == nullptr) {
        return 2;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(std::cin >> matrix[i][j])) {
                freeMatrix(matrix, rows);
                return 1;
            }
        }
    }

    int** transposed = nullptr;
    transposed = allocateMatrix(cols, rows);
    if (transposed == nullptr) {
        freeMatrix(matrix, rows);
        return 2;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }

    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            std::cout << transposed[i][j] << (j + 1 < rows ? " " : "");
        }
        std::cout << "\n";
    }

    freeMatrix(matrix, rows);
    freeMatrix(transposed, cols);

    return 0;
}
