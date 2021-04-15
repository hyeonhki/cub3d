double spritex;
	double spritey;
	int i = 0;
	while (i < info->map.row)
	{
		int j = 0;
		while (j < info->map.column)
		{
			if (info->map.worldmap[i][j] == 2)
			{
				spritex = j + 0.5;
				spritey = i + 0.5;
				printf("%f %f\n", spritex, spritey);
				double spriteX = spritex - info->posX;
				double spriteY = spritey - info->posY;
				
				double invDet = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY); //required for correct matrix multiplication

				double transformX = invDet * (info->dirY * spriteX - info->dirX * spriteY);
				double transformY = invDet * (-info->planeY * spriteX + info->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

				int spriteScreenX = (int)((info->config.width / 2) * (1 + transformX / transformY));

				#define uDiv 1
				#define vDiv 1
				#define vMove 0.0
				int vMoveScreen = (int)(vMove / transformY);

				//calculate height of the sprite on screen
				int spriteHeight = (int)fabs((info->config.height / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye
				//calculate lowest and highest pixel to fill in current stripe
				int drawStartY = -spriteHeight / 2 + info->config.height / 2 + vMoveScreen;
				if(drawStartY < 0) drawStartY = 0;
				int drawEndY = spriteHeight / 2 + info->config.height / 2 + vMoveScreen;
				if(drawEndY >= info->config.height) drawEndY = info->config.height - 1;

				//calculate width of the sprite
				int spriteWidth = (int)fabs((info->config.height / transformY) / uDiv);
				int drawStartX = -spriteWidth / 2 + spriteScreenX;
				if(drawStartX < 0) drawStartX = 0;
				int drawEndX = spriteWidth / 2 + spriteScreenX;
				if(drawEndX >= info->config.width) drawEndX = info->config.width - 1;

				for(int stripe = drawStartX; stripe < drawEndX; stripe++)
				{
					int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * info->config.texwidth / spriteWidth) / 256);
					//the conditions in the if are:
					//1) it's in front of camera plane so you don't see things behind you
					//2) it's on the screen (left)
					//3) it's on the screen (right)
					//4) ZBuffer, with perpendicular distance
					if(transformY > 0 && stripe > 0 && stripe < info->config.width && transformY < info->zBuffer[stripe])
					for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
					{
						int d = (y-vMoveScreen) * 256 - info->config.height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
						int texY = ((d * info->config.texheight) / spriteHeight) / 256;
						int color = info->texture[4][info->config.texwidth * texY + texX]; //get current color from the texture
						if((color & 0x00FFFFFF) != 0) info->screen[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
					}
				}
			}
			j++;
		}
		i++;
	}