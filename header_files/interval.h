#ifndef INTERVAL_H
#define INTERVAL_H

#include "utility.h"

// Class to represent an interval
class interval {
    public:
        double min, max;

        interval() : min(+infinity), max(-infinity) {} 
        interval(double min, double max) : min(min), max(max) {} 

        double size() const { return max - min; }  // Return the size of the interval

        bool contains(double x) const { return (x >= min && x <= max); } //  Check if the interval contains a point

        bool surrounds(double x) const { return (x > min && x < max); } // Check if the interval surrounds a point

        static const interval empty; // Empty interval
        static const interval infinite; // Infinite interval
};


const interval interval::empty = interval(+infinity, -infinity); // Empty interval
const interval interval::infinite = interval(-infinity, +infinity); // Infinite interval

#endif