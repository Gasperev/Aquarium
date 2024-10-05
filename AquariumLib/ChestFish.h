/**
 * @file ChestFish.h
 * @author Evan Gasper
 *
 * A class representing the chests
 */
 
#ifndef CHESTFISH_H
#define CHESTFISH_H

#include "Fish.h"

/**
 * Class representing the Chest
 */
class ChestFish : public Fish {
private:

public:
 /// Disable default constructor
 ChestFish() = delete;
 /// Disable default copy
 ChestFish(const ChestFish&) = delete;
 /// Constructor
 ChestFish(Aquarium* aquarium);
 /// Disable default Assignment
 void operator = (const ChestFish&) = delete;

 /// Used to determine type of fish when saving
 wxXmlNode* XmlSave(wxXmlNode* node) override;
};



#endif //CHESTFISH_H
