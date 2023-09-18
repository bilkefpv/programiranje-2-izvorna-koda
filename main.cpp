#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
class Kopica {
private:
    std::vector<int> heap;
    // Metode za pridobivanje indeksa starša, levega in desnega otroka
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }
    // Metode za vzdrževanje kopice
    void siftUp(int i) {
        while (i && heap[parent(i)] > heap[i]) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    void siftDown(int i) {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < count() && heap[l] < heap[i])
            smallest = l;
        if (r < count() && heap[r] < heap[smallest])
            smallest = r;
        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            siftDown(smallest);
        }
    }
public:
    // Vstavi element v kopico 
    void insert(int val) {
        heap.push_back(val);
        int index = heap.size() - 1;
        siftUp(index);
    }
    // Izbriše najmanjši element iz kopice 
    void deletemin() {
        if (heap.size() == 0) return;
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);
    }
    // Vrne število elementov v kopici
    int count() const {
        return heap.size();
    }
    // Vrne elemente kopice v padajočem vrstnem redu
    std::vector<int> getElementsInDescendingOrder() {
    std::vector<int> copy = heap;
    std::sort(copy.begin(), copy.end(), std::greater<int>());
    return copy;
}

    // Singleton vzorec za pridobitev instance kopice
    static Kopica* getInstance() {
        static Kopica instance;
        return &instance;
    }
    // Razred za obiskovalca (visitor pattern)
    class Visitor {
    public:
        virtual void visit(Kopica* heap) = 0;
    };
    // Razred za izpis kopice s pomočjo obiskovalca
    class PrintVisitor : public Visitor {
    public:
        void visit(Kopica* heap) override {
            std::vector<int> elements = heap->getElementsInDescendingOrder();izpis
            for (int element : elements) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    };
    // Metoda za sprejem obiskovalca
    void accept(Visitor* v) {
        v->visit(this);
    }
};
int main() {
    Kopica* heap = Kopica::getInstance();
    Kopica::PrintVisitor visitor;
    // Izpis prazne kopice
    heap->accept(&visitor);
    // Dodajanje in brisanje elementov ter izpis
    heap->insert(10);
    heap->accept(&visitor);
    heap->deletemin();
    heap->accept(&visitor);
    // Dodajanje več elementov, izpis
    heap->insert(20);
    heap->insert(5);
    heap->insert(1);
    heap->insert(7);
    heap->insert(10);
    heap->accept(&visitor);
    // Dodajanje več elementov, izpis
    for (int i = 21; i <= 40; ++i) {
        heap->insert(i);
    }
    heap->accept(&visitor);
    // Brisanje elementov, dodajanje, izpis
    heap->deletemin();
    heap->insert(4);
    heap->deletemin();
    heap->accept(&visitor);
        
     // Testiranje singletona
    Kopica* kopica1 = Kopica::getInstance();
    Kopica* kopica2 = Kopica::getInstance();
    assert(kopica1 == kopica2);
    assert(kopica1 == heap);
    assert(kopica2 == heap);

   
    std::cout << "Testi so uspešno opravljeni." << std::endl;

    return 0;
}
