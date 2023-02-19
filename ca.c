/**
 * @file ca.c
 * @author Tereza Magerková(xmager00), Tomáš Husár(xhusar11)
 * @brief implementation of cellular automaton simmulating snowflake crystal growth
 *         Usage: ./ca [size] [number_of_iterations] [alpha] [beta] [gamma]
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */
// included libraries
#include <stdio.h>
#include <stdlib.h>

void copy_lattice(double **src, double **dst, int size)
{
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            dst[x][y] = src[x][y];
        }
    }
}

double **lattice_init(int size)
{
    double **lat = malloc(size * sizeof(double));
    for (int i = 0; i < size; i++)
    {
        lat[i] = malloc(size * sizeof(double));
    }
    return lat;
}

void lattice_clear(double **lat, int size)
{
    for (int i = 0; i < size; i++)
        free(lat[i]);

    free(lat);
}

void add_lattice(double **src1, double **src2, double **dst, int size)
{
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            dst[x][y] = src1[x][y] + src2[x][y];
        }
    }
}

void print_lattice(double **lat, int size)
{
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            printf("%.3f ", lat[x][y]);
        }
        printf("\n");
    }
}

void count_diffusion(double **lat, int size, double alpha)
{

    double **diffusion = lattice_init(size);

    copy_lattice(lat, diffusion, size);

    for (int x = 1; x < size - 1; x++)
    {
        for (int y = 1; y < size - 1; y++)
        {
            if (x % 2 == 0)
            {
                double sum = lat[x][y - 1] + lat[x + 1][y - 1] + lat[x - 1][y] + lat[x + 1][y] + lat[x - 1][y - 1] + lat[x][y + 1];
                diffusion[x][y] = lat[x][y] + (alpha / 12) * (-6 * lat[x][y] + sum); // ;
            }
            else
            {
                double sum = lat[x][y - 1] + lat[x - 1][y + 1] + lat[x - 1][y] + lat[x + 1][y] + lat[x + 1][y + 1] + lat[x][y + 1];
                diffusion[x][y] = lat[x][y] + (alpha / 12) * (-6 * lat[x][y] + sum);
            }
        }
    }

    copy_lattice(diffusion, lat, size);

    lattice_clear(diffusion, size);
}

void the_counting(double **lat, double **result, int size, double gamma, double alpha)
{
    double **neighbours = lattice_init(size);

    for (int x = 1; x < size - 1; x++)
    {
        for (int y = 1; y < size - 1; y++)
        {
            if (lat[x][y] >= 1)
            {
                neighbours[x][y] = 1;
                neighbours[(x + 1)][y] = 1;
                neighbours[(x - 1)][y] = 1;
                neighbours[x][(y - 1)] = 1;
                neighbours[x][(y + 1)] = 1;

                if (x % 2 == 0)
                {
                    neighbours[(x - 1)][(y - 1)] = 1;
                    neighbours[(x + 1)][(y - 1)] = 1;
                }
                else
                {
                    neighbours[(x - 1)][(y + 1)] = 1;
                    neighbours[(x + 1)][(y + 1)] = 1;
                }
            }
        }
    }

    double **receptive = lattice_init(size);

    double **non_receptive = lattice_init(size);

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            if (neighbours[x][y] == 1)
            {
                receptive[x][y] = lat[x][y] + gamma;
            }
            else
            {
                non_receptive[x][y] = lat[x][y];
            }
        }
    }

    count_diffusion(non_receptive, size, alpha);

    add_lattice(receptive, non_receptive, result, size);

    lattice_clear(neighbours, size);

    lattice_clear(receptive, size);

    lattice_clear(non_receptive, size);
}

int main(int argc, char **argv)
{

    int size, iter, opt;
    double alpha, beta, gamma;

    // argument parsing
    if (argc == 6)
    {
        size = atoi(argv[1]);
        iter = atoi(argv[2]);
        alpha = atoi(argv[3]);
        beta = atof(argv[4]);
        gamma = atof(argv[5]);
    }
    else
    {
        printf("Usage: ./ca [size] [iter] [alpha] [beta] [gamma]\n");
        return 1;
    }

    double **main_lat = lattice_init(size);
    // setting seed, borders and beta to cells
    for (int i = 0; i < size; i++)
    {

        for (int j = 0; j < size; j++)
        {
            if ((i == size / 2) && (j == size / 2))
            {
                // creating a seed in the middle of grid
                main_lat[i][j] = 1;
            }
            else if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
            {
                // borders
                main_lat[i][j] = 0;
            }
            else
            {
                // rest of the lattice
                main_lat[i][j] = beta;
            }
        }
    }

    for (int i = 0; i < iter; i++) // main iteration cycle
    {
        double **tmp_lat = lattice_init(size);
        the_counting(main_lat, tmp_lat, size, gamma, alpha);
        copy_lattice(tmp_lat, main_lat, size);
        lattice_clear(tmp_lat, size);
    }

    print_lattice(main_lat, size);

    return 0;
}
