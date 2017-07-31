## Object Instantiation
This example demonstrates the simplest way to set up a scene and instantiate the primitive objects in Iris.

Theoretically, the simplest scene requires only a camera to render the it. Here, we set the pinhole (See Perspective Viewing) camera's location in the scene (`withEyeAt()`), specify where it's looking at (`lookingAt()`) and how far from is it's image (or view) plane from it's eye (`withImagePlaneDistance()`). Next, the camera is attached to the scene (`AddCamera()`).

```lua
-- Camera
camera = Pinhole.new()
	.withEyeAt(0.0, 1.0, 2.0)
	.lookingAt(0.0, 1.0, 0.0)
	.withImagePlaneDistance(100.0)

-- Scene
scene = Scene.new()
	.AddCamera(camera)
```

However, if no object is instantiated, the final image is just a black screen.

![Scene with no objects](http://jeancatanho.com/wp-content/uploads/sites/3/2017/07/Scene.png "Scene with no objects")

Let's make our scene more interesting by adding a plane to it. We'll need to add a light source (See Point Lights) as well so that the floor is illuminated and, therefore, visible. Furthermore, all objects need to have a material (See Materials) attached so the tracer knows how their surface interacts with light.

```lua
---- Plane
-- Material
matte1 = Matte.new()
	.withDiffuseColor(0.2, 0.5, 0.5)
	.withAmbientReflection(0.50)
	.withDiffuseReflection(0.85)

-- Object
plane = Plane.new()
	.locatedAt(0.0, 0.0, 0.0)
	.lookingAt(0.0, 1.0, 0.0)
	.withMaterial(matte1)

-- Light
light = PointLight.new()
	.locatedAt(-5.0, 5.0, 5.0)
	.withIntensity(4.0)
	
-- Scene
scene = Scene.new()
	.AddCamera(camera)
	.AddObject(plane)
	.AddLight(light)
```

We create a Matte material, set it's color to a shade of blue (`withDiffuseColor()`) and the percentage of ambient (`withAmbientReflection()`) and diffuse (`withDiffuseReflection()`) reflection are set to 50% and 85% respectively. Next, we create the plane, set it's location (`locatedAt()`), set where it's normal vector points to (`lookingAt()`) and attach the material we previously created to the object (`withMaterial()`).

For the light source, we'll create a point light, set it's location (`locatedAt()`) and it's intensity (`withIntensity()`). Finally, we add the plane (`AddObject()`) and the light (`AddLight()`) to the scene.

![Scene with a plane and a point light](http://jeancatanho.com/wp-content/uploads/sites/3/2017/07/Scene-1.png "Scene with a plane and a point light")

Let's add a red sphere to the scene now. It's code is very similar to the plane.

```lua
---- Sphere
-- Material
matte2 = Matte.new()
	.withDiffuseColor(1.0, 0.0, 0.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.45)

-- Object
red_sphere = Sphere.new()
	.centeredAt(0.0, 1.0, 0.0)
	.withRadius(1.0)
	.withMaterial(matte2)
	
-- Scene
scene = Scene.new()
	.AddCamera(camera)
	.AddObject(plane)
	.AddObject(red_sphere)
	.AddLight(light)

```

We create a new Matte material for the sphere with different parameters from the plane's material. Next, we instantiate the sphere specifying it's location (`centeredAt()`), it's radius (`withRadius()`) and attaching it's material. At last, we add the sphere to the scene just as it was done previously with the plane.

![Scene with objects and light](http://jeancatanho.com/wp-content/uploads/sites/3/2017/07/Scene-2.png "Scene with objects and light")

