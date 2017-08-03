--[[
The MIT License (MIT)

Copyright (c) 2016-2017 Jean Michel Catanho

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
--]]
-- BRDFs
local BRDF = require('BRDFs.BRDF')

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
