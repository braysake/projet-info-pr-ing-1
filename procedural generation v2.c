#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_ROOM 5


typedef struct
{
	int x;
	int y;
	int roomnum1;
	int roomnum2;
	int direction;
} Door;

typedef struct
{
	int roomdoor[4];
	int numofdoor;
	int xmin;
	int xmax;
	int ymin;
	int ymax;

} Room;

int
searchneardoor (Door * tabdoor, Door testdoor, int doorcount)
{
	for (int i = 0; i < doorcount; i++)
		{
			switch (testdoor.direction)
				{
				case 0:
					if (tabdoor[i].x >= (testdoor.x) - 6
							&& tabdoor[i].x <= (testdoor.x) + 6
							&& tabdoor[i].y >= (testdoor.y) + 1
							&& tabdoor[i].y <= (testdoor.y) + 9
						&& tabdoor[i].direction != testdoor.direction)
						{
							if (tabdoor[i].roomnum1 != testdoor.roomnum1
									&& tabdoor[i].roomnum2 != testdoor.roomnum1
									&& tabdoor[i].direction != testdoor.direction)
								{
									return 1;
								}
						}
					break;
				case 1:
					if (tabdoor[i].y >= (testdoor.y) - 6
							&& tabdoor[i].y <= (testdoor.y) + 6
							&& tabdoor[i].x >= (testdoor.x) + 1
							&& tabdoor[i].x <= (testdoor.x) + 9
						&&tabdoor[i].direction != testdoor.direction)
						{
							if (tabdoor[i].roomnum1 != testdoor.roomnum1
									&& tabdoor[i].roomnum2 != testdoor.roomnum1
									&& tabdoor[i].direction != testdoor.direction)
								{
									return 1;
								}
						}
					break;
				case 2:
					if (tabdoor[i].x >= (testdoor.x) - 6
							&& tabdoor[i].x <= (testdoor.x) + 6
							&& tabdoor[i].y <= (testdoor.y) - 1
							&& tabdoor[i].y >= (testdoor.y) - 9
						&& tabdoor[i].direction != testdoor.direction)
						{
							if (tabdoor[i].roomnum1 != testdoor.roomnum1
									&& tabdoor[i].roomnum2 != testdoor.roomnum1
									&& tabdoor[i].direction != testdoor.direction)
								{
									return 1;
								}
						}
					break;
				case 3:
					if (tabdoor[i].y >= (testdoor.y) - 6
							&& tabdoor[i].y <= (testdoor.y) + 6
							&& tabdoor[i].x <= (testdoor.x) - 1
							&& tabdoor[i].x >= (testdoor.x) - 9
						&& tabdoor[i].direction != testdoor.direction)
						{
							if (tabdoor[i].roomnum1 != testdoor.roomnum1
									&& tabdoor[i].roomnum2 != testdoor.roomnum1
									&& tabdoor[i].direction != testdoor.direction)
								{
									return 1;
								}
						}
					break;
				}
		}
	return 0;
}



int searchreallyneardoor (Door possibledoor, Door testdoor)
{
	switch (testdoor.direction)
		{
		case 0:
			if (possibledoor.x >= (testdoor.x) - 5
					&& possibledoor.x <= (testdoor.x) + 5
					&& possibledoor.y >= (testdoor.y) + 1
					&& possibledoor.y <= (testdoor.y) + 8
					&& possibledoor.direction != testdoor.direction)
				{
					if (possibledoor.roomnum1 != testdoor.roomnum1
							&& possibledoor.roomnum2 != testdoor.roomnum1
							&& possibledoor.direction != testdoor.direction)
						{
							return 1;
						}
				}
			break;
		case 1:
			if (possibledoor.y >= (testdoor.y) - 5
					&& possibledoor.y <= (testdoor.y) + 5
					&& possibledoor.x >= (testdoor.x) + 1
					&& possibledoor.x <= (testdoor.x) + 8)
				{
					if (possibledoor.roomnum1 != testdoor.roomnum1
							&& possibledoor.roomnum2 != testdoor.roomnum1
							&& possibledoor.direction != testdoor.direction)
						{
							return 1;
						}
				}
			break;
		case 2:
			if (possibledoor.x >= (testdoor.x) - 5
					&& possibledoor.x <= (testdoor.x) + 5
					&& possibledoor.y <= (testdoor.y) - 1
					&& possibledoor.y >= (testdoor.y) - 8)
				{
					if (possibledoor.roomnum1 != testdoor.roomnum1
							&& possibledoor.roomnum2 != testdoor.roomnum1
							&& possibledoor.direction != testdoor.direction)
						{
							return 1;
						}
				}
			break;
		case 3:
			if (possibledoor.y >= (testdoor.y) - 5
					&& possibledoor.y <= (testdoor.y) + 5
					&& possibledoor.x <= (testdoor.x) - 1
					&& possibledoor.x >= (testdoor.x) - 8)
				{
					if (possibledoor.roomnum1 != testdoor.roomnum1
							&& possibledoor.roomnum2 != testdoor.roomnum1
							&& possibledoor.direction != testdoor.direction)
						{
							return 1;
						}
				}
			break;
		}
	return 0;
}

