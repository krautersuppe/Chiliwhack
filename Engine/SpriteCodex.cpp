#include "SpriteCodex.h"
#include <assert.h>


// 16x16 tile sprites assume (192,192,192) background and top left origin

void SpriteCodex::DrawChili(const Vei2 & pos, int w, Graphics & gfx)
{
	int cx = pos.x, cy = pos.y, width = w;

	float inc = 1; // triangle steepness counter

	for (int x = 0; x <= width / 8.0; x++) //top of the crown
	{
		for (int y = 0; y < inc; y++)
		{
			gfx.PutPixel(cx + x - int(width / 8.0f), cy - y - int(width * 7 / 16.0f), 0, 255, 0);
			gfx.PutPixel(cx + x - int(width / 4.0f), cy - y - int(width * 7 / 16.0f), 0, 255, 0);
			gfx.PutPixel(cx + x - int(width * 3 / 8.0f), cy - y - int(width * 7 / 16.0f), 0, 255, 0);
			gfx.PutPixel(cx + x - int(width / 2.0f), cy - y - int(width * 7 / 16.0f), 0, 255, 0);//first triangle spike from left

			gfx.PutPixel(cx - x + int(width / 8.0f), cy - y - int(width * 7 / 16.0f), 0, 255, 0); //right side mirrored cause of -x
			gfx.PutPixel(cx - x + int(width / 4.0f), cy - y - int(width * 7 / 16.0f), 0, 255, 0);
			gfx.PutPixel(cx - x + int(width * 3 / 8.0f), cy - y - int(width * 7 / 16.0f), 0, 255, 0);
			gfx.PutPixel(cx - x + int(width / 2.0f), cy - y - int(width * 7 / 16.0f), 0, 255, 0);
		}
		inc = inc + 2; //triangles are 2 times higher than wide
	}

	for (int x = 0; x <= width; x++) { // base of the crown (green rectangle)
		for (int y = 0; y <= int(width / 8.0f); y++) {
			gfx.PutPixel(cx + x - int(width / 2.0f), cy + y - int(width * 7 / 16.0f), 0, 255, 0);
		}
	}

	for (int x = 0; x <= width; x++) {//middle of face (white rectangle)
		for (int y = 0; y <= int(width / 2.0f); y++) {
			gfx.PutPixel(cx + x - int(width / 2.0), cy + y - int(width * 5 / 16.0f), 255, 255, 255);
		}
	}

	inc = 1;
	for (int x = 0; x <= int(width / 2.0); x++) // white triangle chin
	{
		for (int y = 0; y < inc; y++)
		{
			gfx.PutPixel(cx + x - int(width / 2.0f), cy + y + int(width * 3 / 16.0f), 255, 255, 255); //left side
			gfx.PutPixel(cx - x + int(width / 2.0f), cy + y + int(width * 3 / 16.0f), 255, 255, 255);//right side
		}
		inc = inc + 0.85f;
	}

	for (int x = 0; x <= int(width / 4.0f); x++) { //black rectangle eyes
		for (int y = 0; y < int(width / 10.0f); y++) {
			gfx.PutPixel(cx + x + int(width / 16.0f), cy + y - int(width / 8.0f), 0, 0, 0); // right eye
			gfx.PutPixel(cx - x - int(width / 16.0f), cy + y - int(width / 8.0f), 0, 0, 0); //left eye
		}
	}

	for (int x = 0; x <= int(width / 20.0f); x++) { //black rectangle beard
		for (int y = 0; y <= int(width * 6 / 25.0f); y++) {
			gfx.PutPixel(cx + x - int(width / 40.0f), cy + y + int(width * 3 / 8.0f), 0, 0, 0);
		}
	}

	for (int x = 1; x <= int(width * 7 / 20.0f); x++) { // black eyebrows
		for (int y = 1; y < int(width / 16.0f); y++) {
			gfx.PutPixel(cx + x - int(width * 3 / 8.0f), cy + y - int(width * 9 / 40.0f), 0, 0, 0); // left eyebrow
			gfx.PutPixel(cx + x + int(width / 40.0f), cy + y - int(width * 9 / 40.0f), 0, 0, 0); //right eyebrow
		}
	}

	for (int x = 0; x <= int(width / 2.0f); x++) { // beige lips
		for (int y = 0; y <= int(width / 20.0f); y++) {
			gfx.PutPixel(cx + x - int(width / 4.0f), cy + y + int(width * 5 / 16.0f), 255, 220, 220);
		}
	}

	inc = 1;

	for (int x = 0; x <= int(width * 3 / 16.0f); x++) //beige cheeks 
	{
		for (int y = 0; y < inc; y++)
		{
			gfx.PutPixel(cx + x - int(width / 2.0f), cy + y + int(width * 3 / 16.0f), 255, 240, 240); //left cheek
			gfx.PutPixel(cx - x + int(width / 2.0f), cy + y + int(width * 3 / 16.0f), 255, 240, 240); // right cheek
		}
		inc = inc + 0.85f;
	}


	inc = 1;

	for (int x = 1; x <= int(width * 5 / 16.0f); x++)//beige nose  - nose height 
	{
		for (int y = 0; y < inc; y++)
		{
			gfx.PutPixel(cx + y, cy + x - int(width / 8.0f), 255, 240, 240);//right side
			gfx.PutPixel(cx - y, cy + x - int(width / 8.0f), 255, 240, 240);//left side
		}
		inc = inc + 0.5f;
	}



	for (int x = 0; x <= int(width / 4.0f); x++) { //black moustache-squares
		for (int y = 1; y < int(width * 3 / 80.0f); y++) {
			gfx.PutPixel(cx + x - int(width * 5 / 16.0f), cy + y + int(width / 4.0f), 0, 0, 0);
			gfx.PutPixel(cx + x + int(width / 16.0f), cy + y + int(width / 4.0f), 0, 0, 0);
		}
	}

	inc = 1;

	for (int x = 0; x <= int(width / 10.0f); x++)//black moustache triangles
	{
		for (int y = 0; y < inc; y++)
		{
			gfx.PutPixel(cx + y + int(width / 40.0f), cy + x + int(width * 3 / 16.0f), 0, 0, 0);
			gfx.PutPixel(cx - y - int(width / 40.0f), cy + x + int(width * 3 / 16.0f), 0, 0, 0);
		}
		inc = inc + 0.85f;
	}

}

