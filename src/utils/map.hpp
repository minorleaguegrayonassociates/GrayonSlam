#pragma once
#include <functional>




namespace nstd
{
    unsigned int* SieveOfEratosthenes(int n);

     /* PRIME LOOKUP TABLE - QUICK ACCESS*/
    struct Primes
    {
        Primes():lookupTable{SieveOfEratosthenes((3000))}{}
        Primes(int n):lookupTable{SieveOfEratosthenes(n)}{}
        unsigned int *lookupTable;
        ~Primes(){delete lookupTable;}
    };

    static Primes TABLE_OF_PRIMES;

    template <typename key>
    class hash;

    template <typename key, typename value, typename Hash = hash<key>>
    class map
    {
    private:
        struct node;
    public:
        class iterator
        {
        public:
            iterator(const iterator &);
            iterator(int,map*,node*);
            iterator& operator++();
            iterator& operator++(int);
            iterator& operator--();
            iterator& operator--(int);
            iterator operator-(int);
            iterator operator+(int);
            value& operator*();
            value* operator->();
            bool operator!=(const iterator&) const;
            bool operator==(const iterator&) const;
        private:
            iterator();
            int m_position = 0;
            map* m_parent = nullptr;
            node* m_data = nullptr;
        };

        map();
        map(key[],value[],const int);
        map(const map&);
        map(map&&);
        map& operator=(const map&);
        ~map();
        /**
         * Creates an exception with a exception message.
         *
         * @param msg Exception message
         */
        value& operator[] (const key&);
        value& operator[] (key&&);
        iterator insert(key, value);
        std::pair<key,value> remove(key);
        std::pair<key,value> remove(value);
        iterator find(key) const;
        iterator find(value) const;
        int size() const {return m_numOfElems;}
        bool isEmpty() const {return (m_numOfElems?false:true);}
        int cap() const {return m_capacity;}
        void reserve(int);
        iterator begin() noexcept;
        iterator end() noexcept;
    private:
        struct node
        {
            key nodeKey;
            value nodeValue;
            bool available;
            node** parentMap;
            node(key, value, bool, node**);
        };
        int (*hash)(key k,int j,int capacity) = Hash();
        node* m_insertFind(key) const;
        node** m_map = nullptr;
        int m_primeNumIndex = 0;
        int m_numOfElems = 0;
        int m_capacity = 0;
    };

    /* MAP METHODS*/

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::map(key[],value[],const int)
    {

    }

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::map(const map&)
    {

    }

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::map(map&&)
    {

    }

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>& map<key,value,Hash>::operator=(const map&)
    {

    }

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::~map()
    {

    }

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::map()
        : m_map{new node*[31]}, m_primeNumIndex{10},m_numOfElems{0},m_capacity{31}
    {
        for(int i = 0; i< m_capacity;++i)
        {
            m_map[i]=nullptr;
        }
    }

    /* ITERATOR METHODS*/

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::iterator::iterator(const iterator &it)
        : m_position{it.m_position}, m_parent{it.m_parent},m_data{it.m_data} {}

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::iterator::iterator(int position, map* parent, node* data)
        : m_position{position}, m_parent{parent}, m_data{data}{}

    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator& map<key,value,Hash>::iterator::operator--(int)
    {
        iterator cpy(*this);
        int i;
        for (i = m_position;i >-1 && m_data != nullptr; --i, --m_data) {}
        m_position = i;
        //invalidate pointer if before beginning
        if(i == -1){m_data = nullptr;}
        return cpy;
    }

    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator& map<key,value,Hash>::iterator::operator--()
    {
        /* starts at current spot in map then goes to non null node*/
        int i;
        for (i = m_position;i >-1 && m_data != nullptr; --i, --m_data) {}
        m_position = i;
        //invalidate pointer if before beginning
        if(i == -1){m_data = nullptr;}
        return *this;
    }

    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator& map<key,value,Hash>::iterator::operator++(int)
    {
        iterator cpy(*this);
        for (;m_position < m_parent->m_capacity && m_data != nullptr; ++m_position, ++m_data) {}
        //invalidate pointer if at end
        if(m_position == m_parent->m_capacity){m_data = nullptr;}
        return cpy;
    }

    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator& map<key,value,Hash>::iterator::operator++()
    {
        /* starts at current spot in map then goes to non null node*/
        for (;m_position < m_parent->m_capacity && m_data != nullptr; ++m_position, ++m_data) {}
        //invalidate pointer if at end
        if(m_position == m_parent->m_capacity){m_data = nullptr;}
        return *this;
    }

    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::iterator::operator+(int numOfSpacesMoved)
    {
        /* starts at current spot in map then goes to non null node*/
        iterator cpy(*this);
        for(int movement = 0; movement < numOfSpacesMoved; ++movement)
        {
            for (;cpy.m_position < cpy.m_parent->m_capacity && cpy.m_data != nullptr; ++cpy.m_position, ++cpy.m_data) {}
        }
        //invalidate pointer if at end
        if(m_position == m_parent->m_capacity){m_data = nullptr;}
        return cpy;
    }

    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::iterator::operator-(int numOfSpacesMoved)
    {
        /* starts at current spot in map then goes to non null node*/
        iterator cpy(*this);
        for(int movement = 0; movement < numOfSpacesMoved; ++movement)
        {

            for (;cpy.m_position >-1 &&cpy.m_data != nullptr; --cpy.m_position, --cpy.m_data) {}
        }
        //invalidate pointer if at end
        if(cpy.m_position == -1){cpy.m_data = nullptr;}
        return cpy;
    }

    template <typename key, typename value, typename Hash>
    value& map<key,value,Hash>::iterator::operator*()
    {
        return m_data->nodeValue;
    }

    template <typename key, typename value, typename Hash>
    value* map<key,value,Hash>::iterator::operator->()
    {
        return &(m_data->nodeValue);
    }

    template <typename key, typename value, typename Hash>
    bool map<key,value,Hash>::iterator::operator!=(const iterator& it) const
    {
        if(m_position !=it.m_position){return true;}
        else if(m_data != it.m_data){return true;}
        return false;
    }

    template <typename key, typename value, typename Hash>
    bool map<key,value,Hash>::iterator::operator==(const iterator& it) const
    {
        if(m_position == it.m_position){return true;}
        else if(m_data == it.m_data){return true;}
        return false;
    }


    /* NODE METHODS*/

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::node::node(key k, value v, bool avail, node** parent)
        : nodeKey{k},nodeValue{v},available{avail},parentMap{parent}{}


    /* PRIME LOOKUP TABLE - QUICK ACCESS*/


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


    template <typename key>
    class hash
    {
        int operator()(key k, int j, int capacity)
        {
            return hashAlgo(k,j,capacity);
        }

        int hashAlgo(std::string k, int j,int capacity)const{return (static_cast<int>(std::hash<std::string>{}(k))+j*j)%capacity;}
        int hashAlgo(key k,int j, int capacity)const {return((static_cast<int>(k))+j*j)%capacity;}

    };

};
