// https://cs50.harvard.edu/x/2022/psets/4/filter/more/

#include "helpers.h"
#include <string.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];

            BYTE red = pixel->rgbtRed, green = pixel->rgbtGreen, blue = pixel->rgbtBlue;
            BYTE average = (BYTE) round((red + green + blue) / 3.0f);

            pixel->rgbtRed = pixel->rgbtGreen = pixel->rgbtBlue = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE *leftmost_pixel = &image[i][j], *rightmost_pixel = &image[i][width - j - 1];

            RGBTRIPLE temp = *leftmost_pixel;
            *leftmost_pixel = *rightmost_pixel;
            *rightmost_pixel = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Local function prototype
    RGBTRIPLE average_nearby_pixels(int height, int width, int y, int x, int distance_from_center, RGBTRIPLE image[height][width]);

    // Copy image before altering it
    RGBTRIPLE original[height][width];
    memcpy(original, image, sizeof(RGBTRIPLE) * height * width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = average_nearby_pixels(height, width, i, j, 1, original);
        }
    }
}

RGBTRIPLE average_nearby_pixels(int height, int width, int y, int x, int distance_from_center, RGBTRIPLE image[height][width])
{
    WORD gx[3] = {0};
    BYTE count = 0;

    for (int i = y - distance_from_center; i <= y + distance_from_center; i++)
    {
        if (i < 0 || i > height - 1)
        {
            continue;
        }

        for (int j = x - distance_from_center; j <= x + distance_from_center; j++)
        {
            if (j < 0 || j > width - 1)
            {
                continue;
            }

            gx[0] += image[i][j].rgbtRed;
            gx[1] += image[i][j].rgbtGreen;
            gx[2] += image[i][j].rgbtBlue;

            count += 1;
        }
    }

    RGBTRIPLE output;
    output.rgbtRed = (BYTE) round(gx[0] / (float) count);
    output.rgbtGreen = (BYTE) round(gx[1] / (float) count);
    output.rgbtBlue = (BYTE) round(gx[2] / (float) count);

    return output;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Local function prototype
    RGBTRIPLE sobel_operator(int height, int width, int y, int x, RGBTRIPLE image[height][width]);

    // Copy image before altering it
    RGBTRIPLE original[height][width];
    memcpy(original, image, sizeof(RGBTRIPLE) * height * width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = sobel_operator(height, width, i, j, original);
        }
    }
}

// Calculate the sobel operator of a given pixel
RGBTRIPLE sobel_operator(int height, int width, int y, int x, RGBTRIPLE image[height][width])
{
    // Local function prototype
    double min(double a, double b);

    const int8_t KERNEL_X[3][3] = {{-1, 00, 01}, {-2, 00, 02}, {-1, 00, 01}};
    const int8_t KERNEL_Y[3][3] = {{-1, -2, -1}, {00, 00, 00}, {01, 02, 01}};

    int gx[3] = {0}, gy[3] = {0};

    for (int i = y - 1, k = 0; i <= y + 1; i++, k++)
    {
        if (i < 0 || i > height - 1)
        {
            continue;
        }

        for (int j = x - 1, l = 0; j <= x + 1; j++, l++)
        {
            if (j < 0 || j > width - 1)
            {
                continue;
            }

            // X-axis weigted sum
            gx[0] += image[i][j].rgbtRed * KERNEL_X[k][l];
            gx[1] += image[i][j].rgbtGreen * KERNEL_X[k][l];
            gx[2] += image[i][j].rgbtBlue * KERNEL_X[k][l];

            // Y-axis weigted sum
            gy[0] += image[i][j].rgbtRed * KERNEL_Y[k][l];
            gy[1] += image[i][j].rgbtGreen * KERNEL_Y[k][l];
            gy[2] += image[i][j].rgbtBlue * KERNEL_Y[k][l];
        }
    }

    RGBTRIPLE output;

    // Merge GX and GY into one value, capped at 255
    output.rgbtRed = (BYTE) round(min(sqrt(gx[0] * gx[0] + gy[0] * gy[0]), 255));
    output.rgbtGreen = (BYTE) round(min(sqrt(gx[1] * gx[1] + gy[1] * gy[1]), 255));
    output.rgbtBlue = (BYTE) round(min(sqrt(gx[2] * gx[2] + gy[2] * gy[2]), 255));

    return output;
}

double min(double a, double b)
{
    return a < b ? a : b;
}
