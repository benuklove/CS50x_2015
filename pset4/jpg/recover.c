/**
 * recover.c
 *
 * Ben Love
 * benuklove@gmail.com
 * 
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPGs from a forensic image made from cf drive.
 * Does not use malloc.
 */

#include <stdio.h>
#include <stdint.h>

// function declaration
int start(uint8_t arg[]);

int main(void)

{
    // remember file name
    char* infile = "card.raw";
    
    // open source file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }
    
    // outfile pointer
    FILE *outptr;
    
    // temporary storage
    uint8_t buffer[512];
    char outfile[8];
    
    int count = 0;
    int gate = 0;
    
    // reading data from card into buffer
    while (fread(buffer, sizeof(buffer), 1, inptr) != 0)
    {
        // function call to see if data contains beginning sequence
        if (start(buffer) == 1)
        {
            // * once beginning sequence of next file found, close
            // previous file
            if (gate == 1)
            {
                fclose(outptr);
                gate = 0;
            }
            
            // if beginning sequence found, write to new file
            if (gate == 0)
            {
                sprintf(outfile, "%.3d.jpg", count++);
                outptr = fopen(outfile, "w");
                fwrite(buffer, sizeof(buffer), 1, outptr);
                gate = 1;
                continue;
            }
        }
        
        // continue writing to that new file if no beginning
        // sequence found *
        if (gate == 1)
        {
            fwrite(buffer, sizeof(buffer), 1, outptr);
        }
    }
    
    // that's all folks
    fclose(inptr);
    return 0;
}

// flag to test beginning of jpg
int start(uint8_t arg[])
{
    int flag;
    if (arg[0] == 0xff && arg[1] == 0xd8 && arg[2] == 0xff
                 && (arg[3] == 0xe0 || arg[3] == 0xe1))
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }
    return flag;
}
