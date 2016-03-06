/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2016 Arb authors

******************************************************************************/

#include "bool_mat.h"

void
bool_mat_transpose(bool_mat_t B, const bool_mat_t A)
{
    slong i, j;

    if (bool_mat_nrows(B) != bool_mat_ncols(A) ||
        bool_mat_ncols(B) != bool_mat_nrows(A))
    {
        flint_printf("bool_mat_transpose: Incompatible dimensions.\n");
        abort();
    }

    if (bool_mat_is_empty(A))
        return;

    if (A == B)  /* In-place, guaranteed to be square */
    {
        int tmp;
        for (i = 0; i < bool_mat_nrows(B) - 1; i++)
        {
            for (j = i + 1; j < bool_mat_ncols(B); j++)
            {
                tmp = bool_mat_get_entry(B, i, j);
                bool_mat_set_entry(B, i, j, bool_mat_get_entry(B, j, i));
                bool_mat_set_entry(B, j, i, tmp);
            }
        }
    }
    else  /* Not aliased; general case */
    {
        for (i = 0; i < bool_mat_nrows(B); i++)
            for (j = 0; j < bool_mat_ncols(B); j++)
                bool_mat_set_entry(B, i, j, bool_mat_get_entry(A, j, i));
    }
}