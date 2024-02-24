import nltk
import pymorphy2

from schemas import Word

def get_lexemes(text):
    # разбиваем текст на слова
    words = nltk.word_tokenize(text.lower(), language='russian')
    # создаем объект MorphAnalyzer для морфологического анализа слов
    morph = pymorphy2.MorphAnalyzer()
    lexemes = []
    for word in words:
        # пропускаем знаки препинания
        if not word.isalpha():
            continue
        # получаем морфологические характеристики слова
        parse = morph.parse(word)[0]
        # создаем запись для каждой лексемы
        lexeme = {
            'base': parse.normal_form,  # основа слова
            'pos': parse.tag.POS,  # часть речи
            'gender': parse.tag.gender,  # род
            'number': parse.tag.number,  # число
            'case': parse.tag.case,  # падеж
            'tense': parse.tag.tense,  # время (для глаголов)
            'aspect': parse.tag.aspect  # вид (для глаголов)
        }
        # добавляем лексему в список
        lexemes.append(lexeme)
    # сортируем список лексем по алфавиту
    lexemes.sort(key=lambda x: x['base'])
    return lexemes

def generate_word_form(word: Word):
    """
    Функция генерирует словоформу по заданным параметрам
    word: базовая форма слова
    gender: род: "муж", "жен", "сред"
    case: падеж: "им", "род", "дат", "вин", "твор", "пр", "мест"
    number: число: "ед", "мн"
    return: словоформа в соответствии с заданными параметрами
    """
    morph = pymorphy2.MorphAnalyzer()
    parse = morph.parse(word.base)[0]
    tags = {"муж": "masc", "жен": "femn", "сред": "neut", "им": "nomn", "род": "gent",
            "дат": "datv", "вин": "accs", "твор": "ablt", "пр": "loct","ед": "sing", "мн": "plur"}
    gram_info = {tags[v] for v in {word.gender, word.case, word.number}}
    return parse.inflect(gram_info).word

def get_lexems_to_text(lexems):
    txt = ""
    tags = {"NOUN":"сущ.", "ADJF":"прилаг.", "ADJS":"прилаг.", "COMP":"компаратив", "VERB":"глагол", "INFN":"глагол","PRTF":"причастие",
            "PRTS":"причастие", "GRND":"дееприч.", "NUMR":"числит.", "ADVB": "наречие", "NRPO":"местоим.-сущ.","PRED":"предикатив",
            "PREP":"предлог","CONJ":"союз","PRCL":"частица","INTJ":"междометие","nomn":"Им.п.", "gent":"Род.п.","datv":"Дат.п.",
            "accs":"Вин.п.","ablt":"Твор.п.","loct":"Пред.п.","sing":"ед.ч.","plur":"мн.ч","masc":"муж.р.","femn":"жен.р.","neut":"ср.р"}
    for item in lexems:
        txt += "Основа: "
        txt += item['base'] + ", ч.речи: "
        txt += tags[item['pos']]
        if item['gender'] != None:
            txt +=", род: " + tags[item['gender']]
        if item['number'] !=None:
            txt +=', число: ' + tags[item['number']]
        if item['case'] != None:
            txt +=', падеж: ' + tags[item['case']]

        txt +='\n'
    return txt