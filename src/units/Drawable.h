#ifndef PROGTEST_PROJECT_DRAWABLE_H
#define PROGTEST_PROJECT_DRAWABLE_H

#include <string>

/**
 * A parent to everything that can be draw
 */
class Drawable
{
public:
	/**
	* Drawable must be provided initial x coordinate and y coordinate
	*/
    Drawable(int x, int y);
    /**
     * @return The X coordinate of this Drawable
     */
    virtual double GetX() const;
    /**
     * @return The Y coordinate of this Drawable
     */
    virtual double GetY() const;
    /**
     * @return The character to draw of this Drawable
     */
    virtual char GetChar() const = 0;

    /**
     * Free resources
     */
    virtual ~Drawable() = default;
protected:
    /// The X (column) coordinate
    int m_X;
    /// The Y (row) coordinate
    int m_Y;
};

#endif //PROGTEST_PROJECT_DRAWABLE_H
