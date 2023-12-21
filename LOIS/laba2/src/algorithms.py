# rule_tuple
# {"x1": 0,7, "x2": 0.1}
# fact_el
# 1.0
def my_choose_one(rule_tuple, fact_el_value):
    res = []
    for main_el in rule_tuple.keys():
        current_row = {}
        for el, value in rule_tuple.items():
            if main_el == el:
                current_el = calculate_equal(value, fact_el_value)
                current_row[el] = current_el
                #print(f'min({el},{value}) = {fact_el_value}, {el} in {current_el}')
            else:
                current_el = calculate_less(value, fact_el_value)
                current_row[el] = current_el
                #print(f'min({el},{value}) <= {fact_el_value}, {el} in {current_el}')
        res.append(current_row)
    return res


def calculate_equal(left, right): 
    if left < right: 
        res = None
    elif left == right: 
        res = [right, 1]
    else: 
        res = [right, right]
    return res


def calculate_less(left, right): 
    return [0, 1] if left <= right else [0, right]


# {"y1": [{"x1": None, "x2": [0.1, 1]}, {"x1": [0.1, 1], "x2": None}], "y2": [...], ...}
def convert_to_list(dct):
    result = []
    for value in dct.values():
        result.append([list(x.values()) for x in value])
    return result

# [ 
#    [ 
#       [None, [0, 1]], 
#       [[0, 1], None] 
#    ],
#    [ 
#       [None, [0, 1]], 
#       [[0, 1], None] 
#    ],
#    [ 
#       [None, [0, 1]], 
#       [[0, 1], None] 
#    ],
# ]
def cycle(results):
    while len(results) > 1:
        temp = intersection_line(results[-2], results[-1])
        if temp is not None:
            results[-2] = temp
            results.pop()
        else: 
            return None
    return results


# [ 
#     [None, [0, 1]], 
#     [[0, 1], None] 
# ],
# [ 
#     [None, [0, 1]], 
#     [[0, 1], None] 
# ],
def intersection_line(line1, line2):
    line = []
    for cond1 in line1:
        for cond2 in line2:
            new_cond = intersection_cond(cond1, cond2)
            if new_cond:
                line.append(new_cond)
    return line

# [[0.1, 0.3], [0, 1]], 
# [[0.2, 0.7], [0, 1]], 
def intersection_cond(cond1, cond2):
    if None in cond1 or None in cond2: 
        return []  
    answ = [intersection(first, second) for first, second in zip(cond1, cond2)]
    return [] if None in answ else answ

# [0.1, 0.2]
# [0.3, 0.7]
def intersection(interval1, interval2):
    if not interval1 or not interval2: 
        return None
    x1 = max(interval1[0], interval2[0])
    x2 = min(interval1[1], interval2[1])
    return [x1, x2] if x1 <= x2 else None


def return_unique(left, right):
    left_unique_counter, left_right_counter = 0, 0
    for left_el, right_el in zip(left, right): 
        if left_el[0] >= right_el[0] and left_el[1] <= right_el[1]:
            left_right_counter += 1
        if left_el[0] <= right_el[0] and left_el[1] >= right_el[1]:
            left_unique_counter += 1
    if left_unique_counter == len(left):
        return left
    if left_right_counter == len(left):
        return right
    
        
def delete_unimportant(results):
    for i, el_i in enumerate(results):
        for j, el_j in enumerate(results):
            if el_i and el_j and i != j:
                rez = return_unique(el_i, el_j)
                if rez == el_i: 
                    results[j] = None
                if rez == el_j: 
                    results[i] = None
    return list(filter(lambda a: a, results))



