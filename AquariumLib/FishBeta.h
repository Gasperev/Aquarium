/**
 * @file FishBeta.h
 * @author Evan Gasper
 *
 * A class representing Beta Fish
 */
 
#ifndef FISHBETA_H
#define FISHBETA_H

#include "Item.h"
#include "Fish.h"

/**
 * Class representing the Beta Fish
 */
class FishBeta : public Fish {
private:

public:
/// Disable Default constructor
FishBeta() = delete;

/// Disable Copy constructor
FishBeta(const FishBeta &) = delete;

 /// Disable Assignment operator
 void operator=(const FishBeta &) = delete;

 /// Constructor
FishBeta(Aquarium* aquarium);

 /// Used to determine type of fish when saving
 wxXmlNode* XmlSave(wxXmlNode* node) override;
};

#endif //FISHBETA_H