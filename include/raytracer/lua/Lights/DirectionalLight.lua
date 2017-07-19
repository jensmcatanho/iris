local Light = require('Lights.Light')

DirectionalLight = {}

function DirectionalLight.new()
	local self = Light.new()

	-- Public member variables
	self.name = "Directional"
	self.direction = {x = 0.0, y = -1.0, z = 0.0}
	self.color = {r = 1.0, g = 1.0, b = 1.0}
	self.intensity = 1.0

	-- Public methods
	function self.lookingAt(x, y, z)
		self.direction.x, self.direction.y, self.direction.z = x, y, z
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

	return self
end

return DirectionalLight