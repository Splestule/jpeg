from PIL import Image
a = list(Image.open("in.pgm").getdata())
b = list(Image.open("out.pgm").getdata())
print("same" if a == b else "diff")