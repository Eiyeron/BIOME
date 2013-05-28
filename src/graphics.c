#include "graphics.h"
#include "macros.h"

void SetPixel(int x, int y, unsigned short color){
	unsigned short* VRAM = (unsigned short*)VRAM_ADRESS; 
	VRAM[LCD_WIDTH_PX * y + x] = color;
}


void CopySpriteNbit(const unsigned char* data, int x, int y, int width, int height, unsigned short* palette, unsigned int bitwidth) {
   unsigned short* VRAM = (unsigned short*)0xA8000000;
   VRAM += (LCD_WIDTH_PX*y + x);
   int offset = 0;
   unsigned char buf;
   for(int j=y; j<y+height; j++) {
      int availbits = 0;
      for(int i=x; i<x+width;  i++) {
         if (!availbits) {
            buf = data[offset++];
            availbits = 8;
         }
         unsigned short this = ((unsigned short)buf>>(8-bitwidth));
         *VRAM++ = palette[(unsigned short)this];
         buf<<=bitwidth;
         availbits-=bitwidth;
      }
      VRAM += (LCD_WIDTH_PX-width);
   }
} 

void CopySprite(const char* data, int x, int y, int width, int height) { 
   char* VRAM = (char*)0xA8000000;
   int j;
   VRAM += 2*(LCD_WIDTH_PX*y + x); 
   for(j=y; j<y+height; j++) { 
      memcpy(VRAM,data,2*width); 
      VRAM += 2*LCD_WIDTH_PX; 
      data += 2*width; 
   } 
}


void CopySprite_Palette(const unsigned char* data, const unsigned short* palette, int x, int y, int width, int height)
{ 
   unsigned short* VRAM = (unsigned short*)VRAM_ADRESS; 
   int i,j;
   unsigned short* ptr = VRAM + y*LCD_WIDTH_PX + x; 
   for(j=0; j<height; j++) { 
		for(i = 0; i < width; i++)
		{
			*ptr = palette[*(data++)];
			ptr++;
		}
		ptr += LCD_WIDTH_PX-width;
   } 
}

void set_Pixel(int x, int y, unsigned short color)
{
   unsigned short* VRAM = (unsigned short*)VRAM_ADRESS; 
	if(x<LCD_WIDTH_PX && x > 0 && y < LCD_WIDTH_PX && y > 0)
		VRAM[LCD_WIDTH_PX * y + x] = color;
}

unsigned short get_Pixel(int x, int y)
{
   unsigned short* VRAM = (unsigned short*)VRAM_ADRESS; 
	if(x<LCD_WIDTH_PX && x > 0 && y < LCD_WIDTH_PX && y > 0)
		return VRAM[LCD_WIDTH_PX * y + x];
}


void Circle(int xi, int yi, int r, unsigned short color)
{
	int x = 0;
	int y = r;
	int d = r - 1;
	while(y>=x)
	{
		set_Pixel( x+xi, y+yi, color);
		set_Pixel( y+xi, x+yi, color);
		set_Pixel( -x+xi, y+yi, color);
		set_Pixel( -y+xi, x+yi, color);
		set_Pixel( x+xi, -y+yi, color);
		set_Pixel( y+xi, -x+yi, color);
		set_Pixel( -x+xi, -y+yi, color);
		set_Pixel( -y+xi, -x+yi, color);
		if(d >= 2*x)
		{
			d -= 2*x+1;
			x++;
		}
		else if (d <= 2*(r-y))
		{
			d += 2*y-1;
			y--;     
		}
		else
		{
			d += 2*(y-x-1);
			y--;
			x++;
		}
	}

}

