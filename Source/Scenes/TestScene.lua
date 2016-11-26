package.path = "../Source/Lua/lib/?.lua;" .. package.path
local Scene = require('Scene')

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
scene.camera.look_at.x = 0.0
scene.camera.look_at.x = 0.0
scene.camera.vpdistance = 850.0

print("Oi")

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