#include <stdio.h>
#include "game.h"



int main()
{
	printf("MINE_STORM GAME\n");

	Game game;
	bool success = initGame(&game);
	if (success)
	{
		runGameLoop(&game);
	}
	shutdown(&game);


	/*Enemy enemy;
	Vector2 position = {210.0f,310.0f};
	float scale = 64.0f;
	float rotation = -90.0f;
	float speed = 5.0f;
	int type = FLOATING_MINE;
	int size = BIG_SIZE;
	FloatingMine mine = {position,scale,rotation,speed,type,size};
	enemy.floatingMine = mine;


	printf("enemy->position : (%f,%f)\tenemy->scale:%f\tenemy->speed:%f\n",enemy.enemyBase.position.x
	,enemy.enemyBase.position.y,enemy.enemyBase.scale,enemy.enemyBase.speed);

	printf("enemy->position : (%f,%f)\tenemy->scale:%f\tenemy->speed:%f\n",mine.position.x
	,mine.position.y,mine.scale,mine.speed);
	*/

	return 0;
}