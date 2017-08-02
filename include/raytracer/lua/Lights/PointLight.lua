[[-----------------------------------------------------------------------------
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
-----------------------------------------------------------------------------]]
local Light = require('Lights.Light')
local Decay = require('Lights.Decay')

PointLight = {}

function PointLight.new()
	local self = Light.new()

	-- Public member variables
	self.name = "Point"
	self.position = {x = 0.0, y = 0.0, z = 0.0}
	self.color = {r = 1.0, g = 1.0, b = 1.0}
	self.intensity = 1.0
	self.attenuate = false
	self.decay = Decay.Quadratic

	-- Public methods
	function self.locatedAt(x, y, z)
		self.position.x, self.position.y, self.position.z = x, y, z
		return self
	end

	function self.withColor(r, g, b)
		self.color.r, self.color.g, self.color.b = r, g, b
		return self
	end

	function self.withIntensity(i)
		self.intensity = i
		return self
	end

	function self.shouldAttenuate(flag)
		self.attenuate = flag
		return self
	end

	function self.withDecay(d)
		self.decay = d
		return self
	end

	return self
end

return PointLight