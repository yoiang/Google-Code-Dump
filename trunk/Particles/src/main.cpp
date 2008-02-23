#include "main.h"

Win32GL g_MainWindow ;
DXKeyboard g_MainInput ;
Fountain WaterFountain ;
std::vector<std::string> g_vTextures ;
int iTextureNum = 0 ;

bool g_bExit = false, g_bPause = false, g_bCollisionModel = false, g_bMoveDisplayTogether = false ;
ParticleSource g_ParticleShooter ;
Point g_ptCameraAngle, g_ptCameraLocation ;

void Display(ParticleSource &ParticleShooter, Point &ptCameraAngle, Point &ptCameraLocation, const bool &bMoveDisplayTogether)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	glLoadIdentity() ;

	glRotatef(- ptCameraAngle.dVal[0], 1.0, 0.0, 0.0) ;
	glRotatef(- ptCameraAngle.dVal[1], 0.0, 1.0, 0.0) ;
	glRotatef(ptCameraAngle.dVal[2], 0.0, 0.0, 1.0) ;

	glTranslatef(- ptCameraLocation.dVal[0], - ptCameraLocation.dVal[1], - ptCameraLocation.dVal[2]) ;

/*	if (bCollisionModel)
	{

		LinkedListNode<Model> *pTravModels = CollisionModel.pHead ;
		while (pTravModels != 0)
		{
			pTravModels->pValue->Display(false) ;
			pTravModels = pTravModels->pNext ;
		}
	}
*/	
	glDisable(GL_DEPTH_TEST);					
	if (bMoveDisplayTogether)
	{
/*		if (bCollisionModel) ParticleShooter.MoveDisplayParticles(0.1, &CollisionModel, ptCameraLocation) ;
		else*/ ParticleShooter.MoveDisplayParticles(0.1f, 0, ptCameraLocation) ;
	} else
	{
		ParticleShooter.DisplayParticles(ptCameraLocation) ;
	}
	glEnable(GL_DEPTH_TEST) ;

	glFinish() ;
}

