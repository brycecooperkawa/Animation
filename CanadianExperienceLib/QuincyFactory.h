/**
 * @file QuincyFactory.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef CANADIANEXPERIENCE_QUINCYFACTORY_H
#define CANADIANEXPERIENCE_QUINCYFACTORY_H

class Actor;

/**
 * Factory class that builds the Sparty character
 */
class QuincyFactory {
private:

public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);

};

#endif //CANADIANEXPERIENCE_QUINCYFACTORY_H
