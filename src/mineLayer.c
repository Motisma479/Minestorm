#include "mineLayer.h"
#include "common.h"

void initLayer(MineLayer* layer)
{
	layer->scale = 640.0f;
	layer->position = (Vector2d){ (float)SCREEN_WIDTH / 2.0f,
		(float)SCREEN_HEIGHT / 2.0f};
	layer->active = true;
	//layer->active = false;
	layer->rotation = 0.0f;
	layer->layerEnd = false;
}

int updateLayer(MineLayer* layer, float deltaTime, bool *levelStart)
{
	if (layer->active && layer->scale >= 32.0f)
	{
		layer->scale -= layer->scale*5000.0f / 100.0f*deltaTime;
		layer->position.y -= 3.0f;
	}

	if(layer->scale <= 32.0f || layer->position.y < 0)
	{
		layer->scale = 0.0f;
		layer->active = false;
		layer->layerEnd = true;
		*levelStart = true;
		return (1);
	}
	return (0);
}
void drawLayer(MineLayer* layer, const Texture2D* texture)
{
	if (layer->active && layer->scale >= 32.0f)
	{
		Rectangle rect = { texture->width / 2.0f,0.0f,texture->width / 4.0f,texture->height / 2.0f };
		Rectangle position = { layer->position.x,layer->position.y,layer->scale,layer->scale};
		Vector2 center = { layer->scale / 2.0f,layer->scale / 2.0f };

		DrawTexturePro(*texture, rect, position, center, layer->rotation, WHITE);
	}
}