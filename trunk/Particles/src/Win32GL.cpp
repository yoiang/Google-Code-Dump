#include "Win32GL.h"

std::map<HWND, Win32GL*> g_Win32GLClasses ;

LRESULT CALLBACK Win32GLWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (g_Win32GLClasses[hWnd] != 0) 
		return (*g_Win32GLClasses[hWnd]).WindowProcedure(hWnd, uMsg, wParam, lParam) ;

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
} 


Win32GL::Win32GL():m_hDC(0),m_hRC(0),m_hWnd(0),m_hInstance(0),
					m_bActive(true),m_bFullscreen(false),m_bPerspective(true),m_bLighting(false),
					m_bFilling(true),m_iWidth(100),m_iHeight(100),m_iBits(16),
					m_szTitle(0), m_WindowProc(Win32GLWndProc)
{
}

Win32GL::~Win32GL()
{
	Destroy() ;

	if (m_szTitle != 0) delete [] m_szTitle ;
}

int Win32GL::Create(char *szSetTitle, HINSTANCE hSetInstance, int iSetWidth, int iSetHeight, int iSetBits, bool bSetFullscreen)
{
	Destroy() ;

	SetTitle(szSetTitle) ;
	m_iWidth = iSetWidth ;
	m_iHeight = iSetHeight ;
	m_iBits = iSetBits ;
	m_bFullscreen = bSetFullscreen ;

	GLuint		PixelFormat;			
	WNDCLASS	wc;						
	DWORD		dwExStyle;				
	DWORD		dwStyle;				
	RECT		WindowRect;				
	WindowRect.left = (long)0 ;			
	WindowRect.right = (long)m_iWidth ;		
	WindowRect.top = (long)0 ;				
	WindowRect.bottom = (long)m_iHeight ;


	m_hInstance = hSetInstance ;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC ;
	wc.lpfnWndProc = m_WindowProc ;	
	wc.cbClsExtra = 0 ;
	wc.cbWndExtra = 0 ;
	wc.hInstance = m_hInstance ;
	wc.hIcon = LoadIcon(0, IDI_WINLOGO) ;	
	wc.hCursor = LoadCursor(0, IDC_ARROW) ;
	wc.hbrBackground = 0 ;
	wc.lpszMenuName	= 0 ;	
	wc.lpszClassName = "Win32GL" ;


	if (!RegisterClass(&wc))
	{
		MessageBox(0,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 1 ;
	}
	
	if (m_bFullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = m_iWidth ;
		dmScreenSettings.dmPelsHeight = m_iHeight ;
		dmScreenSettings.dmBitsPerPel = m_iBits ;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT ;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(0, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","ERROR", MB_YESNO|MB_ICONEXCLAMATION) == IDYES)
			{
				m_bFullscreen = false ;
			} else
			{
				MessageBox(0, "Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return 2;									// Return FALSE
			}
		}
	}

	if (m_bFullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW ;
		dwStyle = WS_POPUP ;
		ShowCursor(false) ;
	} else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE ;
		dwStyle = WS_OVERLAPPEDWINDOW ;
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, 0, dwExStyle) ;

	if (!(m_hWnd = CreateWindowEx(dwExStyle,
								"Win32GL",
								m_szTitle,
								dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
								0, 0,
								WindowRect.right-WindowRect.left,
								WindowRect.bottom-WindowRect.top,
								0,
								0,
								m_hInstance,
								0)))
	{
		MessageBox(0, "Window Creation Error.","ERROR", MB_OK|MB_ICONEXCLAMATION);
		return 3 ;
	}

	g_Win32GLClasses[m_hWnd] = this ;

	static	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		m_iBits,									// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	} ;
	
	if (!(m_hDC = GetDC(m_hWnd)))
	{
		Destroy();
		MessageBox(0,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 4;
	}

	if (!(PixelFormat = ChoosePixelFormat(m_hDC,&pfd)))
	{
		Destroy();
		MessageBox(0,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 5;
	}

	if(!SetPixelFormat(m_hDC,PixelFormat,&pfd))
	{
		Destroy();
		MessageBox(0,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 6;
	}

	if (!(m_hRC = wglCreateContext(m_hDC)))
	{
		Destroy();
		MessageBox(0,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 7;
	}

	if(!wglMakeCurrent(m_hDC, m_hRC))
	{
		Destroy();
		MessageBox(0,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 8;
	}

	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);
	Resize(m_iWidth, m_iHeight);

    glShadeModel(GL_SMOOTH);
 
//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE) ;
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);	 

	// enable depth testing, color materials and alpha blending (just used for eyes really..)
	glEnable(GL_DEPTH_TEST) ;

	glClearColor(0.0, 0.0, 0.0, 1.0) ;
	glClearDepth(1.0) ;

	return 0 ;
}

void Win32GL::Destroy()
{
	if (m_hWnd == 0) return ;

	if (m_bFullscreen)										
	{
		ChangeDisplaySettings(0, 0) ;					
		ShowCursor(true);								
	}

	if (m_hRC)											
	{
		if (!wglMakeCurrent(0, 0))					
			MessageBox(0,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);

		if (!wglDeleteContext(m_hRC))
			MessageBox(0,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);

		m_hRC = 0 ;
	}

	if (m_hDC && !ReleaseDC(m_hWnd, m_hDC))
	{
		MessageBox(0,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hDC = 0 ;
	}

	if (m_hWnd && !DestroyWindow(m_hWnd))
		MessageBox(0,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);

	g_Win32GLClasses[m_hWnd] = 0 ;

	m_hWnd = 0 ;

	if (!UnregisterClass("Win32GL", m_hInstance))
	{
		MessageBox(0,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hInstance = 0 ;	
	}
}

LRESULT CALLBACK Win32GL::WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_ACTIVATE:
		{
			if (wParam == WA_ACTIVE)
			{
				SetActive(true) ;
			} else if (wParam == WA_INACTIVE)
			{
				SetActive(false) ;
			}

			return 0;
		}

		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
			}
			break;
		}

		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		case WM_SIZE:
		{
			Resize(LOWORD(lParam),HIWORD(lParam));
			return 0;
		}
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


void Win32GL::Resize(int iSetWidth, int iSetHeight)
{
	if (iSetHeight == 0) iSetHeight = 1 ;

	m_iWidth = iSetWidth ;
	m_iHeight = iSetHeight ;

	glViewport(0, 0, m_iWidth, m_iHeight);

	SetPerspective(m_bPerspective, true) ;
}

HDC Win32GL::GetHDC()
{ return m_hDC ; }

HGLRC Win32GL::GetHRC()
{ return m_hRC ; }

HWND Win32GL::GetHWND()
{ return m_hWnd ; }

HINSTANCE Win32GL::GetHINSTANCE()
{ return m_hInstance ; }

char*Win32GL::GetTitle()
{ return m_szTitle ; }

bool Win32GL::GetActive()
{ return m_bActive ; }

void Win32GL::SetActive(bool bSetActive)
{ m_bActive = bSetActive ; }

bool Win32GL::GetFullscreen()
{ return m_bFullscreen ; }

void Win32GL::SetFullscreen(bool bSetFullscreen, bool bForce)
{
	if (m_bFullscreen != bSetFullscreen || bForce)
	{
		Create(m_szTitle, m_hInstance, m_iWidth, m_iHeight, m_iBits, bSetFullscreen) ;
	}			
}

bool Win32GL::GetLighting()
{ return m_bLighting ; }

void Win32GL::SetLighting(bool bSetLighting, bool bForce)
{
	if (m_bLighting != bSetLighting || bForce)
	{
		m_bLighting = bSetLighting ;
		if (m_bLighting)
		{
			glEnable(GL_LIGHTING) ;
			glEnable(GL_COLOR_MATERIAL) ;
		}	else
		{
			glDisable(GL_LIGHTING) ;
			glDisable(GL_COLOR_MATERIAL) ;
		}
	}
}

bool Win32GL::GetFilling()
{ return m_bFilling ; }

void Win32GL::SetFilling(bool bSetFilling, bool bForce)
{
	if (m_bFilling != bSetFilling || bForce)
	{
		m_bFilling = bSetFilling ;
		if (m_bFilling)
		{
			glPolygonMode(GL_FRONT, GL_FILL) ;
		}	else
		{
			glPolygonMode(GL_FRONT, GL_LINE) ;
		}	
	}
}

int Win32GL::GetWidth()
{ return m_iWidth ; }

int Win32GL::GetHeight()
{ return m_iHeight ; }

int Win32GL::GetBits()
{ return m_iBits ; }

bool Win32GL::GetPerspective()
{ return m_bPerspective ; }

void Win32GL::SetPerspective(bool bSetPerspective, bool bForce)
{
	if (m_bPerspective != bSetPerspective || bForce)
	{
		m_bPerspective = bSetPerspective ;

		glMatrixMode(GL_PROJECTION) ;
		glLoadIdentity() ;

		if (m_bPerspective)
		{
			gluPerspective(90.0, (GLfloat) m_iWidth/(GLfloat) m_iHeight, 0.1, 200.0) ;	
		}	else
		{
			glOrtho(float(m_iWidth) / -2.0, float(m_iWidth) / 2.0, float(m_iHeight) / -2.0, float(m_iHeight) / 2.0, 0.0, 10.0) ;
		}

		glMatrixMode(GL_MODELVIEW) ;
	}
}


void Win32GL::SetTitle(char *szSetTitle)
{
	if (m_szTitle == 0)
	{
		m_szTitle = new char [strlen(szSetTitle) + 1] ;
		strcpy(m_szTitle, szSetTitle) ;	
	} else
	{
		if (szSetTitle != m_szTitle)
		{
			delete [] m_szTitle ;
			m_szTitle = new char [strlen(szSetTitle) + 1] ;
			strcpy(m_szTitle, szSetTitle) ;
		}
	}
}

// Ian Grossberg - 2002