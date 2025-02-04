//***********************************************************************
 // Team 3                              
//CSCI 2380                          
//Spring 2025                      
//Homework # 1 
// Kasandra Ornelas
// Isabella Morgan
//  
//*********************************************************************** 
#include "pokemon.h"

//single type
Pokemon::Pokemon(string name, int ndex, Type type1) {
    _name = name; //assigns pokemon name
    _ndex = ndex;   //assigns ndex #
    types[0] = type1;   //stores first/only type
    type_count = 1; //stores that theres only one type
}

// multitype
Pokemon::Pokemon(string name, int ndex, Type type1, Type type2) {
    _name = name;   //assigns poke name
    _ndex = ndex;   //assigns poke ndex
    types[0] = type1;   //stores first type
    types[1] = type2;   //stores second typw
    type_count = 2;     //stores that there is two types
}

//returns name 
string Pokemon::name() {
    return _name;
}

// returns ndex
int Pokemon::Ndex() {
    return _ndex;
}

//returns first type of pokemon
Pokemon::Type Pokemon::type1() {
    return types[0];
}

//returns if there are multiple types of pokem
bool Pokemon::is_multitype() {
    return type_count == 2;
}

//will return the second if possible, if not then itll return the first
Pokemon::Type Pokemon::type2() {
    if (type_count == 2) {
    return types[1];    //if there is a second one then it will return second type
    } 
    else {
    return types[0]; //else (means theres only one type) will return first/only
    }
}

//returns damage multiplier against Pokemon for a given attack type
float Pokemon::damage_multiplier(Type attack_type) {
    float multiplier = 1.0; 

    //will loop through each type then muliply damage modifier
    for (int i = 0; i < type_count; i++) {
        switch (attack_type) {
            //normal attacks do normal damage against any type
            case Normal:
                multiplier *= 1.0;
                break;
            case Fighting:
                //fighting has a multiplier of 2.0 against normal
                if (types[i] == Normal) multiplier *= 2.0;
                //fighting only has a multiplier 0f 0.5 against flying/poison
                else if (types[i] == Flying || types[i] == Poison) multiplier *= 0.5;
                else multiplier *= 1.0; //otherwise normal mult of 1.0
                break;
            case Flying:
                 //flying has a mult 0f 2.0 against fighing
                if (types[i] == Fighting) multiplier *= 2.0;
                //any other opponent is a mult of 1.0
                else multiplier *= 1.0;
                break;
            case Poison:
                //poison against posion is 0.5 damage 
                if (types[i] == Poison) multiplier *= 0.5;
                //anything else normal damage
                else multiplier *= 1.0;
                break;
        }
    }
    //return final multiplier
    return multiplier;
}
