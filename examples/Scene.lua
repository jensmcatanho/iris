-- Camera
camera = Pinhole.new()
	.withEyeAt(0.0, 0.0, 500.0)
	.lookingAt(0.0, 0.0, -1.0)

-- Image
image = Image.new()
	.across(400, 400)
	.withPixelSize(1)
	.withSampler(Sampler.MultiJittered)
	.withSamples(16)

-- Bottom
phong = Phong.new()
	.withDiffuseColor(1.0, 1.0, 1.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.65)
	.withSpecularReflection(0.05)

plane = Plane.new()
	.locatedAt(0.0, -80.0, 0.0)
	.lookingAt(0.0, 1.0, 0.0)
	.withMaterial(phong)

-- Top
phong = Phong.new()
	.withDiffuseColor(1.0, 0.0, 1.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.65)
	.withSpecularReflection(0.05)

plane1 = Plane.new()
	.locatedAt(0.0, 80.0, 0.0)
	.lookingAt(0.0, -1.0, 0.0)
	.withMaterial(phong)

-- Sphere
phong = Phong.new()
	.withDiffuseColor(0.0, 1.0, 1.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.65)
	.withSpecularReflection(0.05)

sphere = Sphere.new()
	.centeredAt(0.0, 0.0, 0.0)
	.withRadius(30)
	.withMaterial(phong)

-- Light
light = PointLight.new()
	.locatedAt(0.0, 79.0, 100.0)
	.withIntensity(2.0)
	.castsShadows(true)

-- Scene
scene = Scene.new()
	.withTracer(Tracer.RayCast)
	.withImage(image)
	.AddCamera(camera)
	.AddObject(sphere)
	.AddObject(plane)
	.AddObject(plane1)
	.AddLight(light)