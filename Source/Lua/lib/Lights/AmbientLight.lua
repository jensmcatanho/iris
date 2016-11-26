local Light = require('Lights.Light')

AmbientLight = {}

function AmbientLight.new()
	local self = Light.new()

	-- Public member variables
	color = {r = 1.0, g = 1.0, b = 1.0}
	intensity = 1.0

	return self
end

return AmbientLight