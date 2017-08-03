-- Camera
camera = Pinhole.new()
	.withEyeAt(0.0, 15.0, 15.0)
	.lookingAt(0.0, -1.0, -1.0)
	.withZoom(1.2)
	.withImagePlaneDistance(100.0)

-- Floor
plastic = Plastic.new()
	.withDiffuseColor(0.5, 0.5, 0.5)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.65)
	.withSpecularReflection(0.05)

plane = Plane.new()
	.locatedAt(0.0, 0.0, 0.0)
	.lookingAt(0.0, 1.0, 0.0)
	.withMaterial(plastic)

-- Light
light = PointLight.new()
	.locatedAt(10.0, 20.0, 0.0)
	.withIntensity(5.0)
	.castsShadows(true)

-- Sphere #1
plastic = Plastic.new()
	.withDiffuseColor(1.0, 0.0, 0.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.65)
	.withSpecularReflection(0.05)

sphere1 = Sphere.new()
	.centeredAt(0.0, 5.0, 10.0)
	.withRadius(5)
	.withMaterial(plastic)

-- Sphere #2
plastic = Plastic.new()
	.withDiffuseColor(0.0, 1.0, 0.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.65)
	.withSpecularReflection(0.05)

sphere2 = Sphere.new()
	.centeredAt(0.0, 5.0, 0.0)
	.withRadius(5)
	.withMaterial(plastic)

-- Sphere #3
plastic = Plastic.new()
	.withDiffuseColor(0.0, 0.0, 1.0)
	.withAmbientReflection(0.25)
	.withDiffuseReflection(0.65)
	.withSpecularReflection(0.05)

sphere3 = Sphere.new()
	.centeredAt(0.0, 5.0, -10.0)
	.withRadius(5)
	.withMaterial(plastic)

-- Image
image = Image.new()
	.across(400, 400)
	.withPixelSize(1)
	.withSampler(Sampler.MultiJittered)
	.withSamples(16)

-- Scene
scene = Scene.new()
	.withTracer(Tracer.RayCast)
	.withImage(image)
	.AddCamera(camera)
	.AddObject(plane)
	.AddObject(sphere1)
	.AddObject(sphere2)
	.AddObject(sphere3)
	.AddLight(light)
