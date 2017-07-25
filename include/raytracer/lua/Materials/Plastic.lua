Plastic = {}

function Plastic.new()
	local self = {}

	-- Public member variables
	self.name = "Plastic"
	self.diffuse_color = {r = 0.0, g = 0.0, b = 0.0}
	self.diffuse_reflection = 1.0
	self.ambient_color = {r = 0.0, g = 0.0, b = 0.0}
	self.ambient_reflection = 1.0
	self.specular_color = {r = 1.0, g = 1.0, b = 1.0}
	self.specular_reflection = 1.0
	self.specular_exp = 1.0

	-- Public methods
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

	function self.withSpecularColor(r, g, b)
		self.specular_color.r, self.specular_color.g, self.specular_color.b = r, g, b
		return self
	end

	function self.withSpecularReflection(r)
		self.specular_reflection = r
		return self
	end

	function self.andSpecularExponent(e)
		self.specular_exp = e
		return self
	end

	return self
end

return Plastic
