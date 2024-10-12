#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"
#define min 0
#define max 255
#define one 1
#define two 2
#define three 3

int ***flip_horizontal(int ***image, int N, int M) {
    int ***a_image = malloc(N * sizeof(int**));
    for (int i = min; i < N; ++i) {
        a_image[i] = malloc(M * sizeof(int*));
        for (int j = min; j < M; ++j) {
            a_image[i][j] = calloc(three, sizeof(int));
        }
    }
    for (int i = min; i < N; ++i) {
        for (int j = min; j < M; ++j) {
            for (int k = min; k < three; ++k) {
                a_image[i][j][k] = image[i][M - j - one][k];
            }
        }
    }
    for (int i = min; i < N; ++i) {
        for (int j = min; j < M; ++j) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return a_image;
}

int ***rotate_left(int ***image, int N, int M) {
    int ***a_image = malloc(M * sizeof(int**));
    for (int i = min; i < M; ++i) {
        a_image[i] = malloc(N * sizeof(int*));
        for (int j = min; j < N; ++j) {
            a_image[i][j] = calloc(three, sizeof(int));
        }
    }
    for (int i = min; i < N; ++i) {
        for (int j = min; j < M; ++j) {
            for (int k = min; k < three; ++k) {
                a_image[M - j - one][i][k] = image[i][j][k];
            }
        }
    }
    for (int i = min; i < N; ++i) {
        for (int j = min; j < M; ++j) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return a_image;
}

int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    int ***a_image = malloc(h * sizeof(int**));
    for (int i = min; i < h; ++i) {
        a_image[i] = malloc(w * sizeof(int*));
        for (int j = min; j < w; ++j) {
            a_image[i][j] = calloc(three, sizeof(int));
        }
    }
    for (int i = min; i < h && i + y < N; ++i) {
        for (int j = min; j < w && j + x < M; ++j) {
            for (int k = min; k < three; ++k) {
                a_image[i][j][k] = image[i + y][j + x][k];
            }
        }
    }
    for (int i = min; i < N ; ++i) {
        for (int j = min; j < M; ++j) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return a_image;
}

int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    int ***a_image = malloc((N + two * rows) * sizeof(int**));
    for (int i = min; i < N + two * rows; ++i) {
        a_image[i] = malloc((M + two * cols) * sizeof(int*));
        for (int j = min; j < M + two * cols; ++j) {
            a_image[i][j] = calloc(three, sizeof(int));
        }
    }
    for (int i = min; i < N; ++i) {
        for (int j = min; j < M; ++j) {
            for (int k = min; k < three; ++k) {
                a_image[rows + i][cols + j][k] = image[i][j][k];
            }
        }
    }
    for (int i = min; i < rows; ++i) {
        for (int j = min; j < two * cols + M; ++j) {
            a_image[i][j][min] = new_R;
            a_image[i][j][one] = new_G;
            a_image[i][j][two] = new_B;
        }
    }
    for (int i = rows + N; i < two * rows + N; ++i) {
        for (int j = min; j < two * cols + M; ++j) {
            a_image[i][j][min] = new_R;
            a_image[i][j][one] = new_G;
            a_image[i][j][two] = new_B;
        }
    }
    for (int i = min; i < cols; ++i) {
        for (int j = min; j < two * rows + N; ++j) {
            a_image[j][i][min] = new_R;
            a_image[j][i][one] = new_G;
            a_image[j][i][two] = new_B;
        }
    }
    for (int i = cols + M; i < two * cols + M; ++i) {
        for (int j = min; j < two * rows + N; ++j) {
            a_image[j][i][min] = new_R;
            a_image[j][i][one] = new_G;
            a_image[j][i][two] = new_B;
        }
    }
    for (int i = min; i < N; ++i) {
        for (int j = min; j < M; ++j) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return a_image;
}

int ***paste(int ***image_dst, int N_dst, int M_dst, int ***image_src, int N_src, int M_src, int x, int y) {
    for (int i = y; i < N_dst && i - y < N_src; ++i) {
        for (int j = x; j < M_dst && j - x < M_src; ++j) {
            for (int k = min; k < three; ++k) {
                image_dst[i][j][k] = image_src[i - y][j - x][k];
            }
        }
    }
    return image_dst;
}

int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    int ***a_image = malloc(N * sizeof(int**));
    for (int i = min; i < N; ++i) {
        a_image[i] = malloc(M * sizeof(int*));
        for (int j = min; j < M; ++j) {
            a_image[i][j] = calloc(three, sizeof(int));
        }
    }
    for (int i = min; i < N; ++i) {
        for (int j = min; j < M; ++j) {
            float Red = min, Green = min, Blue = min;
            for (int ii = min; ii < filter_size; ++ii) {
                for (int jj = min; jj < filter_size; ++jj) {
                    int x = i - filter_size / two + ii + one - filter_size % two;
                    int y = j - filter_size / two + jj + one - filter_size % two;
                    if (x >= min && x < N && y >= min && y < M) {
                        Red += (float)image[x][y][min] * filter[ii][jj];
                        Green += (float)image[x][y][one] * filter[ii][jj];
                        Blue += (float)image[x][y][two] * filter[ii][jj];
                    }
                }
            }
            if (Red > max) Red = max;
            if (Red < min) Red = min;
            if (Green > max) Green = max;
            if (Green < min) Green = min;
            if (Blue > max) Blue = max;
            if (Blue < min) Blue = min;
            a_image[i][j][min] = (int)Red;
            a_image[i][j][one] = (int)Green;
            a_image[i][j][two] = (int)Blue;
        }
    }
    for (int i = min; i < N; ++i) {
        for (int j = min; j < M; ++j) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return a_image;
}
