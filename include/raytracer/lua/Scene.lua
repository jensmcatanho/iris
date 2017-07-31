-- BRDFs
local BRDF = require('BRDFs.BRDF')

-- Cameras
local Camera = require('Cameras.Camera')
local Pinhole = require('Cameras.Pinhole')
local Orthographic = require('Cameras.Orthographic')

-- Image
local Image = require('Image.Image')
local Sampler = require('Image.Sampler')
local Tracer = require('Image.Tracer')

-- Lights
local Light = require('Lights.Light')
local AmbientLight = require('Lights.AmbientLight')
local Directional = require('Lights.DirectionalLight')
local PointLight = require('Lights.PointLight')

-- Materials
local Matte = require('Materials.Matte')
local Plastic = require('Materials.Plastic')

-- Objects
local Object = require('Objects.Object')
local Plane = require('Objects.Plane')
local Sphere = require('Objects.Sphere')

Scene = {}

function Scene.new()
	local self = {}

	-- Public member variables
	self.object_list = {}
	self.light_list = {}

	self.tracer = Tracer.RayCast
	self.image = Image.new()
	self.camera = Pinhole.new()
	self.ambient = AmbientLight.new()

	-- Public methods
	function self.AddObject(obj)
		table.insert(self.object_list, obj)
		return self
	end

	function self.AddLight(light)
		table.insert(self.light_list, light)
		return self
	end

	function self.AddCamera(cam)
		self.camera = cam
		return self
	end

	function self.withTracer(t)
		self.tracer = t
		return self
	end

	function self.withImage(i)
		self.image = i
		return self
	end

	return self
end

return Scene
