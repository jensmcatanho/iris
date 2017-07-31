local Camera = require('Cameras.Camera')

Orthographic = {}

function Orthographic.new()
	local self = Camera.new()

	-- Public member variables
	self.name = "Orthographic"
	self.ip_distance = 500.0
	self.zoom = 1.0

	-- Public methods
	function self.withZoom(zoom)
		self.zoom = zoom
		return self
	end

	function self.withImagePlaneDistance(npd)
		self.ip_distance = npd
		return self
	end

	return self
end

return Orthographic