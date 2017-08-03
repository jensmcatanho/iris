-- Camera
camera = Pinhole.new()
	.withEyeAt(0.0, 1.0, 3.0)
	.lookingAt(0.0, 0.0, 0.0)
	.withImagePlaneDistance(75.0)

---- Plane
-- Material
matte1 = Matte.new()
	.withDiffuseColor(0.5, 0.5, 0.5)
	.withAmbientReflection(0.50)
	.withDiffuseReflection(0.85)

-- Object
plane = Plane.new()
	.locatedAt(0.0, 0.0, -5.0)
	.lookingAt(0.0, 0.0, 1.0)
	.withMaterial(matte1)

---- Sphere #1
-- Material
matte2 = Matte.new()
	.withDiffuseColor(1.0, 0.0, 0.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.75)

-- Object
sphere_matte = Sphere.new()
	.centeredAt(0.0, 4.0, 0.0)
	.withRadius(1.0)
	.withMaterial(matte2)

---- Sphere #2
-- Material
plastic = Plastic.new()
	.withDiffuseColor(1.0, 0.0, 0.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.60)
	.withSpecularReflection(0.20)
	.andSpecularExponent(100)

-- Object
sphere_plastic = Sphere.new()
	.centeredAt(0.0, 1.0, 0.0)
	.withRadius(1.0)
	.withMaterial(plastic)

-- Light
light = PointLight.new()
	.locatedAt(5.0, 5.0, 5.0)
	.withIntensity(4.0)

-- Scene
scene = Scene.new()
	.AddCamera(camera)
	.AddObject(plane)
	.AddObject(sphere_matte)
	.AddObject(sphere_plastic)
	.AddLight(light)
