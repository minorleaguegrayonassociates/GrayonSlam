
#include <iostream>
#include <iomanip>
#include "../src/utils/map.hpp"

int main()
{
	/*Creating and Filling up Map*/
    nstd::map<int,string> map2;
    cout << "Populating hash map...\n";
    map2.insert(18,"Laguna Niguel");
    map2.insert(41,"Mission Viejo");
    map2.insert(22,"San Clemente");
    map2.insert(44,"Irvine");
    map2.remove(41);
    map2.insert(58,"Lake Forest");
    map2.insert(32, "San Diego");
    map2.insert(49, "Anaheim");
    map2.remove(58);
    map2.insert(31, "Los Angeles");
    map2.insert(17, "Orange");
    map2.insert(72, "Palm Springs");
    map2.insert(41, "Riverside");
    map2.remove(72);
    map2.insert(19, "Brea");
    map2.insert(60, "Santa Ana");
    map2.insert(35, "Tustin");
    map2.insert(103, "Oceanside");
    map2.insert(11, "La Jolla");
    map2.insert(18, "Del Mar");
    map2.insert(22, "Aliso Viejo");
    map2.insert(49, "Laguna Beach");
    cout <<"The size of the map is " << map2.size() << endl;
    map2.remove(41);
    cout <<"The size of the map is " << map2.size() <<" after removing key 41"<< endl;
    map2.insert(42,"Vista");
    map2.insert(49, "San Diego");
    map2.insert(99, "San Juan");
    map2.insert(29, "Dana Point");
    map2.insert(88, "El Segundo");
    map2.insert(41, "San Clemente");
    map2.insert(62, "Laguna Hills");
    map2.insert(72, "Comercia");
    map2.insert(96, "Ladera Ranch");
    map2.insert(100, "Boston");
    cout << map2;

	/*Testing operator[] and negative int keys*/
    cout << endl <<"Adding Replacing El Segundo with Ladera in the map" <<endl;
    cout <<"Before "<< map2[88] << endl;
    map2[88] = "Ladera";
    cout <<"After "<< map2[88] << endl;
    cout << endl <<"Testing operator[]" <<endl;
    map2[-1] = "harro";
    map2[1] = "hi";
    map2[2] ="hi";
    cout << map2[-1] <<" with key -1"<< endl;
    cout << map2[1]  <<" with key 1"<< endl;
    cout << map2[2]  <<" with key 2"<< endl << endl;
    cout << map2;

	/*Testing backwards iteration*/
    cout << endl << "Testing backwards iteration:" << endl;
    for(nstd::map<int,string>::iterator it = (--map2.end());!it.isNull();--it)
    {
    	cout << *it << endl;
    }

	/*Testing forward iteration*/
    cout << endl << "Testing forward iteration:" << endl;
    for(nstd::map<int,string>::iterator it2 = map2.begin(); it2 != map2.end(); ++it2)
    {
    	cout << *it2 << endl;
    }

	/*Testing string hashing and operator[] with strings*/
    cout << "\nTesting string hashing\n";
    nstd::map<string,string> users;
    users["password"] = "username";
    users["username"] = "password";
    cout << users["password"] << endl;
    cout << users["username"] << endl;
    cout << users;
	return 0;
}


