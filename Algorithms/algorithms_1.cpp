#include <iostream>
#include <random>
#include <time.h>
#include <math.h>
#include <cmath>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

long long** GenerateMatrix1(int rows, int columns) {
    long long** arr = new long long* [rows];
    for (int i = 0; i < rows; i++)
    {
        arr[i] = new long long[columns];
        for (int j = 0; j < columns; j++)
        {
            arr[i][j] = (columns / rows * (i+1) + (j+1)) * 2;
        }
    }
    return arr;
}
long long** GenerateMatrix2(int rows, int columns) {
    long long** arr = new long long* [rows];
    for (int i = 0; i < rows; i++)
    {
        arr[i] = new long long[columns];
        for (int j = 0; j < columns; j++)
        {
            arr[i][j] = (columns / rows * (i + 1) * (j + 1)) * 2;
        }
    }
    return arr;
}
void PrintMatrix(long long** matrix,int rows,int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns;j++) {
            std::cout << matrix[i][j]<< ' ';
        }
        std::cout << std::endl;
    }
}
void ClearMatrix(long long** matrix,int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
int BinarySearch(long long* array,int leftstart,int rightstart, long long target) {
    int left = leftstart;
    int right = rightstart;
    int middle;
    while (right > left) {
        middle = (right + left) / 2;
        if (array[middle] == target) {
            return middle;
        }
        else if (array[middle] < target) {
            left = middle + 1;
        }
        else {
            right = middle;
        }
    }
    return -1;
}
int BinarySearchForAlgo3(long long* array, int leftstart, int rightstart, long long target) {
    int left = leftstart;
    int right = rightstart;
    int middle;
    while (right > left) {
        middle = (right + left) / 2;
        if (array[middle] == target) {
            return middle;
        }
        else if (array[middle] < target) {
            left = middle + 1;
        }
        else {
            right = middle;
        }
    }
    return right-1;
}
int ExpSearch(long long* array,int leftstart, int rightstart, long long target) {
    int step = 1;
    if (array[rightstart] == target) {
        return rightstart;
    }
    while (rightstart-step > leftstart && array[rightstart-step] >= target) {
        step *= 2;
    }
    return BinarySearchForAlgo3(array,std::max(leftstart, rightstart - step),rightstart-(step / 2)+1,target);
}
void Algo1(long long** matrix,int rows,int columns, long long target) {
    int x = 0;
    int y = columns-1;
    while (x<rows && y>=0) {
        if (target > matrix[x][y]) {
            x++;
        }
        else if (target < matrix[x][y]) {
            y--;
        }
        else if (target == matrix[x][y]) {
            break;
        }
    }
}
void Algo2(long long** matrix,int rows,int columns, long long target) {
    for (int i = 0; i < rows; i++) {
        int answer = BinarySearch(matrix[i],0, columns, target);
        if (answer != -1) {
            break;
        }
    }
}
void Algo3(long long** matrix,int rows, int columns, int target) {
    int x = 0;
    int y = columns - 1;
    while (x < rows && y>=0) {
        if (target > matrix[x][y]) {
            x++;
        }
        else if (target < matrix[x][y]) {
            int temp = ExpSearch(matrix[x], 0, y, target);
            if (temp==-1) {
                break;
            }
            else {
                y = temp;
            }
        }
        else if (target == matrix[x][y]) {
            break;
        }
    }
}

int main()
{
    srand(time(0));
    int m = pow(2,13);
    int n;
    long double average1 = 0;
    long double average2 = 0;
    long double average3 = 0;
    for (int g = 1; g < 14; g++) {
        n = pow(2,g);
        int target = 2 * m + 1;
        long long** matrix = GenerateMatrix1(n, m);
        for (int i = 0; i < 100; i++) {
            auto StartTime = Clock::now();
            Algo1(matrix,n,m, target);
            auto EndTime = Clock::now();
            average1+=std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count();
            StartTime = Clock::now();
            Algo2(matrix,n,m, target);
            EndTime = Clock::now();
            average2+=std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count();
            StartTime = Clock::now();
            Algo3(matrix,n,m, target);
            EndTime = Clock::now();
            average3+=std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count();
        }
        ClearMatrix(matrix, n);
        average1 /= 100;
        average2 /= 100;
        average3 /= 100;
        std::cout << average1 << " " << average2 << " " << average3<<std::endl;
    }
    long double average4 = 0;
    for (int g = 1; g < 14; g++) {
        n = pow(2, g);
        int target = 16 * m + 1;
        long long** matrix = GenerateMatrix2(n, m);
        for (int i = 0; i < 100; i++) {
            auto StartTime = Clock::now();
            Algo3(matrix, n, m, target);
            auto EndTime = Clock::now();
            average4 += std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count();
        }
        ClearMatrix(matrix, n);
        average4 /= 100;
        std::cout << average4 << std::endl;
    }
    return 0;
}

