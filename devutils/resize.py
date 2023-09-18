import cv2
import glob

width = 1280
height = int(960 * 3915 // 5872)

print("width: ", width)
print("height: ", height)

for path in glob.glob("../data/from2/*.jpg"):
    img = cv2.imread(path)
    img = cv2.resize(img, (width, height))
    cv2.imwrite(path.replace("from2", "from3"), img)
