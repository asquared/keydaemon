#include "pipe.h"
#include "input.h"
#include "output.h"
#include "key.h"

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

Keyer **keyers;
int nkeyers;

Pipe<Frame *> input_pipe, output_pipe;

void keyer_thread(void) {
    Frame *background;
    Frame *current_key;
    int i;

    coord_t x, y;
    alpha_t alpha;

    while (input_pipe.get(background) != 0) {
        loaded_keys[i]->get(x, y, alpha);

        if (alpha > 0) {
            /* render key */
            current_key = keyers[i]->image_data(
                background->preferred_key_pixel_format( )
            );

            /* draw key */
            background->draw(current_key, x, y, alpha);
        }

        keyers[i]->animate( );

        output_pipe.put(f);
    }
}

int main(int argc, char **argv) {
    /* initialize the various keyers */
        /* load some configuration, parse command line args or something */

    /* start input thread */
    start_input(input_pipe);

    /* start output thread */
    start_output(output_pipe);

    /* start the main keying thread */
    /* FIXME pthread stuff goes here */

    for (;;) {
        /* wait for requests to come in over the network */

        /* dispatch request to the appropriate keyer object (PNG image, scoreboard, ...) */
        keyers[/* FIXME something from the packet */].dispatch_request(
            /* rest of data from packet */
        );
    }
}


