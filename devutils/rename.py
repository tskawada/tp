import glob
import shutil

for filename in glob.glob("../data/from/*.jpg"):
    outputname = int(filename.split("/")[-1].replace("LRT_", "").replace(".jpg", ""))
    shutil.copy(filename, f"../data/from2/{outputname}.jpg")
