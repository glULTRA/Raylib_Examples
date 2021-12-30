#version 330 core

in vec2 coord;
uniform float MaxIterations;
uniform float xColor;

out vec4 pixelColor;

void main()
{
    float   real  = coord.x;
    float   imag  = coord.y;
    float   Creal = real;  
    float   Cimag = imag;  

    float r2 = 0.0;

    for (float iter = 0.0; iter < MaxIterations && r2 < 4.0; ++iter)
    {
        float tempreal = real;

        real = (tempreal * tempreal) - (imag * imag) + Creal;
        imag = 2.0 * tempreal * imag + Cimag;
        r2   = (real * real) + (imag * imag);
    }

    vec3 color;

    if (r2 < 4.0)
        color = vec3(0.0f, 0.0f, 0.0f);
    else
        color = vec3(1.0f, 1.0f, 1.0f);

    pixelColor = vec4(color, 1.0);
    //pixelColor = vec4(1.0f * xColor, 0.5f, 0.31f, 1.0f);
}