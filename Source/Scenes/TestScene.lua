package.path = "../Source/Lua/lib/?.lua;" .. package.path
local Scene = require('Scene')


-- Scene
scene = Scene.new()

scene.image.width = 400
scene.image.height = 400
scene.image.pixel_size = 0.5
scene.image.sampler = Sampler.MultiJittered

scene.tracer = Tracer.RayCast

scene.camera.eye.x = 0.0
scene.camera.eye.y = 0.0
scene.camera.eye.z = 500.0
scene.camera.look_at.x = -5.0
scene.camera.look_at.y = 0.0
scene.camera.look_at.z = 0.0
scene.camera.vpdistance = 850.0

-- Sphere 1
sphere1 = Sphere.new()
sphere1.center.x = 10.0
sphere1.center.y = -5.0
sphere1.center.z = 0.0
sphere1.radius = 27

phong = Phong.new()
phong.ambient_reflection = 0.25
phong.diffuse_reflection = 0.65
phong.specular_reflection = 0.05
phong.diffuse_color.r = 1.0
phong.diffuse_color.g = 1.0
phong.diffuse_color.b = 0.0

sphere1.AddMaterial(phong)
scene.AddObject(sphere1)

-- Sphere 2
sphere2 = Sphere.new()
sphere2.center.x = -25.0
sphere2.center.y = 10.0
sphere2.center.z = -35.0
sphere2.radius = 27

matte1 = Matte.new()
matte1.ambient_reflection = 0.15
matte1.diffuse_reflection = 0.85
matte1.diffuse_color.r = 0.71
matte1.diffuse_color.g = 0.4
matte1.diffuse_color.b = 0.16

sphere2.AddMaterial(matte1)
scene.AddObject(sphere2)

-- Plane
plane = Plane.new()
plane.point.x = 0.0
plane.point.y = 0.0
plane.point.z = -50.0
plane.normal.x = 0.0
plane.normal.y = 0.0
plane.normal.z = 1.0

matte = Matte.new()
matte.ambient_reflection = 0.15
matte.diffuse_reflection = 0.50
matte.diffuse_color.r = 0.0
matte.diffuse_color.g = 0.4
matte.diffuse_color.b = 0.2

plane.AddMaterial(matte)
scene.AddObject(plane)

-- Light
light = PointLight.new()
light.position.x = 100.0
light.position.y = 50.0
light.position.z = 100.0
light.intensity = 3.0

scene.AddLight(light)