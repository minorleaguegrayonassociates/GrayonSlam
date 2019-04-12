#pragma once
#include <functional>
#include <iostream>
#include <iomanip>



namespace nstd
{

    /* FORWARD DECLARATIONS*/

    template <typename key>
    class hash;

    template <typename key, typename value, typename Hash>
    class map;

    template <typename key, typename value, typename Hash>
    std::ostream& operator<<(std::ostream& out, const map<key, value, Hash>& d);


    /**
     * @class nstd::map class
     *
     * A data structure class that is meant to hold key value pairs and
     * hash with the key to retrieve the value. This map is also iteratable
     * meaning that you can start at the beginning or end and read through it
     * as if it was a list.
     *
     * This class also supports custom hashing, but the functions need to be in this
     * format static int staticHashAlgo(key k,int j,int capacity) where the returned
     * int from the function needs to follow this restriction 0 < hash < capacity.
     *
     * @code{.cpp}
     * //Instantiate map
     * nstd::map<int,std::string> myMap;
     *
     * //will create a new key value in map if not present
     * //othewise reassigns value at key 2, this operation requires
     * //copy assignment. As operator[] returns a refrence to the value
     * myMap[2] = "Hi";
     *
     * //Reassign into key 2, replaces "Hi" with "Hello"
     * myMap[2] = "Hello";
     *
     * //myMap[2] returns a refrence to the value at key 2 and will print it out
     * std::cout << myMap[2];
     *
     * //Since key 8 is not defined, the map will add key 8 to the map and use the
     * //values default constructor to construct the value
     * std::cout << myMap[8];
     * @endcode
     *
     * In the code above, a new nstd::map is instantiated with the key being an int
     * and the value being a std::string using the default constructor. We then assign
     * Hi into a newly created value location. Then we use the value copy assignment to
     * reassign hello into hi. We then output what is at key 2. And we readout whatever is
     * in key location 8, in our case nothing so it returns a default constructed value.
     */
    template <typename key, typename value, typename Hash = hash<key>>
    class map
    {
    public:
        class iterator;

        /* Constructors, Destructor, and Assignment */
        map();
        map(const map&);
        map(map&&);
        map& operator=(const map&);
        ~map();

        /* Accessing */
        iterator find(const key&);
        value& operator[] (const key&);
        value& operator[] (key&&);
        friend std::ostream& operator<< <>(std::ostream&, const map&);

        /* Mutation Operations */
        iterator insert(const key&,const value&);
        std::pair<key,value> remove(const key&);
        void reserve(unsigned int);

        /* Iterator Getters */
        iterator begin() noexcept;
        iterator end() noexcept;

        /* Map information*/
        int size() const {return m_numOfElems;}
        int capacity() const {return m_capacity;}
        bool empty() const {return m_numOfElems == 0;}

    private:
        struct node;
        /* Hash Algorithm*/
        Hash hash;

        /* Accessing Helper Function */
        node* insertFind(key, int&) const;

        /* Data Members */
        node** m_array = NULL;
        int m_primeNumIndex = 0;
        int m_numOfElems = 0;
        int m_capacity = 0;
    };

    /**
     * @class nstd::map<key,value,Hash>::iterator class
     *
     * A class that refences internal data which is meant to hold a position of a key,
     * value pair in the corresponding map. It can be incremented and decremeneted to move
     * through the map. It can also access the data it indexes to read the contents of the map
     * and to write to it as well
     *
     * @code{.cpp}
     * ...
     * //will create an iterator to start of the map
     * nstd::map<int,std::string>::iterator iter = myMap.begin();
     * //Loop through the contents of the map
     * while(iter != myMap.end())
     * {
     *   std::cout << *iter;
     *   ++iter;
     * }
     * @endcode
     *
     * In the code above, an iterator is created that indexes the beginning of
     * the map. It is then put into a loop and incremeneted with each pass until
     * it reaches the end of the map. While it is being incremented, it is outputting
     * the data that the iterator is indexing is being accessed and printed
     */
    template <typename key, typename value, typename Hash>
    class map<key,value,Hash>::iterator
    {
    public:
        /* Constructors */
        iterator(const iterator &);
        iterator(int position,map*,node*);

        /* Movement Operators */
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);

        /* Access Operators*/
        value& operator*();
        value* operator->();

