#ifndef PPM_HPP
#define PPM_HPP

//Process a binary PPM file
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

class ppm {
    void init();
    //info about the PPM file (height and width)
    unsigned int nr_lines;
    unsigned int nr_columns;

public:
    //arrays for storing the R,G,B values
    std::vector<unsigned char> r;
    std::vector<unsigned char> g;
    std::vector<unsigned char> b;
    //
    unsigned int height;
    unsigned int width;
    unsigned int max_col_val;
    // Total number of elements (pixels)
    unsigned int size;

    ppm();
    //create a PPM object and fill it with data stored in fname 
    ppm(const std::string &fname);
    //create an "epmty" PPM image with a given width and height;the R,G,B arrays are filled with zeros
    ppm(const unsigned int _width, const unsigned int _height);
    //read the PPM image from fname
    void read(const std::string &fname);
    //write the PPM image in fname
    void write(const std::string &fname);
};

// Init with default values
void ppm::init() {
    width = 0;
    height = 0;
    max_col_val = 255;
}

// Create a PPM object
ppm::ppm() {
    init();
}

// Create a PPM object and fill it with data stored in fname 
ppm::ppm(const std::string &fname) {
    init();
    read(fname);
}

// create an "empty" PPM image with a given width and height;the R,G,B arrays are filled with zeros
ppm::ppm(const unsigned int _width, const unsigned int _height) {
    init();
    width = _width;
    height = _height;
    nr_lines = height;
    nr_columns = width;
    size = width*height;

    // fill r, g and b with 0
    r.resize(size);
    g.resize(size);
    b.resize(size);
}

//read the PPM image from fname

void ppm::read(const std::string &fname) {
    std::ifstream inp(fname.c_str(), std::ios::in | std::ios::binary);
    if (inp.is_open()) {
        std::string line;
        std::getline(inp, line);
        if (line != "P6") {
            std::cout << "Error. Unrecognized file format." << std::endl;
            return;
        }
        std::getline(inp, line);
        while (line[0] == '#') {
            std::getline(inp, line);
        }
        std::stringstream dimensions(line);

        try {
            dimensions >> width;
            dimensions >> height;
            nr_lines = height;
            nr_columns = width;
        } catch (std::exception &e) {
            std::cout << "Header file format error. " << e.what() << std::endl;
            return;
        }

        std::getline(inp, line);
        std::stringstream max_val(line);
        try {
            max_val >> max_col_val;
        } catch (std::exception &e) {
            std::cout << "Header file format error. " << e.what() << std::endl;
            return;
        }

        size = width*height;

        r.reserve(size);
        g.reserve(size);
        b.reserve(size);

        char aux;
        for (unsigned int i = 0; i < size; ++i) {
            inp.read(&aux, 1);
            r[i] = (unsigned char) aux;
            inp.read(&aux, 1);
            g[i] = (unsigned char) aux;
            inp.read(&aux, 1);
            b[i] = (unsigned char) aux;
        }
    } else {
        std::cout << "Error. Unable to open " << fname << std::endl;
    }
    inp.close();
}

//write the PPM image in fname

void ppm::write(const std::string &fname) {
    std::ofstream inp(fname.c_str(), std::ios::out | std::ios::binary);
    if (inp.is_open()) {

        inp << "P6\n";
        inp << width;
        inp << " ";
        inp << height << "\n";
        inp << max_col_val << "\n";

        char aux;
        for (unsigned int i = 0; i < size; ++i) {
            aux = (char) r[i];
            inp.write(&aux, 1);
            aux = (char) g[i];
            inp.write(&aux, 1);
            aux = (char) b[i];
            inp.write(&aux, 1);
        }
    } else {
        std::cout << "Error. Unable to open " << fname << std::endl;
    }
    inp.close();
}
#endif