from nltk.corpus import stopwords
import nltk
import json
from typing import Dict, Union
from metadata import metadata
import os


def prepare() -> Dict[str, Dict[str, Union[str, int]]]:
    corpus = {}
    russian_stopwords = set(stopwords.words("russian"))
    tokenizer = nltk.data.load('tokenizers/punkt/russian.pickle')

    for category in ['pos', 'neg']:
        files = os.listdir(f"data/movie_reviews/{category}")
        for file in files:
            with open(f"data/movie_reviews/{category}/{file}", "r", encoding="utf-8", errors="ignore") as f:
                raw_text = f.read()
                sentences = tokenizer.tokenize(raw_text)

                for sentence in sentences:
                    words = nltk.word_tokenize(sentence)
                    for word in words:
                        word = word.lower()
                        if word.isalpha() and word not in russian_stopwords:
                            pos_tag = nltk.pos_tag([word])[0][1]
                            if pos_tag in metadata:
                                if word not in corpus:
                                    corpus[word] = {
                                        "frequency": 1,
                                        "additional_information": metadata[pos_tag],
                                    }
                                else:
                                    corpus[word]["frequency"] += 1

    with open("data/movie_corpus.json", "w", encoding="utf-8") as file:
        json.dump(corpus, file, indent=4, ensure_ascii=False)

    return corpus