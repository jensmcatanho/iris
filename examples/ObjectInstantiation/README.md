## Object Instantiation
This example demonstrates the simplest way to set up a scene and instantiate the primitive objects in Iris.

Theoretically, the simplest scene requires only a camera to render the it. 
```lua
-- Camera
camera = Pinhole.new()
	.withEyeAt(0.0, 10.0, 10.0)
	.lookingAt(0.0, 0.0, -1.0)
	.withImagePlaneDistance(100.0)

-- Scene
scene = Scene.new()
	.AddCamera(camera)
```

However, if no object is instantiated, the final image is just a black screen:

![Scene with no objects](http://jeancatanho.com/wp-content/uploads/sites/3/2017/07/Scene.png "Scene with no objects")
