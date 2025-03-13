//***********************************************************************
 // Team 3                              
//CSCI 2380                          
//Spring 2025                      
//Homework # 5
// Kasandra Ornelas
// Isabella Morgan
//  
//*********************************************************************** 
#include "pokemon.h"
#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>


// Function prototype for trim
string trim(const string& str);

// single type
Pokemon::Pokemon(string name, int ndex, Type type1) {
    _name = name; //assigns pokemon name
    _ndex = ndex;   //assigns ndex #
    types[0] = type1;   //stores first/only type
    type_count = 1; //stores that there's only one type
}

// multi-type
Pokemon::Pokemon(string name, int ndex, Type type1, Type type2) {
    _name = name;   //assigns poke name
    _ndex = ndex;   //assigns poke ndex
    types[0] = type1;   //stores first type
    types[1] = type2;   //stores second type
    type_count = 2;     //stores that there is two types
}

// constructor initializes from a summary string
Pokemon::Pokemon(string summary) {
    size_t start_pos = summary.find("#");
    
    if (start_pos == string::npos) {
        _ndex = -1;
        return;
    }

    start_pos++; // Move past the "#"
    size_t end_pos = summary.find(",", start_pos);

    if (end_pos == string::npos) {
        _ndex = -1;
        return;
    }

    try {
        _ndex = std::stoi(summary.substr(start_pos, end_pos - start_pos)); // Convert to integer
    } catch (const std::invalid_argument& e) {
        _ndex = -1;
        return;
    }

    size_t name_end_pos = summary.find(", #");
    _name = summary.substr(0, name_end_pos);

    size_t type_start_pos = summary.find(",", end_pos) + 1;
    size_t type_end_pos = summary.find(",", type_start_pos);
    string type1_str = summary.substr(type_start_pos, type_end_pos - type_start_pos);
    Type type1 = string_to_type(type1_str);
    types[0] = type1;

    type_start_pos = type_end_pos + 1;
    if (type_start_pos < summary.length()) {
        type_end_pos = summary.find(",", type_start_pos);
        string type2_str = summary.substr(type_start_pos, type_end_pos - type_start_pos);
        Type type2 = string_to_type(type2_str);
        types[1] = type2;
        type_count = 2;
    } else {
        type_count = 1;
    }
}

string Pokemon::summary() {
    stringstream ss;
    ss << _name << ", #" << (_ndex < 10 ? "00" : (_ndex < 100 ? "0" : "")) << _ndex << ", ";
    ss << type_to_string(types[0]);
    if (type_count == 2) {
        ss << ", " << type_to_string(types[1]);
    }
    ss << ",";
    return ss.str();
}

string Pokemon::name() {
    return _name;
}

int Pokemon::Ndex() {
    return _ndex;
}

Pokemon::Type Pokemon::type1() {
    return types[0];
}

bool Pokemon::is_multitype() {
    return type_count == 2;
}

Pokemon::Type Pokemon::type2() {
    if (type_count == 2) {
        return types[1];
    } else {
        return types[0];
    }
}

float Pokemon::damage_multiplier(Type attack_type) {
    float multiplier = 1.0;
    for (int i = 0; i < type_count; i++) {
        switch (attack_type) {
            case Normal:
                multiplier *= 1.0;
                break;
            case Fighting:
                if (types[i] == Normal) multiplier *= 2.0;
                else if (types[i] == Flying || types[i] == Poison) multiplier *= 0.5;
                else multiplier *= 1.0;
                break;
            case Flying:
                if (types[i] == Fighting) multiplier *= 2.0;
                else multiplier *= 1.0;
                break;
            case Poison:
                if (types[i] == Poison) multiplier *= 0.5;
                else multiplier *= 1.0;
                break;
        }
    }
    return multiplier;
}

string type_to_string(Pokemon::Type t) {
    switch (t) {
        case Pokemon::Normal: return "Normal";
        case Pokemon::Fighting: return "Fighting";
        case Pokemon::Flying: return "Flying";
        case Pokemon::Poison: return "Poison";
        default: return "";
    }
}

Pokemon::Type string_to_type(string s) {
    s = trim(s);  // Remove leading/trailing whitespace

    if (s == "Normal") return Pokemon::Normal;
    if (s == "Fighting") return Pokemon::Fighting;
    if (s == "Flying") return Pokemon::Flying;
    if (s == "Poison") return Pokemon::Poison;

    // If we reach here, the type is unrecognized, print an error but don't crash
    return Pokemon::Normal;  // Default fallback
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}
