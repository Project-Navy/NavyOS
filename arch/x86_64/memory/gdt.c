/*
 * Copyright (C) 2020 Jordan DALCQ & contributors
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

#include "arch/x86_64/memory/gdt.h"
#include "arch/arch.h"

#include <string.h>

struct gdtentry gdtentry[GDT_SIZE];
struct gdtdesc gdtdesc;

void
init_gdt_desc(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags,
              struct gdtentry *desc)
{
    desc->base0_15 = (base & 0xffff);
    desc->limit0_15 = (limit & 0xffff);
    desc->base24_31 = (base & 0xff000000) >> 24;
    desc->limit16_19 = (limit & 0xf0000) >> 16;
    desc->base16_23 = (base & 0xff0000) >> 16;

    desc->flags = (flags & 0xf);
    desc->access = access;
}

void
init_gdt(void)
{
    gdtdesc.size = sizeof(struct gdtentry) * GDT_SIZE;
    gdtdesc.offset = (uintptr_t) & gdtentry[0];

    init_gdt_desc(0, 0, 0, 0, &gdtentry[0]);    /* NULL Segment */
    init_gdt_desc(0, 0, PRESENT | SYSTEM | EXECUTABLE | READ_WRITE, PAGE_GR | BITS64, &gdtentry[1]);    /* Code 
                                                                                                         * segment 
                                                                                                         */
    init_gdt_desc(0, 0, PRESENT | SYSTEM | READ_WRITE, PAGE_GR | BITS64, &gdtentry[2]); /* Data 
                                                                                         * segment 
                                                                                         */
    init_gdt_desc(0, 0, PRESENT | SYSTEM | USER_PRIV | EXECUTABLE | READ_WRITE, PAGE_GR | BITS64, &gdtentry[3]);    /* User 
                                                                                                                     * Code 
                                                                                                                     * Segment 
                                                                                                                     */
    init_gdt_desc(0, 0, PRESENT | SYSTEM | USER_PRIV | READ_WRITE, PAGE_GR | BITS64, &gdtentry[4]); /* User 
                                                                                                     * Data 
                                                                                                     * Segment 
                                                                                                     */


    /*
     * gdt_flush((uint32_t) & gdtdesc); 
     */
}
