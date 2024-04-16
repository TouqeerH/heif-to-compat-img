#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read a file and return its contents as a Base64-encoded string
const char *read_file(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        return NULL; // File not found or cannot be opened
    }

    // Seek to the end of the file to determine its size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file content
    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (buffer == NULL)
    {
        fclose(file);
        return NULL; // Memory allocation failed
    }

    // Read the entire file into the buffer
    size_t bytes_read = fread(buffer, 1, file_size, file);
    fclose(file);

    // Check if the read was successful
    if (bytes_read != file_size)
    {
        free(buffer);
        return NULL; // Error reading file
    }

    // Encode the buffer as Base64
    size_t base64_length = (((file_size + 2) / 3) * 4) + 1;
    char *base64 = (char *)malloc(base64_length);
    if (base64 == NULL)
    {
        free(buffer);
        return NULL; // Memory allocation failed
    }

    const char *base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t i = 0, j = 0;
    for (i = 0, j = 0; i < file_size; i += 3, j += 4)
    {
        uint32_t octet_a = i < file_size ? buffer[i] : 0;
        uint32_t octet_b = (i + 1) < file_size ? buffer[i + 1] : 0;
        uint32_t octet_c = (i + 2) < file_size ? buffer[i + 2] : 0;

        base64[j] = base64_chars[octet_a >> 2];
        base64[j + 1] = base64_chars[((octet_a & 0x03) << 4) | (octet_b >> 4)];
        base64[j + 2] = (i + 1) < file_size ? base64_chars[((octet_b & 0x0F) << 2) | (octet_c >> 6)] : '=';
        base64[j + 3] = (i + 2) < file_size ? base64_chars[octet_c & 0x3F] : '=';
    }
    base64[j] = '\0';

    // Free the buffer and return the Base64 string
    free(buffer);
    printf("base64: %s\n", base64);
    return base64;
}

int main()
{
}

void test()
{
    printf("test\n");
}

// char *read_file(const char *filename)
// {
//     FILE *file = fopen(filename, "r");
//     printf("filename: %s\n", filename);

//     if (!file)
//     {
//         return NULL;
//     }
//     printf("file opened\n");
//     fseek(file, 0, SEEK_END);
//     long size = ftell(file);
//     fseek(file, 0, SEEK_SET);

//     char *buffer = (char *)malloc(size + 1);
//     fread(buffer, 1, size, file);
//     buffer[size] = 0;

//     fclose(file);
//     return buffer;
// }
