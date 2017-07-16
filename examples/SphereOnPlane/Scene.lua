-- Camera
camera = Pinhole.new()
	.withEyeAt(0.0, 0.0, 500.0)
	.lookingAt(0.0, 0.0, -1.0)

camera.vpdistance = 850.0

-- Plane
phong = Phong.new()
	.withDiffuseColor(1.0, 0.0, 1.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.65)
	.withSpecularReflection(0.05)

plane = Plane.new()
	.locatedAt(0.0, 0.0, 0.0)
	.lookingAt(0.0, 0.0, 1.0)
	.withMaterial(phong)

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

-- Light
light = PointLight.new()
	.locatedAt(0.0, 50.0, 100.0)
	.withIntensity(3.0)
	.castsShadows(true)

-- Image
image = Image.new()
	.across(400, 400)
	.withPixelSize(0.5)
	.withSampler(Sampler.MultiJittered)
	.withSamples(16)

-- Scene
scene = Scene.new()
	.withTracer(Tracer.RayCast)
	.withImage(image)
	.AddCamera(camera)
	.AddObject(plane)
	.AddObject(sphere)
	.AddLight(light)
