#pragma once
#include <raylib.h>
#include "Math.h"

typedef struct MineLayer
{
	Vector2d position;
	float scale;
	bool active;
	float rotation;
	bool layerEnd;
} MineLayer;

void initLayer(MineLayer* layer);
int updateLayer(MineLayer* layer, float deltaTime, bool *levelStart);
void drawLayer(MineLayer* layer, const Texture2D* texture);

