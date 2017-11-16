## Installation
Drop the game folder inside the .zip somewhere in your computer and execute the .exe

### Game controls
* Mouse Left Click to select a buttons
* Mouse Right Click Active camera movement:
	* WASD keys for movement
	* move the mouse to rotate
* Mouse Left Click + Left Alt:
	* move the camera arround a point
* Press F centred to selected Game Objects
* Mouse Left Click
	*You can selected Game Objets

### Main Menu
Is fixed at the top of the screen.
Buttons info:

*File ====>Open File submenu
	*Save ==> Save Scene on Assets folder
	*Load ==> Load Scene after showing a load window
	*Quit ==> Quit the application
	
*View ====>Open View submenu

	*Console ==> Open/Close the Console windows (Console info below)
	*Configuration ==>Open/Close the Configuration windows (Configuration info below)
	*Profiler ==>Open/Close the Profiler windows(Profiler info below)
	*Hierarchy ==> Open/Close the Console windows (Hierarchy info below)
	*Inspector ==>Open/Close the Configuration windows Inspectorinfo below)
	*Folders ==>Open/Close the Profiler windows(Folders info below)
        *Debug ==> Hover to see the debug options
		 	* Pulse on draw raycast to see the raycast
			* Pulse on draw quadtree to se the quadtree 

*Help ====>Open Help submenu

	*Documentation ==> Open a link to proyect wiki
	*Download latest ==>Open a link to proyect releases
	*Report a bug ==>Open a link to proyect github issues
	*About us ==>Open/Close the About us windows(About us info below)

### Console
This window shows important information about what happens when exporting a model, it will inform you if the operation has been successful or an error has occurred.

### Configuration
This window shows and allows to edit certain behaviors of the engine:
*Application

	*Application Name ==> Here you can change the name
	*Application Organization ==> Here you can change the Organization 
	*FPS ==> Here you can change the FPS 
	*Histograms ==> Here you can see a visual report of the fps and ms during the time
	*MemoryStatistics ==> Shows the memory in use and the memory used
*Window

	*Name ==> Change the name of the windows
	*Windows Option 
	*Windows Size ==> Change the size of the windows
*Input

	*Displays information about the mouse and keyboard like key down, key repeat, etc 
*Audio

	*Audio driver ==> Show audio drivers
	*Audio device ==> Show audio device
	*Music Volume ==> Change the music volume
	*FX Volume ==> Change the fx volume
*Hardware

	*SDL_Version ==> Show SDL_Version 
	*CPU's ==> Show the amount of CPU's
	*System RAM ==> Show the system RAM
	*GPU Vendor ==> Show the GPU Vendor
	*GPU ==> Show the GPU Model
	*GPU Version ==> Show the GPU drivers
	*OpenGL Version ==> Show the openGL version
*Render

	*Vsync ==> Active/Desactive Vsync
	
	*Depth test ==> Active/Desactive Depth test 
	
	*Cull face ==> Active/Desactive Cull face 
		*Front Culling ==> Active/Desactive Front Culling
		*Back Culling ==> Active/Desactive Back Culling
		
	*Lighting ==> Active/Desactive Lighting
		*Ambient ==> Change the Ambient light
	
	*Color Material ==> Active/Desactive Color Material 
		*Ambient ==> Change the Ambient color
		*Diffuse ==> Change the Diffuse color
		
	*Texture 2D ==> Active/Desactive Texture 2D 
	
	*FOG ==> Active/Desactive FOG
		*Densisty ==> Change the FOG densisty
		*Color==> Change the FOG color
	
	*Wireframe ==> Active/Desactive Wireframe 

### Profiler 
Shows a numerical record of the current speed of each module, to use it you have to open the trees, these will show if they have other elements to show
### About us 

	*Name ==> Name of the engine
	*Description ==> Description of the engine
	*Creators ==> Links to the github pages of the creators
	*Licenses ==> Links to the libraries used in this proyect

