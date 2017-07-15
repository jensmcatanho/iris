local SceneManager = require('../Lua/lib/SceneManager')

sm = SceneManager:new()

image = Image:new(200, 200)
image.SetNumSamples(256)

sphereA = Sphere:new(1.0, 0.0, 0.0)
sphereA.SetCenter({0.0, -25.0, 0.0})
sphereA.SetRadius(80)
sm.AddObject(sphereA)

sphereB = Sphere:new(1.0, 1.0, 0.0)
sphereB.SetCenter({0.0, 30.0, 0.0})
sphereB.SetRadius(60)
sm.AddObject(sphereB)

plane = Plane:new(0.0, 0.3, 0.0)
plane.SetPoint({0.0, 0.0, 0.0})
plane.SetNormal({0.0, 1.0, 1.0})
sm.AddObject(plane)
