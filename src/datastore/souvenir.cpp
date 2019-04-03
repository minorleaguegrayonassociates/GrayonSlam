#include "souvenir.hpp"

/**
 * Constructs a souvenir that is unattached from a stadium.
 * To add it to a stadium, use @a Stadium::addSouvenir.
 *
 * An object created by this should not be used in a stadium
 * unless the name and price has been changed; otherwise, both
 * will be initialized to "invalid" and -1 respectively.
 */
Souvenir::Souvenir()
{}

/**
 * Constructs a souvenir given a name and price. If @a name is
 * an empty string, the souvenir's name becomes "invalid". If
 * @a price is negative, the souvenir's price becomes -1.
 *
 * This souvenir is not attached to a stadium because its
 * ID is -1. To add it to a stadium, use @a Stadium::addSouvenir.
 *
 * @param name Souvenir name
 * @param price Souvenir price
 */
Souvenir::Souvenir(const std::string& name, double price)
{
    setName(name);
    setPrice(price);
}

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
