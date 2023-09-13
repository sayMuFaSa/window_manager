#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

int main(void){
	Display *dp = XOpenDisplay(NULL);
	XEvent ev;
	Window root;
	Window focused;
	int scr;
	scr = DefaultScreen(dp);
	root = DefaultRootWindow(dp);
	// FILE* file = fopen("/home/user/info.txt", "w");
	int revert;

	// XGrabKeyboard(dp, root, GrabModeAsync, True , GrabModeAsync, CurrentTime);
	
	XUngrabKey(dp, AnyKey, AnyModifier, root);
	XGrabKey(dp, XKeysymToKeycode(dp, XK_j), Mod1Mask, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey(dp, XKeysymToKeycode(dp, XK_q), Mod1Mask, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey(dp, XKeysymToKeycode(dp, XK_s), Mod1Mask, root, True, GrabModeAsync, GrabModeAsync);
	while(XNextEvent(dp, &ev) == 0){
		if (ev.type == KeyPress){
			switch(XKeycodeToKeysym(dp, ev.xkey.keycode, 0)){
				case XK_j:
					system("qutebrowser & disown");
					break;
				case XK_s:
					XGetInputFocus (dp, &focused, &revert);
					if (focused != root){
						XDestroyWindow(dp, focused);
						XFlush(dp);
					}
					break;
				case XK_q:
					goto Quit;
					break;
			}
		}
		
	}

Quit:

	fclose(file);

	XDestroyWindow(dp, root);

	
	XCloseDisplay(dp);
}
