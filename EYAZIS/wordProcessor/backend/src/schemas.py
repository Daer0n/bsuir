from pydantic import BaseModel

class Word(BaseModel):
    base: str
    gender: str
    case: str
    number: str