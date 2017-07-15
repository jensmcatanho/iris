local Object = require('Objects.Object')

Sphere = {}

function Sphere.new()
	local self = Object.new()

	-- Public member variables
	self.name = "Sphere"
	self.center = {x = 0.0, y = 0.0, z = 0.0}
	self.radius = 1.0
	
	-- Public methods
	function self.centeredAt(x, y, z)
		self.center.x, self.center.y, self.center.z = x, y, z
		return self
	end

	function self.withRadius(r)
		self.radius = r
		return self
	end

	return self
end

return Sphere
