#include "main.h"

ParticleSource RShooter ;
Path Rosie ;

HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=false;	// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
void CALLBACK TimerProc(HWND hwnd, UINT uMsg,  UINT_PTR idEvent, DWORD dwTime) ;

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
//	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	TogglePerspective(false) ;

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	InitDisplay(true, false, true) ; // initialize variables and display modes

	SYSTEMTIME SystemTime ;
	GetSystemTime(&SystemTime) ;
	srand(SystemTime.wSecond) ;

	RShooter.bRespawn = false ;
	RShooter.bFade = true ;
	RShooter.bGravity = true ;
	RShooter.bWind = true ;
	RShooter.bTexture = true ;
	RShooter.bDie = true ; 
	RShooter.SetTexture("full.bmp") ;

	RShooter.ptInitialLocation = 0.0 ;
	RShooter.ptLocationDeviation = Point(0.3, 0.3, 0.3) ;
	RShooter.ptInitialVelocity = Point(-0.1, -0.1, 0.0) ;
	RShooter.ptVelocityDeviation = Point(0.2, 0.2, 0.0) ;
//	RShooter.ptInitialVelocity = Point(-0.1, 0, 0.5) ;
//	RShooter.ptVelocityDeviation = Point(0.2, 0.2, 0.1) ;

	RShooter.ptInitialColor = Point(1, 0.0, 0.0) ;
	RShooter.ptColorDeviation = Point(0.2, 0.4, 0.4) ;
	RShooter.ptColorIncrimenter = Point(0.0, 0.02, 0.02) ;
	RShooter.ptInitialColor = Point(1, 1, 1) ;
	RShooter.ptColorDeviation = Point(0.2, 0.4, 0.4) ;
	RShooter.ptColorIncrimenter = Point(0.0, -0.02, -0.02) ;

	RShooter.ptWindAcceleration = Point(-0.5, 0, 0) ;
	RShooter.ptGravityAcceleration = Point(0, 0, 0) ;//Point(0, 0, -3) ;

	RShooter.dInitialLife = 1.0 ;
	RShooter.dLifeDeviation = 0.5 ;
	RShooter.dLifeIncrimenter = -0.015 ;

	RShooter.ptScale = 1.0 ;

	Rosie.bConnectEnd = true ;
	Rosie.bLoop = false ;
	// R
	Rosie.Add(0, 0, 0, 20) ;	Rosie.Add(0, 1, 0, 3) ;	Rosie.Add(0, 2, 0, 3) ;	Rosie.Add(0, 3, 0, 3) ;	Rosie.Add(0, 4, 0, 3) ;
	Rosie.Add(1, 3.8, 0, 3) ; Rosie.Add(2, 3.6, 0, 3) ; Rosie.Add(2.5, 2.9, 0, 3) ; Rosie.Add(2, 2.2, 0, 3) ; Rosie.Add(0.8, 2, 0, 3) ;
	Rosie.Add(2, 1.4, 0, 3) ; Rosie.Add(2.4, 0.6, 0, 3) ; Rosie.Add(2.6, 0, 0, 3) ;
	// O
	Rosie.Add(5, 0, 0, 3) ; Rosie.Add(5.5, -0.2, 0, 1) ; Rosie.Add(6, 0, 0, 1) ; 
	Rosie.Add(6.5, 0.2, 0, 3) ; Rosie.Add(7, 1, 0, 3) ; Rosie.Add(7.2, 2, 0, 3) ; Rosie.Add(7, 3, 0, 3) ; Rosie.Add(6.5, 3.8, 0, 3) ; 
	Rosie.Add(6, 4, 0, 3) ; Rosie.Add(5.5, 4.2, 0, 1) ; Rosie.Add(5, 4, 0, 1) ; 
	Rosie.Add(4.5, 3.8, 0, 3) ; Rosie.Add(4, 3, 0, 3) ; Rosie.Add(3.8, 2, 0, 3) ; Rosie.Add(4, 1, 0, 3) ; Rosie.Add(4.5, 0.2, 0, 3) ; 
	Rosie.Add(5, 0, 0, 3) ; Rosie.Add(5.5, -0.2, 0, 1) ; Rosie.Add(6, 0, 0, 1) ;
	// S
	Rosie.Add(8, 0.3, 0, 3) ; Rosie.Add(9, 0, 0, 3) ; Rosie.Add(10, 0, 0, 3) ; Rosie.Add(11, 0.3, 0, 3) ; 
	Rosie.Add(11.3, 0.8, 0, 3) ; Rosie.Add(11.3, 1.4, 0, 3) ; Rosie.Add(11, 2, 0, 3) ; 
	Rosie.Add(10, 2.6, 0, 3) ; Rosie.Add(9, 3.2, 0, 3) ; Rosie.Add(8, 3.3, 0, 3) ; 
	Rosie.Add(9, 3.8, 0, 3) ; Rosie.Add(10, 3.8, 0, 3) ; Rosie.Add(11, 3.5, 0, 3) ; 
	// I
	Rosie.Add(13, 4, 0, 5) ; Rosie.Add(13, 3, 0, 5) ; Rosie.Add(13, 2, 0, 5) ; Rosie.Add(13, 1, 0, 5) ; Rosie.Add(13, 0, 0, 5) ;
	// E
	Rosie.Add(15, 0, 0, 3) ; Rosie.Add(16, 0, 0, 3) ; Rosie.Add(17.5, 0, 0, 3) ; 
	Rosie.Add(16, 0, 0, 3) ; Rosie.Add(15, 0, 0, 3) ; 
	Rosie.Add(15, 1, 0, 3) ; Rosie.Add(15, 2, 0, 3) ; 
	Rosie.Add(16, 2, 0, 3) ; Rosie.Add(17, 2, 0, 3) ; 
	Rosie.Add(16, 2, 0, 3) ; Rosie.Add(15, 2, 0, 3) ; 
	Rosie.Add(15, 3, 0, 3) ; Rosie.Add(15, 4, 0, 3) ; 
	Rosie.Add(16, 4, 0, 3) ; Rosie.Add(17, 4, 0, 3) ;
	// After
	Rosie.Add(50, 4, 0, 100) ;
	Rosie.Add(51, 4, 0, 20) ;
	Rosie.Add(0, 4, 0, 100) ;
	Rosie.Add(-1, 3, 0, 500) ;
	Rosie.Add(-10, 3, 0, 20) ;

	RShooter.ptInitialLocation = Rosie.StartingPoint() ;

	SetTimer(hWnd, 1, 25, (TIMERPROC)TimerProc) ;
	return TRUE;										// Initialization Went OK
}

