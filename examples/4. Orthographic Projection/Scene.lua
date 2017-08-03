-- Camera
camera = Orthographic.new()
	.withEyeAt(0.0, 1.0, 2.0)
	.lookingAt(0.0, 1.0, 0.0)
	.withImagePlaneDistance(100.0)

---- Plane
-- Material
matte1 = Matte.new()
	.withDiffuseColor(0.9, 0.9, 0.9)
	.withAmbientReflection(0.50)
	.withDiffuseReflection(0.65)

-- Object
plane = Plane.new()
	.locatedAt(0.0, 0.0, -50.0)
	.lookingAt(0.0, 0.0, 1.0)
	.withMaterial(matte1)

---- Sphere #1
-- Material
matte2 = Matte.new()
	.withDiffuseColor(1.0, 0.0, 0.0)
	.withAmbientReflection(0.30)
	.withDiffuseReflection(0.60)

-- Object
red_sphere = Sphere.new()
	.centeredAt(-120.0, 0.0, 40.0)
	.withRadius(40.0)
	.withMaterial(matte2)

---- Sphere #2
-- Material
matte3 = Matte.new()
	.withDiffuseColor(0.0, 1.0, 0.0)
	.withAmbientReflection(0.30)
	.withDiffuseReflection(0.60)

-- Object
green_sphere = Sphere.new()
	.centeredAt(0.0, 0.0, 0.0)
	.withRadius(40.0)
	.withMaterial(matte3)

---- Sphere #3
-- Material
matte4 = Matte.new()
	.withDiffuseColor(0.0, 0.0, 1.0)
	.withAmbientReflection(0.30)
	.withDiffuseReflection(0.60)

-- Object
blue_sphere = Sphere.new()
	.centeredAt(120.0, 0.0, -40.0)
	.withRadius(40.0)
	.withMaterial(matte4)

-- Light
light = PointLight.new()
	.locatedAt(0.0, 50.0, 50.0)
	.withIntensity(5.0)

-- Scene
scene = Scene.new()
	.AddCamera(camera)
	.AddObject(plane)
	.AddObject(red_sphere)
	.AddObject(green_sphere)
	.AddObject(blue_sphere)
	.AddLight(light)
