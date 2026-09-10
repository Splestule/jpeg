#include <bits/stdc++.h>
#include <cassert>
using namespace std;

vector<int> processBlocks(const vector<int>& pixels_in, const int width, const int height) {
    vector<int> num_of_blocks(2);
    num_of_blocks[0] = width / 8;
    num_of_blocks[1] = height / 8;
    int new_width = num_of_blocks[0] * 8;
    int new_height = num_of_blocks[1] * 8;
    vector<int> pixels_out(new_width * new_height);

    for (int i = 0; i < num_of_blocks[0]; i++) {
        for (int j = 0; j < num_of_blocks[1]; j++) {
            const int start_point = i * 8 + width * j * 8;

            double block[8][8];
            for (int k = 0; k < 8; k++) {
                for (int l = 0; l < 8; l++) {
                    block[k][l] = pixels_in[start_point + l + k * width];
                }
            }
            // TODO: math stuff
            for (int k = 0; k < 8; k++) {
                for (int l = 0; l < 8; l++) {
                    pixels_out[start_point + l + k * width] = block[k][l];
                }
            }
        }
    }
    return pixels_out;
}

void pixels2img(const char* out_loc, const vector<int>& pixels, const int width, const int height) {
    ofstream out(out_loc);
    out << "P2\n" << width << " " << height << "\n255\n";

    for (int i = 0; i < width * height; i++) {
        out << pixels[i] << " ";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "use: " << argv[0] << " in.pgm out.pgm\n";
        return 1;
    }

    ifstream in(argv[1]);
    if (!in) { cerr << "Cannot open in.pgm" << "\n"; return 1; }

    string type;
    int width, height, maxval;
    in >> type >> width >> height >> maxval;

    cerr << "loaded: " << width << "x" << height << "\n";

    vector<int> pixels(width * height);
    for (int i = 0; i < width * height; i++) {
        in >> pixels[i];
    }

    vector<int> pixels_out = processBlocks(pixels, width, height);
    pixels2img(argv[2], pixels_out, width, height);

    assert(pixels == pixels_out);

    return 0;
}