#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <list>

int selection(std::vector<double> list)
{
    int n = 0;
    for (size_t i = 0; i < list.size() - 1; ++i)
    {
        size_t min = i;
        for (size_t j = i + 1; j < list.size(); ++j)
        {
            if (list[min] > list[j])
                min = j;
            ++n;
        }
        if (min != i)
        {
            double tmp = list[min];
            list[min] = list[i];
            list[i] = tmp;
        }
    }
    return n;
}

int insertion(std::vector<double> list)
{
    int n = 0;
    std::list<double> list2;
    for (size_t i = 0; i < list.size(); ++i)
    {
        if (list2.empty())
            list2.push_back(list[i]);
        else
        {
            std::list<double>::iterator it = list2.begin();
            while (it != list2.end())
            {
                ++n;
                if (*it > list[i])
                {
                    list2.insert(it, list[i]);
                    break ;
                }
                ++it;
            }
            if (it == list2.end())
                list2.push_back(list[i]);
        }

    }
    return n;
}

int bubbles(std::vector<double> list)
{
    int n = 0;
    for (size_t j = list.size() - 2; j + 1 > 0; --j)
        for (size_t i = 0; i < j + 1; ++i)
        {
            ++n;
            if (list[i] > list[i + 1])
            {
                double tmp = list[i];
                list[i] = list[i + 1];
                list[i + 1] = tmp;
            }
        }
    return n;
}

int merge(std::list<double> &list1, std::list<double> &list2)
{
    int n = 0;
    std::list<double>::iterator it1 = list1.begin();
    std::list<double>::iterator it_end1 = list1.end();
    std::list<double>::iterator it2 = list2.begin();
    std::list<double>::iterator it_end2 = list2.end();

    while (it1 != it_end1 && it2 != it_end2)
    {
        ++n;
        if (*it2 < *it1)
        {
            std::list<double>::iterator next = it2;
            it1._M_node->_M_transfer(it2._M_node, (++next)._M_node);
            it2 = next;
        }
        else
            ++it1;
    }
    if (it2 != it_end2)
        it_end1._M_node->_M_transfer(it2._M_node, it_end2._M_node);
    return n;
}

int fusion(std::vector<double> list)
{
    int n = 0;
    std::vector<std::list<double> > list2;

    for (size_t i = 0; i < list.size(); ++i)
        if (i % 2 == 0)
        {
            std::list<double> tmp;
            if (i + 1 >= list.size())
                tmp.push_back(list[i]);
            else
            {
                tmp.push_back(std::min(list[i], list[i + 1]));
                tmp.push_back(std::max(list[i], list[i + 1]));
            }
            list2.push_back(tmp);
        }

    while (list2.size() > 1)
    {
        for (int i = 0; i < list2.size(); i += 2)
            if (i + 1 < list2.size())
                n += merge(list2[i], list2[i + 1]);
        for (int i = 1; i < list2.size(); ++i)
        {
            std::vector<std::list<double> >::iterator it = list2.begin();
            for (int j = 0; j < i; ++j)
                ++it;
            list2.erase(it);
        }
    }
    return n + 2;
}

int fast(std::vector<double> list, int start, int end)
{
    int c = 0;
    if (start < end)
    {
        int n = start;
        double pivot = list[start];
        
        for (int i = start + 1; i <= end; ++i)
        {
            ++c;
            if (list[i] < pivot)
            {
                ++n;
                double tmp = list[i];
                list[i] = list[n];
                list[n] = tmp;
            }
        }

        double tmp = list[n];
        list[n] = list[start];
        list[start] = tmp;

        int p = n;
        c += fast(list, start, p - 1);
        c += fast(list, p + 1, end);
    }
    return c;
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage : " << av[0] << " file" << std::endl;
        return 1;
    }
    std::ifstream ifStream;
    ifStream.open(av[1]);
    if (!ifStream)
    {
        std::cerr << "Can't open file" << std::endl;
        return 1;
    }

    std::vector<double> list;
    std::string line;
    std::getline(ifStream, line);

    std::string word;
    std::istringstream iStringStream(line);
    while (std::getline(iStringStream, word, ' '))
        list.push_back(std::atof(word.c_str()));

    std::cout << list.size() << " éléments" << std::endl;
    std::cout << "tri par sélection : " << selection(list)                << " comparaisons" << std::endl;
    std::cout << "tri par insertion : " << insertion(list)                << " comparaisons" << std::endl;
    std::cout << "tri à bulles : "      << bubbles(list)                  << " comparaisons" << std::endl;
    std::cout << "tri fusion : "        << fusion(list)                   << " comparaisons" << std::endl;
    std::cout << "tri rapide : "        << fast(list, 0, list.size() - 1) << " comparaisons" << std::endl;
    return 0;
}