bool UpdateInput(DXKeyboard &KeyInput, ParticleSource &ParticleShooter, Point &ptCameraAngle, Point &ptCameraLocation, Win32GL &MainWindow) 
{
	float fRadians ;
	int iTrav ;
	if (KeyInput.State(0x1f) == DXKEY_DOWN)
	{
		++ iTextureNum ;
		if (iTextureNum == g_vTextures.size()) iTextureNum = 0 ;
		g_ParticleShooter.SetTexture(g_vTextures[iTextureNum].c_str()) ;
	}
	if (KeyInput.State(0xc8))
	{
		fRadians = ptCameraAngle.dVal[1] * 3.1415 / 180.0 ;
		ptCameraLocation.dVal[0] -= sin(fRadians) ;
		ptCameraLocation.dVal[2] -= cos(fRadians) ;

		fRadians = ptCameraAngle.dVal[0] * 3.1415 / 180.0 ;
		ptCameraLocation.dVal[1] += sin(fRadians) ;
	}
	if (KeyInput.State(0xcb))
	{
		fRadians = ptCameraAngle.dVal[1] * 3.1415 / 180.0 - 90;
//		ptCameraLocation.dVal[0] += sin(fRadians) ;
//		ptCameraLocation.dVal[2] += cos(fRadians) ;
	}
	if (KeyInput.State(0xd0))
	{
		fRadians = ptCameraAngle.dVal[1] * 3.1415 / 180.0 ;
		ptCameraLocation.dVal[0] += sin(fRadians) ;
		ptCameraLocation.dVal[2] += cos(fRadians) ;

		fRadians = ptCameraAngle.dVal[0] * 3.1415 / 180.0 ;
		ptCameraLocation.dVal[1] -= sin(fRadians) ;
	}
	if (KeyInput.State(0xcd))
	{
		fRadians = ptCameraAngle.dVal[1] * 3.1415 / 180.0 + 90;
//		ptCameraLocation.dVal[0] += sin(fRadians) ;
//		ptCameraLocation.dVal[2] += cos(fRadians) ;
	}

	if (KeyInput.State(0x14) == DXKEY_DOWN)
	{
		ParticleShooter.bTexture = !ParticleShooter.bTexture ;
	}
	if (KeyInput.State(0x0d) == DXKEY_DOWN)
	{
		ParticleShooter.SpawnParticles(1000) ;
	}
	if (KeyInput.State(0x0c) == DXKEY_DOWN)
	{
		for (iTrav = 0 ; iTrav < 100 ; iTrav ++)
		{
			if (ParticleShooter.Particles.pTail == 0) break ;
			ParticleShooter.Particles.Remove(ParticleShooter.Particles.pTail, true) ;
		}
	}
	if (KeyInput.State(0x01))
	{
		g_bExit = true ;
	}
	if (KeyInput.State(0x2e) == DXKEY_DOWN)
	{
		ParticleShooter.bLines = !ParticleShooter.bLines ;
	}

	if (KeyInput.State(0x04) == DXKEY_DOWN)
	{

//		MainWindow.SetLighting(true, false) ;

		ParticleShooter.pSpawner = 0 ;

		ParticleShooter.bFade = true ;
		ParticleShooter.bTexture = true ;
		ParticleShooter.bGravity = false ;

		ParticleShooter.ptInitialLocation = 0.0 ;
		ParticleShooter.ptLocationDeviation = Point(4, 0, 4) ;
		ParticleShooter.ptInitialVelocity = Point(0, 1, 0) ;
		ParticleShooter.ptVelocityDeviation = Point(0.5, 1, 0.5) ;

		ParticleShooter.ptInitialColor = Point(0.9f, 0.5f, 0.0) ;
		ParticleShooter.ptColorDeviation = Point(0.1f, 0.1f, 0.0) ;
		ParticleShooter.ptColorIncrimenter = Point(0.001f, 0.01f, 0.01f) ;

		ParticleShooter.ptWindAcceleration = Point(4, 0, 0) ;

		ParticleShooter.dInitialLife = 1.2 ;
		ParticleShooter.dLifeDeviation = 0.5 ;
		ParticleShooter.dLifeIncrimenter = -0.01 ;

		ParticleShooter.ptScale = 1.0 ;
	}
	if (KeyInput.State(0x03) == DXKEY_DOWN)
	{
//		bCollisionModel = false ;
//		ToggleLighting(false) ;

		ParticleShooter.pSpawner = 0 ;

		ParticleShooter.bFade = false ;
		ParticleShooter.bTexture = true ;
		ParticleShooter.bGravity = false ;

		ParticleShooter.ptInitialLocation = Point(0.0f, 5.0f, 5.0f) ;
		ParticleShooter.ptLocationDeviation = Point(10.0f, 0.0f, 10.0f) ;
		ParticleShooter.ptInitialVelocity = Point(0.0f, -0.1f, 0.0f) ;
		ParticleShooter.ptVelocityDeviation = Point(0.5f, -0.05f, 0.5f) ;

		ParticleShooter.ptInitialColor = Point(1.0f, 1.0f, 1.0f) ;
		ParticleShooter.ptColorDeviation = Point(0.01f, 0.01f, 0.01f) ;
		ParticleShooter.ptColorIncrimenter = Point(-0.001f, -0.001f, -0.001f) ;

		ParticleShooter.ptWindAcceleration = Point(0.9f, -0.2f, 0.0f) ;

		ParticleShooter.dInitialLife = 1.0f ;
		ParticleShooter.dLifeDeviation = 0.5f ;
		ParticleShooter.dLifeIncrimenter = -0.001f ;

		ParticleShooter.ptScale = 0.5f ;

	}
	if (KeyInput.State(0x02) == DXKEY_DOWN)
	{
//		bCollisionModel = true ;
//		ToggleLighting(false) ;

		ParticleShooter.bFade = true ;
		ParticleShooter.bTexture = true ;
		ParticleShooter.bGravity = true ;

		ParticleShooter.SetSpawner(&WaterFountain) ;

		ParticleShooter.ptInitialLocation = Point(0.0f, 0.5f, 0.0f) ;
		ParticleShooter.ptLocationDeviation = Point(2.0f, 0.0f, 2.0f) ;
		ParticleShooter.ptInitialVelocity = Point(0.0f, 4.0f, 0.0f) ;
		ParticleShooter.ptVelocityDeviation = Point(2.5f, 0.6f, 2.5f) ;

		ParticleShooter.ptInitialColor = Point(0.8f, 0.8f, 0.9f) ;
		ParticleShooter.ptColorDeviation = Point(0.01f, 0.01f, 0.2f) ;
		ParticleShooter.ptColorIncrimenter = Point(-0.005f, -0.005f, -0.0001f) ;

		ParticleShooter.ptWindAcceleration = Point(4.0f, 0.0f, 0.0f) ;

		ParticleShooter.dInitialLife = 0.8f ;
		ParticleShooter.dLifeDeviation = 0.5f ;
		ParticleShooter.dLifeIncrimenter = -0.005f ;

		ParticleShooter.ptScale = 1.0 ;
	}

/*
shift 0x2a
		int iTrav ;
	float fNumSpawn ;
	switch (cKey)
	{
	case 'f' :0x21
	case 'F' :
//		ToggleFullscreen(!bFullscreen) ;
	break ;

	case 'g' :0x22
	case 'G' :
		ParticleShooter.bGravity = !ParticleShooter.bGravity ;
	break ;

	case 'i' : 0x17
	case 'I' :
		InitCamera() ;
	break ;

	case 'l' : // toggle lighting 0x26
	case 'L' :
		ToggleLighting(!bLighting) ;
	break ;

	case 'm' :0x32
	case 'M' :
		bCollisionModel = !bCollisionModel ;
	break ;

	case 'p' :0x19
	case 'P' :
		bPause = !bPause ;
	break ;

	case 'q' : // quit program
	case 'Q' :0x10 0x01
		exit(0) ;
	break ;

	case 'r' : 0x13
	case 'R' :
		ParticleShooter.bRespawn = !ParticleShooter.bRespawn ;
	break ;

	case 's' :0x1f
	case 'S' :
		printf("Enter number of particles to spawn: ") ;
		scanf("%f", &fNumSpawn) ;
		ParticleShooter.SpawnParticles(fNumSpawn) ;
	break ;

	case 'w' :0x11
	case 'W' :
		ParticleShooter.bWind = !ParticleShooter.bWind ;
	break ;

	case 'x' :0x2d
	case 'X' :
		bMoveDisplayTogether = !bMoveDisplayTogether ;
	break ;

	case '.' :0x34
	case '?' :
		ParticleShooter.bRespawn = !ParticleShooter.bRespawn ;
	break ;
	}
*/
	return 0 ;
}