### Hierarchy
Show information all the GameObject of the scene
If a GameObject is disabled the inspector show the name on the game object in gray
	* Mouse Right Click Active :
		* Delete Game Object ==> Delete selected gameobject and his children
		* Create Game Object ==> Create gameobject on selection
### Inspector
Show information about the selected GameObject and Resources
If you are on the GameObject Inspector you can create Components using the Button "Create Component"
If you create a MeshRenderer Component a Mesh Component is created to
	* Mouse Right Click Active :
		* Delete Component : ==> Delete selected component (You can't delete a Component Mesh if the Game Object have a Component MeshRenderer)
##GameObject
This Engine implement GameObject (Unity like), GameObject contains
	*Enable ==> Enable/Disable GameObject
	*Transform ==> Position,Rotation,Scale of the gameobject
	*Show Bounding Box ==> To see a AABB bounding Box and OBB bounding box
	*Component ==> GameObject contais component that components do other functions (like mesh rendering)

##Component 
This Engine implement Component (Unity like) right now the components implemented are:
All Components have a check box on the right that enable/disable the component
	*Component Mesh ==> Allocate all vertices and index
		*Vertices ==> Show vertices count
		*Indices ==> Show indices count
		*Select Mesh ==> You can change the mesh of the component
	*Component Mesh Render ==> Draw Mesh and Textures
		*RPG Texture Color ==> Change texture color also if you put the mouse inside the image you can see it bigger
		*Select Texture ==> You can change the texture of the component
	*Component Camera ==> Draw Camera and frustum culling optimization
                *From the editor you can change the fov the near and far plane
                *You can see what the frustum is seeing, by pressing Set Render Camera
		*To activate the culling click on enable culling

##Resources
This Engine implement Resources (Unity like) right now the resources implemented are:

	*Resources Mesh 
	*Resources Texture
	*Resources Prefab

##Folders
Show the Assets info

#### Libraries 

This engine use <a href="https://www.libsdl.org/" >SDL library </a>

This engine use <a href="http://bulletphysics.org/wordpress/"> Bullet physics library </a>

This engine use <a href="https://github.com/ocornut/imgui" >ImGui library  </a>

This engine use <a href="https://github.com/nlohmann/json"> JSON library </a>

This engine use <a href="http://clb.demon.fi/MathGeoLib/nightly/"> MathGeolib </a>

This engine use <a href="http://assimp.sourceforge.net/"> Assimp </a>

This engine use <a href="http://openil.sourceforge.net/"> DevIL </a>

## Changelog
#### v0.8.0
* Added: Add Resource structure
* Added: Add ResourceManager
* Added: Add QuadTree
* Added: Add more options to camera

#### v0.7.0

* Added: Add GameObject structure
* Added: Add Component structure
* Added: Add Hierarchy of GameObjects
* Added: Add Serializacion of the scene
* Added: Add Folder System
* Added: Add Custom Format (.frog)
* Added: Add Transformations to components
* Added: Add AABB and OBB Bounding Box
* Added: Add Frustum Culing
* Added: Add Camera do it with MathGeolib
* Added: Add Mouse Picking 
* Added: Add Resize the camera view when you resize the window

#### v0.5.0

* Added: Add Inspector
* Added: Now you can can drag and drop textures

#### v0.4.5

* Added: DevIL library
* Added: Now you can load Textures

#### v0.4.0

* Added: Assimp library
* Added: Now we can load meshes
* Added: Add drag and drop functionality

#### v0.3.5
* Added: Add OpenGL Render Array Buffer mode
* Added: Add OpenGL Render Vertex mode


#### v0.3
* Added: Add Open GL functions
* Added: Add Render primitives
* Added: Add World space


#### v0.2
* Added: A configuration menu
* Added: A bar menu

#### v0.1
* Added: A Collision test windows.
* Added: A Random float and integer generator windows
* Added: A basic console

}
