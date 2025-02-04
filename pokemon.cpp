#include "pokemon.h"

// Constructor for single-type Pokemon
Pokemon::Pokemon(string name, int ndex, Type type1) {
    _name = name;
    _ndex = ndex;
    types[0] = type1;
    type_count = 1;
}

// Constructor for multi-type Pokemon
Pokemon::Pokemon(string name, int ndex, Type type1, Type type2) {
    _name = name;
    _ndex = ndex;
    types[0] = type1;
    types[1] = type2;
    type_count = 2;
}

// Returns the name of the Pokemon
string Pokemon::name() {
    return _name;
}

// Returns the Ndex (National Pokedex number) of the Pokemon
int Pokemon::Ndex() {
    return _ndex;
}

// Returns the first type of the Pokemon
Pokemon::Type Pokemon::type1() {
    return types[0];
}

// Returns whether the Pokemon has multiple types
bool Pokemon::is_multitype() {
    return type_count == 2;
}

// Returns the second type if available, otherwise the first type
Pokemon::Type Pokemon::type2() {
    return type_count == 2 ? types[1] : types[0];
}

// Returns the damage multiplier against this Pokemon for a given attack type
float Pokemon::damage_multiplier(Type attack_type) {
    // Damage multipliers based on Generation I type chart
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