void CALLBACK UpdateTimer(HWND hWnd, UINT uMsg,  UINT_PTR idEvent, DWORD dwTime)
{
	if (!g_bPause)
	{
		if (!g_bMoveDisplayTogether)
		{
/*			if (bCollisionModel) ParticleShooter.MoveParticles(0.1, &CollisionModel) ;
			else */g_ParticleShooter.MoveParticles(0.1f, 0) ;
		}
	}

	UpdateInput(g_MainInput, g_ParticleShooter, g_ptCameraAngle, g_ptCameraLocation, g_MainWindow) ;
}

void InitParticleExample(ParticleSource &ParticleShooter, Point &ptCameraAngle, Point &ptCameraLocation)
{
	srand(time(0)) ;

	ParticleShooter.SpawnParticles(1000) ;

	ParticleShooter.bRespawn = true ;
	ParticleShooter.bGravity = true ;

	WIN32_FIND_DATA Win32FindData ;

	HANDLE hResult = FindFirstFile("*.bmp", &Win32FindData) ;
	if (hResult != INVALID_HANDLE_VALUE)
	{
		g_vTextures.push_back(Win32FindData.cFileName) ;
		while (FindNextFile(hResult, &Win32FindData))
		{
			g_vTextures.push_back(Win32FindData.cFileName) ;
		}
	} else
	{
		MessageBox(0, "No .bmp files found!", "Error", MB_OK) ;
		g_bExit = true ;
		return ;
	}
	ParticleShooter.SetTexture(g_vTextures[0].c_str()) ;
	ptCameraAngle = Point(0.0, 0.0, 0.0) ;
	ptCameraLocation = Point(0.0, 2.0f, 5.0f) ;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

//	Model *pTemp = new Model ;
//	pTemp->ReadFile("models\\floor.ml") ;
//	CollisionModel.AddBack(pTemp) ;

//	bCollisionModel = false ;
//	bMoveDisplayTogether = false ;

//	WaterFountain.fRadius = 3 ;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg ;

	g_MainWindow.Create("Particles Examples", hInstance, 640, 480, 16, true) ;
	g_MainWindow.SetFilling(false, false) ;
	g_MainWindow.SetLighting(false, false) ;

	g_MainInput.Init(hInstance, g_MainWindow.GetHWND()) ;

	SetTimer(g_MainWindow.GetHWND(), 0, 5, UpdateTimer) ;

//	LinkedList<Model> CollisionModel ;
//	Fountain WaterFountain ;

	InitParticleExample(g_ParticleShooter, g_ptCameraAngle, g_ptCameraLocation) ;

	while(!g_bExit)
	{
		g_MainInput.Update() ;
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				g_bExit = true;
			} else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else
		{
			Display(g_ParticleShooter, g_ptCameraAngle, g_ptCameraLocation, g_bMoveDisplayTogether) ;
			SwapBuffers(g_MainWindow.GetHDC());
		}
	}

	KillTimer(g_MainWindow.GetHWND(), 0) ;
	g_MainWindow.Destroy() ;

	return 0;
}
