//
// Created by xy on 2020/11/7.
//

#ifndef PVZ_MARKET_H
#define PVZ_MARKET_H

#include "common.h"
#include "plants.h"

class Item {
private:
    int cd;
    int timer;
    int cost;
    int plant_no;
public:
    Item(int _no, int _cost, double _cd) : plant_no(_no), cd(int(_cd * 10)), cost(_cost), timer(0) {}

    int get_cd() const {
        return cd;
    }

    int get_cost() const {
        return cost;
    }

    int get_timer() const {
        return timer;
    }

    Plant *get_plant() const;

    int get_no() const {
        return plant_no;
    }

    void update_timer() {
        if (timer > 0)
            timer--;
    }

    void reset_timer() {
        timer = cd;
    }
};

class Market {
private:
    bool shovel;
    vector<Item *> items;
    Item *chosen_item; // 商店中选中的植物
public:
    Market();

    void choose_shovel() {
        shovel = 1;
    }
    void cancel_choose_shovel() {
        shovel = 0;
    }
    bool get_shovel() const {
        return shovel;
    }

    int get_number() const {
        return items.size();
    }

    void choose_item(int no) {
        chosen_item = items[no];
    }

    Item *get_chosen() const {
        return chosen_item;
    }

    void cancel_choose() {
        chosen_item = nullptr;
    }

    int number_of_items() const {
        return items.size();
    }

    Item *get_item_k(int k) const {
        if (k < items.size())
            return items[k];
        assert(0);
        return nullptr;
    }
};

#endif //PVZ_MARKET_H
