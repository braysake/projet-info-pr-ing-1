#include"params.h"
int
searchNearDoor (Door * tab_door, Door test_door, int door_count)
{
	for (int i = 0; i < door_count; i++)
		{
			switch (test_door.direction)
				{
				case 0:
					if (tab_door[i].x >= (test_door.x) - 4
							&& tab_door[i].x <= (test_door.x) + 4
							&& tab_door[i].y >= (test_door.y) + 1
							&& tab_door[i].y <= (test_door.y) + 9
							&& tab_door[i].direction != test_door.direction)
						{
							if (tab_door[i].room_num1 != test_door.room_num1
									&& tab_door[i].room_num2 != test_door.room_num1
									&& tab_door[i].direction != test_door.direction)
								{
									return 1;
								}
						}
					break;
				case 1:
					if (tab_door[i].y >= (test_door.y) - 4
							&& tab_door[i].y <= (test_door.y) + 4
							&& tab_door[i].x >= (test_door.x) + 1
							&& tab_door[i].x <= (test_door.x) + 9
							&& tab_door[i].direction != test_door.direction)
						{
							if (tab_door[i].room_num1 != test_door.room_num1
									&& tab_door[i].room_num2 != test_door.room_num1
									&& tab_door[i].direction != test_door.direction)
								{
									return 1;
								}
						}
					break;
				case 2:
					if (tab_door[i].x >= (test_door.x) - 4
							&& tab_door[i].x <= (test_door.x) + 4
							&& tab_door[i].y <= (test_door.y) - 1
							&& tab_door[i].y >= (test_door.y) - 9
							&& tab_door[i].direction != test_door.direction)
						{
							if (tab_door[i].room_num1 != test_door.room_num1
									&& tab_door[i].room_num2 != test_door.room_num1
									&& tab_door[i].direction != test_door.direction)
								{
									return 1;
								}
						}
					break;
				case 3:
					if (tab_door[i].y >= (test_door.y) - 4
							&& tab_door[i].y <= (test_door.y) + 4
							&& tab_door[i].x <= (test_door.x) - 1
							&& tab_door[i].x >= (test_door.x) - 9
							&& tab_door[i].direction != test_door.direction)
						{
							if (tab_door[i].room_num1 != test_door.room_num1
									&& tab_door[i].room_num2 != test_door.room_num1
									&& tab_door[i].direction != test_door.direction)
								{
									return 1;
								}
						}
					break;
				}
		}
	return 0;
}



int
searchReallyNearDoor (Door possibleDoor, Door test_door)
{
	switch (test_door.direction)
		{
		case 0:
			if (possibleDoor.x >= (test_door.x) - 5
					&& possibleDoor.x <= (test_door.x) + 5
					&& possibleDoor.y >= (test_door.y) + 1
					&& possibleDoor.y <= (test_door.y) + 6
					&& possibleDoor.direction != test_door.direction)
				{
					if (possibleDoor.room_num1 != test_door.room_num1
							&& possibleDoor.room_num2 != test_door.room_num1
							&& possibleDoor.direction != test_door.direction)
						{
							return 1;
						}
				}
			break;
		case 1:
			if (possibleDoor.y >= (test_door.y) - 5
					&& possibleDoor.y <= (test_door.y) + 5
					&& possibleDoor.x >= (test_door.x) + 1
					&& possibleDoor.x <= (test_door.x) + 6)
				{
					if (possibleDoor.room_num1 != test_door.room_num1
							&& possibleDoor.room_num2 != test_door.room_num1
							&& possibleDoor.direction != test_door.direction)
						{
							return 1;
						}
				}
			break;
		case 2:
			if (possibleDoor.x >= (test_door.x) - 5
					&& possibleDoor.x <= (test_door.x) + 5
					&& possibleDoor.y <= (test_door.y) - 1
					&& possibleDoor.y >= (test_door.y) - 6)
				{
					if (possibleDoor.room_num1 != test_door.room_num1
							&& possibleDoor.room_num2 != test_door.room_num1
							&& possibleDoor.direction != test_door.direction)
						{
							return 1;
						}
				}
			break;
		case 3:
			if (possibleDoor.y >= (test_door.y) - 5
					&& possibleDoor.y <= (test_door.y) + 5
					&& possibleDoor.x <= (test_door.x) - 1
					&& possibleDoor.x >= (test_door.x) - 6)
				{
					if (possibleDoor.room_num1 != test_door.room_num1
							&& possibleDoor.room_num2 != test_door.room_num1
							&& possibleDoor.direction != test_door.direction)
						{
							return 1;
						}
				}
			break;
		}
	return 0;
}

