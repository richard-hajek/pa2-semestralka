#ifndef PROGTEST_PROJECT_HELP_H
#define PROGTEST_PROJECT_HELP_H

#include "Fragment.h"

/**
 * Provide a hint describing currently loaded setup
 */
class Help final : public Fragment{
public:

    /**
     * Construct a new Help window
     */
    explicit Help(Game * game) : Fragment(game){}

    /**
     * Sets the proffered dimensions of the overview
     * @param width Width of the overview
     * @param height Height of the overview
     */
    void RequestDimensions(int & width, int & height) final;

    /**
     * Render the overview
     */
    void Render() final;

    /**
     * Does nothing
     */
    ~Help() final;
};


#endif //PROGTEST_PROJECT_HELP_H
