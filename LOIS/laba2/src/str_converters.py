def header_to_str(rule_name, rule_value, fact_name, fact_value):
    return f'\033[92mStep:\n'\
            f'\t Rule:\t {rule_to_str(rule_name, rule_value)}\n'\
            f'\t Fact:\t {fact_to_str(fact_name, fact_value)}\n\033[00m'

def rule_to_str(rule_name, rule_value):
    pairs = [f"({x}, {y}), {row[x]})" for y, row in rule_value.items() for x in row]
    return f"{rule_name} = {'{' + ', '.join(pairs) + '}'}"


def fact_to_str(fact_name, fact_value):
    pairs = [f"({key}, {value})" for key, value in fact_value.items()]
    return f"{fact_name} = {'{' + ', '.join(pairs) + '}'}"


def result_to_str(result, facts, rules):
    result_str_lst = []
    for key, values in result.items():
        pairs = [f"({x}, {key}), {value})" for x, value in rules[key].items()]
        result_str_lst.append(f"from ({key}, {facts[key]}) and {'{' + ', '.join(pairs) +'}'}:")
        for line in values:
            result_str_lst.append("\t" + " and ".join(f"{key} ∈ {value if value else '∅'}" for key, value in line.items()))
        result_str_lst.append("")
    return "\n".join(result_str_lst)


def answer_to_str(answer):
    return "\033[91mAnswer: (" + ") U (".join(" x ".join(str(x) for x in part) for part in answer) + ")\033[00m"
