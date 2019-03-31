#pragma once
#include <string>

class Souvenir
{
public:
    /* Constructors */
    Souvenir();
    Souvenir(const std::string& name, double price);

    /* Getters */
    std::string getName() const;
    double getPrice() const;

    /* Setters */
    void setName(const std::string&) const;
    void setPrice(double) const;

    /* Public data */
    bool hidden = true;

private:
    /* Data */
    std::string m_name;
    double m_price = -1.0;
};
