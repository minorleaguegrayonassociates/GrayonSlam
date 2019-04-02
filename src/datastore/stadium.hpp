#pragma once
#include "src/datastore/souvenir.hpp"
#include <map>

class Stadium
{
public:
    friend class DataStore;

    /* Enum types */
    enum class Roof { RETRACTABLE, OPEN, FIXED };
    enum class Surface { GRASS, ASTROTURF, ASTROTURF3D };
    enum class Typology
    {
        RETROMODERN, RETROCLASSIC, JEWELBOX,
        MODERN, CONTEMPORARY, MULTIPURPOSE
    };

    /* Constructors */
    Stadium(const std::string& name, const std::string& location);

    /* Getters */
    int getId() const;
    int getTeamId() const;
    std::string getName() const;
    std::string getLocation() const;
    int getSeatCap() const;
    int getYearOpened() const;
    int getCenterFieldDist() const;

    /* Setters */
    void setTeamId(int);
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
    /* Static variables */
    static int nextId;

    /* IDs */
    int m_id = -1;
    int m_teamId = -1;

    /* Stadium data */
    std::string m_name;
    std::string m_location;
    int m_seatCap = -1;
    int m_yearOpened = -1;
    int m_centerFieldDist = -1;

    /* Souvenirs */
    int m_nextSouvenirId = 0;
    std::map<int,Souvenir> m_souvenirs;
};