void Filled_Circle(int xi, int yi, int r, unsigned short color)
{
	int x = 0;
	int y = r;
	int d = r - 1;
	while(y>=x)
	{
/* 		set_Pixel( x+xi, y+yi, color);
		set_Pixel( -x+xi, y+yi, color);
 */
		Horizontal_Line(x+xi,-x+xi,y+yi,color);
		
/* 		set_Pixel( y+xi, x+yi, color);
		set_Pixel( -y+xi, x+yi, color);
 */
		Horizontal_Line(y+xi,-y+xi,x+yi,color);
		
/* 		set_Pixel( x+xi, -y+yi, color);
		set_Pixel( -x+xi, -y+yi, color);
 */
		Horizontal_Line(x+xi,-x+xi,-y+yi, color);
		
/* 		set_Pixel( -y+xi, -x+yi, color);
		set_Pixel( y+xi, -x+yi, color);
 */
		Horizontal_Line(y+xi,-y+xi, -x+yi, color);
		
	if(d >= 2*x)
		{
			d -= 2*x+1;
			x++;
		}
		else if (d <= 2*(r-y))
		{
			d += 2*y-1;
			y--;     
		}
		else
		{
			d += 2*(y-x-1);
			y--;
			x++;
		}
	}

}

void Vertical_Line(int x, int y1, int y2, unsigned short color)
{
	unsigned short* VRAM = (unsigned short*)VRAM_ADRESS; 
	int i;
	int yi = max(min(y1,y2),0);
	int yf = min(max(y1,y2),LCD_HEIGHT_PX);
	if(x < 0 || x > LCD_WIDTH_PX) return;
	for(i=yi; i <= yf; i++)
		VRAM[LCD_WIDTH_PX*i + x] = color;
}

void Horizontal_Line(int x1, int x2, int y, unsigned short color)
{
	unsigned short* VRAM = (unsigned short*)VRAM_ADRESS; 
	int i;
	int xi = max(min(x1,x2),0);
	int xf = min(max(x1,x2),LCD_WIDTH_PX);
	if(y < 0 || y > LCD_HEIGHT_PX) return;
	for(i=xi; i <= xf; i++)
		VRAM[LCD_WIDTH_PX*y + i] = color;
}


void Line(int xi, int yi, int xf, int yf, unsigned short color)
{
	int dx,dy,i,xinc,yinc,cumul,x,y;
	x = xi;
	y = yi;
	dx = xf - xi;
	if(!dx)
	{
		Vertical_Line(xi, yi,yf,color);
		return;
	}
	dy = yf - yi;
	if(!dy)
	{
		Horizontal_Line(xi,xf,yi,color);
		return;
	}
	xinc = ( dx > 0 ) ? 1 : -1;
	yinc = ( dy > 0 ) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	set_Pixel( x, y, color);
	if ( dx > dy ) 
	{
		cumul = dx >>1; // dy/2
		for ( i = 1; i <= dx; i++ ) 
		{
			x += xinc;
			cumul += dy;
			if (cumul >= dx) 
			{
				cumul -= dx;
				y += yinc;
			}
			set_Pixel( x, y, color);
		} 
	}
    else
	{
		cumul = dy >>2;// dy/2
		for ( i = 1; i <= dy; i++ )
		{
			y += yinc;
			cumul += dx;
			if ( cumul >= dy )
			{
				cumul -= dy;
				x += xinc;
			}
			set_Pixel( x, y, color);
		}
	}
}

void Filled_Rectangle( int xi,  int yi,  int xi2,  int yi2, unsigned short color)
{ 
   unsigned short* VRAM = (unsigned short*)VRAM_ADRESS;
	int i,j;
	const int x = max(0,min(xi,xi2));
	const int x2 = min( LCD_WIDTH_PX,max(xi,xi2));
	
	const int y = max(0,min(yi,yi2));
	const int y2 = min( LCD_WIDTH_PX,max(yi,yi2));
	
	const int xm = max(x,x2);
	const int ym = max(y,y2);
	
	const int xe = x2-x+1;
	
	VRAM += LCD_WIDTH_PX*y + x; 
	for(j = min(y,y2); j <= ym; j++) { 
		for(i=min(x,x2); i <= xm;  i++) { 
			*(VRAM++) = color; 
		} 
		VRAM += LCD_WIDTH_PX-xe; 
	}
}

void Rectangle(int xi, int yi, int xf, int yf, int stroke, unsigned short color)
{
	int i;
	for(i=0;i<stroke; i++)
	{
		Vertical_Line(xi+i,yi,yf,color);
		Vertical_Line(xf-i,yi,yf,color);
		Horizontal_Line(xi,xf-i,yi+i,color);
		Horizontal_Line(xi,xf-i,yf-i,color);
	}
}

