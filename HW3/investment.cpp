//
//  main.cpp
//  HW3
//
//  Created by August Greer on 2/8/18.
//  Copyright © 2018 CS32. All rights reserved.
//



//////////////////////////////////
//       Investment Class       //
//////////////////////////////////

class Investment{
public:
    Investment(string name, int price)
    :m_name(name), m_price(price)
    {}
    virtual ~Investment(){}
    string name() const{
        return m_name;
    }
    int purchasePrice() const{
        return m_price;
    }
    virtual bool fungible() const{
        return false;
    }
    virtual string description() const = 0;
private:
    string m_name;
    int m_price;
};

//////////////////////////////////
//        Painting Class        //
//////////////////////////////////

class Painting: public Investment
{
public:
    Painting(string name, int price)
    : Investment(name, price)
    {}
    ~Painting(){
        cout << "Destroying " << name() << ", a painting" << endl;
    }
    virtual string description() const{
        return "painting";
    }
};

//////////////////////////////////
//          Stock Class         //
//////////////////////////////////

class Stock: public Investment
{
public:
    Stock(string name, int price, string tradingName)
    : Investment(name, price), m_tradingName(tradingName)
    {}
    ~Stock(){
        cout << "Destroying " << name() << ", a stock holding" << endl;
    }
    virtual bool fungible() const{
        return true;
    }
    virtual string description() const{
        string output = "stock trading as " + m_tradingName;
        return output;
    }
private:
    string m_tradingName;
};

//////////////////////////////////
//          House Class         //
//////////////////////////////////

class House: public Investment
{
public:
    House(string address, int price)
    :Investment(address, price)
    {}
    ~House(){
        cout << "Destroying the house " << name() << endl;
    }
    virtual string description() const{
        return "house";
    }
};
