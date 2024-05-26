#include "params.h"

Room createMainRoom() {
  Room fRoom;
  for (int j = 0; j < 4; j++) {
    fRoom.room_door[j] = 1;
  }
  fRoom.num_door = 4;
  fRoom.x_min = 1 * -4;
  fRoom.x_max = 1 * 5;
  fRoom.y_min = 1 * -4;
  fRoom.y_max = 1 * 5;
  fRoom.nbr_enemy=0;
  fRoom.nbr_object=0;
  fRoom.nbr_armor=0;
  fRoom.nbr_blade=0;
  return fRoom;
}
  
void createMainDoor(Door *tabDoor) {
  tabDoor[0].x = 0;
  tabDoor[0].y = 6;
  tabDoor[0].room_num1 = 0;
  tabDoor[0].room_num2 = -1;
  tabDoor[0].direction = 0;
  tabDoor[1].x = 6;
  tabDoor[1].y = 0;
  tabDoor[1].room_num1 = 0;
  tabDoor[1].room_num2 = -1;
  tabDoor[1].direction = 1;
  tabDoor[2].x = 0;
  tabDoor[2].y = -5;
  tabDoor[2].room_num1 = 0;
  tabDoor[2].room_num2 = -1;
  tabDoor[2].direction = 2;
  tabDoor[3].x = -5;
  tabDoor[3].y = 0;
  tabDoor[3].room_num1 = 0;
  tabDoor[3].room_num2 = -1;
  tabDoor[3].direction = 3;
}


int
searchNearDoor (Door * tabDoor, Door testDoor, int Doorcount)
{
	for (int i = 0; i < Doorcount; i++)
		{
			switch (testDoor.direction)
				{
				case 0:
					if (tabDoor[i].x >= (testDoor.x) - 6
							&& tabDoor[i].x <= (testDoor.x) + 6
							&& tabDoor[i].y >= (testDoor.y) + 1
							&& tabDoor[i].y <= (testDoor.y) + 9
						&& tabDoor[i].direction != testDoor.direction)
						{
							if (tabDoor[i].room_num1 != testDoor.room_num1
									&& tabDoor[i].room_num2 != testDoor.room_num1
									&& tabDoor[i].direction != testDoor.direction)
								{
									return 1;
								}
						}
					break;
				case 1:
					if (tabDoor[i].y >= (testDoor.y) - 6
							&& tabDoor[i].y <= (testDoor.y) + 6
							&& tabDoor[i].x >= (testDoor.x) + 1
							&& tabDoor[i].x <= (testDoor.x) + 9
						&&tabDoor[i].direction != testDoor.direction)
						{
							if (tabDoor[i].room_num1 != testDoor.room_num1
									&& tabDoor[i].room_num2 != testDoor.room_num1
									&& tabDoor[i].direction != testDoor.direction)
								{
									return 1;
								}
						}
					break;
				case 2:
					if (tabDoor[i].x >= (testDoor.x) - 6
							&& tabDoor[i].x <= (testDoor.x) + 6
							&& tabDoor[i].y <= (testDoor.y) - 1
							&& tabDoor[i].y >= (testDoor.y) - 9
						&& tabDoor[i].direction != testDoor.direction)
						{
							if (tabDoor[i].room_num1 != testDoor.room_num1
									&& tabDoor[i].room_num2 != testDoor.room_num1
									&& tabDoor[i].direction != testDoor.direction)
								{
									return 1;
								}
						}
					break;
				case 3:
					if (tabDoor[i].y >= (testDoor.y) - 6
							&& tabDoor[i].y <= (testDoor.y) + 6
							&& tabDoor[i].x <= (testDoor.x) - 1
							&& tabDoor[i].x >= (testDoor.x) - 9
						&& tabDoor[i].direction != testDoor.direction)
						{
							if (tabDoor[i].room_num1 != testDoor.room_num1
									&& tabDoor[i].room_num2 != testDoor.room_num1
									&& tabDoor[i].direction != testDoor.direction)
								{
									return 1;
								}
						}
					break;
				}
		}
	return 0;
}



