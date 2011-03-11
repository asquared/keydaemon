#ifndef _KEYDAEMON_FRAME_H
#define _KEYDAEMON_FRAME_H

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
 * An abstract representation of a video frame.
 */

class Frame {
    public:
        enum PixelFormat { RGBA8, UYVY8, YUVA8 };

        Frame(coord_t w, coord_t h, PixelFormat pf, coord_t pitch = 0);
        PixelFormat pixel_format( );
        PixelFormat preferred_key_pixel_format( );
        void draw(Frame *overlay, coord_t x, coord_t y, alpha_t alpha); 
        virtual ~Frame( );
        Frame *convert(PixelFormat new_pf);
};

#endif
