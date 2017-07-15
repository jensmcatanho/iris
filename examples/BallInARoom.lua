local SceneManager = require('../Lua/lib/SceneManager')

sm = SceneManager:new()

image = Image:new(200, 200)
image.SetNumSamples(16)

sphere = Sphere:new(0.0, 1.0, 0.0)
sphere.SetCenter({0.0, 0.0, 0.0})
sphere.SetRadius(80)
sm.AddObject(sphere)

-- Back
planeA = Plane:new(0.1, 0.1, 0.1)
planeA.SetPoint(0.0, 0.0, -80.0)
planeA.SetNormal(0.0, 0.0, 1.0)
sm.AddObject(planeA)

-- Top	
planeB = Plane:new(1.0, 1.0, 1.0)
planeB.SetPoint(0.0, 80.0, 0.0)
planeB.SetNormal(0.0, -1.0, 0.2)
sm.AddObject(planeB)

-- Bottom
planeC = Plane:new(1.0, 1.0, 1.0)
planeC.SetPoint(0.0, -80.0, 0.0)
planeC.SetNormal(0.0, 1.0, 0.2)
sm.AddObject(planeC)

-- Left
planeD = Plane:new(1.0, 0.0, 0.0)
planeD.SetPoint(-80.0, 0.0, 0.0)
planeD.SetNormal(1.0, 0.0, 0.2)
sm.AddObject(planeD)

-- Bottom
planeE = Plane:new(0.0, 0.0, 1.0)
planeE.SetPoint(80.0, 0.0, 0.0)
planeE.SetNormal(-10.0, 0.0, 0.2)
sm.AddObject(planeE)
