from pydantic import BaseModel

class Word(BaseModel):
    base: str
    gender: str
    case: str
    number: str

class Context(BaseModel):
    word: str
    length: int
    count: int