import nltk
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords

import xml.etree.ElementTree as ET
import xml.dom.minidom
import string
import os
import re
from pathlib import Path

from metadata import metadata

nltk.download('punkt')
nltk.download('stopwords')

def text_to_xml(text: str, root_name: str) -> str:
    text = re.sub(r"[^\x20-\x7F]", "", text)
    root = ET.Element(root_name)

    sentences = sent_tokenize(text, language='russian')

    stop_words = set(stopwords.words("russian")).union(set(string.punctuation))
    sentence_counter = 0
    for sentence in sentences:
        sentence_element = ET.SubElement(root, "sentence", id=str(sentence_counter + 1))

        words = word_tokenize(sentence, language='russian')
        words_counter = 0
        for word in words:
            if word not in stop_words:
                try:
                    word_element = ET.SubElement(
                        sentence_element,
                        "word",
                        id=str(words_counter + 1),
                        info=metadata[nltk.pos_tag([word], lang='rus')[0][1]],
                    )

                    word_element.text = word
                    words_counter += 1
                except KeyError:
                    continue
        
        if len(sentence_element) > 0:
            root.append(sentence_element)
            sentence_counter += 1

    xml_str = ET.tostring(root, encoding="utf-8")

    dom = xml.dom.minidom.parseString(xml_str)
    pretty_xml_str = dom.toprettyxml(indent="  ")

    return pretty_xml_str


src_folder = "../data/movie_reviews"

dst_folder = "../data/movie_reviews_converted"
os.makedirs(dst_folder, exist_ok=True)

for root_dir, dirs, files in os.walk(src_folder):
    for file in files:
        if file.endswith(".txt"):
            with open(os.path.join(root_dir, file), "r", encoding="utf-8") as f:
                text = f.read()
            print(file)
            xml_text = text_to_xml(text, file)

            new_dir = root_dir.replace(src_folder, dst_folder)
            os.makedirs(new_dir, exist_ok=True)
            new_file = os.path.join(new_dir, file.replace(".txt", ".xml"))

            with open(new_file, "w", encoding="utf-8") as f:
                f.write(xml_text)