#ifndef INTERVAL_H
#define INTERVAL_H

class interval{
public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {}
    //default constructor

    interval(double min, double max) : min(min), max(max) {}
    //parameterized
    
    double size() const{
	return max - min;
    }

    bool contains(double x) const{
	return min <= x && x <= max;
    }//if x is in bounds of interval 

    bool surrounds(double x) const{
	return min < x && x < max;
    }//if x is not in bounds of interval

    static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);

const interval interval::universe = interval(+infinity, -infinity)
