/*
 * tiktaktoe - a game using SnodeC
 * Copyright (C) 2021 Volker Christian <me@vchrist.at>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "TikTakToeGameModel.h"
#include <iostream>
#include <cctype>
#include <string>
#include <map>               // for operator==
#include <nlohmann/json.hpp> // for basic_json<>::object_t, basic_json<>::v...

TikTakToeGameModel TikTakToeGameModel::gameModel;

void TikTakToeGameModel::playersMove(const std::string& player, int cellID) {
    
    if (player == players[whosNext]) {
        int cellValue = 0;

        if (player == "red") {
            cellValue = 1;
        } else if (player == "blue") {
            cellValue = -1;
        }

        board[cellID] = cellValue;

        if (whosNext >= 1) {
            whosNext = 0;
        } else {
            whosNext += 1;
        }
    }
}

int TikTakToeGameModel::winnerCheck() {
    
    int count = 0;
    for (int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            count += board[i*3 + j];
        };
        if(count ==3){
            std::cout<< "-------###******Player Red has won!!!******###-------";
            return 1;
        };
        count = 0;
    };
    
    
    for (int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            count += board[i*3 + j];
        };
        if(count == -3){
            std::cout<< "-------###******Player Blue has won!!!******###-------";
            return 2;
        };
        count = 0;
    };
    
    
    for (int i=0; i<3;i++){
        for(int j=0; j<3; j++){
            count +=board[i+j*3];
        };
        if(count == 3){
            std::cout<< "-------###******Player Red has won!!!******###-------";
            return 1;
        };
        count = 0;        
    };
    
    
    for (int i=0; i<3;i++){
        for(int j=0; j<3; j++){
            count +=board[i+j*3];
        };
        if(count == -3){
            std::cout<< "-------###******Player Blue has won!!!******###-------";
            return 2;
        };
        count = 0;
    };
    
    
    
    for (int i=0; i<3;i++){
        count += board[i*4];
    };
    if(count ==3){
            std::cout<< "-------###******Player Red has won!!!******###-------";
            return 1;
        };
        count = 0;
   
    
    for (int i=0; i<3;i++){
        count += board[i*4];
    };
    if(count == -3){
        std::cout<< "-------###******Player Blue has won!!!******###-------";
        return 2;
    };
    count = 0;
    
    
    
    for (int i=0; i<3;i++){
        count += board[i*2+2];
    };
    if(count ==3){
            std::cout<< "-------###******Player Red has won!!!******###-------";
            return 1;
        };
    count = 0;
  
            
    
    for (int i=0; i<3;i++){
        count += board[i*2+2];
    };
    if(count == -3){
        std::cout<< "-------###******Player Blue has won!!!******###-------";
        return 2;
    };
    count = 0;
    
    
    
    return 0;
};

void TikTakToeGameModel::resetBoard() {
    whosNext = 0;
    for (int i = 0; i < 9; i++) {
        board[i] = 0;
    }
}

nlohmann::json TikTakToeGameModel::updateClientState() {
    nlohmann::json message;

    message["type"] = "update";
    message["whosTurn"] = players[whosNext];
    message["board"] = board;
    message["winnerCheck"] = winnerCheck();

    return message;
}

TikTakToeGameModel& TikTakToeGameModel::getGameModel() {
    return gameModel;
}
