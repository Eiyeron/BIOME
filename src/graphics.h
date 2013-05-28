#ifndef B_GRAPHICS
#define B_GRAPHICS

#define LCD_WIDTH_PX 384 
#define LCD_HEIGHT_PX 216 

#define VRAM_ADRESS 0xA8000000


void SetPixel(int x, int y, unsigned short color);

void CopySpriteNbit(const unsigned char* data, int x, int y, int width, int height, unsigned short* palette, unsigned int bitwidth);

void CopySprite(const char* data, int x, int y, int width, int height);

void CopySprite_Palette(const unsigned char* data, const unsigned short* palette, int x, int y, int width, int height);

void Vertical_Line(int x, int y1, int y2, unsigned short color);

void Horizontal_Line(int x1, int x2, int y, unsigned short color);

void Line(int xi, int yi, int xf, int yf, unsigned short color);

void Filled_Rectangle(int x, int y, int x2, int y2, unsigned short color);

void Rectangle(int xi, int yi, int xf, int yf, int stroke, unsigned short color);

void Circle(int xi, int yi, int r, unsigned short color);

void Filled_Circle(int xi, int yi, int r, unsigned short color);


#endif