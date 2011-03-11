#ifndef _KEYDAEMON_KEY_H
#define _KEYDAEMON_KEY_H

/*
 * Copyright 2011 Andrew H. Armenia.
 * 
 * This file is part of Keydaemon.
 * 
 * Keydaemon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Keydaemon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Keydaemon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "types.h"

/* 
 * A drawable key of some sort.
 */
class Keyer {
    public:
        /* constructors here... */
    
        /* set key parameters atomically */
        virtual void set(coord_t x, coord_t y, alpha_t galpha);
        
        /* get key parameters atomically */
        virtual void get(coord_t &x, coord_t &y, alpha_t &galpha);
        
        /* 
         * called after a frame of the key is rendered. 
         * Animations, auto-transitions, etc can be implemented here.
         */
        virtual void animate(void);
        
        /* called to render the current frame of the key */
        virtual Frame *image_data(Frame::PixelFormat preferred_format);

};

#endif
