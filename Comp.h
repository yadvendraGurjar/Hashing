#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Comp : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    void merge(std::vector<int>& arr, int left, int middle, int right);
    void mergeSort(std::vector<int>& arr, int left, int right);

private:
    int size = 0;
    std::vector<std::vector<Account>> bankStorage2d = std::vector<std::vector<Account>>(99989);
    // Other data members and functions specific to Your implementation
};

#endif // COMP_H