int searchReallyNearDoor (Door possibleDoor, Door testDoor)
{
	switch (testDoor.direction)
		{
		case 0:
			if (possibleDoor.x >= (testDoor.x) - 5
					&& possibleDoor.x <= (testDoor.x) + 5
					&& possibleDoor.y >= (testDoor.y) + 1
					&& possibleDoor.y <= (testDoor.y) + 8
					&& possibleDoor.direction != testDoor.direction)
				{
					if (possibleDoor.room_num1 != testDoor.room_num1
							&& possibleDoor.room_num2 != testDoor.room_num1
							&& possibleDoor.direction != testDoor.direction)
						{
							return 1;
						}
				}
			break;
		case 1:
			if (possibleDoor.y >= (testDoor.y) - 5
					&& possibleDoor.y <= (testDoor.y) + 5
					&& possibleDoor.x >= (testDoor.x) + 1
					&& possibleDoor.x <= (testDoor.x) + 8)
				{
					if (possibleDoor.room_num1 != testDoor.room_num1
							&& possibleDoor.room_num2 != testDoor.room_num1
							&& possibleDoor.direction != testDoor.direction)
						{
							return 1;
						}
				}
			break;
		case 2:
			if (possibleDoor.x >= (testDoor.x) - 5
					&& possibleDoor.x <= (testDoor.x) + 5
					&& possibleDoor.y <= (testDoor.y) - 1
					&& possibleDoor.y >= (testDoor.y) - 8)
				{
					if (possibleDoor.room_num1 != testDoor.room_num1
							&& possibleDoor.room_num2 != testDoor.room_num1
							&& possibleDoor.direction != testDoor.direction)
						{
							return 1;
						}
				}
			break;
		case 3:
			if (possibleDoor.y >= (testDoor.y) - 5
					&& possibleDoor.y <= (testDoor.y) + 5
					&& possibleDoor.x <= (testDoor.x) - 1
					&& possibleDoor.x >= (testDoor.x) - 8)
				{
					if (possibleDoor.room_num1 != testDoor.room_num1
							&& possibleDoor.room_num2 != testDoor.room_num1
							&& possibleDoor.direction != testDoor.direction)
						{
							return 1;
						}
				}
			break;
		}
	return 0;
}

int confirmOverlap (Room * Roomsizetab, Room newRoom, int Roomcount)
{
	for (int i = 0; i < Roomcount; i++)
		{
			if (((newRoom.y_min >= (Roomsizetab[i].y_min - 1)
						&& newRoom.y_min <= (Roomsizetab[i].y_max + 1))
					 || (newRoom.y_max >= (Roomsizetab[i].y_min - 1)
							 && newRoom.y_max <= (Roomsizetab[i].y_max + 1)))
					&&
					((newRoom.x_min >= (Roomsizetab[i].x_min - 1)
						&& newRoom.x_min <= (Roomsizetab[i].x_max + 1))
					 || (newRoom.x_max >= (Roomsizetab[i].x_min - 1)
							 && newRoom.x_max <= (Roomsizetab[i].x_max + 1))))
				{
					return 0;							//overlap
				}
		}
	return 1;											//no overlap
}

