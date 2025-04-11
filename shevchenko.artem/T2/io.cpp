#include "io.h"
#include "guard.h"
#include <iomanip>

namespace nspace
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        // Проверка состояния потока
        std::istream::sentry sentry(in);
        if (!sentry) return in;

        // Получение символа из потока
        char c;
        in >> c;

        // Проверка символа
        if (c != dest.exp)
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DBLLITIO&& dest)
    {
        // Проверка состояния потока
        std::istream::sentry sentry(in);
        if (!sentry) return in;

        // Пытаемся считать число
        if (!(in >> dest.ref)) return in;

        // Проверяем суффикс

        const int nextChar = in.peek();
        if (nextChar == 'd')
        {
            in >> DelimiterIO{'d'};
        }
        else if (nextChar == 'D')
        {
            in >> DelimiterIO{'D'};
        }
        else
        {
            dest.ref = 0.0;
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream &in, LLIO&& dest)
    {
        // Проверка состояния потока
        std::istream::sentry sentry(in);
        if (!sentry) return in;

        // Читает long long и проверяет префикс
        return in >> DelimiterIO{'N'} >> dest.ref;
    }

    std::istream& operator>>(std::istream &in, ULLIO&& dest)
    {
        // Проверка состояния потока
        std::istream::sentry sentry(in);
        if (!sentry) return in;

        // Читает unsigned long long и проверяет префикс
        return in >> DelimiterIO{'D'} >> dest.ref;
    }

    std::istream &operator>>(std::istream &in, StringIO&& dest)
    {
        // Проверка состояния потока
        std::istream::sentry sentry(in);
        if (!sentry) return in;

        // Читает строку между кавычками
        return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
    }

    std::istream &operator>>(std::istream &in, DataStruct& dest)
    {
        // Проверка состояния потока
        std::istream::sentry sentry(in);
        if (!sentry) return in;

        // Создаём временую структуру данных
        DataStruct tempData;

        bool isKey1Added = false;
        bool isKey2Added = false;
        bool isKey3Added = false;

        // Проверяем первый символ
        in >> DelimiterIO{'('};

        // Распределяем данные по ключам
        while (!(isKey1Added && isKey2Added && isKey3Added))
        {
            std::string currentKey;

            in >> DelimiterIO{':'} >> currentKey;
            if (!in)
            {
                break;
            }
            if (currentKey == "key1") // Записываем данные в key1
            {
                in >> DBLLITIO{tempData.key1};
                isKey1Added = true;
            }
            else if (currentKey == "key2") // Записываем данные в key2
            {
                in >> DelimiterIO{'('};
                in >> DelimiterIO{':'};
                in >> LLIO{tempData.key2.first};
                in >> DelimiterIO{':'};
                in >> ULLIO{tempData.key2.second};
                in >> DelimiterIO{':'};
                in >> DelimiterIO{')'};
                isKey2Added = true;
            }
            else if (currentKey == "key3") // Записываем данные в key3
            {
                in >> StringIO{tempData.key3};
                isKey3Added = true;
            }
            else
            {
                in.setstate(std::ios::failbit);
                break;
            }
        }

        // Проверяем последние символы
        in >> DelimiterIO{':'};
        in >> DelimiterIO{')'};

        // Перемещаем содержимое из темпа
        if (in) dest = std::move(tempData);
        return in;
    }
    std::ostream &operator<<(std::ostream &out, const DataStruct &dest)
    {
        // Проверка состояния потока
        std::ostream::sentry sentry(out);
        if (!sentry) return out;

        // Блокируем поток
        iofmtguard guard(out);

        // Выводим данные в поток
        out << "(:key1 ";
        out << std::setprecision(1) << std::fixed << dest.key1 << "d";
        out << ":key2 ";
        out << "(:N " << dest.key2.first << ":D " << dest.key2.second << ":)";
        out << ":key3 ";
        out << "\"" << dest.key3 << "\"";
        out << ":)";

        return out;
    }
}