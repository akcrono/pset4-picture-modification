/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  BYTE;

// tests whether the beginning of buffer is a jpeg sequence
bool IsStart (BYTE* buffer);

int main(void)
{
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        printf("Could not open\n");
        return 1;
    }
    int numFiles=0;
    BYTE* buffer = malloc(512);
    char* fileName=malloc(32);
        
    while(fread(buffer, 512, 1, inptr)==1 && !IsStart(buffer))
    {}
    
    sprintf (fileName, "%03d.jpg", numFiles);
    numFiles++; 
   
    FILE* outptr = fopen(fileName, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", fileName);
        return 2;
    }           
    fwrite(buffer, 512, 1, outptr);
            
    while(fread(buffer, 512, 1, inptr)==1)
    {
        if (IsStart(buffer))
        {
            fclose(outptr);
 
            sprintf (fileName, "%03d.jpg", numFiles);

            numFiles++; 
    
            outptr = fopen(fileName, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", fileName);
                return 2;
            }                  
        }
        fwrite(buffer, 512, 1, outptr);
    }
    fclose(outptr);
    fclose(inptr);
    free(buffer);
    free(fileName);
    
    return 0;
}

bool IsStart (BYTE* buffer)
{
    if (buffer[0]!=0xff)
        return false;
    else if (buffer[1]!=0xd8)
        return false;    
    else if (buffer[2]!=0xff)
        return false;      
    else if (buffer[3]==0xe0 || buffer[3]==0xe1)
        return true;  
    else
        return false;   
} 
    
    
