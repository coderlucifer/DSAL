#include <iostream>
#include <vector>
#include <algorithm>

class SetADT {
    std::vector<int> elements;

public:
    // Add an element if not already present
    void add(int element) {
        if (!contains(element))
            elements.push_back(element);
    }

    // Remove an element if present
    void remove(int element) {
        auto it = std::find(elements.begin(), elements.end(), element);
        if (it != elements.end())
            elements.erase(it);
    }

    // Check if element is present
    bool contains(int element) const {
        return std::find(elements.begin(), elements.end(), element) != elements.end();
    }

    // Return number of elements
    int size() const {
        return elements.size();
    }

    // Iterator support
    std::vector<int>::const_iterator begin() const { return elements.begin(); }
    std::vector<int>::const_iterator end() const { return elements.end(); }

    // Union of two sets
    SetADT set_union(const SetADT& other) const {
        SetADT result;
        for (int e : elements) result.add(e);
        for (int e : other.elements) result.add(e);
        return result;
    }

    // Intersection of two sets
    SetADT intersection(const SetADT& other) const {
        SetADT result;
        for (int e : elements)
            if (other.contains(e))
                result.add(e);
        return result;
    }

    // Difference between two sets
    SetADT difference(const SetADT& other) const {
        SetADT result;
        for (int e : elements)
            if (!other.contains(e))
                result.add(e);
        return result;
    }

    // Check if this set is a subset of another
    bool is_subset(const SetADT& other) const {
        for (int e : elements)
            if (!other.contains(e))
                return false;
        return true;
    }

    // Check if this set is a proper subset of another
    bool is_proper_subset(const SetADT& other) const {
        return is_subset(other) && size() < other.size();
    }

    // Print set elements
    void print() const {
        std::cout << "{ ";
        for (int e : elements)
            std::cout << e << " ";
        std::cout << "}\n";
    }
};

// Example usage
int main() {
    SetADT A, B;
    A.add(1); A.add(2); A.add(3);
    B.add(2); B.add(3); B.add(4);

    std::cout << "A: "; A.print();
    std::cout << "B: "; B.print();

    std::cout << "Union: "; A.set_union(B).print();
    std::cout << "Intersection: "; A.intersection(B).print();
    std::cout << "Difference (A-B): "; A.difference(B).print();
    std::cout << "A is subset of B: " << (A.is_subset(B) ? "Yes" : "No") << "\n";
    std::cout << "A is proper subset of B: " << (A.is_proper_subset(B) ? "Yes" : "No") << "\n";

    return 0;
}
