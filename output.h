#ifndef _KEYDAEMON_OUTPUT_H
#define _KEYDAEMON_OUTPUT_H

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

#include "pipe.h"
#include "frame.h"

int start_output(Pipe<Frame *> &source);

#endif
