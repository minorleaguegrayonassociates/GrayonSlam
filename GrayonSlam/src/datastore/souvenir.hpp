#pragma once
#include <string>

/**
 * @class Souvenir class
 *
 * This class holds information about a souvenir. It can be
 * hidden from public use by the @a hidden property.
 *
 * A souvenir with an ID of -1 means it's invalid and it
 * isn't attached to a stadium.
 */
class Souvenir
{
public:
    friend class Stadium;

    /* Constructors */
    Souvenir();

    /* Getters */
    int getId() const;
    std::string getName() const;
    double getPrice() const;

    /* Setters */
    void setName(const std::string&);
    void setPrice(double);

    /* Public data */
    bool hidden = true;

private:
    /* Constructors */
    Souvenir(int id, const std::string& name, double price);

    /* Data */
    int m_id = -1;
    std::string m_name = "invalid";
    double m_price = -1;
};
