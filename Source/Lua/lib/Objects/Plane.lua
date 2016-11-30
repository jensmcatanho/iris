local Object = require('Objects.Object')

Plane = {}

function Plane.new()
	local self = Object.new()
	
	-- Public member variables
	self.name = "Plane"
	self.point = {x = 0.0, y = 0.0, z = 0.0}
	self.normal = {x = 0.0, y = 1.0, z = 0.0}

	return self
end

return Plane