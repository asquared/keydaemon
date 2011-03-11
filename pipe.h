#ifndef _PIPE_H
#define _PIPE_H

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

#include <unistd.h>
#include <stdio.h>
#include <stdexcept>

/*
 * A channel for communicating objects between threads.
 * Based on a Unix pipe.
 * 
 * Methods:
 *
 * int get(T& obj): retrieve an object from the pipe.
 *  This blocks until an object is available.
 *  Returns 1 if an object was received, zero if the pipe has been closed.
 *
 * int put(T& obj): put object onto the pipe.
 *  This may also block until a thread tries to get( ).
 *  Returns 1 when the object is put. Zero if the pipe has been closed.
 *
 * void close_read(void):
 *  Close reader end of the pipe.
 *
 * void close_write(void):
 *  Close writer end of the pipe.
 */
template <class T>
class Pipe {
    public:
        Pipe( ) { 
            int pfds[2];

            if (pipe(pfds) != 0) {
                perror("pipe");
                throw std::runtime_error("pipe failed");
            }

            read_fd = pfds[0];
            write_fd = pfds[1];
        }

        int get(T& obj) {
            ssize_t ret;
            uint8_t *byte_ptr = (uint8_t *) &obj;
            size_t ndone = 0;

            while (ndone < sizeof(obj)) {
                /* read as much as possible from pipe */
                ret = read(read_fd, (void *) (byte_ptr + ndone), 
                        sizeof(obj) - ndone);

                if (ret < 0) {
                    /* error */
                    if (errno == EAGAIN || errno == EINTR) {
                        continue;
                    } else {
                        perror("pipe read");
                        throw std::runtime_error("pipe read failed");
                    }
                } else if (ret == 0) {
                    return 0; /* end of pipe */
                } else {
                    ndone += ret;
                }
            }

            return 1;
        }

        int put(const T& obj) {
            ssize_t ret;
            uint8_t *byte_ptr = (uint8_t *) &obj;
            ssize_t ndone = 0;

            while (ndone < sizeof(obj)) {
                ret = write(write_fd, (void *) (byte_ptr + ndone),
                        sizeof(obj) - ndone);

                if (ret < 0) {
                    if (errno == EAGAIN || errno == EINTR) {
                        continue;
                    } else if (errno == EPIPE) {
                        return 0;
                    } else {
                        perror("pipe write");
                        throw std::runtime_error("pipe write failed");
                    }
                } else if (ret == 0) {
                    /* this should really never happen */
                    throw std::runtime_error(
                        "Huh? write call wrote absolutely nothing"
                    );
                } else {
                    ndone += ret;
                }

                return 1;
            }
        }

        ~Pipe( ) { 
        
        }

    protected:
        int write_fd, read_fd;
};

#endif
