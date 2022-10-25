/**
 * @file HaroldFactory.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef CANADIANEXPERIENCE_HAROLDFACTORY_H
#define CANADIANEXPERIENCE_HAROLDFACTORY_H

class Actor;

/**
 * Factory class that builds the Harold character
 */
class HaroldFactory {
private:

public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);

};

#endif //CANADIANEXPERIENCE_HAROLDFACTORY_H
