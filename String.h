#include <iostream>
class String {
private:
    char* m_data;
    size_t m_size;
    
public:
    static const size_t npos = static_cast<size_t>(-1);
    // Konstruktor
    String();
    friend std::istream& operator>>(std::istream& in, String& str);
    friend std::ostream& operator<<(std::ostream& out, const String& str);

    // Konstruktor z jednym argumentem
    String(const char* str);

    // Konstruktor kopiuj¹cy
    String(const String& other);

    // Destruktor
    ~String();

        // Funkcja zwracaj¹ca rozmiar stringa
        size_t size() const;

    // Funkcja zwracaj¹ca wskaŸnik do danych stringa
        const char* c_str() const;

    // Operator przypisania
        String& operator=(const String& other);

    // Operator dodawania stringów
        String operator+(const String& other) const;

    // Operator porównania stringów
        bool operator==(const String& other) const;

    // Operator nierównoœci stringów
        bool operator!=(const String& other) const;

    // Operator mniejszoœci stringów
        bool operator<(const String& other) const;

    // Operator wiêkszoœci stringów
        bool operator>(const String& other) const;

    // Operator mniejszoœci lub równoœci stringów
        bool operator<=(const String& other) const;

    // Operator wiêkszoœci lub równoœci stringów
        bool operator>=(const String& other) const;

    // Operator indeksowania
        char& operator[](size_t index);

    // Funkcja zwracaj¹ca znak na podanej pozycji
        char& at(size_t index);

    // Funkcja przekszta³caj¹ca string na liczbe calkowita
    int to_int() const ;
    

    void erase(size_t pos, size_t count);

    String substr(size_t pos, size_t count) const;

    size_t find(const String& substr) const;

    bool empty() const;

    size_t find_first_of(const char* chars) const;

    size_t find_first_not_of(const char* charsToSkip) const;

    size_t find_last_not_of(const char* chars) const;

    size_t find_first_of(const char* chars, size_t pos) const;

    size_t find_last_of(const char c) const;
    
};
