# GLBrebis
A simple GL extension wrangler drop-in generator for OpenGL and OpenGL ES apps.

this program will generate a set of highly portable C99 compliant OpenGL and OpenGL ES function wrangler code with any *prefix* customization that you want. Just generate your wrangler code, drop the two files into your project and start coding! It's as simple as that.

Now available as a web service:

http://35.186.184.156:3772/?prefix=Mut&include=mut

('Mut' is just a fictional example)

This project replaces the need of using a 3rdparty library to wrangle your GL function pointers (e.g. GLEW). Works pretty much the same way than GLEW, but also adds GLES support, and to some useful utilities, such as `<prefix>GLSupport`:

```C++
if(<prefix>GLSupport(GL_VERSION_3_0) || <prefix>GLSupport(GL_ES_VERSION_3_0))
{
    void *pMapped = glMapBufferRange(target, 0, buffer.size(), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    std::copy(buffer.begin(), buffer.end(), pMapped);
    glUnmapBuffer(target);
}
else if (<prefix>GLSupport(GL_EXT_map_buffer_range) && <prefix>GLSupport(GL_OES_mapbuffer)
{
    void *pMapped = glMapBufferRangeEXT(target, 0, buffer.size(), GL_MAP_WRITE_BIT_EXT | GL_MAP_INVALIDATE_BUFFER_BIT_EXT);
    std::copy(buffer.begin(), buffer.end(), pMapped);
    glUnmapBufferOES(target);
}
else
{
    glBufferData(target, buffer.size(), (const GLvoid *)(&buffer[0]), usage);
}
```

And also comes with this very handy debugging tool that you can wrap around eveyr single GL function calls like so:

```C++
<prefix>GLCheckErrorDebug(glBindBuffer(handle));
```

`<prefix>GLCheckErrorDebug` checks the result of `glGetError` for you, parses the result and prints the error in `stderr` should an error be found. `glGetError` check is automatically removed when compiling in release.

# How to generate my project's drop-in extention wrangler header and source?

```
usage: GLBrebis -p <prefix> [-i includepath] [-z]
-h, --help                                Usage Information
-p<prefix>, --prefix=<prefix>             Project prefix to append to every
                                          generated files and symbols
-i<includepath>, --include=<includepath>  include path prefix to use in the
                                          generated GL.c
-z, --zip                                 Create a zip archive containing all
                                          of the generated content.
```

Example for a fictional project called 'Mut' :
```
GLBrebis -p Mut -i mut
```
* `-p` is mandatory. If you do `-p Mut`, the script will generate `MutGL.c`, and `MutGL.h`, including symbols that will automatically be named after `Mut`.  For example, you will see `_MUT_GL_H_` header guards, and utility functions will be named `mutGLInit()` and `mutGLShutdown()`, etc.
* `-i,--include` is optional. It's mostly used by `MutGL.c` to do `#include <mut/MutGL.h>` instead of just `#include <MutGL.h>` to help you match your application's file layout requirement.

And if everything goes well, you should have `MutGL.c`, `mut/MutGL.h`, and `KHR/khrplatform.h` on your file system.

# How to use the generated extention wrangler code in my project?

1. Drop-in the three generated files into your project
2. Add `<prefix>GL.c` to your CMakeLists.txt/Makefile/VCProj/etc
3. make sure you include `#include "<prefix>GL.h"` instead of including the regular.
4. create your window *and* your GL context.
5. Once the gl context successfully created, simply call `bool success = <prefix>GLInit();`.
6. When shutting down, don't forget to call `<prefix>GLShutdown();`