int confirmoverlap (Room * roomsizetab, Room newroom, int roomcount)
{
	for (int i = 0; i < roomcount; i++)
		{
			if (((newroom.ymin >= roomsizetab[i].ymin - 1
						&& newroom.ymin <= roomsizetab[i].ymax + 1)
					 || (newroom.ymax >= roomsizetab[i].ymin - 1
							 && newroom.ymax <= roomsizetab[i].ymax + 1))
					&&
					((newroom.xmin >= roomsizetab[i].xmin - 1
						&& newroom.xmin <= roomsizetab[i].xmax + 1)
					 || (newroom.xmax >= roomsizetab[i].xmin - 1
							 && newroom.xmax <= roomsizetab[i].xmax + 1)))
				{
					return 0;							//overlap
				}
		}
	return 1;											//no overlap
}

int
	confirmdoorloc (Door * tabdoor, Door testdoor, int doorcount,
									Room * roomsizetab, int roomcount)
{
	for (int i = 0; i < doorcount; i++)
		{
			if (testdoor.x <= tabdoor[i].x + 4
					&& testdoor.x >= tabdoor[i].x - 4
					&& testdoor.y <= tabdoor[i].y + 4
					&& testdoor.y >= tabdoor[i].y - 4
					&& tabdoor[i].direction != testdoor.direction)
				{
					for (int j = 0; j < roomcount; j++)
						{
							switch (testdoor.direction)
								{
								case 0:
									if (((testdoor.y + 1 >= roomsizetab[j].ymin
												&& testdoor.y + 1 <= roomsizetab[j].ymax)
											 || (testdoor.y + 5 >= roomsizetab[j].ymin
													 && testdoor.y + 5 <= roomsizetab[j].ymax))
											&&
											((testdoor.x - 3 >= roomsizetab[j].xmin
												&& testdoor.x - 3 <= roomsizetab[j].xmax)
											 || (testdoor.x + 3 >= roomsizetab[j].xmin
													 && testdoor.x + 3 <= roomsizetab[j].xmax)))
										{
											return 0;
										}
									break;
								case 1:
									if (((testdoor.y - 3 >= roomsizetab[j].ymin
												&& testdoor.y - 3 <= roomsizetab[j].ymax)
											 || (testdoor.y + 3 >= roomsizetab[j].ymin
													 && testdoor.y + 3 <= roomsizetab[j].ymax))
											&&
											((testdoor.x + 1 >= roomsizetab[j].xmin
												&& testdoor.x + 1 <= roomsizetab[j].xmax)
											 || (testdoor.x + 5 >= roomsizetab[j].xmin
													 && testdoor.x + 5 <= roomsizetab[j].xmax)))
										{
											return 0;
										}
									break;
								case 2:
									if (((testdoor.y - 1 >= roomsizetab[j].ymin
												&& testdoor.y - 1 <= roomsizetab[j].ymax)
											 || (testdoor.y - 5 >= roomsizetab[j].ymin
													 && testdoor.y - 5 <= roomsizetab[j].ymax))
											&&
											((testdoor.x - 3 >= roomsizetab[j].xmin
												&& testdoor.x - 3 <= roomsizetab[j].xmax)
											 || (testdoor.x + 3 >= roomsizetab[j].xmin
													 && testdoor.x + 3 <= roomsizetab[j].xmax)))
										{
											return 0;
										}
									break;
								case 3:
									if (((testdoor.y - 3 >= roomsizetab[j].ymin
												&& testdoor.y - 3 <= roomsizetab[j].ymax)
											 || (testdoor.y + 3 >= roomsizetab[j].ymin
													 && testdoor.y + 3 <= roomsizetab[j].ymax))
											&&
											((testdoor.x - 1 >= roomsizetab[j].xmin
												&& testdoor.x - 1 <= roomsizetab[j].xmax)
											 || (testdoor.x - 5 >= roomsizetab[j].xmin
													 && testdoor.x - 5 <= roomsizetab[j].xmax)))
										{
											return 0;
										}
									break;
								}
						}										//not allowed
				}
		}
	return 1;											//allowed
}

