#include "game.h"
#include "player.h"
#include "levels.h"
#include "draw.h"
#include "input.h"
#include "save.h"

static void loadSounds(Game *game, Sound *shot, Sound *explosion)
{
	Wave wave = LoadWave("assets/music.wav");
	game->music = LoadSoundFromWave(wave);
	UnloadWave(wave);
	wave = LoadWave("assets/start.wav");
	game->levelIntro = LoadSoundFromWave(wave);
	UnloadWave(wave);
	wave = LoadWave("assets/shot.wav");
	*shot = LoadSoundFromWave(wave);
	UnloadWave(wave);
	PlaySound(game->music);
	wave = LoadWave("assets/explosion.wav");
	*explosion = LoadSoundFromWave(wave);
	UnloadWave(wave);
	SetSoundVolume(game->music, 0.3);
	SetSoundVolume(game->levelIntro, 0.3);
	SetSoundVolume(*shot, 0.5);
	SetSoundVolume(*explosion, 0.2);
	PlaySound(game->music);
}

static void unloadData(Game *game, Sound *shot, Sound *explosion)
{
	UnloadTexture(game->atlas);
	UnloadTexture(game->background);
	UnloadTexture(game->foreground);
	UnloadSound(game->music);
	UnloadSound(game->levelIntro);
	UnloadSound(*shot);
	UnloadSound(*explosion);
	CloseAudioDevice();
}

int main()
{
	Game game = {0};

	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"MATHIEU-OSVALDO-VICTOR");
	InitAudioDevice();
	game.highScore = loadHScore();
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);
	game.state = GS_MENU;

	initPlayer(&game.player[0], (Vector2d){SCREEN_WIDTH / 3.0f,
				   SCREEN_HEIGHT - 200});
	initPlayer(&game.player[1], (Vector2d){SCREEN_WIDTH / 1.5f,
				   SCREEN_HEIGHT - 200});
	initLayer(&game.layer);

	game.atlas = LoadTexture("assets/mines.png");
	game.background = LoadTexture("assets/background.png");
	game.foreground = LoadTexture("assets/foreground.png");
	Sound shot;
	Sound explosion;

	loadSounds(&game, &shot, &explosion);
	float timeStepAcc = 0;
	float deltaTime = 0;
	while (!WindowShouldClose() && game.state != GS_CLOSE)
	{
		deltaTime = GetFrameTime();
		getInput(&game);

		//We start drawing the background before updating
		//because we want to draw the collisions boxes immediately after updating them
		timeStepAcc = 0;
		BeginDrawing();
		DrawTextureEx(game.background, (Vector2){0, 0}, 0, 1.0f, WHITE);
		game.mineLayerUpdated = false;
		game.bulletShot = false;
		game.entityDestroyed = false;
		while (timeStepAcc < deltaTime)
		{
			game.deltaTime = 0.00035;
			updateGame(&game);
			game.mineLayerUpdated = true;
			timeStepAcc += 0.00035;
		}
		drawGame(&game); 
		if (game.bulletShot)
			PlaySound(shot);
		if (game.entityDestroyed)
			PlaySound(explosion);
		game.framesCounter++;
	}
	unloadData(&game, &shot, &explosion);

	CloseWindow();
	return 0;
}
