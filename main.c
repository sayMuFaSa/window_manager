#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

int main(void){
	Display *dp = XOpenDisplay(NULL);
	XEvent ev;
	Window root;
	int scr;
	scr = DefaultScreen(dp);
	root = DefaultRootWindow(dp);
	FILE* file = fopen("/home/user/info.txt", "w");

	// XGrabKeyboard(dp, root, GrabModeAsync, True , GrabModeAsync, CurrentTime);
	
	XUngrabKey(dp, AnyKey, AnyModifier, root);
	XGrabKey(dp, XKeysymToKeycode(dp, XK_j), Mod1Mask, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey(dp, XKeysymToKeycode(dp, XK_q), Mod1Mask, root, True, GrabModeAsync, GrabModeAsync);
	while(XNextEvent(dp, &ev) == 0){
		if (ev.type == KeyPress){
			if (XKeycodeToKeysym(dp, ev.xkey.keycode, 0) ==  XK_j){
				system("qutebrowser&");
			}else if(XKeycodeToKeysym(dp, ev.xkey.keycode, 0) == XK_q){
				break;
			}
		}
		
	}

	fclose(file);

	XDestroyWindow(dp, root);

	
	XCloseDisplay(dp);
}