void CALLBACK TimerProc(HWND hwnd, UINT uMsg,  UINT_PTR idEvent, DWORD dwTime)
{
	Point ptIterater ;
	RShooter.MoveParticles(0.1) ;
	RShooter.SpawnParticles(4) ;
	ptIterater = Rosie.StepForward() ;
	if (ptIterater.dVal[0] == 0 && ptIterater.dVal[1] == 0 && ptIterater.dVal[2] == 0)
	{
		RShooter.bWind = true ;
	} else RShooter.ptInitialLocation = RShooter.ptInitialLocation + ptIterater ;

//		fCameraLocation[0] = RShooter.ptInitialLocation.dVal[0] ;
//		fCameraLocation[1] = RShooter.ptInitialLocation.dVal[1] ;
//		fCameraAngle[0] = tan((RShooter.ptInitialLocation.dVal[1] - fCameraLocation[1]) / (RShooter.ptInitialLocation.dVal[2] - fCameraLocation[2])) ;
//		fCameraAngle[1] = tan((RShooter.ptInitialLocation.dVal[0] - fCameraLocation[0]) / (RShooter.ptInitialLocation.dVal[2] - fCameraLocation[2])) ;
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	SetCameraView() ;

	glDisable(GL_DEPTH_TEST);					
	RShooter.DisplayParticles(Point(fCameraLocation[0], fCameraLocation[1], fCameraLocation[2])) ;
	glEnable(GL_DEPTH_TEST) ;

	return TRUE;										// Keep Going
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
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
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
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

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	// Create Our OpenGL Window
	if (!CreateGLWindow("right as",800,100,16,false))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}