int
confirmOverlap (Room * room_size_tab, Room new_room, int room_count)
{
	for (int i = 0; i < room_count; i++)
		{
			if (((new_room.y_min >= (room_size_tab[i].y_min - 1)
						&& new_room.y_min <= (room_size_tab[i].y_max + 1))
					 || (new_room.y_max >= (room_size_tab[i].y_min - 1)
							 && new_room.y_max <= (room_size_tab[i].y_max + 1)))
					&&
					((new_room.x_min >= (room_size_tab[i].x_min - 1)
						&& new_room.x_min <= (room_size_tab[i].x_max + 1))
					 || (new_room.x_max >= (room_size_tab[i].x_min - 1)
							 && new_room.x_max <= (room_size_tab[i].x_max + 1))))
				{
					return 0;							//overlap
				}
		}
	return 1;											//no overlap
}

int
confirmDoorLoc (Door * tab_door, Door test_door, int door_count,
								Room * room_size_tab, int room_count)
{


	for (int i = 0; i < room_count; i++)
		{
			switch (test_door.direction)
				{
				case 0:
					if ((test_door.x - 2 >= room_size_tab[i].x_min
							 && test_door.x - 2 <= room_size_tab[i].x_max)
							&& (test_door.y + 2 >= room_size_tab[i].y_min
									&& test_door.y + 2 <= room_size_tab[i].y_max)
							&& (test_door.x + 2 >= room_size_tab[i].x_min
									&& test_door.x + 2 <= room_size_tab[i].x_max)
							&& (test_door.y + 4 >= room_size_tab[i].y_min
									&& test_door.y + 4 <= room_size_tab[i].y_max))
						{
							return 0;
						}
					break;
				case 1:
					if ((test_door.y - 2 >= room_size_tab[i].y_min
							 && test_door.y - 2 <= room_size_tab[i].y_max)
							&& (test_door.x + 2 >= room_size_tab[i].x_min
									&& test_door.x + 2 <= room_size_tab[i].x_max)
							&& (test_door.y + 2 >= room_size_tab[i].y_min
									&& test_door.y + 2 <= room_size_tab[i].y_max)
							&& (test_door.x + 4 >= room_size_tab[i].y_min
									&& test_door.x + 4 <= room_size_tab[i].y_max))
						{
							return 0;
						}
					break;
				case 2:
					if ((test_door.x - 2 >= room_size_tab[i].x_min
							 && test_door.x - 2 <= room_size_tab[i].x_max)
							&& (test_door.y - 2 >= room_size_tab[i].y_min
									&& test_door.y - 2 <= room_size_tab[i].y_max)
							&& (test_door.x + 2 >= room_size_tab[i].x_min
									&& test_door.x + 2 <= room_size_tab[i].x_max)
							&& (test_door.y + 4 >= room_size_tab[i].y_min
									&& test_door.y + 4 <= room_size_tab[i].y_max))
						{
							return 0;
						}
					break;
				case 3:
					if ((test_door.y - 2 >= room_size_tab[i].y_min
							 && test_door.y - 2 <= room_size_tab[i].y_max)
							&& (test_door.x - 2 >= room_size_tab[i].x_min
									&& test_door.x - 2 <= room_size_tab[i].x_max)
							&& (test_door.y + 2 >= room_size_tab[i].y_min
									&& test_door.y + 2 <= room_size_tab[i].y_max)
							&& (test_door.x + 4 >= room_size_tab[i].y_min
									&& test_door.x + 4 <= room_size_tab[i].y_max))
						{
							return 0;
						}
					break;
				}
		}



	/*for (int i = 0; i < door_count; i++)
	   {
	   if ((test_door.x <= tab_door[i].x + 4
	   && test_door.x >= tab_door[i].x - 4
	   && test_door.y <= tab_door[i].y + 4
	   && test_door.y >= tab_door[i].y - 4
	   && tab_door[i].direction != test_door.direction)
	   && (tab_door[i].room_num1=test_door.room_num1)||(tab_door[i].room_num1=test_door.room_num1))
	   {
	   for (int j = 0; j < room_count; j++)
	   {
	   switch (test_door.direction)
	   {
	   case 0:
	   if (((test_door.y + 1 >= room_size_tab[j].y_min
	   && test_door.y + 1 <= room_size_tab[j].y_max)
	   || (test_door.y + 5 >= room_size_tab[j].y_min
	   && test_door.y + 5 <= room_size_tab[j].y_max))
	   &&
	   ((test_door.x - 3 >= room_size_tab[j].x_min
	   && test_door.x - 3 <= room_size_tab[j].x_max)
	   || (test_door.x + 3 >= room_size_tab[j].x_min
	   && test_door.x + 3 <= room_size_tab[j].x_max)))
	   {
	   return 0;
	   }
	   break;
	   case 1:
	   if (((test_door.y - 3 >= room_size_tab[j].y_min
	   && test_door.y - 3 <= room_size_tab[j].y_max)
	   || (test_door.y + 3 >= room_size_tab[j].y_min
	   && test_door.y + 3 <= room_size_tab[j].y_max))
	   &&
	   ((test_door.x + 1 >= room_size_tab[j].x_min
	   && test_door.x + 1 <= room_size_tab[j].x_max)
	   || (test_door.x + 5 >= room_size_tab[j].x_min
	   && test_door.x + 5 <= room_size_tab[j].x_max)))
	   {
	   return 0;
	   }
	   break;
	   case 2:
	   if (((test_door.y - 1 >= room_size_tab[j].y_min
	   && test_door.y - 1 <= room_size_tab[j].y_max)
	   || (test_door.y - 5 >= room_size_tab[j].y_min
	   && test_door.y - 5 <= room_size_tab[j].y_max))
	   &&
	   ((test_door.x - 3 >= room_size_tab[j].x_min
	   && test_door.x - 3 <= room_size_tab[j].x_max)
	   || (test_door.x + 3 >= room_size_tab[j].x_min
	   && test_door.x + 3 <= room_size_tab[j].x_max)))
	   {
	   return 0;
	   }
	   break;
	   case 3:
	   if (((test_door.y - 3 >= room_size_tab[j].y_min
	   && test_door.y - 3 <= room_size_tab[j].y_max)
	   || (test_door.y + 3 >= room_size_tab[j].y_min
	   && test_door.y + 3 <= room_size_tab[j].y_max))
	   &&
	   ((test_door.x - 1 >= room_size_tab[j].x_min
	   && test_door.x - 1 <= room_size_tab[j].x_max)
	   || (test_door.x - 5 >= room_size_tab[j].x_min
	   && test_door.x - 5 <= room_size_tab[j].x_max)))
	   {
	   return 0;
	   }
	   break;
	   }
	   }                    //not allowed
	   }
	   } */
	return 1;											//allowed
}

