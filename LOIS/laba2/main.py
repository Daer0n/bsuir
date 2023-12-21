
from src.parse import parse
from src.algorithms import *
from src.str_converters import *


# rules
# {"A": {"y1": {"x1": 0.7, "x2", 0.7, ...}, "y2": {...}, ...}}
        
# facts
# {"D": {"y1": 0.7, "y2": 0.3, ...}}
def main():   
    rules, facts = parse()
    for rule in rules:
        for fact in facts:
            rule_name = list(rule)[0]
            rule_value = list(rule.values())[0]

            fact_name = list(fact)[0]
            fact_value = list(fact.values())[0]

            print(header_to_str(rule_name, rule_value, fact_name, fact_value))

            # {"y1": [{"x1": None, "x2": [0.1, 1]}, {"x1": [0.1, 1], "x2": None}], "y2": [...], ...}
            results = {}
            for fact_el_key, fact_el_value in fact_value.items():
                results[fact_el_key] = my_choose_one(rule_value[fact_el_key], fact_el_value)

            print(result_to_str(results, fact_value, rule_value))

            results_list = convert_to_list(results)
            results_list = cycle(results_list)  

            answer = delete_unimportant(*results_list)
            print(answer_to_str(answer), end="\n\n\n")


if __name__ == "__main__":
    main()
