local Light = require('Lights.Light')

PointLight = {}

function PointLight.new()
	local self = Light.new()

	-- Public member variables
	self.name = "Point"
	self.position = {x = 0.0, y = 0.0, z = 0.0}
	self.color = {r = 1.0, g = 1.0, b = .0}
	self.intensity = 1.0

	return self
end

return PointLight