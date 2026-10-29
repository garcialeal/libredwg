/*****************************************************************************/
/*  LibreDWG - free implementation of the DWG file format                    */
/*                                                                           */
/*  Copyright (C) 2019 Free Software Foundation, Inc.                        */
/*                                                                           */
/*  This library is free software, licensed under the terms of the GNU       */
/*  General Public License as published by the Free Software Foundation,     */
/*  either version 3 of the License, or (at your option) any later version.  */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program.  If not, see <[gnu.org](http://www.gnu.org/licenses/)>.    */
/*****************************************************************************/

/*
 * geom.h: geometric projections from OCS
 * written by Reini Urban
 */

#ifndef _GEOM_H_
#define _GEOM_H_

#include "config.h"
#include <dwg.h>

#ifndef M_PI
#  define M_PI 3.14159265358979323846264338327950288
#endif

// void normalize (BITCODE_3DPOINT *out, BITCODE_3DPOINT pt);
// void cross (BITCODE_3DPOINT *out, BITCODE_3DPOINT pt1, BITCODE_3DPOINT pt2);
//  transform a 2D point via its OCS (extrusion) to 2D
EXPORT void transform_OCS_2d (BITCODE_2DPOINT *out, BITCODE_2DPOINT pt,
                              BITCODE_BE ext) __nonnull ((1));
// transform a 3D point via its OCS (extrusion) to 2D
EXPORT void transform_OCS (BITCODE_3DPOINT *out, BITCODE_3DPOINT pt,
                           BITCODE_BE ext) __nonnull ((1));

// TODO: bulge -> arc for svg and ps
void angle_vector_2d (BITCODE_2DPOINT *out, BITCODE_2DPOINT ctr,
                      BITCODE_BD angle, BITCODE_BD len) __nonnull ((1));
EXPORT void arc_split (BITCODE_2BD *pts, const int num_pts,
                       const BITCODE_2BD center_2d, BITCODE_BD start_angle,
                       BITCODE_BD end_angle, const BITCODE_BD radius)
    __nonnull ((1));

// Normalize an angle to [0, 2*PI).  Handles inf, nan and denormals.
double angle_normalize (double angle);

/* Fast V4 Spatial Geometry Transformations (Klein Four-Group V4)
 *
 * NOTE: "V4" here is the Klein 4-group integer map over the S12 lattice,
 * not DWG version 4 and not a 4D vector.
 *
 * MATHEMATICAL NOTICE
 * The V4 map is invertible but NOT conformal. Its linear part P has
 * det(P) = 4 and singular values 2, 2, 1. Consequences:
 *   - a right angle becomes 70.53 degrees,
 *   - a circle becomes an ellipse (factors 2.00 and 1.41 in its plane),
 *   - arc sweep angles and text rotation are not preserved.
 * P is NOT an involution (P*P = [[3,1,1],[1,3,-1],[1,-1,3]]), so its
 * inverse is NOT P/4. The "H*H = 4I" relation belongs to the 4-point
 * Hadamard butterfly network, not to this spatial map.
 *
 * Entities inside block definitions are left alone; only the INSERT that
 * references them is transformed.
 */
EXPORT uint32_t dwg_transform_v4 (Dwg_Data *dwg);
EXPORT void dwg_geom_v4_transform_2d (double *x, double *y);

#endif /* _GEOM_H_ */
