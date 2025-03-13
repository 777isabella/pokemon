#include "pokedex.h"
#include <fstream>
#include <iostream>

// Constructs an empty Pokedex
Pokedex::Pokedex() {
    for (int i = 0; i < 1000; i++) {
        A[i] = nullptr;
    }
}

// Constructs a Pokedex with the Pokemon found in the specified file
Pokedex::Pokedex(string filename) {
    for (int i = 0; i < 1000; i++) {
        A[i] = nullptr;
    }

    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Pokemon* p = new Pokemon(line); // dynamically allocate
        add(p);  // Add the Pokemon to the Pokedex
    }
}

// Writes the Pokedex to a file
void Pokedex::save(string filename) {
    ofstream file(filename);
    for (int i = 0; i < 1000; i++) {
        if (A[i] != nullptr) {
            file << A[i]->summary() << endl;
        }
    }
}

// Adds a Pokemon to the Pokedex
void Pokedex::add(Pokemon* p) {
    int ndex = p->Ndex();
    if (ndex >= 0 && ndex < 1000) {
        if (A[ndex] != nullptr) {
            // Only delete if the stored pointer is different
            if (A[ndex] != p) {
                std::cout << "Deleting existing Pokemon at Ndex: " << ndex << std::endl;
                delete A[ndex];  // Delete only if it's a different pointer
            } else {
                std::cout << "Attempted to add the same Pokemon, skipping delete." << std::endl;
                return;  // Skip adding if it's the same Pokemon (avoid duplicates)
            }
        }
        // Add the new Pokemon to the Pokedex
        A[ndex] = p;
        std::cout << "Added Pokemon with Ndex: " << ndex << std::endl;
    } else {
        std::cout << "Invalid Ndex for Pokemon: " << ndex << std::endl;
    }
}





void Pokedex::remove(Pokemon* p) {
    int ndex = p->Ndex();
    if (ndex >= 0 && ndex < 1000 && A[ndex] != nullptr) {
        if (A[ndex] == p) {  // Ensure we're deleting the correct pointer
            std::cout << "Deleting Pokemon at Ndex: " << ndex << std::endl;
            delete A[ndex];
            A[ndex] = nullptr;
        } else {
            std::cout << "Attempted to remove a Pokemon that is not at the specified Ndex: " << ndex << std::endl;
        }
    } else {
        std::cout << "Attempted to remove a Pokemon that doesn't exist or was already deleted at Ndex: " << ndex << std::endl;
    }
}


// Looks up a Pokemon by name
Pokemon* Pokedex::lookup_by_name(string name) {
    for (int i = 0; i < 1000; i++) {
        if (A[i] != nullptr && A[i]->name() == name) {
            return A[i];
        }
    }
    return nullptr;
}

// Looks up a Pokemon by Ndex
Pokemon* Pokedex::lookup_by_Ndex(int ndex) {
    if (ndex >= 0 && ndex < 1000) {
        return A[ndex];
    }
    return nullptr;
}

// Returns the number of Pokemon in the Pokedex
int Pokedex::size() {
    int count = 0;
    for (int i = 0; i < 1000; i++) {
        if (A[i] != nullptr) {
            count++;
        }
    }
    return count;
}
