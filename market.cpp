//
// Created by xy on 2020/11/7.
//

#include "market.h"

Market::Market() {
    chosen_item = nullptr;
    Item* sunflower = new Item(0, 50, 7.5);
    items.push_back(sunflower);
    Item* peashooter = new Item(1, 100, 7.5);
    items.push_back(peashooter);
    Item* repeater = new Item(2, 200, 7.5);
    items.push_back(repeater);
    Item* snow_pea = new Item(3, 175, 7.5);
    items.push_back(snow_pea);
    Item* wall_nut = new Item(4, 50, 30);
    items.push_back(wall_nut);
    Item* tall_nut = new Item(5, 125, 30);
    items.push_back(tall_nut);
    Item* squash = new Item(6, 50, 30);
    items.push_back(squash);
    Item* cherry = new Item(7, 150, 50);
    items.push_back(cherry);
    Item* garlic = new Item(8, 50, 7.5);
    items.push_back(garlic);
    Item* pumpkin = new Item(9, 125, 30);
    items.push_back(pumpkin);
}

Plant * Item::get_plant() const {
    switch (plant_no) {
        case 0:
            return new Sunflower;
        case 1:
            return new Peashooter;
        case 2:
            return new Repeater;
        case 3:
            return new Snow_Pea;
        case 4:
            return new Wall_nut;
        case 5:
            return new Tall_nut;
        case 6:
            return new Squash;
        case 7:
            return new Cherry;
        case 8:
            return new Garlic;
        case 9:
            return new Pumpkin;
        default:
            return nullptr;
    }
}