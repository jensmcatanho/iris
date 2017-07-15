local Camera = require('Cameras.Camera')

Pinhole = {}

function Pinhole.new()
	local self = Camera.new()

	-- Public member variables
	self.vpdistance = 500.0
	self.zoom = 1.0

	-- Public methods
	function self.withZoom(zoom)
		self.zoom = zoom
		return self
	end

	return self
end

return Pinhole
