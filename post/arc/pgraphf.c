
/************************************************************************\ 
 *									*
 * xgraphf.c - HCBS simulation routines for FORTRAN under X11		*
 *									*
 * Copyright (c) 1992-1994 by Georg Umgiesser				*
 *									*
 * Permission to use, copy, modify, and distribute this software	*
 * and its documentation for any purpose and without fee is hereby	*
 * granted, provided that the above copyright notice appear in all	*
 * copies and that both that copyright notice and this permission	*
 * notice appear in supporting documentation.				*
 *									*
 * This file is provided AS IS with no warranties of any kind.		*
 * The author shall have no liability with respect to the		*
 * infringement of copyrights, trade secrets or any patents by		*
 * this file or any part thereof.  In no event will the author		*
 * be liable for any lost revenue or profits or other special,		*
 * indirect and consequential damages.					*
 *									*
 * Comments and additions should be sent to the author:			*
 *									*
 *			Georg Umgiesser					*
 *			ISDGM/CNR					*
 *			S. Polo 1364					*
 *			30125 Venezia					*
 *			Italy						*
 *									*
 *			Tel.   : ++39-41-5216875			*
 *			Fax    : ++39-41-2602340			*
 *			E-Mail : georg@lagoon.isdgm.ve.cnr.it		*
 *									*
 * Revision History:							*
 * 21-Mar-94: include xgraph.h						*
 * 11-Feb-94: copyright notice added to all files			*
 * ..-...-92: routines written from scratch				*
 *									*
\************************************************************************/


/* 
 *	contents :
 *
 *	qopen()			opens window
 *	qclose()		closes window
 *	qstart()		opens a new plot (clears screen)
 *	qend()			closes a plot (flushes the buffer)
 *
 *	qnewp(ic)		changes color (ic=[1,16], 1=black, 16=white)
 *	qgray(c)		sets shade of gray (c=[0,1], 0=black, 1=white)
 *
 *	qline(x1,y1,x2,y2)	draws line from (1) to (2)
 *	qplot(x,y)		draws line from actual position to (x,y)
 *	qmove(x,y)		moves to (x,y)
 *	qpoint(x,y)		draws point at (x,y)
 *
 *	qagray(n,x,y,c)		fills x,y (n points) with shade of gray c
 *	qafill(n,x,y)		fills x,y (n points) with actual color
 *	qrfill(x1,y1,x2,y2,ic)	fills rectangle with color ic
 *
 *	qtxts(ip)		sets text size in points
 *	qtext(x,y,s)		writes text s at position (x,y)
 *
 *	qgetvp(xmin,ymin,xmax,ymax)	gets viewport dimensions (in cm)
 *	qsetvp(xmin,ymin,xmax,ymax)	defines window for clipping (in cm)
 *	qclrvp()			clears viewport
 *	qworld(xmin,ymin,xmax,ymax)	sets world coordinates
 *	qrcfy()				rectifies scale
 *	
 */


#include <stdio.h>
#include <stdlib.h>

#include "general.h"
#include "psgraph.h"

#define BYTES_IN_INTEGER 4	/* size of fortran integer */

typedef int fint;		/* this must correspond to above */

/*****************************************************************/

static void testint( void )

{
	if( BYTES_IN_INTEGER != sizeof(fint) ) {
		Error("Erroneous size of integer");
	}
}

/*****************************************************************/

void qopen_( void )

{
	testint();
	PGraphInit("plot.ps");
}

void qclose_( void )

{
	PGraphClose();
}

void qstart_( void )

{
	PStartPage();
}

void qend_( void )

{
	PEndPage();
}

/*****************************************************************/

void qnewp_( fint *color )

{
	PNewPen( (int) (*color-1) );
}

void qgray_( float *gray )

{
	PSetGray( *gray );
}

void qhue_( float *hue )

{
	PSetHue( *hue );
}

void qhsb_( float *hue , float *sat , float *bri )

{
	PSetHSB( *hue , *sat , *bri );
}

void qrgb_( float *red , float *green , float *blue )

{
	PSetHSB( *red , *green , *blue );
}

/*****************************************************************/

void qline_( float *x1 , float *y1 , float *x2 , float *y2 )

{
	PLine( *x1 , *y1 , *x2 , *y2 );
}

void qplot_( float *x , float *y )

{
	PPlot( *x , *y );
}

void qmove_( float *x , float *y )

{
	PMove( *x , *y );
}

void qpoint_( float *x , float *y )

{
	PPoint( *x , *y );
}

/*****************************************************************/

void qagray_( fint *n , float *x , float *y , float *gray )

{
	PAreaGray( (int) *n , x , y , *gray );
}

void qahue_( fint *n , float *x , float *y , float *hue )

{
	PAreaHue( (int) *n , x , y , *hue );
}

void qafill_( fint *n , float *x , float *y )

{
	PAreaFill( (int) *n , x , y );
}

void qrfill_( float *x1 , float *y1 , float *x2 , float *y2 , fint *color )

{
	PRectFill( *x1 , *y1 , *x2 , *y2 , (int) *color-1 );
}

/*****************************************************************/

void qtxts_( fint *ip )

{
	PTextPointSize( (int) *ip );
}

void qtext_( float *x , float *y , char *s )

{
	PText( *x , *y , s );
}

/*****************************************************************/

void qgetvp_( float *xmin , float *ymin , float *xmax , float *ymax )

{
	PGetViewport(xmin,ymin,xmax,ymax);
}

void qsetvp_( float *xmin , float *ymin , float *xmax , float *ymax )

{
	PSetViewport(*xmin,*ymin,*xmax,*ymax);
}

void qclrvp_( void )

{
	PClearViewport();
}

void qworld_( float *xmin , float *ymin , float *xmax , float *ymax )

{
	PWindow( *xmin , *ymin , *xmax , *ymax );
}

void qrcfy_( void )

{
	PRectifyScale();
}

/*****************************************************************/
