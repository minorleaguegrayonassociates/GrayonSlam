#pragma once
#include <string>

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
    std::string m_name;
    double m_price = -1;
};
