
#include "SmartPlayer.hpp"

SmartPlayer::SmartPlayer(string name){
    name_of_p = name;
}

std::string SmartPlayer::name() const{
    return name_of_p;
};


void SmartPlayer::receiveCards(const std::vector<const Card*>&
                               cardsss){
    if (cardsss.size() == 7){
        cards.clear();
    }
    
    for (int i = 0; i < cardsss.size(); i++){
        cards.push_back(cardsss[i]);
    }
};


const Card * SmartPlayer::playCard(){
    vector<const Card*> array = array_can_play();
    int op_index = game()->activePlayerIndex() == 1 ? 0:1;
    bool is_another_player_have_three_cards = game()->numberOfCards()[op_index] <= 3 ? 1:0;
    
    
        if (is_another_player_have_three_cards){                 // if op_player almost win, we gotta stop him, dropping actioncards
            for(int i = static_cast<int>(array.size()) - 1; i >= 0 ; i--){            // here i try to drop +2 card
                if((array[i]->value == 10)){
                    cards.erase(cards.begin() + find_index(array[i]));
                    return array[i];
                }
            }
            
            for(int i = static_cast<int>(array.size()) - 1; i >= 0 ; i--){            // if i havent got any +2 cards, i try to drop action cards
                if((array[i]->is_action()) || array[i]->is_wild()){
                    cards.erase(cards.begin() + find_index(array[i]));
                    return array[i];
                }
            }
            
        };
        
        if(is_more_than_one_action_card(array)){                                // tactic "action_cards"
            cards.erase(cards.begin() + find_index(array[array.size() - 1]));
            return array[array.size() - 1];
        }
        
        for(int i = static_cast<int>(array.size()) - 1; i >= 0 ; i--){         // drop cards of topcard color which values                                                                                                         are lower than 10
            if(array[i]->color == game()->currentColor() &&
               array[i]->value < 10){
                cards.erase(cards.begin() + find_index(array[i]));
                return array[i];
            }
        }
        
        for(int i = static_cast<int>(array.size()) - 1; i >= 0 ; i--){         // i'm trying to drop card which are                                                                                     similar in value, and color of this card is max_cnt_clr
            if(array[i]->color == return_max_cnt_color() &&
               array[i]->value == game()->topCard()->value)
            {
                cards.erase(cards.begin() + find_index(array[i]));
                return array[i];
            }
        }
        
        for(int i = static_cast<int>(array.size()) - 1; i >= 0 ; i--){      // just try to drop any card which similar in value with topacards
            if(array[i]->value == game()->topCard()->value)
            {
               cards.erase(cards.begin() + find_index(array[i]));
               return array[i];
            }
        }
        
        
        
        
    
    cards.erase(cards.begin() + find_index(array[array.size() - 1]));
    return array[array.size() - 1];
}


bool SmartPlayer::drawAdditionalCard(const Card * additionalCard){
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


CardColor SmartPlayer::changeColor(){
    return return_max_cnt_color();
};

bool CompareCardsByValue_(const Card* a, const Card* b) {
    return a->value < b->value;
}


vector<const Card*> SmartPlayer::array_can_play(){
    vector<const Card*> array;
    
    for (int i = 0; i < cards.size(); i++){
        if ((cards[i]->color == game()->currentColor() && cards[i]->is_wild() == false) ||
            (cards[i]->value == game()->topCard()->value && game()->topCard()->is_wild() == false) ||
            cards[i]->value == 13)
            
        {
            array.push_back(cards[i]);
        }
    }
    
    if (array.size() == 0){
        for (int i = 0; i < cards.size(); i++){
            if (cards[i]->value == 14)
            {
                array.push_back(cards[i]);
            }
        }
    }
    sort(array.begin(), array.end(), CompareCardsByValue_);
    return array;
};


CardColor SmartPlayer::return_max_cnt_color(){
    vector<const Card*> red_arr;
    vector<const Card*> blue_arr;
    vector<const Card*> green_arr;
    vector<const Card*> yellow_arr;
    
    vector<const Card*> mx_size;
    
    for(int i = 0; i < cards.size(); i++){
        switch (cards[i]->color) {
            case Red:
                red_arr.push_back(cards[i]);
                break;
            case Blue:
                if (cards[i]->is_wild() == false){
                    blue_arr.push_back(cards[i]);
                }
                break;
            case Green:
                green_arr.push_back(cards[i]);
                break;
            case Yellow:
                yellow_arr.push_back(cards[i]);
                break;
        }
    }
    
    for (vector<const Card*> arr: {red_arr, blue_arr, green_arr, yellow_arr}) {
        if (arr.size() > mx_size.size()){
            mx_size = arr;
        }
    }
    
    if (mx_size.size() == 0){
        srand((unsigned) time(NULL));
        vector<CardColor> colors {Red, Blue, Green, Yellow};
        int x;
        while(true){
            x = rand() % 4;
            if (colors[x] != game()->currentColor()){
                break;
            }
        }
        return colors[x];
    }
    
    return mx_size[0]->color;
};



int SmartPlayer::find_index(const Card* temp){
    
    for (int i = 0; i < cards.size(); i++){
        if (cards[i]->value == temp->value &&
            cards[i]->color == temp->color){
            return i;
        }
    }
    
    return 0;
}

bool SmartPlayer::is_more_than_one_action_card(vector<const Card*> array){
    bool is_more = false;
    int cnt = 0;
    CardColor temp;
    
    for(int i = static_cast<int>(array.size()) - 1; i >= 0; i--){
        if (array[i]->is_action()){
            cnt++;
            temp = array[i]->color;
        }
    }
    
    if (cnt >= 2){
        is_more = true;
    }

    else if(cnt == 1 && array.size() > 1){
        for(int i = static_cast<int>(array.size()) - 1; i >= 0; i--){
            if (array[i]->is_action() == false && array[i]->color == temp){
                is_more = true;
                break;
            }
        }
    }
        
    return is_more;
}
