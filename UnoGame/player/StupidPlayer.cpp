#include "StupidPlayer.hpp"
#include <iostream>

StupidPlayer::StupidPlayer(string name){
    this->name_of_player = name;
}

std::string StupidPlayer::name() const{
    return name_of_player;
};


void StupidPlayer::receiveCards(const std::vector<const Card*>& cardsss){
    if (cardsss.size() == 7){
        cards.clear();
    }
    
    for (int i = 0; i < cardsss.size(); i++){
        this->cards.push_back(cardsss[i]);
    }
};


bool CompareCardsByValue(const Card* a, const Card* b) {
    return a->value < b->value;
}

const Card * StupidPlayer::playCard(){
    sort(cards.begin(), cards.end(), CompareCardsByValue);
    
    for (int i = 0; i < cards.size(); i++){
        if ((cards[i]->color == this->game()->currentColor() ||
            cards[i]->value == this->game()->topCard()->value) ||
            cards[i]->is_wild()) 
        {
            const Card* temp = cards[i];
            cards.erase(cards.begin() + i);
            return temp;
            break;
            
        }
    }

    return nullptr;
}


bool StupidPlayer::drawAdditionalCard(const Card * additionalCard){
    if (additionalCard->is_wild()){
        return true;
    }
    if (additionalCard->color == this->game()->currentColor() ||
        additionalCard->value == this->game()->topCard()->value){
        return true;
    }
    
    cards.push_back(additionalCard);
    return false;
};


CardColor StupidPlayer::changeColor(){
    srand((unsigned) time(NULL));
    vector<CardColor> colors {Red, Blue, Green, Yellow};
    int x = rand() % 4;
    return colors[x];
};
