#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H
#include <string>
#include "Outfit.h"

Outfit loadOutfit(const std::string& key);
void saveOutfit(const Outfit& o, const std::string& key);

#endif