void SpriteCodex::DrawCell(const Vei2 & pos, int sq_w, int line_g, int r, int g, int b, Graphics & gfx)
{
	/*  pos.x, pos.y - center coordinates of the star(see drawing)
	sq_w  -  cell width/2
	line_g -line gap(see drawing) */

	int movex, movey;

	movey = pos.y;
	for (movex = pos.x - sq_w; movex <= pos.x; movex = movex + line_g) //3rd quadrant
	{
		gfx.DrawLine(pos.x - sq_w, movey, movex, pos.y + sq_w, r, g, b); // x1,y1(start point of the line) x2,y2(end point of the line),red,green,blue from the draw-line function
		movey = movey + line_g;
	}

	movey = pos.y;
	for (movex = pos.x + sq_w; movex >= pos.x; movex = movex - line_g)
	{
		gfx.DrawLine(pos.x + sq_w, movey, movex, pos.y + sq_w, r, g, b); //4th quadrant
		movey = movey + line_g;
	}

	movey = pos.y;
	for (movex = pos.x + sq_w; movex >= pos.x; movex = movex - line_g) //1st quadrant
	{
		gfx.DrawLine(pos.x + sq_w, movey, movex, pos.y - sq_w, r, g, b);
		movey = movey - line_g;
	}

	movey = pos.y;
	for (movex = pos.x - sq_w; movex <= pos.x; movex = movex + line_g)
	{
		gfx.DrawLine(pos.x - sq_w, movey, movex, pos.y - sq_w, r, g, b); //2nd quadrant
		movey = movey - line_g;
	}
}