int
	confirmdoororientation (Room * roomsizetab, Room newroom, int roomcount,
													Door prevdoor)
{
	for (int j = 0; j < 4; j++)
		{
			if (newroom.roomdoor[j] == 1 && (prevdoor.direction + 2) % 4 != j)
				{
					for (int i = 0; i < roomcount; i++)
						{
							switch (j)
								{
								case 0:
									if ((newroom.ymax + 5 >= roomsizetab[i].ymin
											 && newroom.ymax + 5 <= roomsizetab[i].ymax)
											&& (newroom.ymax + 3 >= roomsizetab[i].ymin
													&& newroom.ymax + 3 <= roomsizetab[i].ymax)
											&&
											((newroom.xmin - 1 >= roomsizetab[i].xmin
												&& newroom.xmin - 1 <= roomsizetab[i].xmax)
											 || (newroom.xmax + 1 >= roomsizetab[i].xmin
													 && newroom.xmax + 1 <= roomsizetab[i].xmax)))
										{
											return 0;
										}
									break;
								case 1:
									if (((newroom.ymin - 1 >= roomsizetab[i].ymin
												&& newroom.ymin - 1 <= roomsizetab[i].ymax)
											 || (newroom.ymax + 1 >= roomsizetab[i].ymin
													 && newroom.ymax + 1 <= roomsizetab[i].ymax))
											&& (newroom.xmax + 5 >= roomsizetab[i].xmin
													&& newroom.xmax + 5 <= roomsizetab[i].xmax)
											&& (newroom.xmax + 3 >= roomsizetab[i].xmin
													&& newroom.xmax + 3 <= roomsizetab[i].xmax))
										{
											return 0;
										}
									break;
								case 2:
									if ((newroom.ymin - 5 >= roomsizetab[i].ymin
											 && newroom.ymin - 5 <= roomsizetab[i].ymax)
											&& (newroom.ymin - 3 >= roomsizetab[i].ymin
													&& newroom.ymin - 3 <= roomsizetab[i].ymax)
											&&
											((newroom.xmin - 1 >= roomsizetab[i].xmin
												&& newroom.xmin - 1 <= roomsizetab[i].xmax)
											 || (newroom.xmax + 1 >= roomsizetab[i].xmin
													 && newroom.xmax + 1 <= roomsizetab[i].xmax)))
										{
											return 0;
										}
									break;
								case 3:
									if (((newroom.ymin - 1 >= roomsizetab[i].ymin
												&& newroom.ymin - 1 <= roomsizetab[i].ymax)
											 || (newroom.ymax + 1 >= roomsizetab[i].ymin
													 && newroom.ymax + 1 <= roomsizetab[i].ymax))
											&&
											(newroom.xmin - -5 >= roomsizetab[i].xmin
											 && newroom.xmin - 5 <= roomsizetab[i].xmax)
											&& (newroom.xmin - 3 >= roomsizetab[i].xmin
													&& newroom.xmin - 3 <= roomsizetab[i].xmax))
										{
											return 0;
										}
									break;
								}

						}
				}
		}
	return 1;

}

