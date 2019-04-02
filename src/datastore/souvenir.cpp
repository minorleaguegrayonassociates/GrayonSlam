#include "souvenir.hpp"

/**
 * Constructs a souvenir given a name and price.
 *
 * @param name Souvenir name
 * @param price Souvenir price
 */
Souvenir::Souvenir(const std::string& name, double price)
    : m_name(name), m_price(price)
{}

int Souvenir::getId() const
{
    return m_id;
}

std::string Souvenir::getName() const
{
    return m_name;
}

double Souvenir::getPrice() const
{
    return m_price;
}

/**
 * Sets the souvenir name only if the given string is not empty.
 *
 * @param name Souvenir name
 */
void Souvenir::setName(const std::string& name)
{
    if(!name.empty()) { m_name = name; }
}

/**
 * Sets the souvenir price only if the given price is non-negative.
 *
 * @param price Souvenir price
 */
void Souvenir::setPrice(double price)
{
    if(price >= 0.0) { m_price = price; }
}