int
confirmdoororientation (Room * room_size_tab, Room new_room, int room_count,
												Door prev_door)
{
	for (int j = 0; j < 4; j++)
		{
			if (new_room.room_door[j] == 1 && (prev_door.direction + 2) % 4 != j)
				{
					for (int i = 0; i < room_count; i++)
						{
							switch (j)
								{
								case 0:
									if ((new_room.y_max + 5 >= room_size_tab[i].y_min
											 && new_room.y_max + 5 <= room_size_tab[i].y_max)
											|| (new_room.y_max + 3 >= room_size_tab[i].y_min
													&& new_room.y_max + 3 <= room_size_tab[i].y_max)
											&&
											((new_room.x_min - 1 >= room_size_tab[i].x_min
												&& new_room.x_min - 1 <= room_size_tab[i].x_max)
											 || (new_room.x_max + 1 >= room_size_tab[i].x_min
													 && new_room.x_max + 1 <= room_size_tab[i].x_max)))
										{
											return 0;
										}
									break;
								case 1:
									if (((new_room.y_min - 1 >= room_size_tab[i].y_min
												&& new_room.y_min - 1 <= room_size_tab[i].y_max)
											 || (new_room.y_max + 1 >= room_size_tab[i].y_min
													 && new_room.y_max + 1 <= room_size_tab[i].y_max))
											&& (new_room.x_max + 5 >= room_size_tab[i].x_min
													&& new_room.x_max + 5 <= room_size_tab[i].x_max)
											|| (new_room.x_max + 3 >= room_size_tab[i].x_min
													&& new_room.x_max + 3 <= room_size_tab[i].x_max))
										{
											return 0;
										}
									break;
								case 2:
									if ((new_room.y_min - 5 >= room_size_tab[i].y_min
											 && new_room.y_min - 5 <= room_size_tab[i].y_max)
											|| (new_room.y_min - 3 >= room_size_tab[i].y_min
													&& new_room.y_min - 3 <= room_size_tab[i].y_max)
											&&
											((new_room.x_min - 1 >= room_size_tab[i].x_min
												&& new_room.x_min - 1 <= room_size_tab[i].x_max)
											 || (new_room.x_max + 1 >= room_size_tab[i].x_min
													 && new_room.x_max + 1 <= room_size_tab[i].x_max)))
										{
											return 0;
										}
									break;
								case 3:
									if (((new_room.y_min - 1 >= room_size_tab[i].y_min
												&& new_room.y_min - 1 <= room_size_tab[i].y_max)
											 || (new_room.y_max + 1 >= room_size_tab[i].y_min
													 && new_room.y_max + 1 <= room_size_tab[i].y_max))
											&&
											(new_room.x_min - -5 >= room_size_tab[i].x_min
											 && new_room.x_min - 5 <= room_size_tab[i].x_max)
											|| (new_room.x_min - 3 >= room_size_tab[i].x_min
													&& new_room.x_min - 3 <= room_size_tab[i].x_max))
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
adaptNextSizeRoomFuse (Room * new_room, int room_count,
											 Door * tab_door, Door test_door, int door_count)
{
	int count_door;
	for (int i = 0; i < door_count; i++)
		{
			if (tab_door[i].direction != test_door.direction
					&& searchReallyNearDoor (tab_door[i], test_door) > 0)
				{
					switch (test_door.direction)
						{
						case 0:
							switch (tab_door[i].direction)
								{
								case 1:
									new_room->x_min = tab_door[i].x + 1;
									tab_door[i].room_num2 = room_count;
									count_door++;
									new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
									break;
								case 2:
									new_room->y_max = tab_door[i].y - 1;
									tab_door[i].room_num2 = room_count;
									count_door++;
									new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
									break;
								case 3:
									new_room->x_max = tab_door[i].x - 1;
									tab_door[i].room_num2 = room_count;
									count_door++;
									new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						case 1:
							switch (tab_door[i].direction)
								{
								case 0:
									new_room->y_min = tab_door[i].y + 1;
									tab_door[i].room_num2 = room_count;
									count_door++;
									new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
									break;
								case 2:
									new_room->y_max = tab_door[i].y - 1;
									tab_door[i].room_num2 = room_count;
									count_door++;
									new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
									break;
								case 3:
									new_room->x_max = tab_door[i].x - 1;
									tab_door[i].room_num2 = room_count;
									count_door++;
									new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						case 2:
							switch (tab_door[i].direction)
								{
								case 0:
									new_room->y_min = tab_door[i].y + 1;
									tab_door[i].room_num2 = room_count;
									count_door++;
									new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
									break;
								case 1:
									new_room->x_min = tab_door[i].x + 1;
									tab_door[i].room_num2 = room_count;
									count_door++;
									new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
									break;
								case 3:
									new_room->x_max = tab_door[i].x - 1;
									tab_door[i].room_num2 = room_count;
									count_door++;
									new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						case 3:
							switch (tab_door[i].direction)
								{
								case 0:
									new_room->y_min = tab_door[i].y + 1;
									tab_door[i].room_num2 = room_count;
									count_door++;
									new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
									break;
								case 1:
									new_room->x_min = tab_door[i].x + 1;
									tab_door[i].room_num2 = room_count;
									count_door++;
									new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
									break;
								case 2:
									new_room->y_max = tab_door[i].y - 1;
									tab_door[i].room_num2 = room_count;
									count_door++;
									new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						}
				}
		}
	return count_door;
}


Room
generateRoom (int *seed, Room * tab_room,
							Door * prev_door, int *room_count, Door * tab_door,
							int *door_count)
{
	Room new_room;
	int rand_tamp, direction_index, rand_tamp2, door_num = *door_count;
	prev_door->room_num2 = *room_count;
	new_room.num_door = 1;

	for (int i = 0; i < 4; i++)
		{
			new_room.room_door[i] = -1;
		}
	new_room.room_door[(prev_door->direction + 2) % 4] = 1;
	for (int i = 0; i < *door_count; i++)
		{
			if (searchReallyNearDoor (tab_door[i], *prev_door) > 0)
				{
					new_room.num_door++;
				}
		}
	if (new_room.num_door > 1)
		{
			new_room.x_max = 0;
			new_room.x_min = 0;
			new_room.y_max = 0;
			new_room.y_min = 0;
			adaptNextSizeRoomFuse (&new_room, *room_count, tab_door,
														 *prev_door, *door_count);
			do
				{
					switch (prev_door->direction)
						{
						case 0:
							new_room.y_min = prev_door->y + 1;
							if (new_room.x_min == 0)
								{
									new_room.x_min = prev_door->x - 5 + (rand () % 3);
								}
							if (new_room.x_max == 0)
								{
									new_room.x_max = prev_door->x + 5 - (rand () % 3);
								}
							if (new_room.y_max == 0)
								{
									new_room.y_max = new_room.y_min + 4 + (rand () % 5);
								}
							break;
						case 1:
							new_room.x_min = prev_door->x + 1;
							if (new_room.x_max == 0)
								{
									new_room.x_max = new_room.x_min + 4 + (rand () % 5);
								}
							if (new_room.y_min == 0)
								{
									new_room.y_min = prev_door->y - 5 + (rand () % 3);
								}
							if (new_room.y_max == 0)
								{
									new_room.y_max = prev_door->y + 5 - (rand () % 3);
								}
							break;
						case 2:
							new_room.y_max = prev_door->y - 1;
							if (new_room.x_min == 0)
								{
									new_room.x_min = prev_door->x - 5 + (rand () % 3);
								}
							if (new_room.x_max == 0)
								{
									new_room.x_max = prev_door->x + 5 - (rand () % 3);
								}
							if (new_room.y_min == 0)
								{
									new_room.y_min = new_room.y_max - 4 - (rand () % 5);
								}
							break;
						case 3:
							new_room.x_max = prev_door->x - 1;
							if (new_room.x_min == 0)
								{
									new_room.x_min = new_room.x_max - 4 - (rand () % 5);
								}
							if (new_room.y_min == 0)
								{
									new_room.y_min = prev_door->y - 5 + (rand () % 3);
								}
							if (new_room.y_max == 0)
								{
									new_room.y_max = prev_door->y + 5 - (rand () % 3);
								}
							break;
						}

				}
			while (confirmOverlap (tab_room, new_room, *room_count) == 0);
		}														//connecting rooms
	else if (searchNearDoor (tab_door, *prev_door, *door_count) > 0)
		{
			direction_index = 0;
			do
				{
					switch (prev_door->direction)
						{
						case 0:
							new_room.x_min = prev_door->x - 3 + (rand () % 3);
							new_room.x_max = prev_door->x + 3 - (rand () % 3);
							new_room.y_min = prev_door->y + 1;
							new_room.y_max = new_room.y_min + 3 + (rand () % 4);
							break;
						case 1:
							new_room.x_min = prev_door->x + 1;
							new_room.x_max = new_room.x_min + 3 + (rand () % 4);
							new_room.y_min = prev_door->y - 3 + (rand () % 3);
							new_room.y_max = prev_door->y + 3 - (rand () % 3);
							break;
						case 2:
							new_room.x_min = prev_door->x - 3 + (rand () % 3);
							new_room.x_max = prev_door->x + 3 - (rand () % 3);
							new_room.y_max = prev_door->y - 1;
							new_room.y_min = new_room.y_max - 3 - (rand () % 4);
							break;
						case 3:
							new_room.x_max = prev_door->x - 1;
							new_room.x_min = new_room.x_max - 3 - (rand () % 4);
							new_room.y_min = prev_door->y - 3 + (rand () % 3);
							new_room.y_max = prev_door->y + 3 - (rand () % 3);
							break;
						}
				}
			while (confirmOverlap (tab_room, new_room, *room_count) == 0);
			do
				{
					new_room.num_door = rand () % 3 + 1;
					for (int i = 0; i < 4; i++)
						{
							new_room.room_door[i] = -1;
						}
					new_room.room_door[(prev_door->direction + 2) % 4] = 1;
					while (new_room.num_door > MAX_ROOM - *room_count)
						{
							new_room.num_door--;
							switch (new_room.num_door)
								{
								case 2:
									rand_tamp = rand () % 4;
									if (rand_tamp == (prev_door->direction + 2) % 4)
										{
											rand_tamp = (rand_tamp + 1) % 4;
										}
									new_room.room_door[rand_tamp] = 1;
									break;
								case 3:
									rand_tamp = rand () % 4;
									if (rand_tamp == (prev_door->direction + 2) % 4)
										{
											rand_tamp = (rand_tamp + 1) % 4;
										}
									new_room.room_door[rand_tamp] = 1;
									rand_tamp2 = rand () % 4;
									do
										{
											rand_tamp2 = (rand_tamp2 + 1) % 4;
										}
									while (rand_tamp2 !=
												 (prev_door->direction + 2) % 4
												 && rand_tamp2 != rand_tamp);
									new_room.room_door[rand_tamp2] = 1;
									break;
								}
						}
				}
			while (confirmdoororientation
						 (tab_room, new_room, *room_count, *prev_door) == 0);
			for (int i = *door_count; i < door_num + new_room.num_door - 1; i++)
				{
					tab_door[i].room_num1 = *room_count;
					tab_door[i].room_num2 = -1;
					while (new_room.room_door[direction_index] != 1
								 || direction_index == ((prev_door->direction) + 2) % 4)
						{
							direction_index = (direction_index + 1) % 4;
						}
					tab_door[i].direction = direction_index;
					do
						{
							for (int i = 0; i < 4; i++)
								{
									new_room.room_door[i] = -1;
								}
							switch (tab_door[i].direction)
								{
								case 0:
									tab_door[i].x =
										new_room.x_min + 1 +
										(rand () % (new_room.x_max - new_room.x_min - 1));
									tab_door[i].y = new_room.y_max + 1;
									break;
								case 1:
									tab_door[i].x = new_room.x_max + 1;
									tab_door[i].y =
										new_room.y_min + 1 +
										(rand () % (new_room.y_max - new_room.y_min - 1));
									break;
								case 2:
									tab_door[i].x =
										new_room.x_min + 1 +
										(rand () % (new_room.x_max - new_room.x_min - 1));
									tab_door[i].y = new_room.y_min - 1;
									break;
								case 3:
									tab_door[i].x = new_room.x_min - 1;
									tab_door[i].y =
										new_room.y_min + 1 +
										(rand () % (new_room.y_max - new_room.y_min - 1));
									break;
								}
						}
					while (confirmDoorLoc
								 (tab_door, tab_door[i], *door_count, tab_room,
									*room_count) == 0);
					direction_index++;
					(*door_count)++;
				}
		}														//near rooms
	else
		{
			direction_index = 0;
			do
				{
					switch (prev_door->direction)
						{
						case 0:
							new_room.x_min = prev_door->x - 4 + (rand () % 4);
							new_room.x_max = prev_door->x + 4 - (rand () % 4);
							new_room.y_min = prev_door->y + 1;
							new_room.y_max = new_room.y_min + 3 + (rand () % 6);
							break;
						case 1:
							new_room.x_min = prev_door->x + 1;
							new_room.x_max = new_room.x_min + 3 + (rand () % 6);
							new_room.y_min = prev_door->y - 4 + (rand () % 4);
							new_room.y_max = prev_door->y + 4 - (rand () % 4);
							break;
						case 2:
							new_room.x_min = prev_door->x - 4 + (rand () % 4);
							new_room.x_max = prev_door->x + 4 - (rand () % 4);
							new_room.y_max = prev_door->y - 1;
							new_room.y_min = new_room.y_max - 3 - (rand () % 6);
							break;
						case 3:
							new_room.x_max = prev_door->x - 1;
							new_room.x_min = new_room.x_max - 3 - (rand () % 6);
							new_room.y_min = prev_door->y - 4 + (rand () % 4);
							new_room.y_max = prev_door->y + 4 - (rand () % 4);
							break;
						}
				}
			while (confirmOverlap (tab_room, new_room, *room_count) == 0);
			do
				{
					for (int i = 0; i < 4; i++)
						{
							new_room.room_door[i] = -1;
						}
					new_room.room_door[(prev_door->direction + 2) % 4] = 1;
					new_room.num_door = rand () % 3 + 2;
					while (new_room.num_door > MAX_ROOM - *room_count)
						{
							new_room.num_door--;
						}
					switch (new_room.num_door)
						{
						case 2:
							rand_tamp = rand () % 4;
							if (rand_tamp == (prev_door->direction + 2) % 4)
								{
									rand_tamp = (rand_tamp + 1) % 4;
								}
							new_room.room_door[rand_tamp] = 1;
							break;
						case 3:
							rand_tamp = rand () % 4;
							if (rand_tamp == (prev_door->direction + 2) % 4)
								{
									rand_tamp = (rand_tamp + 1) % 4;
								}
							new_room.room_door[rand_tamp] = 1;
							rand_tamp2 = rand () % 4;
							do
								{
									rand_tamp2 = (rand_tamp2 + 1) % 4;
								}
							while (rand_tamp2 ==
										 (prev_door->direction + 2) % 4
										 || rand_tamp2 == rand_tamp);
							new_room.room_door[rand_tamp2] = 1;
							break;
						case 4:
							for (int i = 0; i < 4; i++)
								{
									new_room.room_door[i] = 1;
								}
						}
				}
			while (confirmdoororientation
						 (tab_room, new_room, *room_count, *prev_door) == 0);
			for (int i = *door_count; i < door_num + new_room.num_door - 1; i++)
				{
					tab_door[i].room_num1 = *room_count;
					tab_door[i].room_num2 = -1;
					while (new_room.room_door[direction_index] != 1
								 || direction_index == ((prev_door->direction) + 2) % 4)
						{
							direction_index = (direction_index + 1) % 4;
						}
					tab_door[i].direction = direction_index;
					do
						{
							switch (tab_door[i].direction)
								{
								case 0:
									tab_door[i].x =
										new_room.x_min + 1 +
										(rand () % (new_room.x_max - new_room.x_min - 1));
									tab_door[i].y = new_room.y_max + 1;
									break;
								case 1:
									tab_door[i].x = new_room.x_max + 1;
									tab_door[i].y =
										new_room.y_min + 1 +
										(rand () % (new_room.y_max - new_room.y_min - 1));
									break;
								case 2:
									tab_door[i].x =
										new_room.x_min + 1 +
										(rand () % (new_room.x_max - new_room.x_min - 1));
									tab_door[i].y = new_room.y_min - 1;
									break;
								case 3:
									tab_door[i].x = new_room.x_min - 1;
									tab_door[i].y =
										new_room.y_min + 1 +
										(rand () % (new_room.y_max - new_room.y_min - 1));
									break;
								}
						}
					while (confirmDoorLoc
								 (tab_door, tab_door[i], *door_count, tab_room,
									*room_count) == 0);
					(*door_count)++;
					direction_index++;
				}
		}

	(*room_count)++;
	return new_room;
}

Room createMainRoom() {
  Room f_room;
  for (int j = 0; j < 4; j++) {
      f_room.room_door[j] = 1;
  }
    f_room.num_door = 4;
    f_room.x_min = 1 * -4;
    f_room.x_max = 1 * 5;
    f_room.y_min = 1 * -4;
    f_room.y_max = 1 * 5;
    f_room.nbr_enemy = 0;
    f_room.nbr_object = 0;
    f_room.nbr_armor = 0;
    f_room.nbr_blade = 0;
  return f_room;
}
  
void createMainDoor(Door *tab_door) {
    tab_door[0].x = 0;
    tab_door[0].y = 6;
    tab_door[0].room_num1 = 0;
    tab_door[0].room_num2 = -1;
    tab_door[0].direction = 0;
    tab_door[1].x = 6;
    tab_door[1].y = 0;
    tab_door[1].room_num1 = 0;
    tab_door[1].room_num2 = -1;
    tab_door[1].direction = 1;
    tab_door[2].x = 0;
    tab_door[2].y = -5;
    tab_door[2].room_num1 = 0;
    tab_door[2].room_num2 = -1;
    tab_door[2].direction = 2;
    tab_door[3].x = -5;
    tab_door[3].y = 0;
    tab_door[3].room_num1 = 0;
    tab_door[3].room_num2 = -1;
    tab_door[3].direction = 3;
}
