#include <iostream>
#include <raylib.h>

#if defined(_WIN32)
    #define GLSL_VERSION 330
#else
    #define GLSL_VERSION 100
#endif

#define RAYGUI_IMPLEMENTATION
#include <extras/raygui.h>

#define SCR_WIDTH 612
#define SCR_HEIGHT 612

typedef struct ULTHeightMap{
    Image image;
    Texture texture;
    Mesh mesh;
    Model model;
    Shader shader;
} HeightMap;

HeightMap ChooseHeightMap(const char* path){
    // Texture
    Image image = LoadImage(path);
    Texture2D texture = LoadTextureFromImage(image);
    // Shader
    Shader shader = LoadShader(0, TextFormat("res/Shader/glsl%i/Shader3.fs", GLSL_VERSION));

    // Mesh
    Mesh mesh = GenMeshHeightmap(image, Vector3{1.0f, 1.0f, 1.0f});
    
    // Model
    Model model = LoadModelFromMesh(mesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    model.materials[0].shader = shader;

    HeightMap heightmap;
    heightmap.image = image;
    heightmap.texture = texture;
    heightmap.mesh = mesh;
    heightmap.model = model;

    UnloadImage(image);

    return heightmap;
}

int main()
{
    // Initialize Window
    SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    // Camera
    Camera3D camera = Camera3D{ { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
    SetCameraMode(camera, CAMERA_ORBITAL);

    // HeightMap
    int choose = 0;
    HeightMap heightmap = ChooseHeightMap("res/Texture/heightmap.png");

    // FPS
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        float time = GetTime();
        UpdateCamera(&camera);
        static int prevChoose = choose;
        static float xValue = 0.0f;
        xValue = (std::sin(time) / 2.0f) + 0.5f;

        if(choose == 0 && prevChoose != choose ){
            heightmap = ChooseHeightMap("res/Texture/heightmap.png");
            prevChoose = choose;
        }
        else if(choose == 1 && prevChoose != choose){
            heightmap = ChooseHeightMap("res/Texture/heightmap2.png");
            prevChoose = choose;
        }else if(choose == 2 && prevChoose != choose){
            heightmap = ChooseHeightMap("res/Texture/heightmap3.png");
            prevChoose = choose;
        }else if(choose == 3 && prevChoose != choose){
            heightmap = ChooseHeightMap("res/Texture/heightmap4.png");
            prevChoose = choose;
        }

        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(WHITE);
            BeginMode3D(camera);
                BeginShaderMode(heightmap.shader);
                    DrawGrid(10, 1.0f);
                    DrawModel(heightmap.model, Vector3{-3.0f, 0.0f, -3.0f}, 5.0f, WHITE);
                    SetShaderValue(heightmap.shader, GetShaderLocation(heightmap.shader, "xColor"), &xValue, SHADER_UNIFORM_FLOAT);
                EndShaderMode();
            EndMode3D();
            //DrawTexture(texture, SCR_WIDTH - texture.width, 50, WHITE);
            if(GuiButton(Rectangle{500.0f, 50.0f, 70.0f ,30.0f}, "HeightMap1"))
                choose = 0;
            else if(GuiButton(Rectangle{500.0f, 80.0f, 70.0f ,30.0f}, "HeightMap2"))
                choose = 1;
            else if(GuiButton(Rectangle{500.0f, 110.0f, 70.0f ,30.0f}, "HeightMap3"))
                choose = 2;
            else if(GuiButton(Rectangle{500.0f, 140.0f, 70.0f ,30.0f}, "HeightMap4"))
                choose = 3;
        EndDrawing();
    }

    CloseWindow();
}