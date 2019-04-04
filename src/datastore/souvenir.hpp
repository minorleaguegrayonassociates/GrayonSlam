#pragma once
#include <string>

/**
 * @class Souvenir class
 *
 * This class holds information about a souvenir. It can be
 * hidden from public use by the @a hidden property.
 *
 * A souvenir with an ID value of -1 means that it hasn't
 * been attached to a stadium.
 */
class Souvenir
{
public:
    friend class Stadium;

    /* Constructors */
    Souvenir();
    Souvenir(const std::string& name, double price);

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
    /* Data */
    int m_id = -1;
    std::string m_name = "invalid";
    double m_price = -1;
};
