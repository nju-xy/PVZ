//
// Created by xy on 2020/11/7.
//

#ifndef PVZ_MARKET_H
#define PVZ_MARKET_H

#include "common.h"
#include "plants.h"

class Item {
private:
    double cd;
    int cost;
    int plant_no;
public:
    Item(int _no, int _cost, double _cd) : plant_no(_no), cd(_cd), cost(_cost) {}
    double get_cd() {
        return cd;
    }
    int get_cost() {
        return cost;
    }
    Plant* get_plant() const;
    int get_no() {
        return plant_no;
    }
};

class Market {
private:
    vector<Item*> items;
    Item* chosen_item; // 商店中选中的植物
public:
    Market();
    void choose_item(int no) {
        chosen_item = items[no];
    }
    Item* get_chosen() const {
        return chosen_item;
    }
    void cancel_choose() {
        chosen_item = nullptr;
    }
    int number_of_items() const {
        return items.size();
    }
    Item* get_item_k(int k) const {
        if(k < items.size())
            return items[k];
        assert(0);
        return nullptr;
    }
};

#endif //PVZ_MARKET_H
