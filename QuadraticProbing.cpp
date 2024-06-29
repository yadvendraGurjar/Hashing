#include "QuadraticProbing.h"

void QuadraticProbing::createAccount(std::string id, int count) {
    Account newaccount;
    newaccount.id = id;
    newaccount.balance = count;
    size++;
    int i = 0;
    int n = hash(id);
    while(bankStorage1d[n].id != ""){
        i++;
        n += i*i;
        if(n > 100000) n-=100000;
    }
    bankStorage1d[n]=newaccount;
}

std::vector<int> QuadraticProbing::getTopK(int k) {
    std::vector<int> vec1 ,vec2;
    for (int j = 0 ; j < bankStorage1d.size(); j++) {
        if(bankStorage1d[j].id != ""){
            vec2.push_back(bankStorage1d[j].balance);
        }
    }
    mergeSort(vec2 ,0 ,vec2.size()-1);
    for (int i = 0; i < k; i++)
    {
        vec1.push_back(vec2[vec2.size() - 1 - i]);
    }
    return vec1; // Placeholder return value
}

int QuadraticProbing::getBalance(std::string id) {
    int n = hash(id);
    int i = 0;
    while(bankStorage1d[n].id != id){
        i++;
        n += i*i;
        if(n > 100000) n-=100000;
        if(bankStorage1d[n].id == "") return -1;
    }
    return bankStorage1d[n].balance; // Placeholder return value
}

void QuadraticProbing::addTransaction(std::string id, int count) {
    int n = hash(id);
    int i = 0;
    while(bankStorage1d[n].id != id){
        i++;
        n += i*i;
        if(n > 100000) n-=100000;
        if(bankStorage1d[n].id == ""){
            createAccount(id, count);
            return;
        }
    }
    bankStorage1d[n].balance += count;
}

bool QuadraticProbing::doesExist(std::string id) {
    int n = hash(id);
    int i = 0;
    while(bankStorage1d[n].id != id){
        i++;
        n += i*i;
        if(n > 100000) n-=100000;
        if(bankStorage1d[n].id == "") return false;
    }
    return true; // Placeholder return value
}

bool QuadraticProbing::deleteAccount(std::string id) {
    int n = hash(id);
    int i = 0;
    while(bankStorage1d[n].id != id){
        i++;
        n += i*i;
        if(n > 100000) n-=100000;
        if(bankStorage1d[n].id == "") return false;
    }
    bankStorage1d[n].id = "";
    bankStorage1d[n].balance=0;
    size--;
    return true; // Placeholder return value
}
int QuadraticProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int QuadraticProbing::hash(std::string id) {
    int res = 0;
    for (int i = 0; i < 22; i++)
    {
        res += (i + 1) * int(id[i]) * int(id[i]);
        res = res % 99989;
    }
    return res; // Placeholder return value
}

void QuadraticProbing::merge(std::vector<int>& arr, int left, int middle, int right) {
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

void QuadraticProbing::mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}