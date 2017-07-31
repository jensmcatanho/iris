-- Camera
camera = Pinhole.new()
	.withEyeAt(0.0, 10.0, 10.0)
	.lookingAt(0.0, 0.0, -1.0)
	.withImagePlaneDistance(100.0)

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

---- Sphere
-- Material
matte2 = Matte.new()
	.withDiffuseColor(1.0, 0.0, 0.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.45)

-- Object
red_sphere = Sphere.new()
	.centeredAt(0.0, 3.0, 5.0)
	.withRadius(3.0)
	.withMaterial(matte2)

-- Light
light = PointLight.new()
	.locatedAt(-10.0, 10.0, 10.0)
	.withIntensity(4.0)

-- Scene
scene = Scene.new()
	.AddCamera(camera)
	.AddObject(plane)
	.AddObject(red_sphere)
	.AddLight(light)
