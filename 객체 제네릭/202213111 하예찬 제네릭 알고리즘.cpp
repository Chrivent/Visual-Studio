#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

template<typename T>
void removeDuplicates(std::vector<T>& array)
{
    array.erase(unique(array.begin(), array.end()), array.end());
}

template<typename T>
void removeDuplicatesWithSet(std::vector<T>& array)
{
    set<T> uniqueSet(array.begin(), array.end());
    array.assign(uniqueSet.begin(), uniqueSet.end());
}

int main()
{
    vector<string> array1 = { "A", "A", "A", "B", "C", "D", "E" };
    vector<string> array2 = { "A", "A", "E", "V", "E", "E", "E", "Z" };

    // 첫 번째 제네릭 알고리즘 사용
    removeDuplicates(array1);

    cout << "Array 1 after removing duplicates: ";
    for (const auto& element : array1)
        cout << element << " ";
    cout << endl;

    // 두 번째 제네릭 알고리즘 사용
    removeDuplicatesWithSet(array2);

    cout << "Array 2 after removing duplicates: ";
    for (const auto& element : array2)
        cout << element << " ";
    cout << std::endl;

    return 0;
}