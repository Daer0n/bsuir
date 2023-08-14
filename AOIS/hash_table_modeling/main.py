from collections import defaultdict
from typing import Any, Optional


class HashTable:

     def __init__(self):
         self.capacity = 50
         self.data = defaultdict(list)
         self.length = 0

     def get_item(self, key: str) -> Optional[Any]:
         hash_key = self._hash_key(key)
         try:
             value = self.data[hash_key]
         except KeyError:
             return None

         return value

     def add_item(self, key: str, value: Any) -> None:
         hash_key = self._hash_key(key)
         if self.get_item(key):
             self.delete_item(key)
         self.data[hash_key].append((key, value))
         self.length += 1
         if self.length == self.capacity:
             self.rehash()

     def delete_item(self, key: str) -> None:
        hash_key = self._hash_key(key)
        self.data[hash_key] = list(filter(lambda item: item[0] != key, self.data[hash_key]))
        self.length -= 1

     def _hash_key(self, key: str) -> int:
         value = 0
         for i in range(0, 3):
            value += ord(key[i])
         return value % self.capacity


     def rehash(self) -> None:
         self.capacity += 50
         new_data = defaultdict(list)
         for items in self.data.values():
             for item in items:
                 hash_key = self._hash_key(item[0])
                 new_data[hash_key].append(item)
         self.data = new_data

     def print_hash_table(self) -> None:
         print(self.data.values())

def main():
    hash_table = HashTable()
    hash_table.add_item('Audi', 'c4 100')
    hash_table.add_item('Audi', 'С5 200')
    hash_table.add_item('Bmw', 'M5')
    hash_table.add_item('Ford', 'Mondeo 1')
    hash_table.add_item('Citroen', 'c5')

    print(hash_table.get_item('Audi'))

    hash_table.print_hash_table()

    hash_table.delete_item('Bmw')

    hash_table.print_hash_table()

if __name__ == "__main__":
    main()