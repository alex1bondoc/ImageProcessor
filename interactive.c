#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"

#define min 0
#define max 255
#define one 1
#define two 2
#define three 3
#define size 13
int main() {
    char functie[max] = "a";
    int cnt_im = min;
    int cnt_fil = min;
    int ****imagini = malloc(size * sizeof(int***));
    int *row_sizes = calloc(size, sizeof(int));
    int *col_sizes = calloc(size, sizeof(int));
    float ***filters = malloc(size * sizeof(float**));
    int *fil_sizes = calloc(size, sizeof(int));

    while (strcmp(functie, "e") != min) {
        scanf("%s", functie);

        if (strcmp(functie, "l") == min) {
            int N = min, M = min;
            char path[max] = "";
            scanf("%d %d", &N, &M);
            scanf("%s", path);
            imagini[cnt_im] = malloc(N * sizeof(int**));
            for (int i = min; i < N; ++i) {
                imagini[cnt_im][i] = malloc(M * sizeof(int*));
                for (int j = min; j < M; ++j) {
                    imagini[cnt_im][i][j] = calloc(three, sizeof(int));
                }
            }
            row_sizes[cnt_im] = N;
            col_sizes[cnt_im] = M;
            read_from_bmp(imagini[cnt_im], N, M, path);
            cnt_im++;
        } else if (strcmp(functie, "s") == min) {
            int index = min;
            char path[max] = "";
            scanf("%d", &index);
            scanf("%s", path);
            write_to_bmp(imagini[index], row_sizes[index], col_sizes[index], path);
        } else if (strcmp(functie, "ah") == min) {
            int index = min;
            scanf("%d", &index);
            imagini[index] = flip_horizontal(imagini[index], row_sizes[index], col_sizes[index]);
        } else if (strcmp(functie, "ar") == min) {
            int index = min;
            scanf("%d", &index);
            imagini[index] = rotate_left(imagini[index], row_sizes[index], col_sizes[index]);
            int aux = row_sizes[index];
            row_sizes[index] = col_sizes[index];
            col_sizes[index] = aux;
        } else if (strcmp(functie, "ac") == min) {
            int index = min, x = min, y = min, w = min, h = min;
            scanf("%d %d %d %d %d", &index, &x, &y, &w, &h);
            imagini[index] = crop(imagini[index], row_sizes[index], col_sizes[index], x, y, h, w);
            row_sizes[index] = h;
            col_sizes[index] = w;
        } else if (strcmp(functie, "ae") == min) {
            int index = min, rows = min, cols = min, r = min, g = min, b = min;
            scanf("%d %d %d %d %d %d", &index, &rows, &cols, &r, &g, &b);
            imagini[index] = extend(imagini[index], row_sizes[index], col_sizes[index], rows, cols, r, g, b);
            row_sizes[index] += two * rows;
            col_sizes[index] += two * cols;
        } else if (strcmp(functie, "ap") == min) {
            int index_dst = min, index_src = min;
            int x = min, y = min;
            scanf("%d %d %d %d", &index_dst, &index_src, &x, &y);
            imagini[index_dst] = paste(imagini[index_dst], row_sizes[index_dst], col_sizes[index_dst],
            imagini[index_src], row_sizes[index_src], col_sizes[index_src], x, y);
        } else if (strcmp(functie, "cf") == min) {
            int N = min;
            scanf("%d", &N);
            filters[cnt_fil] = malloc(N * sizeof(float*));
            for (int i = min; i < N; ++i) {
                filters[cnt_fil][i] = calloc(N, sizeof(float));
                for (int j = min; j < N; ++j) {
                    scanf("%f", &filters[cnt_fil][i][j]);
                }
            }
            fil_sizes[cnt_fil] = N;
            cnt_fil++;
        } else if (strcmp(functie, "af") == min) {
            int index_img = min, index_filter = min;
            scanf("%d %d", &index_img, &index_filter);
            imagini[index_img] = apply_filter(imagini[index_img], row_sizes[index_img],
            col_sizes[index_img], filters[index_filter], fil_sizes[index_filter]);
        } else if (strcmp(functie, "df") == min) {
            int index = min;
            scanf("%d", &index);
            for (int i = min; i < fil_sizes[index]; ++i) {
                free(filters[index][i]);
            }
            free(filters[index]);
            for (int i = index; i < cnt_fil - one; ++i) {
                filters[i] = filters[i + one];
                fil_sizes[i] = fil_sizes[i + one];
            }
            cnt_fil--;
        } else if (strcmp(functie, "di") == min) {
            int index = min;
            scanf("%d", &index);
            for (int i = min; i < row_sizes[index]; ++i) {
                for (int j = min; j < col_sizes[index]; ++j) {
                    free(imagini[index][i][j]);
                }
                free(imagini[index][i]);
            }
            free(imagini[index]);
            for (int i = index; i < cnt_im - one; ++i) {
                imagini[i] = imagini[i + one];
                row_sizes[i] = row_sizes[i + one];
                col_sizes[i] = col_sizes[i + one];
            }
            cnt_im--;
        }
    }

    for (int i = min; i < cnt_im; ++i) {
        for (int j = min; j < row_sizes[i]; ++j) {
            for (int k = min; k < col_sizes[i]; ++k) {
                free(imagini[i][j][k]);
            }
            free(imagini[i][j]);
        }
        free(imagini[i]);
    }
    free(imagini);
    free(row_sizes);
    free(col_sizes);

    for (int i = min; i < cnt_fil; ++i) {
        for (int j = min; j < fil_sizes[i]; ++j) {
            free(filters[i][j]);
        }
        free(filters[i]);
    }
    free(filters);
    free(fil_sizes);

    return min;
}
