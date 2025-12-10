#include <cstdlib>
#include <ctime>
#include <cmath>

#include <raylib.h>

const int WINDOW_WIDTH = 1590;
const int WINDOW_HEIGHT = 800;
const char WINDOW_NAME[] = "Pipes";
const Color myBlue = { 144, 196, 224, 255 }; 
const float SIZE = 2.0f;
const float STEP = 50.0f;

using namespace std;

int main(void) {

  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
  SetTargetFPS(60);

  srand(time(0));

  Vector2 start = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
  Vector2 end = start;
  float t = 0.0f; // animation progress (0.0 to 1.0)
  float speed = 5.0f; // anim speed
  Vector2 delta = {0, 0};
  
  // Predefined angles for fixed lines
  int angles[] = { 0, 90, 180, 270 };
  int numAngles = sizeof(angles)/sizeof(angles[0]);
  
  // Render texture for trail
  RenderTexture2D trail = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);

  // Clear trail to white initially
  BeginTextureMode(trail);
    ClearBackground(BLACK);
  EndTextureMode();

  SetTextureFilter(trail.texture, TEXTURE_FILTER_BILINEAR);

  while (!WindowShouldClose()) {

    // If window resized, resize the trail texture
    if (IsWindowResized()) {
      UnloadRenderTexture(trail);
      trail = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
      BeginTextureMode(trail);
        ClearBackground(BLACK);
        EndTextureMode();
      SetTextureFilter(trail.texture, TEXTURE_FILTER_BILINEAR);
    }

    // Pick a new target if we reached the previous one
    Vector2 delta = { end.x - start.x, end.y - start.y };
    float length = sqrtf(delta.x * delta.x + delta.y * delta.y);

    // Update animation
    t += (speed / length);  // speed of animation

    if (t >= 1.0f) {
      t = 0.0f;
      start = end;

      int dir = rand() % 4;

      switch (dir) {
        case 0: end = { start.x + STEP - 1, start.y }; break; // right
        case 1: end = { start.x, start.y + STEP }; break; // down
        case 2: end = { start.x - STEP, start.y }; break; // left
        case 3: end = { start.x, start.y - STEP }; break; // up
      } 

      start.x = floorf(start.x);
      start.y = floorf(start.y);
      end.x   = floorf(end.x);
      end.y   = floorf(end.y);

      // Recalculate for new segment immediately
      delta = { end.x - start.x, end.y - start.y };
      length = sqrtf(delta.x * delta.x + delta.y * delta.y);
    }
    
    Vector2 current = { start.x + delta.x * t, start.y + delta.y * t };

    
    // Draw line onto trail texture
    BeginTextureMode(trail);
      DrawLineEx(start, current, SIZE, myBlue);
    EndTextureMode();
   
    BeginDrawing();
      ClearBackground(BLACK);
      DrawTextureRec(trail.texture,
                     (Rectangle){ 0, 0, (float)trail.texture.width, -(float)trail.texture.height },
                     (Vector2){ 0, 0 },
                     WHITE
                    );
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
