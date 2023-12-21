import re

def parse():

    rules_pattern = r"^[A-Z]=\{(\(\([a-x\d]+\,[a-z\d]+\)\,\d\.\d\)\,?)*\}$"
    facts_pattern = r"^[A-Z]=\{(\([a-z\d]+\,\d\.\d\),?)*\}$"
    
    facts, rules, used_names = [], [], [],
    
    with open("data", 'r') as file:
        for line in file:

            line = line.strip()
            line = line.replace(" ", "")
            line = line.replace(',0)', ',0.0)')
            line = line.replace(',1)', ',1.0)')

            rule_match = re.fullmatch(rules_pattern, line)
            fact_match = re.fullmatch(facts_pattern, line)
            
            if rule_match:
                try:
                    rule = parse_rule(rule_match, used_names)
                except ValueError as e:
                    print(e)
                    continue
                rules.append(rule)
                used_names.append(list(rule)[0])

            elif fact_match:
                try:
                    fact = parse_fact(fact_match, used_names)
                except ValueError as e:
                    print(e)
                    continue
                facts.append(fact)
                used_names.append(list(fact)[0])

            else:
               print(f"Line '{line}' is NOT in the correct format.")
                    
    return rules, facts


def parse_rule(match, used_names):

    name = match.group().split('=')[0].strip()
               
    if name in used_names:
        raise ValueError(f"Rule name '{name}' is already used. Skipping...")

    values = re.findall(r"(\(\([a-x\d]+\,[a-z\d]+\)\,\d\.\d\))\,?", match.group())
    values = (re.findall(r"\(\(([a-x\d]+)\,([a-z\d]+)\)\,(\d\.\d)\)", value) for value in values)
    values = [(value[0][0], value[0][1], float(value[0][2])) for value in values]

    values_dct = {}
    for value in values:
        if not values_dct.get(value[1]):
            values_dct[value[1]] = {}
        values_dct[value[1]][value[0]] = value[2]

    result = {name: values_dct}
    return result


def parse_fact(match, used_names):

    name = match.group().split('=')[0].strip()
               
    if name in used_names:
        raise ValueError(f"Fact name '{name}' is already used. Skipping...")

    values = re.findall(r"(\([a-z\d]+\,\d\.\d\)),?", match.group())
    values = (re.findall(r"\(([a-z\d]+)\,(\d\.\d)\)", value) for value in values)

    values_dict = {value[0][0]: float(value[0][1]) for value in values}

    result = {name: values_dict}
    return result
