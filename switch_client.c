#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int showwindow(char *displayname, char *msg, int shape) {
    Display *d;
    Window w;
    XEvent e;
    int s;

    d = XOpenDisplay(displayname);
    if (d == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 200, 200, 400, 400, 1, 777215, 111111);
    printf("BlackPixel(d, s) is %d\n", (int) BlackPixel(d, s));
    printf("WhitePixel(d, s) is %d\n", (int) WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    while (1) {
        XNextEvent(d, &e);
        if (e.type == Expose) {
			if (shape == 0) {
            	XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 100, 100);
			}else{
				XFillArc(d, w, DefaultGC(d, s), 40, 40, 100, 100, 60, 60);
			}	
           	XDrawString(d, w, DefaultGC(d, s), 230, 250, msg, strlen(msg));
        }
        if (e.type == KeyPress)
            break;
        if (e.type == ButtonPress)
			break;
    }
    XCloseDisplay(d);
    return 0;
}

void main()
{
	while(1){
		showwindow(":0", "This is ubuntu window", 0);
		showwindow("192.168.56.1:0", "This is MobaX window", 1);
	}
}
