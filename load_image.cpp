#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "use: " << argv[0] << " in.pgm out.pgm\n";
        return 1;
    }

    ifstream in(argv[1]);
    if (!in) { cerr << "Cannot open in.pgm" << endl; return 1; }

    string type;
    int width, height, maxval;
    in >> type >> width >> height >> maxval;

    cerr << "loaded: " << width << "x" << height << endl;

    vector<int> pixels(width * height);
    for (int i = 0; i < width * height; i++) {
        in >> pixels[i];
    }

    ofstream out(argv[2]);
    out << "P2\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < width * height; i++) {
        out << pixels[i] << " ";
    }

    return 0;
}