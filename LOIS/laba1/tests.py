from src.operations import *
from src.data_loader import load_from_file
from src.data_validators import remove_variable_from_head

assert(conjunction({"x": 0.1, "y": 1, "z": 0, "f": 0.4}, {"x": 0.5, "y": 0, "z": 0.2, "d": 0.5})== {"x": 0.5, "y":1,"z":0.2, "f":0.4, "d": 0.5})
assert(disjunction({"x": 0.1, "y": 1, "z": 0, "f": 0.4}, {"x": 0.5, "y": 0, "z": 0.2, "d": 0.5})=={"x": 0.1, "y": 0, "z": 0})
assert(difference({"x": 0.1, "y": 1, "z": 0, "f": 0.4}, {"x": 0.5, "y": 0, "z": 0.2, "d": 0.5})=={"x": 0, "y":1,"z":0, "f": 0.4})

    
assert(remove_variable_from_head("p(x)") == "p()")
assert(remove_variable_from_head("p(x, y)") == "p(,)")
assert(remove_variable_from_head("f(x)") == "f()")
assert(remove_variable_from_head("f(x, y)") == "f(,)")
