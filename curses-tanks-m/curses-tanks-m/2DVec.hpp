//
//  2DVec.hpp
//  curses-tanks-m
//
//  Created by Kevin Mahoney on 5/8/17.
//  Copyright © 2017 Carthage College. All rights reserved.
//
#pragma once
#ifndef _DVec_hpp
#define _DVec_hpp


#include <stdio.h>

class Vec2D
{
    public:
    Vec2D operator + (const Vec2D & v);
    Vec2D operator * (double d);
    void operator = (const Vec2D & v);
};







#endif /* _DVec_hpp */
