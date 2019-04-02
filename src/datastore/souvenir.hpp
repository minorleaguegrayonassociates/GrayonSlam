#pragma once
#include <string>

/**
 * @class Souvenir class
 *
 * This class holds information about a souvenir. It can be
 * hidden from public use by the @a hidden property. Other
 * properties of the souvenir can be changed through
 * @a getter functions.
 */
class Souvenir
{
public:
    friend class Stadium;

    /* Constructors */
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
    std::string m_name;
    double m_price = -1;
};
