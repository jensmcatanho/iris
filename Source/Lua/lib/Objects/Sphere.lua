local Object = require('Objects.Object')

Sphere = {}

function Sphere.new()
	local self = Object.new()

	-- Private member variables
	self.name = "Sphere"
	
	-- Public member variables
	self.center = {x = 0.0, y = 0.0, z = 0.0}
	self.radius = 1.0
	
	-- Public methods
	function self.SetCenter(x, y, z)
		center.x, center.y, center.z = x, y, z
	end

	return self
end

return Sphere
