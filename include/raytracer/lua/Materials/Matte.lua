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