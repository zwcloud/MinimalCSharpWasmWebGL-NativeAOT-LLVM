#include <emscripten.h>
#include <SDL.h>

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>

// Shader sources
const GLchar* vertexSource =
    "attribute vec4 position;                     \n"
    "void main()                                  \n"
    "{                                            \n"
    "  gl_Position = vec4(position.xyz, 1.0);     \n"
    "}                                            \n";
const GLchar* fragmentSource =
    "precision mediump float;\n"
    "void main()                                  \n"
    "{                                            \n"
    "  gl_FragColor[0] = gl_FragCoord.x/640.0;    \n"
    "  gl_FragColor[1] = gl_FragCoord.y/480.0;    \n"
    "  gl_FragColor[2] = 0.5;                     \n"
    "}                                            \n";

// an example of something we will control from the javascript side
int background_is_black = 1;

// the function called by the javascript code
void EMSCRIPTEN_KEEPALIVE toggle_background_color()
{
	if (background_is_black)
	{
		background_is_black = 0;
	}
	else{
		background_is_black = 1;
	}
}

SDL_Window *window = 0;
SDL_Renderer* renderer = 0;
GLfloat vertices[] = {0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f};

void loop()
{
	// move a vertex
	const uint32_t milliseconds_since_start = SDL_GetTicks();
	const uint32_t milliseconds_per_loop = 3000;
	vertices[0] = ( milliseconds_since_start % milliseconds_per_loop ) / (1.0f * milliseconds_per_loop) - 0.5f;
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Clear the screen
	if( background_is_black )
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	else
		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw a triangle from the 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapWindow(window);
}

int NativeFunc()
{
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);


    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    emscripten_set_main_loop(loop, 0, 1);

    return EXIT_SUCCESS;
}