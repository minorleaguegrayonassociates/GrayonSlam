#pragma once
#include "souvenir.hpp"
#include <map>
#include <vector>

/**
 * @class Stadium class
 *
 * This class is used for holding information about a stadium.
 * It can also be hidden from public use through the @a hidden
 * property. A stadium contains a list of souvenirs that it contains.
 *
 * Enum classes are available for information about the stadium's
 * architecture. There is also static variables in the class to
 * convert an enum type to an associated string.
 *
 * Note:
 * All stadiums have their IDs defaulted to -1. The only way for a
 * stadium to have a valid ID is for it to be created by the
 * @a Database class. This is why @a Database is a friend class.
 */
class Stadium
{
public:
    friend class Database;

    /* Enum types */
    enum Roof { RETRACTABLE, OPEN, FIXED };
    enum Surface { GRASS, ASTROTURF, ASTROTURF3D };
    enum Typology { RETROMODERN, RETROCLASSIC, JEWELBOX, MODERN, CONTEMPORARY, MULTIPURPOSE };

    /* Enum to strings */
    static const std::string ROOF_STRING[];
    static const std::string SURFACE_STRING[];
    static const std::string TYPOLOGY_STRING[];

    /* Constructors */
    Stadium();
    Stadium(const std::string& name, const std::string& location);

    /* Getters */
    int getId() const;
    std::string getName() const;
    std::string getLocation() const;
    int getSeatCap() const;
    int getYearOpened() const;
    int getCenterFieldDist() const;
    std::vector<Souvenir> getSouvenirs() const;

    /* Setters */
    void setName(const std::string&);
    void setLocation(const std::string&);
    void setSeatCap(int);
    void setYearOpened(int);
    void setCenterFieldDist(int);

    /* Souvenirs */
    void addSouvenir(const std::string& name, double price);
    Souvenir& findSouvenir(int id);

    /* Public data */
    bool hidden = true;
    Roof roof = Roof::RETRACTABLE;
    Surface surface = Surface::GRASS;
    Typology typology = Typology::RETROMODERN;

private:
    /* Constructors */
    Stadium(int id, const std::string& name, const std::string& location,
            int seatCap, int yearOpened, int centerFieldDist,
            Roof, Surface, Typology);

    /* Data */
    int m_id = -1;
    std::string m_name = "invalid";
    std::string m_location = "invalid";
    int m_seatCap = -1;
    int m_yearOpened = -1;
    int m_centerFieldDist = -1;

    /* Souvenirs */
    int m_nextSouvenirId = 0;
    std::map<int,Souvenir> m_souvenirs;
    //TODO replace with nstd::map when completed as per project reqs
};
