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
Visual Studio

## Loading models

To load a custom model, you can edit the source code like this (It automatically looks in a folder called "Assets/models"):
```Cpp
mesh.MakeMesh("filename.obj");

```

## Loading Textures

To load a texture, you can edit the source code like this (It automatically looks in a folder called "Assets/textures")
```cpp
engine.LoadTexture("filename.jpg");
```

<img alt="image" src="https://i.imgur.com/9Bz7drR.gif" />
