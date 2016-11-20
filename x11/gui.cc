// Written by Ch. Tronche (http://tronche.lri.fr:8000/)
// Copyright by the author. This is unmaintained, no-warranty free software. 
// Please use freely. It is appreciated (but by no means mandatory) to
// acknowledge the author's contribution. Thank you.
// Started on Thu Jun 26 23:29:03 1997

//
// Xlib tutorial: 2nd program
// Make a window appear on the screen and draw a line inside.
// If you don't understand this program, go to
// http://tronche.lri.fr:8000/gui/x/xlib-tutorial/2nd-program-anatomy.html
//

#include <X11/Xlib.h> // Every Xlib program must include this
#include <assert.h>   // I include this to test return values the lazy way
#include <unistd.h>   // So we got the profile for 10 seconds

#define NIL (0)       // A name for the void pointer


unsigned char mandelbrot(double cx, double cy) {
  int i = 0;
  double x = cx, y = cy;

  for(i = 0; i < 256; i++) {
    double t = x;
    x = x*x-y*y+cx;
    y = 2*t*y+cy;
    if(x*x+y*y > 4.0) break;
   }

  return i;
}



main()
{
      // Open the display
int 	Width=640, Height=480;
double 	X1= 1.0, Y1= 1,
	X2=-2.0, Y2=-1;

      Display *dpy = XOpenDisplay(NIL);
      assert(dpy);

      // Get some colors

      int blackColor = BlackPixel(dpy, DefaultScreen(dpy));
      int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));

      // Create the window

      Window w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 
				     Width, Height, 0, blackColor, blackColor);

      // We want to get MapNotify events

      XSelectInput(dpy, w, StructureNotifyMask);

      // "Map" the window (that is, make it appear on the screen)

      XMapWindow(dpy, w);

      // Create a "Graphics Context"

      GC gc = XCreateGC(dpy, w, 0, NIL);

      // Tell the GC we draw using the white color

      XSetForeground(dpy, gc, whiteColor);

      // Wait for the MapNotify event

      for(;;) {
	    XEvent e;
	    XNextEvent(dpy, &e);
	    if (e.type == MapNotify)
		  break;
      }

      // Draw the line
      
      /*XDrawLine(dpy, w, gc, 10, 60, 180, 20);
      for (int i=0; i<100; i++)
		XDrawPoint(dpy, w, gc, 10, i);
*/

   double X,Y;
   for (int x=0 ; x < Width ; x++) {
	   for (int y=0 ; y < Height ; y++) {
			X = (double)x / Width  * (X1 - X2) + X2;
			Y = (double)y / Height * (Y2 - Y1) + Y1;
			//printf("%f %f,%d\n",X,Y,(int)mandelbrot(X,Y));
			if (mandelbrot(X,Y) == 0)
				XDrawPoint(dpy, w, gc, x,y);
			}
		}

      // Send the "DrawLine" request to the server

      XFlush(dpy);

      // Wait for 10 seconds

      sleep(10);
}

