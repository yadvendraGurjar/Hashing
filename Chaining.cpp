#include "Chaining.h"


void Chaining::createAccount(std::string id, int count)
{
    Account newaccount;
    newaccount.id = id;
    newaccount.balance = count;
    size++;
    int n = hash(id);
    bankStorage2d[n].push_back(newaccount);
}

std::vector<int> Chaining::getTopK(int k)
{
    std::vector<int> vec1, vec2;
    for (int i = 0; i < bankStorage2d.size(); i++)
    {
        if (bankStorage2d[i].size() != 0)
        {
            for (int j = 0; j < bankStorage2d[i].size(); j++)
            {
                vec2.push_back(bankStorage2d[i][j].balance);
            }
        }
    }
    mergeSort(vec2 ,0 ,vec2.size()-1);
    for (int i = 0; i < k; i++)
    {
        vec1.push_back(vec2[vec2.size() - 1 - i]);
    }
    return vec1; // Placeholder return value
}

int Chaining::getBalance(std::string id)
{
    int n = hash(id);
    int i = 0;
    if (bankStorage2d[n].size() != 0){
    while (bankStorage2d[n][i].id != id)
    {
        i++;
        if (i == bankStorage2d[n].size())
            return -1;
    }
    }
    else return -1;
    return bankStorage2d[n][i].balance; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count)
{
    int n = hash(id);
    int i = 0;
    if (bankStorage2d[n].size() != 0)
    {
        while (bankStorage2d[n][i].id != id)
        {
            i++;
            if (i == bankStorage2d[n].size())
            {
                createAccount(id, count);
                return;
            }
        }
    }
    else
    {
        createAccount(id, count);
        return;
    }
    bankStorage2d[n][i].balance += count;
}

bool Chaining::doesExist(std::string id)
{
    int n = hash(id);
    int i = 0;
    if (bankStorage2d[n].size() == 0) return false;
    while (bankStorage2d[n][i].id != id)
    {
        i++;
        if (i == bankStorage2d[n].size())
            return false;
    }
    return true; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id)
{
    int n = hash(id);
    int i = 0;
    if (bankStorage2d[n].size() == 0) return false;
    while (bankStorage2d[n][i].id != id)
    {
        i++;
        if (i == bankStorage2d[n].size())
            return false;
    }
    bankStorage2d[n].erase(bankStorage2d[n].begin() + i);
    size--;
    return true; // Placeholder return value
}

int Chaining::databaseSize()
{
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int Chaining::hash(std::string id)
{
    int res = 0;
    for (int i = 0; i < 22; i++)
    {
        res += (i + 1) * int(id[i]) * int(id[i]);
        res = res % 99989;
    }
    return res; // Placeholder return value
}


void Chaining::merge(std::vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[middle + 1 + j];
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void Chaining::mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}