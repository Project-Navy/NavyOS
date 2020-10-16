/*
 * Copyright (C) 2020  Jordan DALCQ & contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Navy/range.h>

#include <stdbool.h>
#include <stddef.h>

#include "arch/arch.h"
#include "kernel/log.h"

size_t
get_range_size(Range range)
{
    return range.end - range.begin;
}

bool
is_range_page_aligned(Range range)
{
    return (range.begin % PAGE_SIZE == 0) && (get_range_size(range) % PAGE_SIZE == 0);
}

void
align_range(Range *range)
{
    size_t align = PAGE_SIZE - range->begin % PAGE_SIZE;

    if (range->begin % PAGE_SIZE == 0)
    {
        align = 0;
    }

    range->begin += align;
    range->end -= align;

    range->end -= range->end % PAGE_SIZE;
}
