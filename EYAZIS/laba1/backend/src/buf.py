import os

import xml.etree.ElementTree as ET
import xml.dom.minidom

src_folder = "data/movie_reviews"

dst_folder = "data/movie_reviews_converted"
os.makedirs(dst_folder, exist_ok=True)

for root_dir, dirs, files in os.walk(src_folder):
    for file in files:
        if file.endswith(".txt"):
            with open(os.path.join(root_dir, file), "r") as f:
                text = f.read()
            print(file)
            xml_text = text_to_xml(text, file)

            new_dir = root_dir.replace(src_folder, dst_folder)
            os.makedirs(new_dir, exist_ok=True)
            new_file = os.path.join(new_dir, file.replace(".txt", ".xml"))

            with open(new_file, "w") as f:
                f.write(xml_text)
