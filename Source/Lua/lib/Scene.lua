-- Cameras
local Camera = require('Cameras.Camera')
local Pinhole = require('Cameras.Pinhole')

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
local Phong = require('Materials.Phong')

-- Objects
local Object = require('Objects.Object')
local Plane = require('Objects.Plane')
local Sphere = require('Objects.Sphere')


Scene = {}

function Scene.new()
	local self = {}

	-- Private member variables
	self.object_list = {}
	self.light_list = {}

	-- Public member variables
	self.tracer = Tracer.RayCast
	self.image = Image.new(200, 200)
	self.camera = Pinhole.new()
	self.ambient = AmbientLight.new()

	-- Private methods

	-- Public methods
	function self.AddObject(obj)
		table.insert(object_list, obj)
	end

	function self.AddLight(light)
		table.insert(light_list, light)
	end

	return self
end

return Scene
