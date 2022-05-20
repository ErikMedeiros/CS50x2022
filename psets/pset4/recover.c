// https://cs50.harvard.edu/x/2022/psets/4/recover/

#include <stdio.h>
#include <stdint.h>

// Define buffer size
const int BUFFER_SIZE = 512;

int main(int argc, char *argv[])
{
    // Assert correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover file.raw\n");
        return 1;
    }

    // Assert valid file
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        fclose(raw);
        printf("Could not open recover file.\n");
        return 2;
    }

    uint8_t buffer[BUFFER_SIZE];
    int img_count = 0;
    FILE *img = NULL;

    while (fread(buffer, sizeof(uint8_t), BUFFER_SIZE, raw) == BUFFER_SIZE)
    {
        // Detect jpg start
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }

            char name[8];
            if (sprintf(name, "%.3i.jpg", img_count++) != 7)
            {
                printf("Could not create filename %.3i.jpg.\n", img_count - 1);
                return 3;
            }

            img = fopen(name, "w");
            if (img == NULL)
            {
                fclose(img);
                printf("Could not create %s.\n", name);
                return 4;
            }
        }

        // Write if image open
        if (img != NULL)
        {
            fwrite(buffer, sizeof(uint8_t), BUFFER_SIZE, img);
        }
    }

    fclose(raw);
    fclose(img);
}