#include <iostream>
#include <vector>
using namespace std;

void printVector(vector<int> vec)
{
    for (int i = 0; i < vec.size() - 1; i++)
        cout << vec[i] << " + ";
    cout << vec[vec.size() - 1] << endl;
}

vector<int> startVectorGenerator(int n, int m)
{
    vector<int> arr;
    arr.resize(m);

    for (int i = 0; i < m; i++)
        arr[i] = 1;
    arr[arr.size() - 1] = n - (m - 1);

    return arr;
}

int Gitenburg(vector<int> vec)
{
    int elIdx = vec.size() - 2;

    while (true)
    {
        if (elIdx == -1)
            elIdx = vec.size() - 2;

        vec[vec.size() - 1] -= 1;
        vec[elIdx] += 1;
        elIdx -= 1;

        if (vec[vec.size() - 1] < vec[vec.size() - 2])
            return 0;

        printVector(vec);
    }

    return 0;
}

int main(int argc, const char *argv[])
{
    int n, m;

    cout << "Введите целое число больше 0: ";
    cin >> n;
    cout << "Введите количество слагаемых: ";
    cin >> m;

    if ((n * m == 0) || (n < 0) || (m < 0) || (m > n))
    {
        cout << "Ошибка ввода" << endl;
        return 1;
    }

    if (m == 1)
    {
        cout << n << endl;
        return 0;
    }

    vector<int> vec = startVectorGenerator(n, m);
    printVector(vec);

    return Gitenburg(vec);
}
