# OpenGL-Playground

## Dependencies
-   **[OpenGL Mathematics (GLM)](https://glm.g-truc.net/0.9.9/index.html)** is a C++ mathematics library for 3D software based on the OpenGL Shading Language (GLSL) specification
-   **[std-image](https://github.com/nothings/stb)** to load images as texture.
-   **[FreeGLUT](http://freeglut.sourceforge.net/)** is a free-software/open-source alternative to the OpenGL Utility Toolkit (GLUT) library. Grab binary libs for [Windows](https://www.transmissionzero.co.uk/software/freeglut-devel/)
-   **[The OpenGL Extension Wrangler Library (GLEW)](http://glew.sourceforge.net/)** is a cross-platform open-source C/C++ extension loading library. GLEW provides efficient run-time mechanisms for determining which OpenGL extensions are supported on the target platform.

## Config setting in Visual Studio
Set project properties:
-   **Include Dir:** Include dependencies includes
-   **Linker:** Add Additional Library Directories of glew and freeglut
-   **Linker Input:** glew32s.lib, glew32.lib, freeglut.lib
