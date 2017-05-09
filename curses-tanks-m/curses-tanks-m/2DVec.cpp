//
//  2DVec.cpp
//  curses-tanks-m
//
//  Created by Kevin Mahoney on 5/8/17.
//  Copyright © 2017 Carthage College. All rights reserved.
//

#include "2DVec.hpp"


Vec2D::Vec2D()
{
    
    double x;
    double y;
    
    

    
    
}


Vec2D Vec2D :: operator+(const Vec2D & other,)
{
    
    x += other.x;
    y += other.y;
    
    return Vec2D (*this);
 
}
Vec2D Vec2D :: operator * (const double d)
{
    
    x = x * d;
    y = y * d;
   
    return Vec2D (*this);
    
}
Vec2D Vec2D :: operator * (const int d)
{
    
    x = x * d;
    y = y * d;
    
    return Vec2D (*this);
    
}



