local Light = require('Lights.Light')

AmbientLight = {}

function AmbientLight.new()
	local self = Light.new()

	-- Public member variables
	self.name = "Ambient"
	self.color = {r = 1.0, g = 1.0, b = 1.0}
	self.intensity = 1.0

	-- Public methods
	function self.withColor(r, g, b)
		self.color.r, self.color.g, self.color.b = r, g, b
		return self
	end

	function self.withIntensity(i)
		self.intensity = i
		return self
	end

	return self
end

return AmbientLight