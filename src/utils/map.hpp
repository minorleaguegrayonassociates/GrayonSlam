#pragma once
#include <functional>
#include <iostream>
#include <iomanip>



namespace nstd
{

    /* FORWARD DECLARATIONS*/
    unsigned int* SieveOfEratosthenes(int n);

    template <typename key>
    class hash;

    template <typename key, typename value, typename Hash>
    class map;



     /* PRIME LOOKUP TABLE - QUICK ACCESS*/
    struct Primes
    {
        Primes():lookupTable{SieveOfEratosthenes((3000))}{}
        Primes(int n):lookupTable{SieveOfEratosthenes(n)}{}
        unsigned int *lookupTable;
        ~Primes(){delete lookupTable;}
    };

    static Primes TABLE_OF_PRIMES;


    template <class k, class v, class Hash>
    std::ostream& operator<<(std::ostream& out, const map<k, v, Hash>& d);

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
            iterator operator++(int);
            iterator& operator--();
            iterator operator--(int);
            iterator operator-(int);
            iterator operator+(int);
            value& operator*();
            value* operator->();
            bool operator!=(const iterator&) const;
            bool operator==(const iterator&) const;
            bool isEmpty(){return (m_data == NULL ||m_data->available);}
            node* getData(){return m_data;}
            map* getParent(){return m_parent;}
            void setEnd(bool isEnd){m_end= isEnd;}
        private:
            iterator();
            int m_position = 0;
            map* m_parent = nullptr;
            node* m_data = nullptr;
            bool m_end = false;
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
        iterator find(key);
        int size() const {return m_numOfElems;}
        bool isEmpty() const {return (m_numOfElems?false:true);}
        int cap() const {return m_capacity;}
        void reserve(unsigned int);
        friend std::ostream& operator<< <>(std::ostream&, const map<key,value,Hash>&);
        iterator begin() noexcept;
        iterator end() noexcept;
    private:
        struct node
        {
            key nodeKey = key();
            value nodeValue = value();
            bool available = false;
            map* parentMap = NULL;
            node(key, value, bool, map*);
        };
        int (*hash)(key k,int j,int capacity) = &(Hash::staticHashAlgo);
        node* m_insertFind(key, int&) const;
        node** m_map = nullptr;
        int m_primeNumIndex = 0;
        int m_numOfElems = 0;
        int m_capacity = 0;
    };

    /* MAP METHODS*/

    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::begin() noexcept
    {
        node * firstElem = NULL;
        int position = -1;
        if(m_map)
        {

            firstElem = m_map[0];
            int i = 0;
            position = 0;
            while(firstElem != NULL && firstElem->available && i < m_capacity)
            {
              ++i;
              ++position;
              ++firstElem;
            }
        }
        return iterator(position,this, firstElem);

    }

    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::end() noexcept
    {
        iterator it(-1,this,NULL);
        it.setEnd(true);
        return it;
    }

    template <typename key, typename value, typename Hash>
    std::pair<key,value> map<key,value,Hash>::remove(key k)
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


    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::find(key k)
    {
        int position = -1;
        node* val = NULL;
        for(int i = 0; i < m_capacity; ++i)
        {
            if(m_map[i])
            {
                unsigned int hashCode;
                int j;
                j = 1; //collision j
                hashCode = hash(k, 0, m_capacity);
                while(m_map[hashCode] != 0 && m_map[hashCode]->available != true && j<=m_capacity)
                {
                    if(m_map[hashCode]->nodeKey == k)break;
                    hashCode = hash(k, j, m_capacity);
                    ++j;
                }
                if(m_map[hashCode] != 0 && m_map[hashCode]->available != true)
                {
                    val = m_map[hashCode];
                    position = static_cast<int>(hashCode);
                }
            }
        }
        return iterator(position, this, val);
    }



    template <typename key, typename value, typename Hash>
    value& map<key,value,Hash>::operator[](const key& k)
    {
        iterator it = find(k);
        if(it.isEmpty())
        {
            it = insert(k,value());
        }
        return *it;
    }

    template <typename key, typename value, typename Hash>
    value& map<key,value,Hash>::operator[] (key&& k)
    {
        iterator it = find(k);
        if(it.isEmpty())
        {
            it = insert(k,value());
        }
        return *it;
    }

    template <typename key, typename value, typename Hash>
    void map<key,value,Hash>::reserve(unsigned int newInternalSize)
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
            if(m_map[i] == 0 || m_map[i]->available) continue;
            tmp = new node(m_map[i]->nodeKey, m_map[i]->nodeValue,false, this);
            j = 1;
            hashCode = hash(m_map[i]->nodeKey,0, m_capacity);
            while(newArr[hashCode] != 0)
            {
                hashCode = hash(m_map[i]->nodeKey, j, m_capacity);
                ++j;
            }
            newArr[hashCode] = tmp;
            delete m_map[i];
         }
         delete [] m_map;
         m_map = newArr;
    }

    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::insert(key k, value v)
    {
        ++m_numOfElems;
        if(m_numOfElems == m_capacity) reserve(TABLE_OF_PRIMES.lookupTable[m_primeNumIndex+1]);
        int findPosition = -1;
        node* found = m_insertFind(k, findPosition);
        if(found) found->available = false;
        node* tmp;
        unsigned int hashCode = 0;
        if(!found)
        {
            unsigned int j;
            tmp = new node(k, v,false, this);
            j = 1;
            hashCode = hash(k,0,m_capacity);
            while(m_map[hashCode] != 0 && m_map[hashCode]->available != true)
            {
                hashCode = hash(k, j, m_capacity);
                ++j;
            }
            if(m_map[hashCode] != 0)if(m_map[hashCode]->available == true) delete m_map[hashCode];
            m_map[hashCode] = tmp;
            findPosition = static_cast<int>(hashCode);
        }
        else
        {found->nodeKey = k; found->nodeValue = v; found->available = false; tmp = found; }
        return iterator(findPosition,this,tmp);
    }

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::map(key keys[], value values[], const int ARR_SIZE)
    {
        m_primeNumIndex = 0;
        while(TABLE_OF_PRIMES.lookupTable[m_primeNumIndex] <= ARR_SIZE) ++m_primeNumIndex;
        m_numOfElems = ARR_SIZE;
        m_capacity = TABLE_OF_PRIMES.lookupTable[m_primeNumIndex];
        m_map = new node*[TABLE_OF_PRIMES.lookupTable[m_primeNumIndex]];
        for(int i = 0; i < m_capacity; ++i) m_map[i] = 0;
        node* tmp;
        unsigned int hashCode;
        unsigned int j;
        for(int i = 0; i < ARR_SIZE; ++i)
        {
            tmp = new node(keys[i], values[i],false, this);
            j = 1;
            hashCode = hash(keys[i],0);
            while(m_map[hashCode] != 0 && j < m_capacity)
            {
                hashCode = hash(keys[i],j);
                ++j;
            }
            if(m_map[hashCode]) delete m_map[hashCode];
            m_map[hashCode] = tmp;
        }
    }

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::map(const map& otherMap)
        : m_primeNumIndex{otherMap.m_primeNumIndex},m_numOfElems{otherMap.m_numOfElems},m_capacity{otherMap.m_capacity}
    {
        m_map = new node*[otherMap.m_capacity];
        for(int i = 0; i < otherMap.m_capacity; ++i)
        {
            m_map[i] = new node(otherMap.m_map[i]->nodeKey,otherMap.m_map[i]->nodeValue,false, this);
        }
    }

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::map(map&& otherMap)
        : m_primeNumIndex{otherMap.m_primeNumIndex}, m_numOfElems{otherMap.m_numOfElems},m_capacity{otherMap.m_capacity}
    {
        m_map = otherMap.m_map;
        otherMap.m_map = NULL;
    }

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>& map<key,value,Hash>::operator=(const map& otherMap)
    {
        if(&otherMap != this)
        {
            if(m_numOfElems != 0)
            {
                for(int i = 0; i < m_capacity; ++i)
                {
                    if(m_map[i]) delete m_map[i];
                }
                delete [] m_map;
            }
            m_primeNumIndex = otherMap.m_primeNumIndex;
            m_numOfElems = otherMap.m_numOfElems;
            m_capacity = otherMap.m_capacity;
            m_map = new node*[otherMap.m_capacity];
            for(int i = 0; i < otherMap.m_capacity; ++i)
            {
                m_map[i] = new node(otherMap.m_map[i]->nodeKey,otherMap.m_map[i]->nodeValue,false, this);
            }
        }
        return *this;
    }

    template <typename key, typename value, typename Hash>
    map<key,value,Hash>::~map()
    {
        for(int i = 0; i < m_capacity; ++i)
        {
            if(m_map[i]) delete m_map[i];
        }
        delete [] m_map;
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


    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::node*  map<key,value,Hash>::m_insertFind(key k, int& position) const
    {
       node* val = NULL;
       for(int i = 0; i < m_capacity; ++i)
       {
           if(m_map[i])
           {
                if(m_map[i]->nodeKey == k)
                {
                    val = m_map[i];
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

    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::iterator::operator--(int)
    {
        iterator cpy(*this);
        if(m_position != -1)
        {
            --m_position, m_data = m_parent->m_map[m_position];
            if(m_position <= -1 ||(m_data != NULL && m_data->available)) m_data = NULL;
            while (m_position > -1 && (m_data == NULL ||(m_data != NULL && m_data->available)))
            {
                --m_position; if(m_data != NULL)m_data = m_parent->m_map[m_position];
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
                if(m_parent->m_map)
                {

                  lastElem = m_parent->m_map[m_parent->m_capacity-1];
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
            }
        }
        return cpy;
    }

    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator& map<key,value,Hash>::iterator::operator--()
    {
        /* starts at current spot in map then goes to non null node*/

        if(m_position != -1)
        {
            --m_position, m_data = m_parent->m_map[m_position];
            if(m_position <= -1 ||(m_data != NULL && m_data->available)) m_data = NULL;
            while (m_position > -1 && (m_data == NULL ||(m_data != NULL && m_data->available)))
            {
                --m_position; if(m_data != NULL)m_data = m_parent->m_map[m_position];
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
                if(m_parent->m_map)
                {

                  lastElem = m_parent->m_map[m_parent->m_capacity-1];
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
            }
        }
        return *this;
    }

    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::iterator::operator++(int)
    {
        iterator cpy(*this);
        if(m_position != -1)
        {
            ++m_position, m_data = m_parent->m_map[m_position];
            if(m_position == m_parent->m_capacity ||(m_data != NULL && m_data->available)) m_data = NULL;
            while (m_position < m_parent->m_capacity && (m_data == NULL ||(m_data != NULL && m_data->available)))
            {
                ++m_position; if(m_data != NULL) m_data = m_parent->m_map[m_position];
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

    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator& map<key,value,Hash>::iterator::operator++()
    {
        /* starts at current spot in map then goes to non null node*/
        if(m_position != -1)
        {
            ++m_position, m_data = m_parent->m_map[m_position];
            if(m_position == m_parent->m_capacity ||(m_data != NULL && m_data->available)) m_data = NULL;
            while (m_position < m_parent->m_capacity && (m_data == NULL ||(m_data != NULL && m_data->available)))
            {
                ++m_position; if(m_data!= NULL) m_data = m_parent->m_map[m_position];
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


    template <typename key, typename value, typename Hash>
    typename map<key,value,Hash>::iterator map<key,value,Hash>::iterator::operator-(int numOfSpacesMoved)
    {
        /* starts at current spot in map then goes to non null node*/
        iterator cpy(*this);
        for(int movement = 0; movement < numOfSpacesMoved; ++movement)
        {

            for (;cpy.m_position >-1 &&cpy.m_data != nullptr && cpy.m_data->available != true; --cpy.m_position, --cpy.m_data) {}
        }
        //invalidate pointer if at end
        if(cpy.m_position == -1 || cpy.m_data->available == true){cpy.m_data = nullptr;}
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
    map<key,value,Hash>::node::node(key k, value v, bool avail, map* parent)
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
    public:
        int operator()(key k, int j, int capacity)
        {
            return hashAlgo(k,j,capacity);
        }

        int hashAlgo(key k,int j, int capacity)const {return((static_cast<int>(k))+j*j)%capacity;}
        static int staticHashAlgo(key k,int j, int capacity)
        {
            int hash = ((static_cast<int>(k))+j*j)%capacity;
            return hash;
        }

    };




    template <>
    class hash<std::string>
    {
    public:
        int operator()(std::string k, int j, int capacity)
        {
            return hashAlgo(k,j,capacity);
        }


        int hashAlgo(std::string k, int j,int capacity)const{return (static_cast<int>(std::hash<std::string>{}(k))+j*j)%capacity;}
        static int staticHashAlgo(std::string k,int j, int capacity) {return (static_cast<int>(std::hash<std::string>{}(k))+j*j)%capacity;}
    };

    template <class k, class v, class Hash>
    std::ostream& operator<<(std::ostream& out, const map<k, v, Hash>& d)
    {
        out << "The key value combos inside double hash map are: \n";
        for(int i = 0; i < d.m_capacity; ++i)
        {
            if(d.m_map[i]&& d.m_map[i]->available != true)
            out << "Hash: "<<std::setw(2)<<std::right<< i <<" Key: " <<std::setw(3)<< d.m_map[i]->nodeKey << " Value: " << d.m_map[i]->nodeValue << "\n";
        }
        return out;
    }

};
