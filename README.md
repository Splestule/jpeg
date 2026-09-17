# JPEG from scratch

A side project where I implemented the mathematical core of JPEG in C++.
I wanted to practice C++, which I'm just starting to learn, and use
something from MIT 18.06 Linear Algebra along the way.

It doesn't write a compressed file. I focused on the part I found
interesting: changing the basis (to a cosine one in this case), throwing away the coefficients the eye
notices least, and showing what the image looks like afterwards.

Works on .pgm grayscale images — use img2P2.py to convert.

P2 image → 8x8 blocks → DCT → **quantize** → IDCT → image out

## Running it

    cmake -B build
    cmake --build build
    ./build/jpeg in.pgm out.pgm 50

Last argument is quality, 1–100.

## Results

| quality | zero coefficients | avg pixel error |
|---------|-------------------|-----------------|
| 90      |         0.704          |     1.18            |
| 50      |           0.860        |       3.00          |
| 10      |        0.945           |       5.35          |

At quality 10 the 8x8 blocks become visible.

