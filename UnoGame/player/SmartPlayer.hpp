#pragma once

#include "events.h"
#include "uno_game.h"
#include <algorithm>
#include <iostream>


using std::string;
using std::vector;
using std::sort;

class SmartPlayer: public UnoPlayer{
    vector<const Card*> cards;
    string name_of_p;
public:
    SmartPlayer(string name);
    /// @brief Игрок возвращает свое имя.
    /// @return имя игрока.
    virtual std::string name() const;

    /// @brief Игрок получает на руки карты.
    /// @param cards массив карт.
    virtual void receiveCards(const vector<const Card*>& cards);

    /// @brief Игрок возвращает карту, которую он сыграет (положит в сброс).
    /// @return карта, которую игрок положит в сброс.
    virtual const Card * playCard();

    /// @brief Если у игрока нет подходящих карт, он тянет дополнительную
    /// карту и говорит, хочет ли он ее сразу положить или нет.
    /// @param additionalCard дополнительная карта.
    /// @return true, если игрок сразу же кладет эту карту, иначе false.
    virtual bool drawAdditionalCard(const Card * additionalCard);

    /// @brief Если игрок положил "Закажи цвет" или "Возьми четыре", то
    /// игра запросит у него новый цвет.
    /// @return новый цвет.
    virtual CardColor changeColor();
    
    
    
    CardColor return_max_cnt_color();
    vector<const Card*> array_can_play();
    
    int find_index(const Card* temp);
    bool is_more_than_one_action_card(vector<const Card*> array);
    
    
};
