#ifndef _EXAMPLE_POINT_H
#define _EXAMPLE_POINT_H

#include <vector>
#include <iostream>

/**
 * A simple point class containing a vector of doubles and a single char name.
 */
class example_point
{
private:
    std::vector<double> _vec;
    char _name;

public:

    example_point(const std::vector<double>& v, char name) : _vec(v), _name(name) {}

    double distance(const example_point& p) const {

        const std::vector<double>& vec=p.getVec();
        double dist=0;
        size_t lim = vec.size();
        for(size_t i=0; i<lim;i++) {
            double d = vec[i]-_vec[i];
            dist+=d*d;
        }
        dist=sqrt(dist);
        return dist;

    }

    const std::vector<double>& getVec() const {
        return _vec;
    }

    const char& getChar() const{
        return _name;
    };

    void print() const
        {

            std::cout << "point " << _name << ": ";
            for(const auto& it : _vec) {
                std::cout << it << " ";
            }
            std::cout << "\n";
    };

    bool operator==(const example_point& p) const{
        //TODO: equality for floating point numbers is a tricky thing
        bool value = _name==p.getChar();
        value = value && _vec==p.getVec();

        return (value);
    };
};

#endif // _EXAMPLE_POINT_H
