local Object = require('Objects.Object')

Plane = {}

function Plane.new()
	local self = Object.new()
	
	-- Public member variables
	self.name = "Plane"
	self.point = {x = 0.0, y = 0.0, z = 0.0}
	self.normal = {x = 0.0, y = 1.0, z = 0.0}

	-- Public methods
	function self.locatedAt(x, y, z)
		self.point.x, self.point.y, self.point.z = x, y, z
		return self
	end

	function self.lookingAt(x, y, z)
		self.normal.x, self.normal.y, self.normal.z = x, y, z
		return self
	end

	return self
end

return Plane
