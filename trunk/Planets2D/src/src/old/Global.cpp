int dx,dy ;
int last_x,last_y ;

int nNumlockStatus ;
float fGamma ;
int bDisplayHelp ;
char *szDefaultModelFile ;

int nEYE_DIST ;

/*
#define DEPTH_BUFFER_W 0 
#define DEPTH_BUFFER_Z 1 

#define SHADE_NONE 0
#define SHADE_GOURAND 1
#define SHADE_PHONG 2
*/
//#define POLY_RENDER_TEXTURE 2 
//#define POLY_RENDER_LIGHTING_TEXTURE 3
//GrScreenResolution_t resolution = GR_RESOLUTION_640x480 ;
/*
#define GR_REFRESH_60Hz   0x0
#define GR_REFRESH_70Hz   0x1
#define GR_REFRESH_72Hz   0x2
#define GR_REFRESH_75Hz   0x3
#define GR_REFRESH_80Hz   0x4
#define GR_REFRESH_90Hz   0x5
#define GR_REFRESH_100Hz  0x6
#define GR_REFRESH_85Hz   0x7
#define GR_REFRESH_120Hz  0x8
#define GR_REFRESH_NONE   0xff

typedef FxI32 GrScreenResolution_t;
#define GR_RESOLUTION_320x200   0x0
#define GR_RESOLUTION_320x240   0x1
#define GR_RESOLUTION_400x256   0x2
#define GR_RESOLUTION_512x384   0x3
#define GR_RESOLUTION_640x200   0x4
#define GR_RESOLUTION_640x350   0x5
#define GR_RESOLUTION_640x400   0x6
#define GR_RESOLUTION_640x480   0x7
#define GR_RESOLUTION_800x600   0x8
#define GR_RESOLUTION_960x720   0x9
#define GR_RESOLUTION_856x480   0xa
#define GR_RESOLUTION_512x256   0xb
#define GR_RESOLUTION_1024x768  0xC
#define GR_RESOLUTION_1280x1024 0xD
#define GR_RESOLUTION_1600x1200 0xE
#define GR_RESOLUTION_400x300   0xF
#define GR_RESOLUTION_NONE      0xff
*/
//GrScreenRefresh_t refresh_rate = GR_REFRESH_60Hz ;
//int depth_buffer = DEPTH_BUFFER_W ;
//int shade_mode = SHADE_NONE ;

/*
typedef struct
{
 float x, y, z;	      // X, Y, Z 
 float r, g, b;	      // R, G, B 
 float ooz;	              // 65535/Z (used for Z-buffering) 
 float a;	              // Alpha 
 float oow;	              // 1/W (used for W-buffering, texturing) 
//     GrTmuVertex tmuvtx[GLIDE_NUM_TMU];
} GrVertex ;	              
*/
//  grCoordinateSpace(GR_WINDOW_COORDS);