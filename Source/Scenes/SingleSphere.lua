local SceneManager = require('../Lua/lib/SceneManager')

sm = SceneManager:new()

image = Image:new(200, 200)

sphere = Sphere:new(0.0, 0.0, 1.0)
sphere.SetCenter({0.0, 0.0, 0.0})
sphere.SetRadius(85.0)

sm.AddObject(sphere)
