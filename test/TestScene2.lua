package.path = "../Source/Lua/lib/?.lua;" .. package.path
local Scene = require('Scene')


-- Scene
scene = Scene.new()

scene.image.width = 400
scene.image.height = 400
scene.image.pixel_size = 1
scene.image.sampler = Sampler.MultiJittered

scene.tracer = Tracer.RayCast

scene.camera.eye.x = 0.0
scene.camera.eye.y = 0.0
scene.camera.eye.z = 500.0
scene.camera.look_at.x = 0.0
scene.camera.look_at.y = 0.0
scene.camera.look_at.z = -1.0
scene.camera.vpdistance = 850.0

-- Sphere 1
sphere1 = Sphere.new()
sphere1.center.x = 0.0
sphere1.center.y = 0.0
sphere1.center.z = 0.0
sphere1.radius = 80

phong = Phong.new()
phong.ambient_reflection = 0.25
phong.diffuse_reflection = 0.65
phong.specular_reflection = 0.05
phong.diffuse_color.r = 0.8
phong.diffuse_color.g = 0.3
phong.diffuse_color.b = 0.3

sphere1.AddMaterial(phong)
scene.AddObject(sphere1)

-- Bottom
bottom = Plane.new()
bottom.point.x = 0.0
bottom.point.y = -80.0
bottom.point.z = 0.0
bottom.normal.x = 0.0
bottom.normal.y = 1.0
bottom.normal.z = 0.0

matte = Matte.new()
matte.ambient_reflection = 0.15
matte.diffuse_reflection = 0.50
matte.diffuse_color.r = 0.0
matte.diffuse_color.g = 0.4
matte.diffuse_color.b = 0.2

bottom.AddMaterial(matte)
--scene.AddObject(bottom)

-- Light
light = PointLight.new()
light.position.x = 100.0
light.position.y = 50.0
light.position.z = 100.0
light.intensity = 10.0

scene.AddLight(light)