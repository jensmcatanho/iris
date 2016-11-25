package.path = "../Source/Lua/lib/?.lua;" .. package.path
local Scene = require('Scene')

scene = Scene.new()

scene.image.width = 400
scene.image.height = 400
scene.image.pixel_size = 0.5
scene.image.sampler = Sampler.MultiJittered

scene.tracer = Tracer.RayCast

scene.camera = Pinhole.new()