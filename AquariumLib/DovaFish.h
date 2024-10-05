/**
 * @file DovaFish.h
 * @author Evan Gasper
 *
 * A class representing the DovaFish
 */
 
#ifndef DOVAFISH_H
#define DOVAFISH_H

#include "Item.h"
#include "Fish.h"

/**
 * Class representing the Skyrim Themed Fish
 */
class DovaFish : public Fish{
private:

public:
 /// Disable Default constructor
 DovaFish() = delete;

 /// Disable Copy constructor
 DovaFish(const DovaFish &) = delete;

 /// Disable Assignment operator
 void operator=(const DovaFish &) = delete;

 /// Constructor
 DovaFish(Aquarium* aquarium);

 /// Used to determine type of fish when saving
 wxXmlNode* XmlSave(wxXmlNode* node) override;
};



#endif //DOVAFISH_H
