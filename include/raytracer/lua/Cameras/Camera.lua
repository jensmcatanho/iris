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
	
	-- Public methods
	function self.withEyeAt(x, y, z)
		self.eye.x, self.eye.y, self.eye.z = x, y, z
		return self
	end

	function self.lookingAt(x, y, z)
		self.look_at.x, self.look_at.y, self.look_at.z = x, y, z
		return self
	end
	
	return self
end

return Camera