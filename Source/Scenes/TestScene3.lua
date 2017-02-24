package.path = "../Source/Lua/lib/?.lua;" .. package.path
local Scene = require('Scene')

-- Scene
scene = Scene.new()

scene.image.width = 400
scene.image.height = 400
scene.image.pixel_size = 0.5
scene.image.sampler = Sampler.MultiJittered
scene.image.samples = 16

scene.tracer = Tracer.RayCast

scene.camera = Pinhole.new()
	.withEyeAt(0.0, 0.0, 500.0)
	.lookingAt(0.0, 0.0, -1.0)

scene.camera.vpdistance = 850.0

-- Plane
phong = Phong.new()
	.withDiffuseColor(1.0, 1.0, 0.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.65)
	.withSpecularReflection(0.05)

plane = Plane.new()
	.locatedAt(0.0, 0.0, 0.0)
	.lookingAt(0.0, 0.0, 1.0)
	.withMaterial(phong)

scene.AddObject(plane)

-- Sphere
phong1 = Phong.new()
	.withDiffuseColor(0.0, 1.0, 0.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.65)
	.withSpecularReflection(0.05)

sphere = Sphere.new()
	.centeredAt(10.0, 20.0, 19.0)
	.withRadius(10)
	.withMaterial(phong1)

scene.AddObject(sphere)

-- Light
light = PointLight.new()
	.locatedAt(0.0, 50.0, 100.0)
	.withIntensity(3.0)
	.castsShadows(true)

scene.AddLight(light)