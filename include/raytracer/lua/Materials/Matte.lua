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
Matte = {}

function Matte.new()
	local self = {}

	-- Public member variables
	self.name = "Matte"
	self.diffuse_brdf = BRDF.Lambertian
	self.diffuse_color = {r = 0.0, g = 0.0, b = 0.0}
	self.diffuse_reflection = 1.0
	self.ambient_color = {r = 0.0, g = 0.0, b = 0.0}
	self.ambient_reflection = 1.0

	-- Public methods
	function self.withDiffuseBRDF(brdf)
		self.diffuse_brdf = brdf
		return self
	end

	function self.withDiffuseColor(r, g, b)
		self.diffuse_color.r, self.diffuse_color.g, self.diffuse_color.b = r, g, b
		return self
	end

	function self.withDiffuseReflection(r)
		self.diffuse_reflection = r
		return self
	end

	function self.withAmbientColor(r, g, b)
		self.ambient_color.r, self.ambient_color.g, self.ambient_color.b = r, g, b
		return self
	end

	function self.withAmbientReflection(r)
		self.ambient_reflection = r
		return self
	end

	return self
end

return Matte