int
	confirmDoorLock (Door * tabDoor, Door testDoor, int Doorcount, Room * Roomsizetab, int Roomcount)
{

	for (int i = 0; i < Doorcount; i++)
		{ 

			if (testDoor.x <= tabDoor[i].x + 4
					&& testDoor.x >= tabDoor[i].x - 4
					&& testDoor.y <= tabDoor[i].y + 4
					&& testDoor.y >= tabDoor[i].y - 4
					&& tabDoor[i].direction != testDoor.direction)
				{
					for (int j = 0; j < Roomcount; j++)
						{

							switch (testDoor.direction)
								{
								case 0:
									if (((testDoor.y + 1 >= Roomsizetab[j].y_min
												&& testDoor.y + 1 <= Roomsizetab[j].y_max)
											 || (testDoor.y + 5 >= Roomsizetab[j].y_min
													 && testDoor.y + 5 <= Roomsizetab[j].y_max))
											&&
											((testDoor.x - 3 >= Roomsizetab[j].x_min
												&& testDoor.x - 3 <= Roomsizetab[j].x_max)
											 || (testDoor.x + 3 >= Roomsizetab[j].x_min
													 && testDoor.x + 3 <= Roomsizetab[j].x_max)))
										{
											return 0;
										}
									break;
								case 1:
									if (((testDoor.y - 3 >= Roomsizetab[j].y_min
												&& testDoor.y - 3 <= Roomsizetab[j].y_max)
											 || (testDoor.y + 3 >= Roomsizetab[j].y_min
													 && testDoor.y + 3 <= Roomsizetab[j].y_max))
											&&
											((testDoor.x + 1 >= Roomsizetab[j].x_min
												&& testDoor.x + 1 <= Roomsizetab[j].x_max)
											 || (testDoor.x + 5 >= Roomsizetab[j].x_min
													 && testDoor.x + 5 <= Roomsizetab[j].x_max)))
										{
											return 0;
										}
									break;
								case 2:
									if (((testDoor.y - 1 >= Roomsizetab[j].y_min
												&& testDoor.y - 1 <= Roomsizetab[j].y_max)
											 || (testDoor.y - 5 >= Roomsizetab[j].y_min
													 && testDoor.y - 5 <= Roomsizetab[j].y_max))
											&&
											((testDoor.x - 3 >= Roomsizetab[j].x_min
												&& testDoor.x - 3 <= Roomsizetab[j].x_max)
											 || (testDoor.x + 3 >= Roomsizetab[j].x_min
													 && testDoor.x + 3 <= Roomsizetab[j].x_max)))
										{
											return 0;
										}
									break;
								case 3:
									if (((testDoor.y - 3 >= Roomsizetab[j].y_min
												&& testDoor.y - 3 <= Roomsizetab[j].y_max)
											 || (testDoor.y + 3 >= Roomsizetab[j].y_min
													 && testDoor.y + 3 <= Roomsizetab[j].y_max))
											&&
											((testDoor.x - 1 >= Roomsizetab[j].x_min
												&& testDoor.x - 1 <= Roomsizetab[j].x_max)
											 || (testDoor.x - 5 >= Roomsizetab[j].x_min
													 && testDoor.x - 5 <= Roomsizetab[j].x_max)))
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

int confirmDoororientation (Room * Roomsizetab, Room newRoom, int Roomcount,
													Door prevDoor)
{
	for (int j = 0; j < 4; j++)
		{
			if (newRoom.room_door[j] == 1 && (prevDoor.direction + 2) % 4 != j)
				{
					for (int i = 0; i < Roomcount; i++)
						{
							switch (j)
								{
								case 0:
									if ((newRoom.y_max + 5 >= Roomsizetab[i].y_min
											 && newRoom.y_max + 5 <= Roomsizetab[i].y_max)
											&& (newRoom.y_max + 3 >= Roomsizetab[i].y_min
													&& newRoom.y_max + 3 <= Roomsizetab[i].y_max)
											&&
											((newRoom.x_min - 1 >= Roomsizetab[i].x_min
												&& newRoom.x_min - 1 <= Roomsizetab[i].x_max)
											 || (newRoom.x_max + 1 >= Roomsizetab[i].x_min
													 && newRoom.x_max + 1 <= Roomsizetab[i].x_max)))
										{
											return 0;
										}
									break;
								case 1:
									if (((newRoom.y_min - 1 >= Roomsizetab[i].y_min
												&& newRoom.y_min - 1 <= Roomsizetab[i].y_max)
											 || (newRoom.y_max + 1 >= Roomsizetab[i].y_min
													 && newRoom.y_max + 1 <= Roomsizetab[i].y_max))
											&& (newRoom.x_max + 5 >= Roomsizetab[i].x_min
													&& newRoom.x_max + 5 <= Roomsizetab[i].x_max)
											&& (newRoom.x_max + 3 >= Roomsizetab[i].x_min
													&& newRoom.x_max + 3 <= Roomsizetab[i].x_max))
										{
											return 0;
										}
									break;
								case 2:
									if ((newRoom.y_min - 5 >= Roomsizetab[i].y_min
											 && newRoom.y_min - 5 <= Roomsizetab[i].y_max)
											&& (newRoom.y_min - 3 >= Roomsizetab[i].y_min
													&& newRoom.y_min - 3 <= Roomsizetab[i].y_max)
											&&
											((newRoom.x_min - 1 >= Roomsizetab[i].x_min
												&& newRoom.x_min - 1 <= Roomsizetab[i].x_max)
											 || (newRoom.x_max + 1 >= Roomsizetab[i].x_min
													 && newRoom.x_max + 1 <= Roomsizetab[i].x_max)))
										{
											return 0;
										}
									break;
								case 3:
									if (((newRoom.y_min - 1 >= Roomsizetab[i].y_min
												&& newRoom.y_min - 1 <= Roomsizetab[i].y_max)
											 || (newRoom.y_max + 1 >= Roomsizetab[i].y_min
													 && newRoom.y_max + 1 <= Roomsizetab[i].y_max))
											&&
											(newRoom.x_min - -5 >= Roomsizetab[i].x_min
											 && newRoom.x_min - 5 <= Roomsizetab[i].x_max)
											&& (newRoom.x_min - 3 >= Roomsizetab[i].x_min
													&& newRoom.x_min - 3 <= Roomsizetab[i].x_max))
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
	adaptNextSizeRoomFuse (Room * newRoom, int Roomcount,
												 Door * tabDoor, Door testDoor, int Doorcount)
{
	int countDoor;
	for (int i = 0; i < Doorcount; i++)
		{
			if (tabDoor[i].direction != testDoor.direction
					&& searchReallyNearDoor (tabDoor[i], testDoor) > 0)
				{
					switch (testDoor.direction)
						{
						case 0:
							switch (tabDoor[i].direction)
								{
								case 1:
									newRoom->x_min = tabDoor[i].x + 1;
									tabDoor[i].room_num2 = Roomcount;
									countDoor++;
									newRoom->room_door[((tabDoor[i].direction) + 2) % 4] = 1;
									break;
								case 2:
									newRoom->y_max = tabDoor[i].y - 1;
									tabDoor[i].room_num2 = Roomcount;
									countDoor++;
									newRoom->room_door[((tabDoor[i].direction) + 2) % 4] = 1;
									break;
								case 3:
									newRoom->x_max = tabDoor[i].x - 1;
									tabDoor[i].room_num2 = Roomcount;
									countDoor++;
									newRoom->room_door[((tabDoor[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						case 1:
							switch (tabDoor[i].direction)
								{
								case 0:
									newRoom->y_min = tabDoor[i].y + 1;
									tabDoor[i].room_num2 = Roomcount;
									countDoor++;
									newRoom->room_door[((tabDoor[i].direction) + 2) % 4] = 1;
									break;
								case 2:
									newRoom->y_max = tabDoor[i].y - 1;
									tabDoor[i].room_num2 = Roomcount;
									countDoor++;
									newRoom->room_door[((tabDoor[i].direction) + 2) % 4] = 1;
									break;
								case 3:
									newRoom->x_max = tabDoor[i].x - 1;
									tabDoor[i].room_num2 = Roomcount;
									countDoor++;
									newRoom->room_door[((tabDoor[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						case 2:
							switch (tabDoor[i].direction)
								{
								case 0:
									newRoom->y_min = tabDoor[i].y + 1;
									tabDoor[i].room_num2 = Roomcount;
									countDoor++;
									newRoom->room_door[((tabDoor[i].direction) + 2) % 4] = 1;
									break;
								case 1:
									newRoom->x_min = tabDoor[i].x + 1;
									tabDoor[i].room_num2 = Roomcount;
									countDoor++;
									newRoom->room_door[((tabDoor[i].direction) + 2) % 4] = 1;
									break;
								case 3:
									newRoom->x_max = tabDoor[i].x - 1;
									tabDoor[i].room_num2 = Roomcount;
									countDoor++;
									newRoom->room_door[((tabDoor[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						case 3:
							switch (tabDoor[i].direction)
								{
								case 0:
									newRoom->y_min = tabDoor[i].y + 1;
									tabDoor[i].room_num2 = Roomcount;
									countDoor++;
									newRoom->room_door[((tabDoor[i].direction) + 2) % 4] = 1;
									break;
								case 1:
									newRoom->x_min = tabDoor[i].x + 1;
									tabDoor[i].room_num2 = Roomcount;
									countDoor++;
									newRoom->room_door[((tabDoor[i].direction) + 2) % 4] = 1;
									break;
								case 2:
									newRoom->y_max = tabDoor[i].y - 1;
									tabDoor[i].room_num2 = Roomcount;
									countDoor++;
									newRoom->room_door[((tabDoor[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						}
				}
		}
	return countDoor;
}


Room
	generateRoom (int *seed, int *maxRoom, Room * tabRoom,
								Door * prevDoor, int *Roomcount, Door * tabDoor,
								int *Doorcount)
{
	Room newRoom;
	int randtamp, directionindex, randtamp2, Doornum = *Doorcount;
	prevDoor->room_num2 = *Roomcount;
	newRoom.num_door = 1;

	for (int i = 0; i < 4; i++)
		{
			newRoom.room_door[i] = -1;
		}
	newRoom.room_door[(prevDoor->direction + 2) % 4] = 1;
	for (int i = 0; i < *Doorcount; i++)
		{
			if (searchReallyNearDoor (tabDoor[i], *prevDoor) > 0)
				{
					newRoom.num_door++;
				}
		}
//verif
	if (newRoom.num_door > 1)
		{

			newRoom.x_max = 0;
			newRoom.x_min = 0;
			newRoom.y_max = 0;
			newRoom.y_min = 0;
			adaptNextSizeRoomFuse (&newRoom, *Roomcount, tabDoor,
														 *prevDoor, *Doorcount);
			do
				{
					switch (prevDoor->direction)
						{
						case 0:
							newRoom.y_min = prevDoor->y + 1;
							if (newRoom.x_min == 0)
								{
									newRoom.x_min = prevDoor->x - 5 + (rand () % 3);
								}
							if (newRoom.x_max == 0)
								{
									newRoom.x_max = prevDoor->x + 5 - (rand () % 3);
								}
							if (newRoom.y_max == 0)
								{
									newRoom.y_max = newRoom.y_min + 4 + (rand () % 5);
								}
							break;
						case 1:
							newRoom.x_min = prevDoor->x + 1;
							if (newRoom.x_max == 0)
								{
									newRoom.x_max = newRoom.x_min + 4 + (rand () % 5);
								}
							if (newRoom.y_min == 0)
								{
									newRoom.y_min = prevDoor->y - 5 + (rand () % 3);
								}
							if (newRoom.y_max == 0)
								{
									newRoom.y_max = prevDoor->y + 5 - (rand () % 3);
								}
							break;
						case 2:
							newRoom.y_max = prevDoor->y - 1;
							if (newRoom.x_min == 0)
								{
									newRoom.x_min = prevDoor->x - 5 + (rand () % 3);
								}
							if (newRoom.x_max == 0)
								{
									newRoom.x_max = prevDoor->x + 5 - (rand () % 3);
								}
							if (newRoom.y_min == 0)
								{
									newRoom.y_min = newRoom.y_max - 4 - (rand () % 5);
								}
							break;
						case 3:
							newRoom.x_max = prevDoor->x - 1;
							if (newRoom.x_min == 0)
								{
									newRoom.x_min = newRoom.x_max - 4 - (rand () % 5);
								}
							if (newRoom.y_min == 0)
								{
									newRoom.y_min = prevDoor->y - 5 + (rand () % 3);
								}
							if (newRoom.y_max == 0)
								{
									newRoom.y_max = prevDoor->y + 5 - (rand () % 3);
								}
							break;
						}

				}
			while (confirmOverlap (tabRoom, newRoom, *Roomcount) == 0);

        if(*Roomcount==2){
            exit(12);
        }
		}													//connecting Rooms
//verif
	else if (searchNearDoor (tabDoor, *prevDoor, *Doorcount) > 0)
		{

			directionindex = 0;
			do
				{
					switch (prevDoor->direction)
						{
						case 0:
							newRoom.x_min = prevDoor->x - 3 + (rand () % 3);
							newRoom.x_max = prevDoor->x + 3 - (rand () % 3);
							newRoom.y_min = prevDoor->y + 1;
							newRoom.y_max = newRoom.y_min + 3 + (rand () % 4);
							break;
						case 1:
							newRoom.x_min = prevDoor->x + 1;
							newRoom.x_max = newRoom.x_min + 3 + (rand () % 4);
							newRoom.y_min = prevDoor->y - 3 + (rand () % 3);
							newRoom.y_max = prevDoor->y + 3 - (rand () % 3);
							break;
						case 2:
							newRoom.x_min = prevDoor->x - 3 + (rand () % 3);
							newRoom.x_max = prevDoor->x + 3 - (rand () % 3);
							newRoom.y_max = prevDoor->y - 1;
							newRoom.y_min = newRoom.y_max - 3 - (rand () % 4);
							break;
						case 3:
							newRoom.x_max = prevDoor->x - 1;
							newRoom.x_min = newRoom.x_max - 3 - (rand () % 4);
							newRoom.y_min = prevDoor->y - 3 + (rand () % 3);
							newRoom.y_max = prevDoor->y + 3 - (rand () % 3);
							break;
						}
				}
			while (confirmOverlap (tabRoom, newRoom, *Roomcount) == 0);

			do
				{
					newRoom.num_door = rand () % 3 + 1;
					for (int i = 0; i < 4; i++)
						{
							newRoom.room_door[i] = -1;
						}
					newRoom.room_door[(prevDoor->direction + 2) % 4] = 1;
					while (newRoom.num_door > MAX_ROOM - *Roomcount)
						{
							newRoom.num_door--;
							switch (newRoom.num_door)
								{
								case 2:
									randtamp = rand () % 4;
									if (randtamp == (prevDoor->direction + 2) % 4)
										{
											randtamp = (randtamp + 1) % 4;
										}
									newRoom.room_door[randtamp] = 1;
									break;
								case 3:
									randtamp = rand () % 4;
									if (randtamp == (prevDoor->direction + 2) % 4)
										{
											randtamp = (randtamp + 1) % 4;
										}
									newRoom.room_door[randtamp] = 1;
									randtamp2 = rand () % 4;
									do
										{
											randtamp2 = (randtamp2 + 1) % 4;
										}
									while (randtamp2 !=
												 (prevDoor->direction + 2) % 4
												 && randtamp2 != randtamp);
									newRoom.room_door[randtamp2] = 1;
									break;
								}
						}
				}
			while (confirmDoororientation (tabRoom, newRoom, *Roomcount, *prevDoor)
						 == 0);
			for (int i = *Doorcount; i < Doornum + newRoom.num_door - 1; i++)
				{
					tabDoor[i].room_num1 = *Roomcount;
					tabDoor[i].room_num2 = -1;
					while (newRoom.room_door[directionindex] != 1
								 || directionindex == ((prevDoor->direction) + 2) % 4)
						{
							directionindex = (directionindex + 1) % 4;
						}
					tabDoor[i].direction = directionindex;
					do
						{
							for (int i = 0; i < 4; i++)
								{
									newRoom.room_door[i] = -1;
								}
							switch (tabDoor[i].direction)
								{
								case 0:
									tabDoor[i].x =
										newRoom.x_min + 1 +
										(rand () % (newRoom.x_max - newRoom.x_min - 1));
									tabDoor[i].y = newRoom.y_max + 1;
									break;
								case 1:
									tabDoor[i].x = newRoom.x_max + 1;
									tabDoor[i].y =
										newRoom.y_min + 1 +
										(rand () % (newRoom.y_max - newRoom.y_min - 1));
									break;
								case 2:
									tabDoor[i].x =
										newRoom.x_min + 1 +
										(rand () % (newRoom.x_max - newRoom.x_min - 1));
									tabDoor[i].y = newRoom.y_min - 1;
									break;
								case 3:
									tabDoor[i].x = newRoom.x_min - 1;
									tabDoor[i].y =
										newRoom.y_min + 1 +
										(rand () % (newRoom.y_max - newRoom.y_min - 1));
									break;
								}
						}
					while (confirmDoorLock
								 (tabDoor, tabDoor[i], *Doorcount, tabRoom, *Roomcount) == 0);
					directionindex++;
					(*Doorcount)++;
				}
        if(*Roomcount==2){
            exit(12);
        }
		}														//near Rooms
	else
		{         
			directionindex = 0;
            do{
			switch (prevDoor->direction)
				{
				case 0:
					newRoom.x_min = prevDoor->x - 4 + (rand () % 4);
					newRoom.x_max = prevDoor->x + 4 - (rand () % 4);
					newRoom.y_min = prevDoor->y + 1;
					newRoom.y_max = newRoom.y_min + 3 + (rand () % 6);
					break;
				case 1:
					newRoom.x_min = prevDoor->x + 1;
					newRoom.x_max = newRoom.x_min + 3 + (rand () % 6);
					newRoom.y_min = prevDoor->y - 4 + (rand() % 4);
					newRoom.y_max = prevDoor->y + 4 - (rand () % 4);
					break;
				case 2:
					newRoom.x_min = prevDoor->x - 4 + (rand () % 4);
					newRoom.x_max = prevDoor->x + 4 - (rand () % 4);
					newRoom.y_max = prevDoor->y - 1;
					newRoom.y_min = newRoom.y_max - 3 - (rand () % 6);
					break;
				case 3:
					newRoom.x_max = prevDoor->x - 1;
					newRoom.x_min = newRoom.x_max - 3 - (rand () % 6);
					newRoom.y_min = prevDoor->y - 3 + (rand () % 4);
					newRoom.y_max = prevDoor->y + 4 - (rand () % 4);
					break;
				}
            }while (confirmOverlap (tabRoom, newRoom, *Roomcount) == 0);

			do
				{
					for (int i = 0; i < 4; i++)
						{
							newRoom.room_door[i] = -1;
						}
					newRoom.room_door[(prevDoor->direction + 2) % 4] = 1;
					newRoom.num_door = rand () % 3 + 2;
					while (newRoom.num_door > MAX_ROOM - *Roomcount)
						{
							newRoom.num_door--;
						}

					switch (newRoom.num_door)
						{
						case 2:
							randtamp = rand () % 4;
							if (randtamp == (prevDoor->direction + 2) % 4)
								{
									randtamp = (randtamp + 1) % 4;
								}
							newRoom.room_door[randtamp] = 1;
							break;
						case 3:
							randtamp = rand () % 4;
							if (randtamp == (prevDoor->direction + 2) % 4)
								{
									randtamp = (randtamp + 1) % 4;
								}
							newRoom.room_door[randtamp] = 1;
							randtamp2 = rand () % 4;
							do
								{
									randtamp2 = (randtamp2 + 1) % 4;
								}
							while (randtamp2 ==
										 (prevDoor->direction + 2) % 4 || randtamp2 == randtamp);
							newRoom.room_door[randtamp2] = 1;
							break;
						case 4:
							for (int i = 0; i < 4; i++)
								{
									newRoom.room_door[i] = 1;
								}
						}
				}
			while (confirmDoororientation (tabRoom, newRoom, *Roomcount, *prevDoor)
						 == 0);

			for (int i = *Doorcount; i < Doornum + newRoom.num_door - 1; i++)
				{
					tabDoor[i].room_num1 = *Roomcount;
					tabDoor[i].room_num2 = -1;

					while (newRoom.room_door[directionindex] != 1
								 || directionindex == ((prevDoor->direction) + 2) % 4)
						{
							directionindex = (directionindex + 1) % 4;
						}

					tabDoor[i].direction = directionindex;

					do
						{
							switch (tabDoor[i].direction)
								{
								case 0:
									tabDoor[i].x =
										newRoom.x_min + 1 +
										(rand () % (newRoom.x_max - newRoom.x_min - 1));
									tabDoor[i].y = newRoom.y_max + 1;
									break;
								case 1:
									tabDoor[i].x = newRoom.x_max + 1;
									tabDoor[i].y =
										newRoom.y_min + 1 +
										(rand () % (newRoom.y_max - newRoom.y_min - 1));
									break;
								case 2:
									tabDoor[i].x =
										newRoom.x_min + 1 +
										(rand () % (newRoom.x_max - newRoom.x_min - 1));
									tabDoor[i].y = newRoom.y_min - 1;
									break;
								case 3:
									tabDoor[i].x = newRoom.x_min - 1;
									tabDoor[i].y =
										newRoom.y_min + 1 +
										(rand () % (newRoom.y_max - newRoom.y_min - 1));
									break;
								}
						}
					while (confirmDoorLock
								 (tabDoor, tabDoor[i], *Doorcount, tabRoom, *Roomcount) == 0);
					(*Doorcount)++;
					directionindex++;
				}
		}

	(*Roomcount)++;
	return newRoom;
}