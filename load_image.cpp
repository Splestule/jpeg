#include <bits/stdc++.h>
#include <cassert>
#include <array>
using Matrix8 = std::array<std::array<double, 8>, 8>;

using namespace std;

struct Image {
    int width = 0, height = 0;
    vector<int> pixels;
};

// Cosine bases for DCT
Matrix8 makeDCTMatrix() {
    const double PI = acos(-1.0);
    Matrix8 M{};
    for (int u = 0; u < 8; u++) {
        double k = (u == 0) ? sqrt(1.0/8) : 0.5;
        for (int x = 0; x < 8; x++) {
            M[u][x] = k * cos((2*x + 1) * u * PI / 16.0);
        }
    }
    return M;
}

const Matrix8 A = makeDCTMatrix();

Matrix8 matmul(const Matrix8& A, const Matrix8& B) {
    Matrix8 C{};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

Matrix8 transpose(const Matrix8& M) {
    Matrix8 C{};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            C[j][i] = M[i][j];
        }
    }
    return C;
}

Matrix8 dct8x8(Matrix8 in) {
    Matrix8 out;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            out[i][j] = in[i][j] - 128;
        }
    }
    return matmul(matmul(A, out), transpose(A));
}

Matrix8 idct8x8(Matrix8 in) {
    Matrix8 out = matmul(matmul(transpose(A), in), A);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            out[i][j] += 128;
        }
    }
    return out;
}

Image processBlocks(const Image& input) {
    vector<int> num_of_blocks(2);
    num_of_blocks[0] = input.width / 8;
    num_of_blocks[1] = input.height / 8;
    int new_width = num_of_blocks[0] * 8;
    int new_height = num_of_blocks[1] * 8;
    vector<int> pixels_out(new_width * new_height);

    for (int i = 0; i < num_of_blocks[0]; i++) {
        for (int j = 0; j < num_of_blocks[1]; j++) {
            const int start_point = i * 8 + input.width * j * 8;
            const int start_point_write = i * 8 + new_width * j * 8;

            Matrix8 block;
            for (int k = 0; k < 8; k++) {
                for (int l = 0; l < 8; l++) {
                    block[k][l] = input.pixels[start_point + l + k * input.width];
                }
            }
            // TODO: math stuff
            block = dct8x8(block);
            block = idct8x8(block);
            for (int k = 0; k < 8; k++) {
                for (int l = 0; l < 8; l++) {
                    pixels_out[start_point_write + l + k * new_width] = clamp(static_cast<int>(lround(block[k][l])), 0, 255);
                }
            }
        }
    }
    Image img_out = {
        new_width, new_height, std::move(pixels_out)
    };
    return img_out;
}

void pixels2img(const char* out_loc, const Image& input) {
    ofstream out(out_loc);
    out << "P2\n" << input.width << " " << input.height << "\n255\n";

    for (int i = 0; i < input.width * input.height; i++) {
        out << input.pixels[i] << " ";
    }
}

void printMatrix(const Matrix8& M) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) cerr << setw(10) << fixed << setprecision(4) << M[i][j];
        cerr << "\n";
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
    Image img;
    int maxval;
    in >> type >> img.width >> img.height >> maxval;

    cerr << "loaded: " << img.width << "x" << img.height << "\n";

    img.pixels.resize(img.width * img.height);
    for (int i = 0; i < img.width * img.height; i++) {
        in >> img.pixels[i];
    }

    Image img_out = processBlocks(img);
    pixels2img(argv[2], img_out);

    assert(img.pixels == img_out.pixels);

    return 0;
}