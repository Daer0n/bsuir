import nltk
from nltk.text import Text
from nltk.corpus import stopwords, movie_reviews
import pymorphy2

from schemas import Word
from typing import Dict, List, Union
import os
import json
import codecs
from utils.prepare_corpus import prepare

nltk.download('punkt')
#nltk.download('movie_reviews')
nltk.download('averaged_perceptron_tagger')


def get_lexemes(text):
    words = nltk.word_tokenize(text.lower(), language='russian')
    morph = pymorphy2.MorphAnalyzer()
    lexemes = []
    for word in words:
        if not word.isalpha():
            continue
        parse = morph.parse(word)[0]
        lexeme = {
            'base': parse.normal_form,  
            'pos': parse.tag.POS, 
            'gender': parse.tag.gender, 
            'number': parse.tag.number,  
            'case': parse.tag.case, 
            'tense': parse.tag.tense,  
            'aspect': parse.tag.aspect  
        }
        lexemes.append(lexeme)
    lexemes.sort(key=lambda x: x['base'])
    return lexemes

def generate_word_form(word: Word):
    morph = pymorphy2.MorphAnalyzer()
    parse = morph.parse(word.base)[0]
    tags = {
        "мужской": "masc",
        "женский": "femn", 
        "средний": "neut", 
        "именительный": "nomn", 
        "родительный": "gent",
        "дательный": "datv",
        "винительный": "accs",
        "творительный": "ablt", 
        "предложный": "loct",
        "единственное": "sing", 
        "множественное": "plur"
    }
    gram_info = {tags[v] for v in {word.gender, word.case, word.number}}
    return parse.inflect(gram_info).word

def get_lexems_to_text(lexems):
    result = []
    tags = {
        "NOUN": "существительное",
        "ADJF": "прилагательное",
        "ADJS": "прилагательное",
        "COMP": "компаратив",
        "VERB": "глагол",
        "INFN": "глагол",
        "PRTF": "причастие",
        "PRTS": "причастие",
        "GRND": "деепричастие",
        "NUMR": "числительное",
        "ADVB": "наречие",
        "NRPO": "местоимение-существительное",
        "PRED": "предикатив",
        "PREP": "предлог",
        "CONJ": "союз",
        "PRCL": "частица",
        "INTJ": "междометие",
        "nomn": "именительный",
        "gent": "родительный",
        "datv": "дательный",
        "accs": "винительный",
        "ablt": "творительный",
        "loct": "предложный",
        "sing": "единственное",
        "plur": "множественное",
        "masc": "мужской",
        "femn": "женский",
        "neut": "средний"
    }

    for item in lexems:
        lexem = {
            'Основа': item['base'],
            'ч.речи': tags.get(item['pos'])
        }
        if item['gender'] is not None:
            lexem['род'] = tags.get(item['gender'])
        if item['number'] is not None:
            lexem['число'] = tags.get(item['number'])
        if item['case'] is not None:
            lexem['падеж'] = tags.get(item['case'])
        result.append(lexem)

    return result

def import_corpus() -> Dict[str, Dict[str, Union[str, int]]]:
    with open("data/movie_corpus.json", "r") as file:
        try:
            corpus = json.load(file)
        except json.JSONDecodeError:
            corpus = {}

    return corpus

def find_words(words: List[str]) -> Dict[str, Dict[str, Union[str, int]]]:
    words_with_info = dict()
    if not os.path.isfile("./data/movie_corpus.json"):
        frequency = prepare()
    else:
        frequency = import_corpus()

    for i in words:
        try:
            if frequency[i]["frequency"] != 0:
                words_with_info[i] = frequency[i]
        except KeyError:
            continue

    return words_with_info

def main_corpus(text: str) -> Dict[str, Dict[str, Union[str, int]]]:
    parsed_text = list()

    for i in nltk.word_tokenize(text):
        if i not in stopwords.words():
            parsed_text.append(i)
    words_dict = find_words(parsed_text)
    return words_dict

def find_context(word: str, length: int, count: int) -> str:
    words = []
    with codecs.open(movie_reviews.abspath(movie_reviews.fileids()[0]), encoding='utf-8') as file:
        for line in file:
            words.extend(line.split())

    text = Text(words)
    con_list = text.concordance_list(word, width=length, lines=count)
    return "\n".join([f"{i + 1}. {j.line}" for i, j in enumerate(con_list)])

