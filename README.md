# Model Viewer Engine

A lightweight 3D model viewer which can transform, rotate, and translate models in real time.  
The engine uses imgui.

## Features

Real-time model manipulation
Translate (X/Y/Z)
Rotate (X/Y/Z)
Scale / Transform
ImGui UI panel for adjustments
Loads OBJ models with textures
Default model: **AK-47**

### Requirements
Build in x64
Visual Studio IDE

## Loading models

To load a custom model, you can edit the source code like this:
```Cpp
mesh.MakeMesh("Path_to_model");

![Preview Image](FirstOpenGLProject/images/image.png)
