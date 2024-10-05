/**
 * @file DecorCastle.h
 * @author Evan Gasper
 *
 * Class representing a castle
 */
 
#ifndef DECORCASTLE_H
#define DECORCASTLE_H

#include "Item.h"

/// Castle holding information for the decoration object, castle
class DecorCastle : public Item {
private:

public:
 /// Disable Constructor
 DecorCastle() = delete;

 /// Disable Copy
 DecorCastle(const DecorCastle &) = delete;

 /// Disable Destructor
 void operator=(const DecorCastle &) = delete;

 /// Constructor
 DecorCastle(Aquarium *aquarium);

 /// Used to determine type of fish when saving
 wxXmlNode* XmlSave(wxXmlNode* node) override;
};



#endif //DECORCASTLE_H
