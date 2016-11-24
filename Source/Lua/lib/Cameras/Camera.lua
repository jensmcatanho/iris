Camera = {}

function Camera.new()
	local self = {}

	-- Public member variables
	self.eye = {x = 0.0, y = 0.0, z = 0.0}
	self.look_at = {x = 0.0, y = 0.0, z = -1.0}
	self.yaw = 0.0
	self.pitch = 0.0
	self.roll = 0.0
	self.exposure_time = 1.0

	return self
end

return Camera