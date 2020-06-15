#include <GL/glew.h>

#include <iostream>

unsigned int loadBMP(const char* texturePath)
{
    printf("LOG: Reading image: %s\n", texturePath);

    // Data read from the BMP file
    unsigned char header[54];       // Each BMP file begins with a 54-bytes header
    unsigned int dataPos;           // Position in file where the data begins
    unsigned int width, height;
    unsigned int imageSize;         // = width*height*3
    unsigned char* data;            // Actual rgb data

    // Open the file
    FILE* file = fopen(texturePath, "rb");
    if (!file)
    {
        printf("ERROR: Texture %s could not be opened\n", texturePath);
        return 0;
    }

    // Check the header actually has 54 bytes, if not there's a problem
    if (fread(header, 1, 54, file) != 54)
    {
        printf("ERROR, %s is not a valid BPM file---- incorrect header size", texturePath);
        return 0;
    }

    // Header always begins with a BM, so check that the first two bytes are a "B" and a "M"
    if (header[0] != 'B' || header[1] != 'M')
    {
        printf("ERROR, %s is not a valid BPM file---- 'BM' missing", texturePath);
        return 0;
    }

    // Read ints from byte array
    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    // We have to make up some info if it is missing
    if (imageSize == 0) imageSize = width*height*3; //3: one byte for each red, green and blue component
    if (dataPos == 0) dataPos = 54; // This is the format of a BPM file

    // Create buffer
    data = new unsigned char[imageSize];

    // Read the actual data from the file into the buffer
    fread(data,1,imageSize,file);

    // Everything is now in memory so file can be closed
    fclose(file);

    // Create one opengl texture
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to opengl
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    // opengl has a copy of the data so we can delete ours from memory
    delete [] data;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return textureID;
}