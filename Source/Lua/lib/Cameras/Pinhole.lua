local Camera = require('Cameras.Camera')

Pinhole = {}

function Pinhole.new()
	local self = Camera.new()

	-- Public member variables
	self.vpdistance = 500.0
	self.zoom = 1.0

	return self
end

return Pinhole
