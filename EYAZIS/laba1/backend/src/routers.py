import io
from docx import Document
from fastapi import APIRouter, UploadFile
from fastapi import HTTPException, status

from schemas import Word
from functions import generate_word_form, get_lexemes, get_lexems_to_text

router = APIRouter(
    prefix="/word",
    tags=[""]
)

@router.post("/generate")
async def generate_word(word: Word) -> str:
    return generate_word_form(word)


@router.post('/parsing/sentence')
async def sentence_parsing(file: UploadFile):
    try:
        file_content = await file.read()
        file_object = io.BytesIO(file_content)
        doc = Document(file_object)
        sentence = '\n'.join([paragraph.text for paragraph in doc.paragraphs])
        return get_lexems_to_text(get_lexemes(sentence))
    except FileNotFoundError:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="File not found")
    except Exception as e:
        raise HTTPException(status_code=status.HTTP_422_UNPROCESSABLE_ENTITY, detail="Unprocessable entity")