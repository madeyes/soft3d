#include <SDL2/SDL.h>
#include <inttypes.h>
#include <stdio.h>
#include "vec.h"
#include "matrix.h"
#include "mesh.h"

static const uint16_t W = 1200;
static const uint16_t H = 1200;

static void draw(SDL_Renderer *r);
static void update();

static mesh object;

int main()
{
   if (mesh_from_obj_file("/home/paul/untitled.obj", &object) != 0)
   {
      printf("Failed to load mesh data.");
      return 1;
   }
   else
   {
      printf("Mesh loaded.");
   }

   if (SDL_Init(SDL_INIT_VIDEO) != 0)
   {
      printf("Init failed!\n");
      return 1;
   }

   SDL_Window *win = SDL_CreateWindow("madeyes 2019",
                                      100, 100,
                                      W, H,
                                      SDL_WINDOW_SHOWN);
   if (win == nullptr)
   {
      printf("Window creation failed!");
      SDL_Quit();
      return 1;
   }

   SDL_Renderer *ren = SDL_CreateRenderer(win, -1,
                       SDL_RENDERER_ACCELERATED);
   if (ren == nullptr)
   {
      SDL_DestroyWindow(win);
      SDL_Quit();
      return 1;
   }

   bool quit = false;
   SDL_Event event;
   while (!quit)
   {
      while (SDL_PollEvent(&event) != 0)
      {
         if (event.type == SDL_QUIT)
         {
            quit = true;
         }
      }
      const uint32_t start = SDL_GetTicks();
      draw(ren);
      update();
      const int32_t remain = 16 - (SDL_GetTicks() - start);
      if (remain > 0)
      {
         //SDL_Delay(remain);
      }
   }

   SDL_DestroyWindow(win);
   SDL_Quit();
   return 0;
}

/* x,y range from [-1.0, +1.0] */
static void to_screen(const double x, const double y, int &sx, int &sy)
{
   // TODO: Adjust for aspect ratio.
   sx = W * ((x + 1.0) / 2.0);
   sy = H * ((-y + 1.0) / 2.0);
}

static void draw_mesh(SDL_Renderer *r, const mesh & object)
{
   for (int i = 0; i < object.vertices.size(); i+=2)
   {
      vec4 p1 = multiply(object.vertices[i], object.transform);
      vec4 p2 = multiply(object.vertices[i], object.transform);
      if (p1.z != 0)
      {
         p1.x /= p1.z;
         p1.y /= p1.z;
      }
      if (p2.z != 0)
      {
         p2.x /= p2.z;
         p2.y /= p2.z;
      }
      int x1, y1, x2, y2;
      to_screen(p1.x, p1.y, x1, y1);
      to_screen(p2.x, p2.y, x2, y2);
      SDL_RenderDrawLine(r, x1, y1, x2, y2);
   }
}

static void draw_line_list(SDL_Renderer *r, const vec4 points [], const int num_lines, matrix4x4 model_view)
{
   for (int i = 0; i < 2 * num_lines; i+=2)
   {
      vec4 p1 = multiply(points[i], model_view);
      vec4 p2 = multiply(points[i+1], model_view);
      if (p1.z != 0)
      {
         p1.x /= p1.z;
         p1.y /= p1.z;
      }
      if (p2.z != 0)
      {
         p2.x /= p2.z;
         p2.y /= p2.z;
      }
      int x1, y1, x2, y2;
      to_screen(p1.x, p1.y, x1, y1);
      to_screen(p2.x, p2.y, x2, y2);
      SDL_RenderDrawLine(r, x1, y1, x2, y2);
   }
}

static const vec4 lines[] = {vec4(-0.5f, 0.5f, -2.0f), vec4(0.5f, 0.5f, -2.0f),
                             vec4(0.5f, 0.5f, -2.0f), vec4(0.5f, -0.5f, -2.0f),
                             vec4(0.5f, -0.5f, -2.0f), vec4(-0.5f, -0.5f, -2.0f),
                             vec4(-0.5f, -0.5f, -2.0f), vec4(-0.5f, 0.5f, -2.0f)};
static const size_t NUM_POINTS = sizeof(lines)/sizeof(vec4);
static const size_t NUM_LINES = NUM_POINTS / 2;


static void draw(SDL_Renderer *r)
{
   static double angle = 0.1f;

   //SDL_SetRenderDrawColor(r, 0x64, 0x95, 0xed, 0xff);
   SDL_SetRenderDrawColor(r, 0x0, 0x0, 0x0, 0xff);
   SDL_RenderClear(r);

   matrix4x4 model0 = multiply(translate(0.0, 0.0, 2.0), multiply(rot_y(angle), translate(0.0, 0.0, -2.0)));
   matrix4x4 model = multiply(rot_y(angle), translate(0.0, 0.0, -2.0));
   matrix4x4 view = look_at_rh(vec4(0.0, 0.0, 0.0), vec4(0.0, 0.0, -5.0), vec4(0.0, 1.0, 0.0));
   object.transform = multiply(model, view);
   matrix4x4 model_view = multiply(model0, view);
   Uint8 red = 100;

   SDL_SetRenderDrawColor(r, red, 0, red, 0xff);
   draw_mesh(r, object);
   draw_line_list(r, lines, NUM_LINES, model_view);

   SDL_RenderPresent(r);

   angle += 0.0005f;
}

static void update()
{
}

