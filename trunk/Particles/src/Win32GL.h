// check coloring of full screen modes
// check if winproc = 0 works correctly

#ifndef __WIN32GL_H__
#define __WIN32GL_H__

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include <string.h>
#include <map>

class Win32GL // Win32 OpenGL Window Class
{
private:
	HDC	m_hDC ;				// device context for window
	HGLRC m_hRC ;				// rendering context for window
	HWND m_hWnd ;				// window handle
	HINSTANCE m_hInstance ;	// instance window belongs to

	bool m_bActive,		// whether window is active or not
		 m_bFullscreen,	// whether window is fullscreened or not
		 m_bPerspective,	// whether perspective viewing is enabled
		 m_bLighting,		// whether lighting is enabled
		 m_bFilling ;		// whether filling is enabled

	WNDPROC m_WindowProc ; // the window's event handling procedure

	int m_iWidth,		// width of window
		m_iHeight,	// height of window
		m_iBits ;		// color depth of window

	char *m_szTitle ;	// title of window

	void SetTitle(char *szSetTitle) ;	// set the title of the window
	
public:
	Win32GL() ;		// constructor
	~Win32GL() ;	// destructor

	virtual LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;

	// create the window
	int Create(char *szSetTitle,		// title of new window
			   HINSTANCE hSetInstance,	// instance of new window
			   int iSetWidth,			// width of new window
			   int iSetHeight,			// height of new window
			   int iSetBits,			// color depth of new window
			   bool bSetFullscreen) ;	// whether new window should be fullscreen or not
	void Destroy() ; // destroy the window
	void Resize(int iSetWidth, int iSetHeight) ; // resize the window

	HDC GetHDC() ;				// get the device context of the window
	HGLRC GetHRC() ;			// get the rendering context of the window
	HWND GetHWND() ;			// get the window handle
	HINSTANCE GetHINSTANCE() ;	// get the instance the window is running

	char*GetTitle() ;					// get the title of the window
	bool GetActive() ;					// get whether the window is active or not
	void SetActive(bool bSetActive) ;	// set the active status of the window
	bool GetFullscreen() ;				// get whether the window is fullscreen or not
	void SetFullscreen(bool bSetFullscreen, bool bForce) ;	// set fullscreen
	bool GetPerspective() ;				// get whether persperctive viewing is enabled
	void SetPerspective(bool bSetPerspective, bool bForce) ;	// set perspective viewing
	bool GetLighting() ;				// get whether lighting is enabled
	void SetLighting(bool bSetLighting, bool bForce) ;	// set lighting
	bool GetFilling() ;					// get whether filling is enabled
	void SetFilling(bool bSetFilling, bool bForce) ;	// set filling

	int GetWidth() ;	// get the window's width
	int GetHeight() ;	// get the window's height
	int GetBits() ;		// get the window's color depth
} ;

#endif

// Ian Grossberg - 2002