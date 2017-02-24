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
plane = Plane.new()
plane.point.x = 0.0
plane.point.y = 0.0
plane.point.z = 0.0
plane.normal.x = 0.0
plane.normal.y = 0.0
plane.normal.z = 1.0

phong = Phong.new()
	.withDiffuseColor(1.0, 1.0, 0.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.65)
	.withSpecularReflection(0.05)

plane.AddMaterial(phong)
scene.AddObject(plane)

-- Sphere 1
sphere1 = Sphere.new()
sphere1.center.x = 10.0
sphere1.center.y = 20.0
sphere1.center.z = 19.0
sphere1.radius = 10

phong1 = Phong.new()
	.withDiffuseColor(0.0, 1.0, 0.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.65)
	.withSpecularReflection(0.05)

sphere1.AddMaterial(phong1)
scene.AddObject(sphere1)

-- Light
light = PointLight.new()
light.position.x = 0.0
light.position.y = 50.0
light.position.z = 100.0
light.intensity = 3.0
light.shadows = true

scene.AddLight(light)