from PIL import Image
im = Image.open("image.png").convert("L").resize((64, 64))
w, h = im.size
open("in.pgm","w").write(f"P2\n{w} {h}\n255\n" + " ".join(map(str, im.getdata())))