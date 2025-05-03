class SetADT:
    def __init__(self):
        # Store elements in a dictionary for fast lookup
        self._elements = {}

    def add(self, element):
        # Add an element to the set
        self._elements[element] = True

    def remove(self, element):
        # Remove an element from the set if it exists
        if element in self._elements:
            del self._elements[element]

    def contains(self, element):
        # Check if an element is in the set
        return element in self._elements

    def size(self):
        # Return the number of elements in the set
        return len(self._elements)

    def iterator(self):
        # Return an iterator to loop over the set
        return iter(self._elements)

    def union(self, other):
        # Return a new set with all elements from both sets
        result = SetADT()
        for elem in self._elements:
            result.add(elem)
        for elem in other._elements:
            result.add(elem)
        return result

    def intersection(self, other):
        # Return a new set with elements common to both sets
        result = SetADT()
        for elem in self._elements:
            if elem in other._elements:
                result.add(elem)
        return result

    def difference(self, other):
        # Elements in self but not in other
        result = SetADT()
        for elem in self._elements:
            if elem not in other._elements:
                result.add(elem)
        return result

    def is_subset(self, other):
        # True if every element in self is also in other
        for elem in self._elements:
            if elem not in other._elements:
                return False
        return True

    def is_proper_subset(self, other):
        # True if self is subset of other and smaller
        return self.is_subset(other) and self.size() < other.size()

    def __str__(self):
        # Print set like {1, 2, 3}
        return "{" + ", ".join(str(e) for e in self._elements) + "}"

# Example usage:
if __name__ == "__main__":
    # Create two sets
    A = SetADT()
    B = SetADT()
    # Add elements
    for x in [1, 2, 3]:
        A.add(x)
    for x in [2, 3, 4]:
        B.add(x)
    # Show sets and operations
    print("A:", A)
    print("B:", B)
    print("Union:", A.union(B))
    print("Intersection:", A.intersection(B))
    print("Difference (A-B):", A.difference(B))
    print("A is subset of B:", A.is_subset(B))
    print("A is proper subset of B:", A.is_proper_subset(B))
