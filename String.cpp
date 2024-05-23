#define _CRT_SECURE_NO_WARNINGS 
#include "String.h"
#include <iostream>
#include <string.h>
    // Konstruktor
    String::String() : m_data(nullptr), m_size(0) {}

    // Konstruktor z jednym argumentem
    String::String(const char* str) {
        m_size = strlen(str);
        m_data = new char[m_size + 1];
        strcpy(m_data, str);
    }

    // Konstruktor kopiuj¹cy
    String::String(const String& other) {
        m_size = other.m_size;
        m_data = new char[m_size + 1];
        strcpy(m_data, other.m_data);
    }

    // Destruktor
    String::~String() {
        delete[] m_data;
    }

    // Funkcja zwracaj¹ca rozmiar stringa
    size_t String::size() const {
        return m_size;
    }

    // Funkcja zwracaj¹ca wskaŸnik do danych stringa
    const char* String::c_str() const {
        return m_data;
    }

    // Operator przypisania
    String& String::operator=(const String& other) {
        if (this != &other) {//sprawdzam czy wskasuja na ten sam obiekt w pamieci
            delete[] m_data;
            m_size = other.m_size;
            m_data = new char[m_size + 1];
            strcpy(m_data, other.m_data);
        }
        return *this;
    }

    // Operator dodawania stringów
    String String::operator+(const String& other) const {
        size_t new_size = m_size + other.m_size;
        char* new_data = new char[new_size + 1];
        strcpy(new_data, m_data);
        strcat(new_data, other.m_data);//dziala tak ze dopisuje na koniec
        String new_string(new_data);
        delete[] new_data;
        return new_string;
    }

    // Operator porównania stringów
    bool String::operator==(const String& other) const {
        return strcmp(m_data, other.m_data) == 0;
    }

    // Operator nierównoœci stringów
    bool String::operator!=(const String& other) const {
        return !(*this == other);
    }

    // Operator mniejszoœci stringów
    bool String::operator<(const String& other) const {
        return strcmp(m_data, other.m_data) < 0;
    }

    // Operator wiêkszoœci stringów
    bool String::operator>(const String& other) const {
        return strcmp(m_data, other.m_data) > 0;
    }

    // Operator mniejszoœci lub równoœci stringów
    bool String::operator<=(const String& other) const {
        return strcmp(m_data, other.m_data) <= 0;
    }

    // Operator wiêkszoœci lub równoœci stringów
    bool String::operator>=(const String& other) const {
        return strcmp(m_data, other.m_data) >= 0;
    }

    // Operator indeksowania
    char& String::operator[](size_t index) {
        return m_data[index];
    }

    // Funkcja zwracaj¹ca znak na podanej pozycji
    char& String::at(size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range.");
        }
        return m_data[index];
    }

    // Funkcja przekszta³caj¹ca string na liczbe calkowita
    int String::to_int() const {
        return std::atoi(m_data);
    }

    std::istream& operator>>(std::istream& in, String& str) {//czyta ci¹g znaków z wejœcia, a nastêpnie tworzy nowy obiekt klasy String na podstawie tego ci¹gu za pomoc¹ konstruktora z jednym argumentem. zwracany jest strumieñ wejœciowy
        char buffer[4096];
        in >> buffer;
        str = String(buffer);
        return in;
    }
    std::ostream& operator<<(std::ostream& out, const String& str) {//wypisuje zawartoœæ stringa na strumieñ wyjœciowy (std::ostream)
        out << str.m_data;
        return out;
    }

    

    void String::erase(size_t pos, size_t count) {
        if (pos >= m_size) {
            throw std::out_of_range("Index out of range.");
        }
        // Jeœli count jest wiêksze od liczby pozosta³ych znaków po pozycji pos,
        // to usuwamy tylko tyle znaków, ile jest pozosta³ych po pozycji pos.
        if (count > m_size - pos) {
            count = m_size - pos;
        }
        // Przesuwamy znaki od pozycji pos + count do pozycji pos
        for (size_t i = pos + count; i <= m_size; i++) {
            m_data[i - count] = m_data[i];
        }
        m_size -= count;
        m_data[m_size] = '\0';
    }

    String String::substr(size_t pos, size_t count) const {
        if (pos >= m_size) {
            //throw std::out_of_range("Index out of range.");
            return "";
        }
        // Jeœli count jest wiêksze od liczby pozosta³ych znaków po pozycji pos,
        // to zwracamy tylko tyle znaków, ile jest pozosta³ych po pozycji pos.
        if (count > m_size - pos) {
            count = m_size - pos;
        }
        // Tworzymy nowy string zawieraj¹cy podci¹g
        char* new_data = new char[count + 1];
        strncpy(new_data, m_data + pos, count);
        new_data[count] = '\0';
        String new_string(new_data);
        delete[] new_data;
        return new_string;
    }

    size_t String::find(const String& substr) const {
        const char* result = strstr(m_data, substr.m_data);//strstr, która zwraca wskaŸnik na pierwsze wyst¹pienie pod³añcucha w ci¹gu. Funkcja find zwraca pozycjê pierwszego wyst¹pienia pod³añcucha, lub std::string::npos
        if (result == nullptr) {
            return std::string::npos;
        }
        return result - m_data;
    }

    bool String::empty() const {
        return m_size == 0;
    }

    size_t String::find_first_of(const char* chars) const {//Ta funkcja wyszukuje pierwsze wyst¹pienie jednego z znaków podanych w ³añcuchu chars w obiekcie String. Do tego celu wykorzystywana jest funkcja strpbrk, która zwraca wskaŸnik na pierwsze wyst¹pienie dowolnego znaku z ³añcucha chars w ci¹gu
        const char* result = strpbrk(m_data, chars);
        if (result == nullptr) {
            return std::string::npos;
        }
        return result - m_data;
    }

    size_t String::find_first_not_of(const char* charsToSkip) const {//wyszukuje pierwsze wyst¹pienie znaku, który nie nale¿y do podanego jako argument charsToSkip ³añcucha w obiekcie String. Algorytm iteruje po kolejnych znakach ³añcucha, sprawdzaj¹c czy ka¿dy z nich znajduje siê w charsToSkip. Jeœli znak nie nale¿y do charsToSkip, to jego pozycja zostaje zwrócona. Gdy wszystkie znaki s¹ elementami charsToSkip, zwracana jest wartoœæ std::string::npos
        size_t i = 0;
        while (i < m_size) {
            bool skipChar = false;
            for (size_t j = 0; charsToSkip[j] != '\0'; j++) {
                if (m_data[i] == charsToSkip[j]) {
                    skipChar = true;
                    break;
                }
            }
            if (!skipChar) {
                return i;
            }
            i++;
        }
        return npos;
    }

    size_t String::find_last_not_of(const char* chars) const {//Funkcja przechodzi przez ci¹g znaków w odwrotnej kolejnoœci, a¿ znajdzie pierwszy znak, który nie jest obecny w ci¹gu chars, lub dojdzie do pocz¹tku ci¹gu. Jeœli znak zostanie znaleziony, funkcja zwraca jego pozycjê, a w przeciwnym przypadku zwraca npos
        if (m_data == nullptr) {
            return npos;
        }

        size_t pos = m_size;
        bool found = false;
        while (pos > 0 && !found) {
            pos--;
            found = true;
            for (size_t i = 0; chars[i] != '\0'; i++) {
                if (m_data[pos] == chars[i]) {
                    found = false;
                    break;
                }
            }
        }

        return found ? pos : npos;
    }

    size_t String::find_first_of(const char* chars, size_t pos) const {//szuka pierwszego znaku w ci¹gu, który znajduje siê w podanym ci¹gu znaków chars. Funkcja rozpoczyna szukanie od pozycji pos i przeszukuje ci¹g znaków w poszukiwaniu pierwszego znaku, który znajduje siê w ci¹gu chars. Jeœli taki znak zostanie znaleziony, funkcja zwraca jego pozycjê, a w przeciwnym przypadku zwraca npos.
        if (pos >= m_size) {
            throw std::out_of_range("Starting position out of range.");
        }
        const char* result = std::strpbrk(m_data + pos, chars);
        if (result == nullptr) {
            return std::string::npos;
        }
        return result - m_data;
    }

    size_t String::find_last_of(const char c) const {//szuka ostatniego wyst¹pienia danego znaku c w ci¹gu. Funkcja przeszukuje ci¹g znaków od koñca i zwraca pozycjê ostatniego wyst¹pienia danego znaku c
        char* p = strrchr(m_data, c);
        if (p == nullptr) {
            return std::string::npos;
        }
        return p - m_data;
    }
 

