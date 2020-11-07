//
// Created by xy on 2020/11/7.
//

#include "market.h"

Market::Market() {
    chosen_item = nullptr;
    Item* peashooter = new Item(0, 100, 7.5);
    items.push_back(peashooter);
    Item* repeater = new Item(1, 200, 7.5);
    items.push_back(repeater);
    Item* snow_pea = new Item(2, 175, 7.5);
    items.push_back(snow_pea);
    Item* wall_nut = new Item(3, 50, 30);
    items.push_back(wall_nut);
    Item* tall_nut = new Item(4, 125, 30);
    items.push_back(tall_nut);
    Item* squash = new Item(5, 50, 30);
    items.push_back(squash);
    Item* cherry = new Item(6, 150, 50);
    items.push_back(cherry);
    Item* garlic = new Item(7, 50, 7.5);
    items.push_back(garlic);
    Item* pumpkin = new Item(8, 125, 30);
    items.push_back(pumpkin);
}

Plant * Item::get_plant() const {
    switch (plant_no) {
        case 0:
            return new Peashooter;
        case 1:
            return new Repeater;
        case 2:
            return new Snow_Pea;
        case 3:
            return new Wall_nut;
        case 4:
            return new Tall_nut;
        case 5:
            return new Squash;
        case 6:
            return new Cherry;
        case 7:
            return new Garlic;
        case 8:
            return new Pumpkin;
        default:
            return nullptr;
    }
}