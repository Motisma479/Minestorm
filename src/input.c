#include "game.h"
#include "input.h"
#include "player.h"
#include "levels.h"

static int setInputFlagPressed(KeyboardKey key, PlayerAction *flag, PlayerAction action)
{
	if(IsKeyPressed(key))
	{
		*flag |= action;
		return (1);
	}
	else
		*flag &= ~action;
	return (0);
}

static void setInputFlag(KeyboardKey key, PlayerAction *flag, PlayerAction action)
{
	if(IsKeyDown(key))
		*flag |= action;
	else
		*flag &= ~action;
}

void getInput(Game* game)
{
	Player *player1 = &game->player[0];
	Player *player2 = &game->player[1];
	if(IsKeyPressed(KEY_SPACE))
	{
		if (game->state == GS_PLAY)
			game->state = GS_PAUSE;
		else
			game->state = GS_PLAY;
	}

	setInputFlagPressed(KEY_F, &player1->action, PA_SHOOT);
	if (!setInputFlagPressed(KEY_T, &player1->action, PA_TELEPORT))
		setInputFlagPressed(KEY_E, &player1->action, PA_TELEPORT);
	setInputFlag(KEY_D, &player1->action, PA_TURN_LEFT);
	setInputFlag(KEY_G, &player1->action, PA_TURN_RIGHT);
	setInputFlag(KEY_R, &player1->action, PA_ACCELERATION);

	if(IsKeyPressed('K') && (game->state == GS_MENU))
		game->twoPlayers = true;
	if (game->twoPlayers)
	{
		setInputFlagPressed(KEY_K, &player2->action, PA_SHOOT);
		if (!setInputFlagPressed(KEY_U, &player2->action, PA_TELEPORT))
			setInputFlagPressed(KEY_O, &player2->action, PA_TELEPORT);
		setInputFlag(KEY_J, &player2->action, PA_TURN_LEFT);
		setInputFlag(KEY_L, &player2->action, PA_TURN_RIGHT);
		setInputFlag(KEY_I, &player2->action, PA_ACCELERATION);
	}
	if (IsKeyPressed('C'))
	{
		if (game->draw == DS_DEFAULT)
			game->draw = DS_EVERYTHING;
		else if (game->draw == DS_EVERYTHING)
			game->draw = DS_COLLISIONS;
		else
			game->draw = DS_DEFAULT;
	}

	if(IsKeyPressed(KEY_ESCAPE))
	{
		if (game->state == GS_MENU)
			game->state = GS_CLOSE;
		if (game->state == GS_PAUSE  ||
			game->state == GS_GAMEOVER || game->state == GS_PLAY)
		{
			game->state = GS_MENU;
			*player1 = (Player){0};
			*player2 = (Player){0};
			game->layer = (MineLayer){0};
			initPlayer(player1, (Vector2d){SCREEN_WIDTH / 3.0f,
						   SCREEN_HEIGHT - 200});
			initPlayer(player2, (Vector2d){SCREEN_WIDTH / 1.5f,
						   SCREEN_HEIGHT - 200});
			game->twoPlayers = false;
			game->levelStart = false;
			game->mineLayerSpawned = false;
			game->level = 1;
			startLevel(game);
		}
	}
}