        /* Comparison Operators */
        bool operator!=(const iterator&) const;
        bool operator==(const iterator&) const;

        /* Iterator Information */
        bool isNull(){return (m_data == NULL ||m_data->available);}
        node* getData(){return m_data;}
        map* getParent(){return m_parent;}
        void setEnd(bool isEnd){m_end= isEnd;}

    private:
        iterator();

        /* Data Members */
        int m_position = 0;
        map* m_parent = NULL;
        node* m_data = NULL;
        bool m_end = false;
    };


    /**
     * @struct A node struct for holding the internal data of the map
     * This node struct that holds internal data of the map class
     */
    template <typename key, typename value, typename Hash>
    struct map<key,value,Hash>::node
    {
        /* Data Memebers */
        key nodeKey;
        value nodeValue;
        //available is used when removing an element, marks node as free to fill in with new data
        //but if searching not to stop search on that node
        bool available = false;
        map* parentMap = NULL;

        /* Constructor */
        node(key, value, bool, map*);
    };

    /**
     * @class nstd::hash class
     *
     * A functor class that takes in a key of template type
     * @a k and an int @a j for quadratic hashing and hashes it to
     * produce a int for use in a data structure
     *
     * @code{.cpp}
     *
     * nstd::hash<int> myHash();
     * int ar[20];
     * ...
     * std::cout << ar[myHash(15, 2, 20)];
     * ...
     * @endcode
     *
     * In the code above, a hash class is instantiated along side
     * an array of size 20. Later on in the code, the key 15 is hashed with
     * a @a j value of 2 for the quadratic hash and the size of the array 20 in
     * order to access elements inside the array, which are then printed out.
     */
    template <typename key>
    class hash
    {
    public:
        /**
         * This method will hash the key into an int for mapping
         * using quadratic hashing.
         * @param k the key itself
         * @param j the collision value, increase for more values
         * @param capacity (capacity - 1) is max hashcode
         * @return returns a hashcode in the form of an int
         */
        int operator()(key k, int j, int capacity)
        {
            return hashAlgo(k,j,capacity);
        }
        /**
         * This method is the same as operator() but named
         * (i.e. hash.hashAlgo(params) vs hash(params) both are same)
         * @param k the key itself
         * @param j the collision value, increase for more values
         * @param capacity (capacity - 1) is max hashcode
         * @return returns a hashcode in the form of an int
         */
        int hashAlgo(key k,int j, int capacity)const
        {
            return std::abs(((static_cast<int>(k))+j*j)%capacity);
        }
        /**
         * @brief This method is the static version of operator()
         * @param k the key itself
         * @param j the collision value, increase for more values
         * @param capacity (capacity - 1) is max hashcode
         * @return returns a hashcode in the form of an int
         */
        static int staticHashAlgo(key k,int j, int capacity)
        {
            return std::abs(((static_cast<int>(k))+j*j)%capacity);
        }
    };

    /**
     * @class nstd::hash class string specialization
     *
     * A functor class that takes in a key of type
     * std::string and an int j for quadratic hashing and hashes it to
     * produce a int for use in a data structure
     *
     * @code{.cpp}
     *
     * nstd::hash<std::string> myHash();
     * int ar[20];
     * ...
     * std::cout << ar[myHash("Chicago", 2, 20)];
     * ...
     * @endcode
     *
     * In the code above, a hash class is instantiated along side
     * an array of size 20. Later on in the code, the key "Chicago" is hashed with
     * a j value of 2 for the quadratic hash and the size of the array 20 in
     * order to access elements inside the array, which are then printed out.
     */
    template <>
    class hash<std::string>
    {
    public:
        /**
         * This method will hash the a string into an int for mapping
         * with the murmur hash2/3
         * @param k the std::string key itself
         * @param j the collision value, increase for more values
         * @param capacity (capacity - 1) is max hashcode
         * @return returns a hashcode in the form of an int
         */
        int operator()(std::string k, int j, int capacity)
        {
            return hashAlgo(k,j,capacity);
        }
        /**
         * This method is the same as operator() but named
         * @param k the key itself
         * @param j the collision value, increase for more values
         * @param capacity (capacity - 1) is max hashcode
         * @return returns a hashcode in the form of an int
         */
        int hashAlgo(std::string k, int j,int capacity)const
        {
            int hash = static_cast<int>(std::hash<std::string>{}(k)) + (j*j);
            return hash%capacity;
        }
        /**
         * This method is the static version of operator()
         * @param k the key itself
         * @param j the collision value, increase for more values
         * @param capacity (capacity - 1) is max hashcode
         * @return returns a hashcode in the form of an int
         */
        static int staticHashAlgo(std::string k,int j, int capacity)
        {
            int hash = static_cast<int>(std::hash<std::string>{}(k)) + (j*j);
            return hash%capacity;
        }
    };


    /**
    * @struct Primes (a prime lookup table struct)
    * This struct serves as a way to instantiate a prime look up table and adds cleanup once the
    * program has terminated
    */
   struct Primes
   {
       /* Constructors */
       Primes():lookupTable{SieveOfEratosthenes(4000)}{}
       Primes(int n):lookupTable{SieveOfEratosthenes(n)}{}

       /* Data Members */
       unsigned int* lookupTable;

       /* Destructor */
       ~Primes(){delete lookupTable;}

       /* PRIME LOOKUP TABLE - QUICK ACCESS*/

       /**
        * @brief This function will take an integer and create an array of prime
        * values up to the given integer
        * @param n number of values, from 0 to n to select primes from
        * @return A pointer to an array of primes
        */
       unsigned int* SieveOfEratosthenes(int n)
       {
           //inspired by geeksforgeeks.org
           int *primes = new int[static_cast<unsigned int>(n)+1];
           if(n >1) for(int i = 2; i <=n; ++i) primes[i] = true;
           primes[0] = false;
           primes[1] = false;
           unsigned int numOfPrimes = 0;
           for(int p=2; p*p<=n; ++p)
           {
               if(primes[p])
               {
                   for(int i=p*p; i<=n; i += p)
                   {
                       primes[i] = false;
                   }
               }
           }
           for(int i = 0; i < n+1; ++i)
           {
               if(primes[i])
               {
                   ++numOfPrimes;
               }
           }
           int index = 0;
           unsigned int * actualPrimes = new unsigned int[numOfPrimes];
           for(unsigned int i = 0; i < static_cast<unsigned int>(n)+1; ++i)
           {
               if(primes[i])
               {
                   actualPrimes[index] = i;
                   ++index;
               }
           }
           delete [] primes;
           return actualPrimes;
       }
   };

   /**
     * @brief Static object that contains an array of primes for use by the map
     */
    static Primes TABLE_OF_PRIMES;

    /* MAP METHODS*/

    /**
     * This method is the default constructor for the map. It
     * defaults the size of the map to 31 and initializes the map to nullptrs.
     */
    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::map()
        : m_array{new node*[31]}, m_primeNumIndex{10},m_numOfElems{0},m_capacity{31}
    {
        for(int i = 0; i< m_capacity;++i)
        {
            m_array[i]=NULL;
        }
    }

    /**
     * This constructor constructs a map by copying the keys and values of a second map
     * @param otherMap The other map to be copied from (source map)
     */
    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::map(const map& otherMap)
        : m_primeNumIndex{otherMap.m_primeNumIndex},m_numOfElems{otherMap.m_numOfElems},m_capacity{otherMap.m_capacity}
    {
        m_array = new node*[otherMap.m_capacity];
        for(int i = 0; i < otherMap.m_capacity; ++i)
        {

            if(otherMap.m_array[i] != NULL && otherMap.m_array[i]->available == false)
            {
                m_array[i] = new node(otherMap.m_array[i]->nodeKey,otherMap.m_array[i]->nodeValue,false, this);
            }
            else
            {
                m_array[i] = NULL;
            }
        }
    }

    /**
     * This constructor copies a map by moving the pointers from the temporary map
     * @param otherMap the map where the data will stolen from in the move constuctor
     */
    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::map(map&& otherMap)
        : m_primeNumIndex{otherMap.m_primeNumIndex}, m_numOfElems{otherMap.m_numOfElems},m_capacity{otherMap.m_capacity}
    {
        m_array = otherMap.m_array;
        otherMap.m_array = NULL;
    }

    /**
     * This operator overload copies the contents of one map into this map
     * @param The map to be copied from
     */
    template <typename key, typename value, typename Hash>
    map<key,value,Hash>& map<key,value,Hash>::operator=(const map& otherMap)
    {
        if(&otherMap != this)
        {
            if(m_numOfElems != 0)
            {
                for(int i = 0; i < m_capacity; ++i)
                {
                    if(m_array[i] != NULL){ delete m_array[i]; }
                }
                delete [] m_array;
            }
            m_primeNumIndex = otherMap.m_primeNumIndex;
            m_numOfElems = otherMap.m_numOfElems;
            m_capacity = otherMap.m_capacity;
            m_array = new node*[otherMap.m_capacity];
            for(int i = 0; i < otherMap.m_capacity; ++i)
            {
                if(otherMap.m_array[i] != NULL && otherMap.m_array[i]->available == false)
                {
                    m_array[i] = new node(otherMap.m_array[i]->nodeKey,otherMap.m_array[i]->nodeValue,false, this);
                }
                else
                {
                    m_array[i] = NULL;
                }
            }
        }
        return *this;
    }

    /**
    * deletes all the nodes and map array.
    */
    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::~map()
    {
        for(int i = 0; i < m_capacity; ++i)
        {
            if(m_array[i] != NULL) delete m_array[i];
        }
        delete [] m_array;
    }

    /**
     * @brief This function attempts to find the key in the map and returns an iterator of its position.
     *
     * This function will search through the map looking for the key. If successful, it will return
     * an iterator corresponding to its position. If unsuccessful, it will return an iterator with
     * a position of -1 (Corresponding to end).
     *
     * @param k the key to search for in the map
     * @return iterator containing the position of the key in the map
     */
    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::find(const key& k)
    {
        int position = -1;
        node* val = NULL;
        for(int i = 0; i < m_capacity; ++i)
        {
            if(m_array[i] != NULL)
            {
                int j = 1; //collision j
                unsigned int hashCode = hash(k, 0, m_capacity);
                while(m_array[hashCode] != NULL && !m_array[hashCode]->available && j<=m_capacity)
                {
                    if(m_array[hashCode]->nodeKey == k){break;}
                    hashCode = hash(k, j, m_capacity);
                    ++j;
                }
                if(m_array[hashCode] != 0 && !m_array[hashCode]->available)
                {
                    val = m_array[hashCode];
                    position = static_cast<int>(hashCode);
                }
            }
        }
        return iterator(position, this, val);
    }

    /**
     * @brief This function finds the value corresponding to key and returns it.
     *
     * This function will attempt to find the given key in the map. If it is successful,
     * it will return the object by reference. If it cannot locate it, it will construct
     * a new object that corresponds to the given key and inserts both the key and value.
     *
     * @param k the key to be searched for in the array
     * @return Value that corresponds to the given key by reference.
     */
    template <typename key, typename value, typename Hash>
    value& map<key,value,Hash>::operator[](const key& k)
    {
        iterator it = find(k);
        if(it.isNull())
        {
            it = insert(k,value());
        }
        return *it;
    }

    /**
     * @brief This function finds the value corresponding to a temporary key and returns it.
     *
     * This function will attempt to find the given key in the map. If it is successful,
     * it will return the object by reference. If it cannot locate it, it will construct
     * a new object that corresponds to the given key and insert them both into the map.
     *
     * @return Value that corresponds to the given key by reference.
     */
    template <typename key, typename value, typename Hash>
    value& map<key,value,Hash>::operator[] (key&& k)
    {
        iterator it = find(k);
        if(it.isNull())
        {
            it = insert(k,value());
        }
        return *it;
    }

    /**
     * This function iterates through the map and prints the keys and value
     * to the ostream. This is implemented with the intent of error logging
     * @param out the ostream you are writing to
     * @param d the map you are reading from
     * @return the ostream to continue the output chain
     */
    template <typename key, typename value, typename Hash>
    std::ostream& operator<<(std::ostream& out, const map<key, value, Hash>& d)
    {
        out << "The key value combos inside hash map are: \n";
        for(int i = 0; i < d.m_capacity; ++i)
        {
            if(d.m_array[i] != NULL && !d.m_array[i]->available)
            {
                out << "Hash: "<<std::setw(2)<<std::right
                    << i <<" Key: " <<std::setw(3)<< d.m_array[i]->nodeKey
                    << " Value: " << d.m_array[i]->nodeValue << "\n";
            }
        }
        return out;
    }

    /**
     * @brief This function insert a key and corresponding value into the map
     *
     * This function will attempt to find the given key in the map. If it is successful,
     * it will replace the old value with the new one. If it cannot locate it, it will construct
     * a new object that corresponds to the given key and insert them both into the map.
     *
     * @param k key to be inserted
     * @param v value to be inserted
     * @return iterator corresponding to the position of the inserted key
     */
    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::insert(const key& k,const value& v)
    {
        int findPosition = -1;
        node* found = insertFind(k, findPosition);
        if(found != NULL) found->available = false;
        node* tmp;
        unsigned int hashCode = 0;
        if(!found)
        {
            ++m_numOfElems;
            if(m_numOfElems == m_capacity) reserve(TABLE_OF_PRIMES.lookupTable[m_primeNumIndex+1]);
            unsigned int j;
            tmp = new node(k, v,false, this);
            j = 1;
            hashCode = hash(k,0,m_capacity);
            while(m_array[hashCode] != 0 && m_array[hashCode]->available != true)
            {
                hashCode = hash(k, j, m_capacity);
                ++j;
            }
            if(m_array[hashCode] != 0)if(m_array[hashCode]->available == true) delete m_array[hashCode];
            m_array[hashCode] = tmp;
            findPosition = static_cast<int>(hashCode);
        }
        else
        {found->nodeKey = k; found->nodeValue = v; found->available = false; tmp = found; }
        return iterator(findPosition,this,tmp);
    }

    /**
     * @brief This function removes the given key and corresponding value from the map.
     *
     * This function will attempt to find a given key in the map. If successful, it will remove
     * it and the corresponding key in the map and return them as a pair. If it cannot locate the key,
     * it will construct a pair of the key and value made from default constructors and return that pair.
     *
     * @return std::pair containing the key and value removed from the map.
     */
    template <typename key, typename value, typename Hash>
    std::pair<key,value> map<key,value,Hash>::remove(const key& k)
    {
        key resultKey = key();
        value resultValue = value();
        iterator found = find(k);
        if(found.getData())
        {
           found.getData()->available = true;
           resultKey = found.getData()->nodeKey;
           resultValue = found.getData()->nodeValue;
           --m_numOfElems;
        }
        return std::make_pair(resultKey, resultValue);
    }

    /**
     * If the given integer is larger than the current capacity of the map,
     * this function will reserve room up to the nearest prime number that is larger
     * than the given integer and rehash all of the key and value pairs.
     */
    template <typename key, typename value, typename Hash>
    void map<key,value,Hash>::reserve(unsigned int newInternalSize)
    {
        if(newInternalSize > TABLE_OF_PRIMES.lookupTable[m_primeNumIndex] )
        {
            while(TABLE_OF_PRIMES.lookupTable[m_primeNumIndex] < newInternalSize) ++m_primeNumIndex;
            unsigned int oldCap = m_capacity;
            m_capacity = TABLE_OF_PRIMES.lookupTable[m_primeNumIndex];
            node ** newArr = new node*[m_capacity];
            for(int i = 0; i < m_capacity; ++i) newArr[i] = 0;
            node * tmp;
            unsigned int hashCode, j;
            for(unsigned int i = 0; i < oldCap; ++i)
            {
                if(m_array[i] == 0 || m_array[i]->available) continue;
                tmp = new node(m_array[i]->nodeKey, m_array[i]->nodeValue,false, this);
                j = 1;
                hashCode = hash(m_array[i]->nodeKey,0, m_capacity);
                while(newArr[hashCode] != 0)
                {
                    hashCode = hash(m_array[i]->nodeKey, j, m_capacity);
                    ++j;
                }
                newArr[hashCode] = tmp;
                delete m_array[i];
            }
            delete [] m_array;
            m_array = newArr;
        }
    }

    /**
     * This function will return an iterator corresponding to the beginning of the map
     *
     * @return iterator corresponding to the beginning of the map
     */
    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::begin() noexcept
    {
        node * firstElem = NULL;
        int position = -1;
        if(m_array)
        {
            firstElem = m_array[0];
            int i = 0;
            position = 0;
            while((firstElem == NULL || firstElem->available) && i < m_capacity)
            {
              ++i;
              ++position;
              firstElem = m_array[i];
            }
        }
        return iterator(position,this, firstElem);
    }

    /**
     * This function will return an iterator that corresponds to the end of the map
     *
     * @return iterator corresponding to the end of the map
     */
    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::end() noexcept
    {
        iterator it(-1,this,NULL);
        it.setEnd(true);
        return it;
    }

    /**
     * This function is a helper function for the map in locating a key
     * and sets the variable position to that value. Used to set iterators internal
     * values to index of given key.
     */
    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::node* map<key,value,Hash>::insertFind(key k, int& position) const
    {
       //finds key does not care about availability
       node* val = NULL;
       for(int i = 0; i < m_capacity; ++i)
       {
           if(m_array[i] != NULL)
           {
                if(m_array[i]->nodeKey == k)
                {
                    val = m_array[i];
                    position = i;
                    break;
                }
           }
       }
       return val;
    }

    /* ITERATOR METHODS*/

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::iterator::iterator(const iterator &it)
        : m_position{it.m_position}, m_parent{it.m_parent},m_data{it.m_data},m_end{false} {}

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::iterator::iterator(int position, map* parent, node* data)
        : m_position{position}, m_parent{parent}, m_data{data},m_end{false}{}

    /**
     * This function overloads the preincrement operator for the iterator.
     * It moves the Iterator to a position that is "after" its current position in the map.
     * If the iterator arrives at one past the last element, this function will have no
     * effect
     */
    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator& map<key,value,Hash>::iterator::operator++()
    {
        /* starts at current spot in map then goes to non null node*/
        if(m_position != -1 ||m_end == true)
        {
            ++m_position, m_data = m_parent->m_array[m_position];
            if(m_position == m_parent->m_capacity ||(m_data != NULL && m_data->available)) m_data = NULL;
            while (m_position < m_parent->m_capacity && (m_data == NULL ||(m_data != NULL && m_data->available)))
            {
                ++m_position;
                if(m_position < m_parent->m_capacity)m_data = m_parent->m_array[m_position];
                else{m_data = NULL;}
                if(m_data != NULL && m_data->available) m_data = NULL;
            }
            //invalidate pointer if at end
            if(m_position >= m_parent->m_capacity || m_data == NULL|| m_data->available)
            {
                m_position = -1;
                m_data = NULL;
                m_end = true;
            }
        }
        return *this;
    }

    /**
     * This function overloads the post increment operator for the iterator.
     * It moves the Iterator to a position that is "after" its current position in the map.
     * If the iterator arrives at one past the last element, this function will have no
     * effect
     */
    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::iterator::operator++(int)
    {
        iterator cpy(*this);
        if(m_position != -1 ||m_end == true)
        {
            ++m_position, m_data = m_parent->m_array[m_position];
            if(m_position == m_parent->m_capacity ||(m_data != NULL && m_data->available)) m_data = NULL;
            while (m_position < m_parent->m_capacity && (m_data == NULL ||(m_data != NULL && m_data->available)))
            {
                ++m_position;
                if(m_position < m_parent->m_capacity)m_data = m_parent->m_array[m_position];
                else{m_data = NULL;}
                if(m_data != NULL && m_data->available) m_data = NULL;
            }
            //invalidate pointer if at end
            if(m_position >= m_parent->m_capacity || m_data == NULL|| m_data->available)
            {
                m_position = -1;
                m_data = NULL;
                m_end = true;
            }
        }
        return cpy;
    }

    /**
     * This function overloads the predecrement operator for the iterator.
     * It moves the Iterator to a position that is "before" it in the map.
     * If the iterator hits the beginning the post decrement is called, the
     * iterator is invalidated
     */
    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator& map<key,value,Hash>::iterator::operator--()
    {
        /* starts at current spot in map then goes to non null node*/

        if(m_position != -1)
        {
            --m_position, m_data = m_parent->m_array[m_position];
            if(m_position <= -1 ||(m_data != NULL && m_data->available)) m_data = NULL;
            while (m_position > -1 && (m_data == NULL ||(m_data != NULL && m_data->available)))
            {
                --m_position;
                if(m_position > -1)m_data = m_parent->m_array[m_position];
                else{m_data = NULL;}
                if(m_data != NULL && m_data->available) m_data = NULL;
            }
            //invalidate pointer if at end
            if(m_position <= -1 || m_data == NULL|| m_data->available){m_position = -1;m_data = NULL;}
        }
        else
        {
            if(m_end == true)
            {
                node * lastElem = NULL;
                int position = -1;
                if(m_parent->m_array)
                {

                  lastElem = m_parent->m_array[m_parent->m_capacity-1];
                  int i = m_parent->m_capacity-1;
                  position = m_parent->m_capacity-1;
                  while(lastElem != NULL && i >-1 && lastElem->available)
                  {
                      --i;
                      --position;
                      --lastElem;
                  }
                }
                if(position > -1)
                {
                    m_data = lastElem;
                    m_position = position;
                    m_end = false;
                }
                else
                {
                    m_data = NULL;
                }
            }
        }
        return *this;
    }

    /**
     * This function overloads the post decrement operator for the iterator.
     * It moves the Iterator to a position that is "before" it in the map.
     * If the iterator hits the beginning the post decrement is called, the
     * iterator is invalidated
     */
    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::iterator::operator--(int)
    {
        iterator cpy(*this);
        if(m_position != -1)
        {
            --m_position, m_data = m_parent->m_array[m_position];
            if(m_position <= -1 ||(m_data != NULL && m_data->available)) m_data = NULL;
            while (m_position > -1 && (m_data == NULL ||(m_data != NULL && m_data->available)))
            {
                --m_position;
                if(m_position > -1)m_data = m_parent->m_array[m_position];
                else{m_data = NULL;}
                if(m_data != NULL && m_data->available) m_data = NULL;
            }
            //invalidate pointer if at end
            if(m_position <= -1 || m_data == NULL|| m_data->available){m_position = -1;m_data = NULL;}
        }
        else
        {
            if(m_end == true)
            {
                node * lastElem = NULL;
                int position = -1;
                if(m_parent->m_array)
                {

                  lastElem = m_parent->m_array[m_parent->m_capacity-1];
                  position = m_parent->m_capacity-1;
                  for(int i = m_parent->m_capacity-1;lastElem != NULL && i >-1 && lastElem->available; --i)
                  {
                      --position;
                      --lastElem;
                  }
                 }
                if(position > -1)
                {
                    m_data = lastElem;
                    m_position = position;
                    m_end = false;
                }
                else
                {
                    m_data = NULL;
                }
            }
        }
        return cpy;
    }

    /**
     * This function overloads the dereference operator.
     * When called, it will return the value that the
     * iterator is indexing by reference.
     */
    template <typename key, typename value, typename Hash>
    value& map<key,value,Hash>::iterator::operator*()
    {
        return m_data->nodeValue;
    }

    /**
     * This function overloads the arrow operator.
     * When called, it will return a pointer to the value that the
     * iterator is indexing
     */
    template <typename key, typename value, typename Hash>
    value* map<key,value,Hash>::iterator::operator->()
    {
        return &(m_data->nodeValue);
    }

    /**
     * This function overloads the not equal operator.
     * It is used to compare iterators's positions in the map
     * to check if they are not at the same position
     */
    template <typename key, typename value, typename Hash>
    bool map<key,value,Hash>::iterator::operator!=(const iterator& it) const
    {
        if(m_position !=it.m_position){return true;}
        else if(m_data == NULL && it.m_data!=NULL){return true;}
        else if(m_data != NULL && it.m_data==NULL){return true;}
        else if(m_data == NULL && it.m_data==NULL){return false;}
        else if((m_data != NULL && it.m_data!=NULL) &&(m_data->nodeKey != it.m_data->nodeKey)){return true;}
        return false;
    }

    /**
     * This function overloads the equal comparison operator.
     * It is used to compare iterators's positions in the map
     * to check if they are at the same position
     */
    template <typename key, typename value, typename Hash>
    bool map<key,value,Hash>::iterator::operator==(const iterator& it) const
    {
        if(m_position == it.m_position){return true;}
        else if(m_data == it.m_data){return true;}
        return false;
    }

    /* NODE METHODS*/

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::node::node(key k, value v, bool avail, map* parent)
        : nodeKey{k},nodeValue{v},available{avail},parentMap{parent}{}


};// End nstd namespace
