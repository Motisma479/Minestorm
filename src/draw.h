/* date = October 18th 2021 11:44 am */

#ifndef DRAW_H
#define DRAW_H

void drawGame(Game* game);
void drawBullet(Bullet* bullet, const Texture2D* texture, Color color);
void drawPlayerGizmo(Game* game);
void drawEnemyGizmo(Game* game);

#endif //DRAW_H
