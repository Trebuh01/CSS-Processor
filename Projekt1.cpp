#include <iostream>
#include "List.h"
#include "Block_List.h"
#include "String.h"
#include <string.h>
using namespace std;
struct Sekcja {
    Block_List<String> attributeName;
    Block_List<String> attributeValue;
    Block_List<String> sectionName;
};
void parsowanie(Block_List<Sekcja*>& lista);
void komendy(Block_List<Sekcja*>& lista);
int main()
{
    Block_List<Sekcja*> lista;
    parsowanie(lista);

}
void parsowanie(Block_List<Sekcja*>& lista)
{
    String znak = "";
    while (1)
    {
        Sekcja* sekcja = new Sekcja;
        if (znak != "????")znak = "";
        String cssCode = "";
        char buffer[1000];
        if (fgets(buffer, 1000, stdin) == NULL) break;
        buffer[strcspn(buffer, "\n")] = '\0'; // usuwa znak końca linii
        znak = buffer;
        if (znak == "" || znak == " " || znak == "\t")continue;
        if (znak == "????")
        {
            komendy(lista);
        }
        else if (znak != "")
        {
            while (znak.empty() == 0 && znak[znak.size() - 1] != '}' && znak != "????")
            {
                cssCode = cssCode + znak;
                if (fgets(buffer, 1000, stdin) == NULL) break;
                buffer[strcspn(buffer, "\n")] = '\0'; // usuwa znak końca linii
                znak = buffer;
                int lastNonWhitespaceZ = znak.find_last_not_of(" \t\r\n");
                if (lastNonWhitespaceZ != std::string::npos && lastNonWhitespaceZ != znak.size() - 1) {
                    znak = znak.substr(0, lastNonWhitespaceZ + 1);
                }

            }
            if (znak.size() > 1)cssCode = cssCode + znak;
            if (znak == "????")break;
            size_t selectorStart = 0;
            size_t selectorEnd = cssCode.find_first_of("{");
            String selectors = cssCode.substr(selectorStart, selectorEnd - selectorStart);

            // Wypisanie nazw selektorów
            size_t selectorPos = 0;
            while (selectorPos < selectors.size()) {
                size_t selectorEndPos = selectors.find_first_of(",", selectorPos);
                if (selectorEndPos == String::npos) {
                    selectorEndPos = selectors.size();
                }
                String selectorName = selectors.substr(selectorPos, selectorEndPos - selectorPos);
                selectorName.erase(0, selectorName.find_first_not_of(" \t\r\n"));


                int lastNonWhitespaceName = selectorName.find_last_not_of(" \t\r\n");
                if (lastNonWhitespaceName != std::string::npos && lastNonWhitespaceName != selectorName.size() - 1) {
                    selectorName = selectorName.substr(0, lastNonWhitespaceName + 1);
                }
                //sprawdzanie duplikatow

                bool foundDuplicate = false;
                for (int i = 1; i <= sekcja->sectionName.rozmiar(); i++) {

                    if (*sekcja->sectionName.getElement(i) == selectorName)
                    {
                        foundDuplicate = true;
                        break;
                    }

                }

                if (foundDuplicate == false)
                {
                    sekcja->sectionName.push_back(selectorName);
                }

                selectorPos = selectorEndPos + 1;
            }

            // Wydzielenie atrybutów z kodu CSS
            size_t attributeStart = cssCode.find_first_of("{") + 1;
            size_t attributeEnd = cssCode.find_first_of("}");
            String attributes = cssCode.substr(attributeStart, attributeEnd - attributeStart);

            int lastNonWhitespaceAtr = attributes.find_last_not_of(" \t\r\n");
            if (lastNonWhitespaceAtr != std::string::npos && lastNonWhitespaceAtr != attributes.size() - 1) {
                attributes = attributes.substr(0, lastNonWhitespaceAtr + 1);
            }

            // Wypisanie nazw atrybutów i ich wartości
            size_t attributePos = 0;
            while (attributePos < attributes.size()) {
                size_t attributeEndPos = attributes.find_first_of(";", attributePos);
                if (attributeEndPos == String::npos) {
                    attributeEndPos = attributes.size();
                }
                String attribute = attributes.substr(attributePos, attributeEndPos - attributePos);

                attribute.erase(0, attribute.find_first_not_of(" \t\r\n"));


                int lastNonWhitespace = attribute.find_last_not_of(" \t\r\n");
                if (lastNonWhitespace != std::string::npos && lastNonWhitespace != attribute.size() - 1) {
                    attribute = attribute.substr(0, lastNonWhitespace + 1);
                }

                size_t colonPos = attribute.find_first_of(":");

                size_t pomocnicza = 0;

                String attributeName = attribute.substr(pomocnicza, colonPos);
                attributeName.erase(0, attributeName.find_first_not_of(" \t\r\n"));

                int lastNonWhitespaceN = attributeName.find_last_not_of(" \t\r\n");
                if (lastNonWhitespaceN != std::string::npos && lastNonWhitespaceN != attributeName.size() - 1) {
                    attributeName = attributeName.substr(0, lastNonWhitespaceN + 1);
                }
                String attributeValue = attribute.substr(colonPos + 1, attribute.size() - colonPos - 1);
                attributeValue.erase(0, attributeValue.find_first_not_of(" \t\r\n"));

                int lastNonWhitespaceV = attributeValue.find_last_not_of(" \t\r\n");
                if (lastNonWhitespaceV != std::string::npos && lastNonWhitespaceV != attributeValue.size() - 1) {
                    attributeValue = attributeValue.substr(0, lastNonWhitespaceV + 1);
                }
                //sprawdzanie duplikatow

                bool foundDuplicate = false;
                for (int i = 1; i <= sekcja->attributeName.rozmiar(); i++) {

                    if (*sekcja->attributeName.getElement(i) == attributeName)
                    {
                        foundDuplicate = true;
                        *sekcja->attributeValue.getElement(i) = attributeValue;
                        break;
                    }
                }

                if (foundDuplicate == false)
                {
                    sekcja->attributeName.push_back(attributeName);
                    sekcja->attributeValue.push_back(attributeValue);
                }

                attributePos = attributeEndPos + 1;
            }
            lista.push_back(sekcja);
        }


    }


}
void komendy(Block_List<Sekcja*>& lista)
{
    String komenda;
    char buffer[1000];


    while (fgets(buffer, 1000, stdin))
    {
        buffer[strcspn(buffer, "\n")] = '\0'; // usuwa znak końca linii
        komenda = buffer;

        if (komenda == "****")break;
        if (komenda == "?")
        {
            cout << "? == " << lista.rozmiar() << endl;
        }
        else if (komenda.substr(komenda.find(","), 4) == ",S,?")
        {
            String i = komenda.substr(0, komenda.find(","));
            if (i[0] == '0' || i[0] == '1' || i[0] == '2' || i[0] == '3' || i[0] == '4' || i[0] == '5' || i[0] == '6' || i[0] == '7' || i[0] == '8' || i[0] == '9')
            {
                int num = i.to_int();
                if (lista.getElement(num) != NULL)
                {
                    cout << komenda << " == " << (*lista.getElement(num))->sectionName.rozmiar() << endl;

                }
            }
            else
            {
                String z = komenda.substr(0, komenda.find(","));
                int suma = 0;
                for (int i = 1; i <= lista.rozmiar(); ++i)
                {
                    for (int j = 1; j <= (*lista.getElement(i))->sectionName.rozmiar(); ++j)
                    {
                        if (*(*lista.getElement(i))->sectionName.getElement(j) == z)++suma;

                    }
                }
                cout << komenda << " == " << suma << endl;

            }

        }
        else if (komenda.substr(komenda.find(","), 4) == ",A,?")
        {
            String i = komenda.substr(0, komenda.find(","));
            if (i[0] == '0' || i[0] == '1' || i[0] == '2' || i[0] == '3' || i[0] == '4' || i[0] == '5' || i[0] == '6' || i[0] == '7' || i[0] == '8' || i[0] == '9')
            {
                int num = i.to_int();
                if (lista.getElement(num) != NULL)
                {

                    cout << komenda << " == " << (*lista.getElement(num))->attributeName.rozmiar() << endl;

                }
            }
            else
            {
                String n = komenda.substr(0, komenda.find(","));
                int suma = 0;
                int pom = 1;
                for (int i = 1; i <= lista.rozmiar(); ++i)
                {
                    ++pom;
                    int pom2 = 1;

                    for (int j = 1; j <= (*lista.getElement(i))->attributeName.rozmiar(); j++)
                    {
                        ++pom2;
                        Sekcja** ptr = lista.getElement(i);
                        String* ptr2 = (*ptr)->attributeName.getElement(j);
                        String jakis = (*ptr2);
                        if (ptr != nullptr && jakis == n)++suma;


                    }
                }
                cout << komenda << " == " << suma << endl;

            }


        }
        else if (komenda.find(",S,") != -1)
        {
            String i = komenda.substr(0, komenda.find(","));
            size_t pos = komenda.find_last_of(',');
            String j = komenda.substr(pos + 1, komenda.size() - pos);
            int i2 = i.to_int(), j2 = j.to_int();
            if (i2 <= lista.rozmiar())
            {
                if (lista.getElement(i2) != nullptr && (*lista.getElement(i2))->sectionName.rozmiar() >= j2)
                {
                    cout << komenda << " == " << *(*lista.getElement(i2))->sectionName.getElement(j2) << endl;
                }
            }


        }
        else if (komenda.find(",A,") != -1)
        {
            String i = komenda.substr(0, komenda.find(","));
            size_t pos = komenda.find_last_of(',');
            String n = komenda.substr(pos + 1, komenda.size() - pos);
            int i2 = i.to_int();
            if (i2 <= lista.rozmiar())
            {
                for (int i = 1; i <= (*lista.getElement(i2))->attributeName.rozmiar(); ++i)
                {
                    if (*(*lista.getElement(i2))->attributeName.getElement(i) == n)
                    {
                        cout << komenda << " == " << *(*lista.getElement(i2))->attributeValue.getElement(i) << endl;

                    }
                }
            }

        }
        else if (komenda.find(",E,") != -1)
        {
            String z = komenda.substr(0, komenda.find(","));
            size_t pos = komenda.find_last_of(',');
            String n = komenda.substr(pos + 1, komenda.size() - pos);
            int pom = 0;
            for (int i = lista.rozmiar(); i > 0; --i)
            {
                for (int j = (*lista.getElement(i))->sectionName.rozmiar(); j > 0; --j)
                {
                    if ((*lista.getElement(i))->sectionName.getElement(j) != nullptr && *(*lista.getElement(i))->sectionName.getElement(j) == z)
                    {

                        for (int x = 1; x <= (*lista.getElement(i))->attributeName.rozmiar(); ++x)
                        {
                            if ((*lista.getElement(i))->attributeName.getElement(x) != nullptr && *(*lista.getElement(i))->attributeName.getElement(x) == n)
                            {
                                cout << komenda << " == " << *(*lista.getElement(i))->attributeValue.getElement(x) << endl;
                                ++pom;
                                break;
                            }
                        }
                        break;
                    }
                }
                if (pom > 0)break;
            }
        }
        else if (komenda.find(",D,*") != -1)
        {
            String i = komenda.substr(0, komenda.find(","));
            int num = i.to_int();
            if (num <= lista.rozmiar())
            {
                lista.removeAtIndex(num);
                cout << komenda << " == " << "deleted" << endl;
            }

        }
        else if (komenda.find(",D,"))
        {
            String i = komenda.substr(0, komenda.find(","));
            size_t pos = komenda.find_last_of(',');
            String n = komenda.substr(pos + 1, komenda.size() - pos);
            int num = i.to_int();


            if (lista.getElement(num) != nullptr && *(*lista.getElement(num))->attributeName.getElement(1) == n && (*lista.getElement(num))->attributeName.rozmiar() == 1)
            {
                lista.removeAtIndex(num);
                cout << komenda << " == " << "deleted" << endl;
            }
            else if (lista.getElement(num) != nullptr && num <= lista.rozmiar())
            {
                for (int x = 1; x <= (*lista.getElement(num))->attributeName.rozmiar(); ++x)
                {
                    if (*(*lista.getElement(num))->attributeName.getElement(x) == n)
                    {
                        // (*lista.getElement(num))->attributeName.kasowanie(x);
                        // (*lista.getElement(num))->attributeValue.kasowanie(x);
                         //cout << komenda << " == " << "deleted" << endl;

                        break;
                    }
                }
            }


        }
    }


}