int
	adaptnextsizeroomfuse (Room * newroom, int roomcount,
												 Door * tabdoor, Door testdoor, int doorcount)
{
	int countdoor;
	for (int i = 0; i < doorcount; i++)
		{
			if (tabdoor[i].direction != testdoor.direction
					&& searchreallyneardoor (tabdoor[i], testdoor) > 0)
				{
					switch (testdoor.direction)
						{
						case 0:
							switch (tabdoor[i].direction)
								{
								case 1:
									newroom->xmin = tabdoor[i].x + 1;
									tabdoor[i].roomnum2 = roomcount;
									countdoor++;
									newroom->roomdoor[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 2:
									newroom->ymax = tabdoor[i].y - 1;
									tabdoor[i].roomnum2 = roomcount;
									countdoor++;
									newroom->roomdoor[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 3:
									newroom->xmax = tabdoor[i].x - 1;
									tabdoor[i].roomnum2 = roomcount;
									countdoor++;
									newroom->roomdoor[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						case 1:
							switch (tabdoor[i].direction)
								{
								case 0:
									newroom->ymin = tabdoor[i].y + 1;
									tabdoor[i].roomnum2 = roomcount;
									countdoor++;
									newroom->roomdoor[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 2:
									newroom->ymax = tabdoor[i].y - 1;
									tabdoor[i].roomnum2 = roomcount;
									countdoor++;
									newroom->roomdoor[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 3:
									newroom->xmax = tabdoor[i].x - 1;
									tabdoor[i].roomnum2 = roomcount;
									countdoor++;
									newroom->roomdoor[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						case 2:
							switch (tabdoor[i].direction)
								{
								case 0:
									newroom->ymin = tabdoor[i].y + 1;
									tabdoor[i].roomnum2 = roomcount;
									countdoor++;
									newroom->roomdoor[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 1:
									newroom->xmin = tabdoor[i].x + 1;
									tabdoor[i].roomnum2 = roomcount;
									countdoor++;
									newroom->roomdoor[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 3:
									newroom->xmax = tabdoor[i].x - 1;
									tabdoor[i].roomnum2 = roomcount;
									countdoor++;
									newroom->roomdoor[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						case 3:
							switch (tabdoor[i].direction)
								{
								case 0:
									newroom->ymin = tabdoor[i].y + 1;
									tabdoor[i].roomnum2 = roomcount;
									countdoor++;
									newroom->roomdoor[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 1:
									newroom->xmin = tabdoor[i].x + 1;
									tabdoor[i].roomnum2 = roomcount;
									countdoor++;
									newroom->roomdoor[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 2:
									newroom->ymax = tabdoor[i].y - 1;
									tabdoor[i].roomnum2 = roomcount;
									countdoor++;
									newroom->roomdoor[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						}
				}
		}
	return countdoor;
}


Room
	generateroom (int *seed, int *maxroom, Room * tabroom,
								Door * prevdoor, int *roomcount, Door * tabdoor,
								int *doorcount)
{
	Room newroom;
	int randtamp, directionindex, randtamp2, doornum = *doorcount;
	prevdoor->roomnum2 = *roomcount;
	newroom.numofdoor = 1;

	for (int i = 0; i < 4; i++)
		{
			newroom.roomdoor[i] = -1;
		}
	newroom.roomdoor[(prevdoor->direction + 2) % 4] = 1;
	for (int i = 0; i < *doorcount; i++)
		{
			if (searchreallyneardoor (tabdoor[i], *prevdoor) > 0)
				{
					newroom.numofdoor++;
				}
		}
	if (newroom.numofdoor > 1)
		{
			newroom.xmax = 0;
			newroom.xmin = 0;
			newroom.ymax = 0;
			newroom.ymin = 0;
			adaptnextsizeroomfuse (&newroom, *roomcount, tabdoor,
														 *prevdoor, *doorcount);
			do
				{
					switch (prevdoor->direction)
						{
						case 0:
							newroom.ymin = prevdoor->y + 1;
							if (newroom.xmin == 0)
								{
									newroom.xmin = prevdoor->x - 5 + (rand () % 3);
								}
							if (newroom.xmax == 0)
								{
									newroom.xmax = prevdoor->x + 5 - (rand () % 3);
								}
							if (newroom.ymax == 0)
								{
									newroom.ymax = newroom.ymin + 4 + (rand () % 5);
								}
							break;
						case 1:
							newroom.xmin = prevdoor->x + 1;
							if (newroom.xmax == 0)
								{
									newroom.xmax = newroom.xmin + 4 + (rand () % 5);
								}
							if (newroom.ymin == 0)
								{
									newroom.ymin = prevdoor->y - 5 + (rand () % 3);
								}
							if (newroom.ymax == 0)
								{
									newroom.ymax = prevdoor->y + 5 - (rand () % 3);
								}
							break;
						case 2:
							newroom.ymax = prevdoor->y - 1;
							if (newroom.xmin == 0)
								{
									newroom.xmin = prevdoor->x - 5 + (rand () % 3);
								}
							if (newroom.xmax == 0)
								{
									newroom.xmax = prevdoor->x + 5 - (rand () % 3);
								}
							if (newroom.ymin == 0)
								{
									newroom.ymin = newroom.ymax - 4 - (rand () % 5);
								}
							break;
						case 3:
							newroom.xmax = prevdoor->x - 1;
							if (newroom.xmin == 0)
								{
									newroom.xmin = newroom.xmax - 4 - (rand () % 5);
								}
							if (newroom.ymin == 0)
								{
									newroom.ymin = prevdoor->y - 5 + (rand () % 3);
								}
							if (newroom.ymax == 0)
								{
									newroom.ymax = prevdoor->y + 5 - (rand () % 3);
								}
							break;
						}

				}
			while (confirmoverlap (tabroom, newroom, *roomcount) == 0);
		}														//connecting rooms
	else if (searchneardoor (tabdoor, *prevdoor, *doorcount) > 0)
		{
			directionindex = 0;
			do
				{
					switch (prevdoor->direction)
						{
						case 0:
							newroom.xmin = prevdoor->x - 3 + (rand () % 3);
							newroom.xmax = prevdoor->x + 3 - (rand () % 3);
							newroom.ymin = prevdoor->y + 1;
							newroom.ymax = newroom.ymin + 3 + (rand () % 4);
							break;
						case 1:
							newroom.xmin = prevdoor->x + 1;
							newroom.xmax = newroom.xmin + 3 + (rand () % 4);
							newroom.ymin = prevdoor->y - 3 + (rand () % 3);
							newroom.ymax = prevdoor->y + 3 - (rand () % 3);
							break;
						case 2:
							newroom.xmin = prevdoor->x - 3 + (rand () % 3);
							newroom.xmax = prevdoor->x + 3 - (rand () % 3);
							newroom.ymax = prevdoor->y - 1;
							newroom.ymin = newroom.ymax - 3 - (rand () % 4);
							break;
						case 3:
							newroom.xmax = prevdoor->x - 1;
							newroom.xmin = newroom.xmax - 3 - (rand () % 4);
							newroom.ymin = prevdoor->y - 3 + (rand () % 3);
							newroom.ymax = prevdoor->y + 3 - (rand () % 3);
							break;
						}
				}
			while (confirmoverlap (tabroom, newroom, *roomcount) == 0);
			do
				{
					newroom.numofdoor = rand () % 3 + 1;
					for (int i = 0; i < 4; i++)
						{
							newroom.roomdoor[i] = -1;
						}
					newroom.roomdoor[(prevdoor->direction + 2) % 4] = 1;
					while (newroom.numofdoor > MAX_ROOM - *roomcount)
						{
							newroom.numofdoor--;
							switch (newroom.numofdoor)
								{
								case 2:
									randtamp = rand () % 4;
									if (randtamp == (prevdoor->direction + 2) % 4)
										{
											randtamp = (randtamp + 1) % 4;
										}
									newroom.roomdoor[randtamp] = 1;
									break;
								case 3:
									randtamp = rand () % 4;
									if (randtamp == (prevdoor->direction + 2) % 4)
										{
											randtamp = (randtamp + 1) % 4;
										}
									newroom.roomdoor[randtamp] = 1;
									randtamp2 = rand () % 4;
									do
										{
											randtamp2 = (randtamp2 + 1) % 4;
										}
									while (randtamp2 !=
												 (prevdoor->direction + 2) % 4
												 && randtamp2 != randtamp);
									newroom.roomdoor[randtamp2] = 1;
									break;
								}
						}
				}
			while (confirmdoororientation (tabroom, newroom, *roomcount, *prevdoor)
						 == 0);
			for (int i = *doorcount; i < doornum + newroom.numofdoor - 1; i++)
				{
					tabdoor[i].roomnum1 = *roomcount;
					tabdoor[i].roomnum2 = -1;
					while (newroom.roomdoor[directionindex] != 1
								 || directionindex == ((prevdoor->direction) + 2) % 4)
						{
							directionindex = (directionindex + 1) % 4;
						}
					tabdoor[i].direction = directionindex;
					do
						{
							for (int i = 0; i < 4; i++)
								{
									newroom.roomdoor[i] = -1;
								}
							switch (tabdoor[i].direction)
								{
								case 0:
									tabdoor[i].x =
										newroom.xmin + 1 +
										(rand () % (newroom.xmax - newroom.xmin - 1));
									tabdoor[i].y = newroom.ymax + 1;
									break;
								case 1:
									tabdoor[i].x = newroom.xmax + 1;
									tabdoor[i].y =
										newroom.ymin + 1 +
										(rand () % (newroom.ymax - newroom.ymin - 1));
									break;
								case 2:
									tabdoor[i].x =
										newroom.xmin + 1 +
										(rand () % (newroom.xmax - newroom.xmin - 1));
									tabdoor[i].y = newroom.ymin - 1;
									break;
								case 3:
									tabdoor[i].x = newroom.xmin - 1;
									tabdoor[i].y =
										newroom.ymin + 1 +
										(rand () % (newroom.ymax - newroom.ymin - 1));
									break;
								}
						}
					while (confirmdoorloc
								 (tabdoor, tabdoor[i], *doorcount, tabroom, *roomcount) == 0);
					directionindex++;
					(*doorcount)++;
				}
		}														//near rooms
	else
		{
			directionindex = 0;
			switch (prevdoor->direction)
				{
				case 0:
					newroom.xmin = prevdoor->x - 4 + (rand () % 4);
					newroom.xmax = prevdoor->x + 4 - (rand () % 4);
					newroom.ymin = prevdoor->y + 1;
					newroom.ymax = newroom.ymin + 3 + (rand () % 6);
					break;
				case 1:
					newroom.xmin = prevdoor->x + 1;
					newroom.xmax = newroom.xmin + 3 + (rand () % 6);
					newroom.ymin = prevdoor->y - 4 + (rand () % 4);
					newroom.ymax = prevdoor->y + 4 - (rand () % 4);
					break;
				case 2:
					newroom.xmin = prevdoor->x - 4 + (rand () % 4);
					newroom.xmax = prevdoor->x + 4 - (rand () % 4);
					newroom.ymax = prevdoor->y - 1;
					newroom.ymin = newroom.ymax - 3 - (rand () % 6);
					break;
				case 3:
					newroom.xmax = prevdoor->x - 1;
					newroom.xmin = newroom.xmax - 3 - (rand () % 6);
					newroom.ymin = prevdoor->y - 4 + (rand () % 4);
					newroom.ymax = prevdoor->y + 4 - (rand () % 4);
					break;
				}
			while (confirmoverlap (tabroom, newroom, *roomcount) == 0);
			do
				{
					for (int i = 0; i < 4; i++)
						{
							newroom.roomdoor[i] = -1;
						}
					newroom.roomdoor[(prevdoor->direction + 2) % 4] = 1;
					newroom.numofdoor = rand () % 3 + 2;
					while (newroom.numofdoor > MAX_ROOM - *roomcount)
						{
							newroom.numofdoor--;
						}
					switch (newroom.numofdoor)
						{
						case 2:
							randtamp = rand () % 4;
							if (randtamp == (prevdoor->direction + 2) % 4)
								{
									randtamp = (randtamp + 1) % 4;
								}
							newroom.roomdoor[randtamp] = 1;
							break;
						case 3:
							randtamp = rand () % 4;
							if (randtamp == (prevdoor->direction + 2) % 4)
								{
									randtamp = (randtamp + 1) % 4;
								}
							newroom.roomdoor[randtamp] = 1;
							randtamp2 = rand () % 4;
							do
								{
									randtamp2 = (randtamp2 + 1) % 4;
								}
							while (randtamp2 ==
										 (prevdoor->direction + 2) % 4 || randtamp2 == randtamp);
							newroom.roomdoor[randtamp2] = 1;
							break;
						case 4:
							for (int i = 0; i < 4; i++)
								{
									newroom.roomdoor[i] = 1;
								}
						}
				}
			while (confirmdoororientation (tabroom, newroom, *roomcount, *prevdoor)
						 == 0);
			for (int i = *doorcount; i < doornum + newroom.numofdoor - 1; i++)
				{
					tabdoor[i].roomnum1 = *roomcount;
					tabdoor[i].roomnum2 = -1;
					while (newroom.roomdoor[directionindex] != 1
								 || directionindex == ((prevdoor->direction) + 2) % 4)
						{
							directionindex = (directionindex + 1) % 4;
						}
					tabdoor[i].direction = directionindex;
					do
						{
							switch (tabdoor[i].direction)
								{
								case 0:
									tabdoor[i].x =
										newroom.xmin + 1 +
										(rand () % (newroom.xmax - newroom.xmin - 1));
									tabdoor[i].y = newroom.ymax + 1;
									break;
								case 1:
									tabdoor[i].x = newroom.xmax + 1;
									tabdoor[i].y =
										newroom.ymin + 1 +
										(rand () % (newroom.ymax - newroom.ymin - 1));
									break;
								case 2:
									tabdoor[i].x =
										newroom.xmin + 1 +
										(rand () % (newroom.xmax - newroom.xmin - 1));
									tabdoor[i].y = newroom.ymin - 1;
									break;
								case 3:
									tabdoor[i].x = newroom.xmin - 1;
									tabdoor[i].y =
										newroom.ymin + 1 +
										(rand () % (newroom.ymax - newroom.ymin - 1));
									break;
								}
						}
					while (confirmdoorloc
								 (tabdoor, tabdoor[i], *doorcount, tabroom, *roomcount) == 0);
					(*doorcount)++;
					directionindex++;
				}
		}

	(*roomcount)++;
	return newroom;
}

Room
createmainroom ()
{
	Room froom;
	for (int j = 0; j < 4; j++)
		{
			froom.roomdoor[j] = 1;
		}
	froom.numofdoor = 4;
	froom.xmin = 1 * -4;
	froom.xmax = 1 * 5;
	froom.ymin = 1 * -4;
	froom.ymax = 1 * 5;

	return froom;
}

void
createmaindoor (Door * tabdoor)
{
	tabdoor[0].x = 0;
	tabdoor[0].y = 6;
	tabdoor[0].roomnum1 = 0;
	tabdoor[0].roomnum2 = -1;
	tabdoor[0].direction = 0;
	tabdoor[1].x = 6;
	tabdoor[1].y = 0;
	tabdoor[1].roomnum1 = 0;
	tabdoor[1].roomnum2 = -1;
	tabdoor[1].direction = 1;
	tabdoor[2].x = 0;
	tabdoor[2].y = -5;
	tabdoor[2].roomnum1 = 0;
	tabdoor[2].roomnum2 = -1;
	tabdoor[2].direction = 2;
	tabdoor[3].x = -5;
	tabdoor[3].y = 0;
	tabdoor[3].roomnum1 = 0;
	tabdoor[3].roomnum2 = -1;
	tabdoor[3].direction = 3;
}

int
main ()
{
	int seed = 999;
	srand (seed);
	int grid[MAX_ROOM * 13][MAX_ROOM * 13];
	int maxroom = MAX_ROOM;
	int roomcount = 1;
	int doorcount = 4;
	Room *tabroom;
	Door *tabdoor;
	tabdoor = calloc (MAX_ROOM * 4, sizeof (Door));
	if (tabdoor == NULL)
		{
			exit (1);
		}
	tabroom = calloc (MAX_ROOM, sizeof (Room));
	if (tabroom == NULL)
		{
			exit (1);
		}
	createmainroom ();
	createmaindoor (tabdoor);
	tabroom[0] = createmainroom ();
	tabroom[roomcount] =
		generateroom (&seed, &maxroom, tabroom, &tabdoor[3],
									&roomcount, tabdoor, &doorcount);
	tabroom[roomcount] =
		generateroom (&seed, &maxroom, tabroom, &tabdoor[4],
									&roomcount, tabdoor, &doorcount);
	tabroom[roomcount] =
		generateroom (&seed, &maxroom, tabroom, &tabdoor[5], &roomcount, tabdoor,
									&doorcount);
	tabroom[roomcount] =
		generateroom (&seed, &maxroom, tabroom, &tabdoor[7], &roomcount, tabdoor,
									&doorcount);
	tabroom[roomcount] =
		generateroom (&seed, &maxroom, tabroom, &tabdoor[6], &roomcount, tabdoor,
									&doorcount);
  tabroom[roomcount] =
		generateroom (&seed, &maxroom, tabroom, &tabdoor[9], &roomcount, tabdoor,
									&doorcount);
	printf ("%d", tabroom[1].roomdoor[0]);
	printf ("%d", tabroom[1].roomdoor[1]);
	printf ("%d", tabroom[1].roomdoor[2]);
	printf ("%d", tabroom[1].roomdoor[3]);
	printf ("%d", tabroom[1].numofdoor);
	//printf("%d",tabroom[roomcount].xmin);
	//printf("%d",tabroom[roomcount].xmax);
	/*for(int i=0; i<doorcount; i++){
	   printroomset(tabroom, tabdoor, doorcount, i, grid);
	   }
	   printgrid(grid); */
	return 0;
}

