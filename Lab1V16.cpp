#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <map>

/*!
    \brief Класс, задающий абитуриента
*/
struct enrollee
{
    std::string name; ///< ФИО абитуриента
    std::string faculty; ///< Факультет
    std::string speciality; ///< Специальность
    int result; ///< Количество набранных баллов

    enrollee(std::string name = "", std::string faculty = "", std::string speciality = "", int result = 0)
    {
        this->name = name;
        this->faculty = faculty;
        this->speciality = speciality;
        this->result = result;
    }

    /*!
        Оператор сравнения меньше
        \param[in] right правое сравниваемое значение
        \return Возвращает true, если левый объект строго меньше, false - иначе
    */
    bool operator<(enrollee right)
    {
        if (this->name == right.name)
        {
            return false;
        }

        return this->name < right.name;
    }

    /*!
        Оператор сравнения больше
        \param[in] right правое сравниваемое значение
        \return Возвращает true, если левый объект строго больше, false - иначе
    */
    bool operator>(enrollee right)
    {
        if (this->name == right.name)
        {
            return false;
        }

        return this->name > right.name;
    }

    /*!
        Оператор сравнения меньше или равно
        \param[in] right правое сравниваемое значение
        \return Возвращает true, если левый объект меньше или равен, false - иначе
    */
    bool operator<=(enrollee right)
    {
        if (this->name == right.name)
        {
            return true;
        }

        return this->name < right.name;
    }

    /*!
        Оператор сравнения больше или равно
        \param[in] right правое сравниваемое значение
        \return Возвращает true, если левый объект больше или равен, false - иначе
    */
    bool operator>=(enrollee right)
    {
        if (this->name == right.name)
        {
            return true;
        }

        return this->name > right.name;
    }

    bool operator==(enrollee right)
    {
        if (this->name == right.name)
        {
            return true;
        }

        return false;
    }
};

/*!
    \brief Класс, содержащий алгоритмы поиска
*/
template<typename T>
class searches
{
public:
    static std::vector<int> linear_search(T data[], int size, T& b)
    {
        std::vector<int> result;
        for (int i = 0; i < size; i++)
            if (data[i] == b)
                result.push_back(i);

        return result;
    }

    static std::vector<int> binary_search(T data[], int size, T& b)
    {
        int left = 0, right = size - 1;
        std::vector<int> result;
        while (left <= right && ! (data[(left + right) / 2] == b))
        {
            if (data[(left + right) / 2] > b)
                right = (left + right) / 2 - 1;
            else
                left = (left + right) / 2 + 1;
        }
        if(left <= right)
        {
            int i = (left + right) / 2;
            while(data[--i] == b) { }

            while (data[++i] == b) result.push_back(i);
        }
        return result;
    }
};

/*!
    \brief Класс, содержащий реализуемые сортировки
*/
template<typename T>
class sorts
{
public:
    /*!
        Интерфейс для сортировки слиянием
        \param[in] data Сортируемый массив
        \param[in] n Число элементов в массиве
    */
    static void mergeSort(T* data, int n)
    {
        nowMerge(data, 0, n - 1);
    }

private:

    /*!
        Сортировка слиянием
        \param[in] data Сортируемый массив
        \param[in] start Индекс первого сортируемого элемента
        \param[in] end Индекс последнего сортируемого элемента
    */
    static void nowMerge(T* data, int start, int end)
    {
        if (start == end)
            return;

        nowMerge(data, start, (start + end) / 2);
        nowMerge(data, (start + end) / 2 + 1, end);

        merge(data, start, (start + end) / 2, end);
    }

    /*!
        Слияние массивов
        \param[in] data Сортируемый массив
        \param[in] start Индекс начала первого сливаемого отрезка
        \param[in] mid Индекс конца первого сливаемого отрезка
        \param[in] end Индекс конца последнего сливаемого отрезка
    */
    static void merge(T* data, int start, int mid, int end)
    {
        int i = start;
        int j = mid + 1;

        T* temp = new T[end - start + 1];

        int k = 0;

        while (i <= mid && j <= end)
        {
            if (data[i] < data[j])
            {
                temp[k] = data[i];
                i++;
            }
            else
            {
                temp[k] = data[j];
                j++;
            }

            k++;
        }

        while (i <= mid)
        {
            temp[k] = data[i];
            i++;
            k++;
        }

        while (j <= end)
        {
            temp[k] = data[j];
            j++;
            k++;
        }

        for (int i = 0; i < end - start + 1; i++)
            data[i + start] = temp[i];
    }
};



int main()
{
    int sizes[10] = {100, 1000, 5000, 10000, 20000, 30000, 40000, 50000, 75000, 100000};

    for (int size : sizes)
    {
        {
            std::ifstream in;
            char filename[80];
            memset(filename, 0, 80);
            sprintf_s(filename, "%s%d%s", "data_", size, ".txt");

            in.open(filename);

            enrollee* data = new enrollee[size];
            std::multimap<std::string, enrollee> multimap;

            for (int i = 0; i < size; i++)
            {
                std::string name, faculty, speciality;
                int result;
                in >> name >> faculty >> speciality >> result;
                data[i] = enrollee(name, faculty, speciality, result);

                multimap.insert(std::pair<std::string, enrollee>(name, data[i]));
            }

            in.close();

            enrollee searching = data[(int)(rand() / RAND_MAX * size)];

            auto begin = std::chrono::high_resolution_clock::now();

            searches<enrollee>::linear_search(data, size, searching);

            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Linear search " << size << " elements " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " mcs" << std::endl;

            auto sort_begin = std::chrono::high_resolution_clock::now();

            sorts<enrollee>::mergeSort(data, size);

            auto search_begin = std::chrono::high_resolution_clock::now();

            searches<enrollee>::binary_search(data, size, searching);

            end = std::chrono::high_resolution_clock::now();

            std::cout << "Merge sort " << size << " elements " << std::chrono::duration_cast<std::chrono::microseconds>(search_begin - sort_begin).count() << " mcs" << std::endl;
            std::cout << "Binary search " << size << " elements " << std::chrono::duration_cast<std::chrono::microseconds>(end - search_begin).count() << " mcs" << std::endl;
            std::cout << "Binary search with sorting " << size << " elements " << std::chrono::duration_cast<std::chrono::microseconds>(end - sort_begin).count() << " mcs" << std::endl;

            begin = std::chrono::high_resolution_clock::now();

            multimap.find(searching.name);

            end = std::chrono::high_resolution_clock::now();

            std::cout << "Multimap search " << size << " elements " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " mcs" << std::endl << std::endl;

        }
    }
}


/*Генерация данных

std::string genStr()
{
    int length = rand() % 50 + 10;
    std::string result = "";

    for (int i = 0; i < length; i++)
    {
        result.append(1, (rand() % ('Z' - 'A' + 1)) + 'A');
    }

    return result;
}


int main()
{
    int sizes[10] = { 100, 1000, 5000, 10000, 20000, 30000, 40000, 50000, 75000, 100000 };

    for (int size : sizes)
    {
        std::ofstream out;
        char filename[80];
        memset(filename, 0, 80);
        sprintf_s(filename, "%s%d%s", "data_", size, ".txt");

        out.open(filename);

        for (int i = 0; i < size; i++)
        {
            out << genStr() << " " << genStr() << " " << genStr() << " " << rand() % 310 << std::endl;
        }

        out.close();
    }
}*/

